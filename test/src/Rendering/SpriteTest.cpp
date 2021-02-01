#include "RedEngine/Core/Application.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Sprite test", "[RENDERING]")
{
    using namespace red;

    World world;
    auto* e = world.CreateEntity();
    auto* spriteComponent = e->AddComponent<Sprite>("sprite_test/sprite_test");

    REQUIRE(spriteComponent->GetAnimations().size() == 2);

    SECTION("Frames change properly according to framerate")
    {
        red::Time::SetDeltaTime(0.033F);
        auto oldIt = spriteComponent->GetCurrentAnimationInfo().currentAnimationFrame;

        // With a duration of 1 second, the next animation should start after this one
        for (int i = 0; i < 31; i++)
        {
            REQUIRE(oldIt == spriteComponent->GetCurrentAnimationInfo().currentAnimationFrame);
            spriteComponent->NextFrame();
        }

        REQUIRE(oldIt != spriteComponent->GetCurrentAnimationInfo().currentAnimationFrame);
    }

    SECTION("Animation change properly")
    {
        spriteComponent->StartAnimation("second");

        REQUIRE(spriteComponent->GetCurrentAnimationInfo().currentAnimation->name == "second");

        spriteComponent->StartAnimation("first");

        REQUIRE(spriteComponent->GetCurrentAnimationInfo().currentAnimation->name == "first");
    }
}