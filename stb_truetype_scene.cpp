#include "stb_truetype_scene.hpp"

#include <algorithm>
#include <fstream>
#include <streambuf>
#include <vector>

#include <imgui.h>
#include <utf8.h>

#include "menu_scene.hpp"
#include "texture.hpp"

bool Stb_TruetypeScene::Init(const Context &context) {
  std::basic_ifstream<char> file(fontFile, std::ios::binary);
  fontData = std::vector<char>{std::istreambuf_iterator<char>(file),
                               std::istreambuf_iterator<char>()};

  file.close();

  if (!stbtt_InitFont(&fontInfo,
                      reinterpret_cast<unsigned char *>(fontData.data()), 0)) {
    return false;
  }

  std::fill(buffer.begin(), buffer.end(), 0);
  std::copy(std::begin(text), std::end(text), std::begin(buffer));

  return true;
}

void Stb_TruetypeScene::Tick(const Context &context) {

  ImGui::Begin("Menu");
  ImGui::InputText("text", buffer.data(), buffer.size());

  ImGui::SliderInt("font size", &fontSize, 0, 128);

  float c[4]{color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0};

  ImGui::ColorPicker4("color", c, ImGuiColorEditFlags_InputRGB);
  color.r = c[0] * 255;
  color.g = c[1] * 255;
  color.b = c[2] * 255;

  bool quit = ImGui::Button("Back");

  ImGui::End();

  if (quit) {
    ChangeScene<MenuScene>(context);

    return;
  }

  float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontSize);

  DrawText(buffer, color, 300, 300, fontInfo, scale, context.renderer);
}

void Stb_TruetypeScene::Cleanup(const Context &context) { fontData.clear(); }