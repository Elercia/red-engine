#include <RedEngine/Application.hpp>
#include <RedEngine/Core/Configuration/Configuration.hpp>

int main(int argc, char* argv[])
{
    red::Configuration::GetInstance().LoadConfigFile("Resources/config.ini");
    red::Configuration::GetInstance().ParseCommandLine(argc, argv);

    red::Application app;

    app.CreateWorld();

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
