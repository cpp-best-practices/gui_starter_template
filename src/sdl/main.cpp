#include <SDL2/SDL.h>
#include <cstdio>

static constexpr auto SCREEN_WIDTH = 640;
static constexpr auto SCREEN_HEIGHT = 480;


#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <spdlog/spdlog.h>

static void check_audio_driver(const char *name)
{
  spdlog::info("checking for audio driver {} ...", name);
  int count = SDL_GetNumAudioDrivers();
  for (int i = 0; i < count; ++i) {
    if (0 == strcmp(name, SDL_GetAudioDriver(i))) {
      spdlog::info("checking for audio driver {} ... found", name);
      return;
    }
  }
  spdlog::info("checking for audio driver {} ... Not Found :(", name);
}

static void check_video_driver(const char *name)
{
  spdlog::info("checking for video driver {} ...", name);
  int count = SDL_GetNumVideoDrivers();
  for (int i = 0; i < count; ++i) {
    if (0 == strcmp(name, SDL_GetVideoDriver(i))) {
      spdlog::info("checking for video driver {} ... found", name);
      return;
    }
  }
  spdlog::info("checking for video driver {} ... Not Found :(", name);
}


// required to give full function signature for linking on Windows
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
  SDL_version v;
  SDL_GetVersion(&v);
  spdlog::info("SDL version {}.{}.{}", v.major, v.minor, v.patch);
  check_video_driver("x11");
  check_audio_driver("alsa");
  check_audio_driver("pulseaudio");
  check_audio_driver("esd");
  check_audio_driver("arts");
  check_video_driver("directfb");
  check_audio_driver("directsound");


  SDL_Window *window = nullptr;
  SDL_Surface *screenSurface = nullptr;
  //  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
  //    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
  //    return 1;
  //  }
  window = SDL_CreateWindow("hello_sdl2",
    SDL_WINDOWPOS_UNDEFINED,// NOLINT
    SDL_WINDOWPOS_UNDEFINED,// NOLINT
    SCREEN_WIDTH,// NOLINT
    SCREEN_HEIGHT,// NOLINT
    SDL_WINDOW_SHOWN);// NOLINT

  if (window == nullptr) {
    spdlog::error("could not create window: {}", SDL_GetError());
    return EXIT_FAILURE;
  }
  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));// NOLINT
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);// NOLINT
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
