#include "PerfLevel.hpp"

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Utils/Random.hpp"

using namespace red;

namespace perf
{

void PerfLevel::Init()
{
    const Color colors[] = {ColorConstant::BLACK, ColorConstant::BLUE, ColorConstant::GREEN, ColorConstant::RED,
                            ColorConstant::WHITE};
    constexpr int nbColors = sizeof(colors) / sizeof(Color);

    for (int i = 0; i < 200; i++)
    {
        const Vector2 position = {RandomFloatRange(0.f, 1000.f), RandomFloatRange(0.f, 1000.f)};
        const Vector2 scale = {RandomFloatRange(1.f, 1.5f), RandomFloatRange(1.f, 1.5f)};
        const float size = 30.f;
        const int layerIndex = i % 32;

        PhysicBodyCreationDesc bodyDesc = {PhysicsBodyType::DYNAMIC_BODY};
        CircleColliderDesc colliderDesc;
        colliderDesc.isTrigger = false;
        colliderDesc.center = {size / 2.f, size / 2.f};
        colliderDesc.radius = size / 2.f;
        colliderDesc.restitution = 1.f;

        auto* ball = CreateEntity("Ball_" + i);
        auto* s = ball->AddComponent<Sprite>(Path::Resource("ball"));
        s->SetRenderLayerIndex(layerIndex);

        BindingValue value;
        value.type = BindingType::Vector4;
        auto vec4Color = colors[i % nbColors].AsVector4();
        memcpy(value.floats, &vec4Color.x, sizeof(value.floats));

        s->GetMaterial().overiddenBindings.bindings[BindingIndex::Color] = value;

        ball->GetComponent<Transform>()->SetPosition(position);
        ball->GetComponent<Transform>()->SetScale(scale);
        ball->AddComponent<PhysicBody>(bodyDesc);
        ball->AddComponent<ColliderList>()->AddCircleCollider(colliderDesc);
    }

    auto* window = m_world->GetWorldComponent<red::WindowComponent>();

    auto* manager = CreateEntity("Manager");
    manager->AddComponent<red::CameraComponent>(window, red::Vector4(0.f, 0.f, 1.f, 1.f), red::Vector2i{800, 600});
}

void PerfLevel::Finalize()
{
}
}  // namespace perf
