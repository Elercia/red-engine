#include "PerfLevel.hpp"

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
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
class CameraManager : public System
{
public:
    CameraManager(red::World* world, Entity* camera) : System(world), m_camera(camera)
    {
    }
    ~CameraManager() override = default;

    void Update() override
    {
        auto* events = m_world->GetWorldComponent<UserInputComponent>();

        Vector2 speed = Vector2(20.f, 20.f) * Time::DeltaTime();
        Vector2 direction;
        if (events->GetKey("Up"))
        {
            direction.y = 1.f;
        }
        else if (events->GetKey("Down"))
        {
            direction.y = -1.f;
        }

        if (events->GetKey("Left"))
        {
            direction.x = -1.f;
        }
        else if (events->GetKey("Right"))
        {
            direction.x = 1.f;
        }

        auto* transform = m_camera->GetComponent<Transform>();

        transform->SetLocalPosition(transform->GetLocalPosition() + (direction * speed));
    }

    Entity* m_camera;
};

class EntityManager : public System
{
public:
    EntityManager(red::World* world) : System(world)
    {
        m_debugId = 0;
    }
    ~EntityManager() override = default;

    void Init() override
    {
        auto* debug = m_world->GetWorldComponent<DebugComponent>();
        if (debug != nullptr)
        {
            m_debugId = debug->AddDebugDrawer("PerfLevel", &EntityManager::DebugMenu);
        }
    }

    void Finalise() override
    {
        auto* debug = m_world->GetWorldComponent<DebugComponent>();
        if (debug != nullptr)
        {
            debug->RemoveDebugDrawer(m_debugId);
        }
    }

    static void DebugMenu(DebugComponent* /*comp*/)
    {
    }

    int m_debugId;
};

const float s_worldSizeMin = 0.f;
const float s_worldSizeMax = 5000.f;

void PerfLevel::Init()
{
    Color colors[32];
    for (auto& color : colors)
    {
        color = Color(RandomFloatRange(0.f, 1.f), RandomFloatRange(0.f, 1.f), RandomFloatRange(0.f, 1.f));
    }

    m_world->GetPhysicsWorld()->SetGravity({0.f, 9.f});

    // setup walls on the arena
    auto* wallEntity = CreateEntity("Walls");

    red::PhysicBodyCreationDesc wallBodyDesc = {red::PhysicsBodyType::STATIC_BODY};
    auto wallsBody = wallEntity->AddComponent<red::PhysicBody>(wallBodyDesc);

    red::EdgeColliderDesc wallColliderDesc;
    wallColliderDesc.isTrigger = false;
    wallColliderDesc.restitution = 1.f;

    wallColliderDesc.start = {s_worldSizeMin, s_worldSizeMin};
    wallColliderDesc.end = {s_worldSizeMax, s_worldSizeMin};
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {s_worldSizeMax, s_worldSizeMin};
    wallColliderDesc.end = {s_worldSizeMax, s_worldSizeMax};
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {s_worldSizeMax, s_worldSizeMax};
    wallColliderDesc.end = {s_worldSizeMin, s_worldSizeMax};
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {s_worldSizeMin, s_worldSizeMax};
    wallColliderDesc.end = {s_worldSizeMin, s_worldSizeMin};
    wallsBody->AddEdgeCollider(wallColliderDesc);

    float boundMin = s_worldSizeMin + 60;
    float boundMax = s_worldSizeMax - 60;

    for (int i = 0; i < 5000; i++)
    {
        const Vector2 position = {RandomFloatRange(boundMin, boundMax), RandomFloatRange(boundMin, boundMax)};

        std::string name = "Ball";
        AddEntity(name, position, (RenderLayerIndex) RandomRange(0, 31), colors);
    }

    auto* window = m_world->GetWorldComponent<red::WindowComponent>();

    auto* manager = CreateEntity("Camera");
    manager->AddComponent<red::CameraComponent>(window, red::Vector4(0.f, 0.f, 1.f, 1.f),
                                                red::Vector2{s_worldSizeMax, s_worldSizeMax});
    manager->GetComponent<Transform>()->SetLocalPosition({0.f, 0.f});

    m_world->AddSystem<CameraManager>(manager);
    m_world->AddSystem<EntityManager>();
}

void PerfLevel::Finalize()
{
}

void PerfLevel::AddEntity(const std::string& name, const red::Vector2& position, red::RenderLayerIndex layerIndex,
                          red::Color* colors)
{
    const float scale = RandomFloatRange(1.f, 1.f);
    const Vector2 axisscale = {scale, scale};
    const float size = 30.f * scale;

    PhysicBodyCreationDesc bodyDesc = {PhysicsBodyType::DYNAMIC_BODY};
    bodyDesc.linearDamping = 0.f;
    bodyDesc.angularDamping = 0.f;

    CircleColliderDesc colliderDesc;
    colliderDesc.isTrigger = false;
    colliderDesc.center = {size / 2.f, size / 2.f};
    colliderDesc.radius = size / 2.f;
    colliderDesc.restitution = 0.9f;

    auto vec4Color = colors[layerIndex % 32].AsVector4();

    BindingValue value;
    value.type = BindingType::Vector4;
    memcpy(value.floats, &vec4Color.x, sizeof(value.floats));

    auto* ball = CreateEntity(name);
    auto* s = ball->AddComponent<Sprite>(Path::Resource("ball"));
    s->SetRenderLayerIndex(layerIndex);
    s->GetMaterial().overriddenBindings.bindings[BindingIndex::Color] = value;

    ball->GetComponent<Transform>()->SetLocalPosition(position);
    ball->GetComponent<Transform>()->SetScale(axisscale);
    auto ballBody = ball->AddComponent<PhysicBody>(bodyDesc);
    ballBody->AddCircleCollider(colliderDesc);
}
}  // namespace perf
