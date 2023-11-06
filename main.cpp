#include <SDL2/SDL.h>
#include <imgui.h>

#include "context.hpp"
#include "menu_scene.hpp"
#include "scene.hpp"
#include "texture.hpp"

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window =
      SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("Sarabun-Regular.ttf", 20.0f, NULL,
                               io.Fonts->GetGlyphRangesThai());

  ImGui_ImplSDLRenderer2_Init(renderer);
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);

  Context c{.renderer = renderer};

  InitGlyphTexture();
  while (true) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        break;
    }

    SDL_SetRenderDrawColor(renderer, 0x50, 0x82, 0xaa, 0xff);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    Scene::TickCurrent(c);

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }

  CleanUpGlyphTexture();
  
  ImGui_ImplSDL2_Shutdown();
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}