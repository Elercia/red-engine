hunter_add_package(Catch)
find_package(Catch2 REQUIRED)

hunter_add_package(SDL2)
find_package(SDL2 CONFIG REQUIRED)

hunter_add_package(SDL_image)
find_package(SDL_image CONFIG REQUIRED)

hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)