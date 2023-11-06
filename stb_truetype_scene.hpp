#pragma once

#include "scene.hpp"
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <stb_truetype.h>

#include "draw_text.hpp"

class Stb_TruetypeScene : public Scene {
public:
  virtual bool Init(const Context &context);
  virtual void Tick(const Context &context);
  virtual void Cleanup(const Context &context);

private:
  std::string text = "Test";
  static constexpr char fontFile[] = "Sarabun-Regular.ttf";

  int fontSize = 64;
  SDL_Color color = {0, 0, 0, 255};

  TextBuffer buffer;

  stbtt_fontinfo fontInfo;
  std::vector<unsigned char> fontData;
};