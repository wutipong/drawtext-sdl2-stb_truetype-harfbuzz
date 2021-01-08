#include "menu_scene.hpp"

#include <imgui.h>

#include "compare_scene.hpp"
#include "stb_truetype_harfbuzz_scene.hpp"
#include "stb_truetype_scene.hpp"

bool MenuScene::Init(const Context &context) { return true; }

void MenuScene::Tick(const Context &context) {
  ImGui::Begin("Menu");
  if (ImGui::Button("stb_truetype")) {
    ChangeScene<Stb_TruetypeScene>(context);
  }

  if (ImGui::Button("stb_truetype + Harfbuzz")) {
    ChangeScene<STB_TrueTypeHarfbuzzScene>(context);
  }

  if (ImGui::Button("Compare the two")) {
    ChangeScene<CompareScene>(context);
  }

  ImGui::End();
}

void MenuScene::Cleanup(const Context &context) {}