#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"

#include <SDL2/SDL_events.h>
#include <catch2/catch.hpp>

using namespace red;

TEST_CASE("Raw input handling", "[Input]")
{
    World world;

    auto* e = world.CreateSingletonEntity();
    auto* eventsComonent = e->AddComponent<EventsComponent>();
    auto* eventSystem = world.AddSystem<EventSystem>();

    eventsComonent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

    eventSystem->PreUpdate();

    REQUIRE(eventsComonent->GetKey(red::KeyCodes::KEY_W));
    REQUIRE(eventsComonent->GetKeyDown(red::KeyCodes::KEY_W));
    REQUIRE(!eventsComonent->GetKeyUp(red::KeyCodes::KEY_W));

    eventsComonent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);

    eventSystem->PreUpdate();

    REQUIRE(!eventsComonent->GetKey(red::KeyCodes::KEY_W));
    REQUIRE(!eventsComonent->GetKeyDown(red::KeyCodes::KEY_W));
    REQUIRE(eventsComonent->GetKeyUp(red::KeyCodes::KEY_W));
}

TEST_CASE("User input handling", "[Input]")
{
    red::World world;
    auto* singletonEntity = world.CreateSingletonEntity();

    auto* comp = singletonEntity->AddComponent<red::UserInputComponent>();
    world.AddSystem<red::UserInputSystem>();

    auto* eventsComponent = singletonEntity->AddComponent<EventsComponent>();
    world.AddSystem<red::EventSystem>();
   
    world.Init();

    SECTION("Single input without modifiers")
    {
        // Define the action key we will be using
        red::ActionKey key = "Action1";
        red::KeyMapping m;
        m.mapping = red::KeyCodes::KEY_W;
        red::UserActionMapping mapping{{key, m}};
        comp->SetActionMapping(mapping);

        // Send event for the same key
        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

        // Then update
        world.Update();

        // Verify the output
        REQUIRE(comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));
        REQUIRE(comp->GetKey(key));

        // Update a second time
        world.Update();

        // Should not be down anymore
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));
        REQUIRE(comp->GetKey(key));

        // Send event for key UP
        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);

        // Update one last time
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
        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_DOWN);

        // Then update
        world.Update();

        // Verify the output (should not be down)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_LCTRL, red::KeyEventType::KEY_DOWN);

        world.Update();

        // Verify the output (should not be down)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_LALT, red::KeyEventType::KEY_DOWN);

        world.Update();

        // Verify the output (now this is good)
        REQUIRE(comp->GetKey(key));
        REQUIRE(comp->GetKeyDown(key));
        REQUIRE(!comp->GetKeyUp(key));

        eventsComponent->SendKeyEvent(red::KeyCodes::KEY_W, red::KeyEventType::KEY_UP);

        world.Update();

        // Verify the output (should be UP)
        REQUIRE(!comp->GetKey(key));
        REQUIRE(!comp->GetKeyDown(key));
        REQUIRE(comp->GetKeyUp(key));
    }
}