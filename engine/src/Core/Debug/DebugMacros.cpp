#include "RedEngine/Core/CoreModule.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"

#include <SDL2/SDL_messagebox.h>
#include <filesystem>
#include <fmt/format.h>
#include <iostream>

namespace red
{
ErrorReturn HandleAssert(bool expr, std::string_view message, const char* filename, int line)
{
    if (expr)
        return ErrorReturn::CONTINUE;

    /* .flags, .buttonid, .text */
    const SDL_MessageBoxButtonData buttons[] = {
        {0, 0, "Abort"},
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Break"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Continue"},
    };

    const SDL_MessageBoxColorScheme colorScheme = {{/* .colors (.r, .g, .b) */
                                                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                                                    {255, 0, 0},
                                                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                                                    {0, 255, 0},
                                                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                                                    {255, 255, 0},
                                                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                                                    {0, 0, 255},
                                                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                                                    {255, 0, 255}}};
    std::string fileFormat = std::string(filename);
    fileFormat = fileFormat.substr(fileFormat.find_last_of(std::filesystem::path::preferred_separator) + 1);

    std::string formattedMessage =
        fmt::format(FMT_STRING("[ERROR]\n[FILENAME] {}\n[LINE] {}\n[MESSAGE] {}"), fileFormat, line, message);

    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_ERROR,          /* .flags */
        NULL,                          /* .window */
        "Red-engine assert triggered", /* .title */
        formattedMessage.c_str(),      /* .message */
        SDL_arraysize(buttons),        /* .numbuttons */
        buttons,                       /* .buttons */
        &colorScheme                   /* .colorScheme */
    };

    int returnButtonID;
    if (SDL_ShowMessageBox(&messageboxdata, &returnButtonID) < 0)
    {
        std::cerr << "Error showing message box" << std::endl;
        return ErrorReturn::BREAK;
    }

    if (returnButtonID == -1)
    {
        return ErrorReturn::BREAK;
    }

    switch (returnButtonID)
    {
        case 0:
            abort();
        case 1:
            return ErrorReturn::BREAK;
        case 2:
            return ErrorReturn::CONTINUE;
        default:
            return ErrorReturn::CONTINUE;
    };
}
}  // namespace red