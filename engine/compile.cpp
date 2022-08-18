// Headers
#include "RedEngine/Math/MathModule.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Hash.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/SerializationFunction.hpp"
#include "RedEngine/Math/Vector.hpp"

#include "RedEngine/Filesystem/FileSystemModule.hpp"
#include "RedEngine/Filesystem/File.hpp"
#include "RedEngine/Filesystem/Path.hpp"

#include "RedEngine/Utils/UtilityModule.hpp"
#include "RedEngine/Utils/BitfieldUtils.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Utils/Random.hpp"
#include "RedEngine/Utils/StringUtils.hpp"
#include "RedEngine/Utils/Types.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include "RedEngine/Core/CoreModule.hpp"
#include "RedEngine/Core/Macros.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Core/Memory/MemoryManager.hpp"
#include "RedEngine/Core/Memory/MemoryProfiler.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Configuration/CVarUtils.hpp"
#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Configuration/UserInputHelper.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistryFunction.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/Delegate.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Core/Time/FrameCounter.hpp"
#include "RedEngine/Core/Time/Time.hpp"

#include "RedEngine/Audio/AudioModule.hpp"
#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Audio/AudioUtils.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Audio/Resource/SoundResource.hpp"
#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Audio/System/AudioSystem.hpp"

#include "RedEngine/Input/InputModule.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/Input/InputDefinitionTranslationUnit.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Input/UserInputDefinition.hpp"

#include "RedEngine/Level/LevelModule.hpp"
#include "RedEngine/Level/JsonLevelNames.hpp"
#include "RedEngine/Level/JsonLevelLoader.hpp"
#include "RedEngine/Level/JsonLevelSerializer.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Level/LevelData.hpp"
#include "RedEngine/Level/LevelLoader.hpp"
#include "RedEngine/Level/LevelSerializer.hpp"

#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"
#include "RedEngine/Physics/PhysicsModule.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/FrameBuffer.hpp"
#include "RedEngine/Rendering/GPUBuffer.hpp"
#include "RedEngine/Rendering/RenderDebugUtils.hpp"
#include "RedEngine/Rendering/Renderer.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/SpriteResource.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include "RedEngine/Resources/ResourceModule.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

// Sources
#include "Audio/AudioUtils.cpp"
#include "Audio/Component/AudioListener.cpp"
#include "Audio/Component/AudioSource.cpp"
#include "Audio/Resource/SoundResource.cpp"
#include "Audio/Resource/SoundResourceLoader.cpp"
#include "Audio/System/AudioSystem.cpp"
#include "Core/Configuration/CVar.cpp"
#include "Core/Configuration/CVarManager.cpp"
#include "Core/Configuration/CVarUtils.cpp"
#include "Core/Configuration/IniReader.cpp"
#include "Core/Configuration/UserInputHelper.cpp"
#include "Core/Debug/Component/DebugComponent.cpp"
#include "Core/Debug/DebugDraw/PhysicsDebugDraw.cpp"
#include "Core/Debug/DebugMacros.cpp"
#include "Core/Debug/Logger/Logger.cpp"
#include "Core/Debug/System/DebugSystem.cpp"
#include "Core/Engine.cpp"
#include "Core/Entity/Components/Component.cpp"
#include "Core/Entity/Components/ComponentManager.cpp"
#include "Core/Entity/Components/ComponentRegistry.cpp"
#include "Core/Entity/Components/ComponentRegistryFunction.cpp"
#include "Core/Entity/Components/Transform.cpp"
#include "Core/Entity/Entity.cpp"
#include "Core/Entity/System.cpp"
#include "Core/Entity/World.cpp"
#include "Core/Event/Component/EventsComponent.cpp"
#include "Core/Event/Delegate.cpp"
#include "Core/Event/System/EventSystem.cpp"
#include "Core/Memory/MemoryManager.cpp"
#include "Core/Memory/MemoryProfiler.cpp"
#include "Core/SerializationFunction.cpp"
#include "Core/Time/FrameCounter.cpp"
#include "Core/Time/Time.cpp"
#include "Filesystem/File.cpp"
#include "Filesystem/Path.cpp"
#include "Input/Component/UserInput.cpp"
#include "Input/InputDefinition.cpp"
#include "Input/System/UserInputSystem.cpp"
#include "Level/JsonLevelLoader.cpp"
#include "Level/JsonLevelSerializer.cpp"
#include "Level/Level.cpp"
#include "Level/LevelData.cpp"
#include "Level/LevelLoader.cpp"
#include "Level/LevelSerializer.cpp"
#include "Math/Hash.cpp"
#include "Math/Math.cpp"
#include "Math/SerializationFunction.cpp"
#include "Math/Vector.cpp"
#include "Physics/Components/Collider.cpp"
#include "Physics/Components/PhysicBody.cpp"
#include "Physics/ContactInfo.cpp"
#include "Physics/PhysicsWorld.cpp"
#include "Physics/System/PhysicSystem.cpp"
#include "Rendering/Component/CameraComponent.cpp"
#include "Rendering/Component/Renderable.cpp"
#include "Rendering/Component/Sprite.cpp"
#include "Rendering/Component/WindowComponent.cpp"
#include "Rendering/FrameBuffer.cpp"
#include "Rendering/GPUBuffer.cpp"
#include "Rendering/Renderer.cpp"
#include "Rendering/Resource/Geometry.cpp"
#include "Rendering/Resource/GeometryResourceLoader.cpp"
#include "Rendering/Resource/Material.cpp"
#include "Rendering/Resource/MaterialResourceLoader.cpp"
#include "Rendering/Resource/ShaderProgram.cpp"
#include "Rendering/Resource/ShaderProgramResourceLoader.cpp"
#include "Rendering/Resource/SpriteResource.cpp"
#include "Rendering/Resource/SpriteResourceLoader.cpp"
#include "Rendering/Resource/Texture2D.cpp"
#include "Rendering/Resource/TextureResourceLoader.cpp"
#include "Rendering/System/RenderingSystem.cpp"
#include "Resources/Resource.cpp"
#include "Resources/ResourceHolderComponent.cpp"
#include "Resources/ResourceLoader.cpp"
#include "Utils/FileUtils.cpp"
#include "Utils/Random.cpp"
#include "Utils/StringUtils.cpp"
#include "Utils/Types.cpp"
#include "Utils/TypesInfo.cpp"