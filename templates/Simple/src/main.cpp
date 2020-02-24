#include <RedEngine/Application.hpp>
#include <RedEngine/Platform.hpp>
#include <RedEngine/components/RigidBody.hpp>
#include <RedEngine/ecs/Entity.hpp>
#include <RedEngine/ecs/World.hpp>

#include "CustomComponent.hpp"

#ifdef WIN32
#pragma warning(disable : 28251)

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    red::Application app;
    char* cmdLine = GetCommandLineA();

    app.InitFromCommandLine(cmdLine);
#else
int main(int argc, char* argv[])
{
    red::Application app();

    app.InitFromCommandLine(argc, argv);
#endif // WIN32

    std::wstring title = L"Template Simple";

    auto world = app.CreateWorld();
    auto window = app.InitWindow(title);

    auto entity = world->CreateEntity();
    entity->AddComponent<CustomComponent>();
    entity->AddComponent<red::RigidBody>();

    app.Run();

    return EXIT_SUCCESS;
}
