#include <RedEngine/Application.hpp>

int main(int argc, char* argv[])
{
    red::Application app;

    app.InitFromCommandLine(argc, argv);

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
