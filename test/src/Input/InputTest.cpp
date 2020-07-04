#include <RedEngine/Core/Event/EventSystem.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Input/System/UserInputSystem.hpp>
#include <RedEngine/Input/Component/UserInput.hpp>

#include <catch2/catch.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_gamecontroller.h>

TEST_CASE("Raw input handling", "[Input]")
{
    auto* eventSystem = red::GetRedSubEngine<red::EventSystem>();

    eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

    eventSystem->Update();

    REQUIRE(eventSystem->GetKey(red::KeyCodes::KEY_W));
    REQUIRE(eventSystem->GetKeyDown(red::KeyCodes::KEY_W));
    REQUIRE(!eventSystem->GetKeyUp(red::KeyCodes::KEY_W));

    eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);

    eventSystem->Update();

    REQUIRE(!eventSystem->GetKey(red::KeyCodes::KEY_W));
    REQUIRE(!eventSystem->GetKeyDown(red::KeyCodes::KEY_W));
    REQUIRE(eventSystem->GetKeyUp(red::KeyCodes::KEY_W));
}

TEST_CASE("User input handling", "[Input]")
{
    auto* eventSystem = red::GetRedSubEngine<red::EventSystem>();
    red::World world;
    auto* singletonEntity = world.CreateSingletonEntity();
    auto* comp = singletonEntity->AddComponent<red::UserInputComponent>();
    auto* sys = world.AddSystem<red::UserInputSystem>();

    sys->Init();

    SECTION("Single input without modifiers")
    {
        // Define the action key we will be using
        red::ActionKey key = "Action1";
        red::KeyMapping m;
        m.mapping = red::KeyCodes::KEY_W;
        red::UserActionMapping mapping{{key, m}};
        comp->SetActionMapping(mapping);

        // Send event for the same key
        eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

        // Then update
        eventSystem->Update();
        world.Update();

        // Verify the output
        REQUIRE(comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));
        REQUIRE(comp->GetKey(key));

        // Update a second time
        eventSystem->Update();
        world.Update();

        // Should not be down anymore
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));
        REQUIRE(comp->GetKey(key));

        // Send event for key UP
        eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);

        // Update one last time
        eventSystem->Update();
        world.Update();

        // The key should not be pressed and should be UP
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(comp->GetKeyUp(key));
        REQUIRE(!comp->GetKey(key));
    }

    SECTION("Key with modifiers")
    {
        // Define the action key we will be using
        red::ActionKey key = "Action1";

        // Set the key W and add Left alt and left ctrl modifiers
        red::KeyMapping m;
        m.mapping = red::KeyCodes::KEY_W;
        m.modifiers.set(red::ModifierKey::LCTRL).set(red::ModifierKey::LALT);

        red::UserActionMapping actionMapping{{key, m}};
        comp->SetActionMapping(actionMapping);

        // Send event for the same key (without modifiers)
        eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

        // Then update
        eventSystem->Update();
        world.Update();

        // Verify the output (should not be down)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventSystem->SendKeyEvent(red::KeyCodes::KEY_LCTRL, red::KeyEventType::KEY_DOWN);
        eventSystem->Update();
        world.Update();

        // Verify the output (should not be down)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventSystem->SendKeyEvent(red::KeyCodes::KEY_LALT, red::KeyEventType::KEY_DOWN);
        eventSystem->Update();
        world.Update();

        // Verify the output (now this is good)
        REQUIRE(comp->GetKey(key));
        REQUIRE(comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventSystem->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);
        eventSystem->Update();
        world.Update();

        // Verify the output (should be UP)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(comp->GetKeyUp(key));
    }
}