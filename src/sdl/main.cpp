#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>



static void check_audio_driver(const char *name)
{
  std::cout << "checking for audio driver " << name << " ... ";
  int count = SDL_GetNumAudioDrivers();
  for (int i = 0; i < count; ++i) {
    if (0 == strcmp(name, SDL_GetAudioDriver(i))) {
      std::cout << "found\n";
      return;
    }
  }
  std::cout << "Not Found :(\n";
}

static void check_video_driver(const char *name)
{
  std::cout << "checking for video driver " << name << " ... ";
  int count = SDL_GetNumVideoDrivers();
  for (int i = 0; i < count; ++i) {
    if (0 == strcmp(name, SDL_GetVideoDriver(i))) {
      std::cout << "found\n";
      return;
    }
  }
  std::cout << "Not Found :(\n";
}


int main(int argc, char *argv[]) {
  SDL_version v;
  SDL_GetVersion(&v);
  std::cout << "SDL version " << int(v.major) << "." << int(v.minor) << "." << int(v.patch) << std::endl;
  check_video_driver("x11");
  check_audio_driver("alsa");
  check_audio_driver("pulseaudio");
  check_audio_driver("esd");
  check_audio_driver("arts");
  check_video_driver("directfb");
  check_audio_driver("directsound");


  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
//  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
//    return 1;
//  }
  window = SDL_CreateWindow(
    "hello_sdl2",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
