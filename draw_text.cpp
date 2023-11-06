#include "draw_text.hpp"

#include "texture.hpp"
#include <utf8.h>

void DrawText(const std::array<char, bufferSize> &text, const SDL_Color &color,
              const int &x_start, const int &baseline,
              const stbtt_fontinfo &info, const float &scale,
              SDL_Renderer *renderer) {
  int x = x_start;

  std::vector<wchar_t> charactors;
  auto end_it = utf8::find_invalid(text.begin(), text.end());
  utf8::utf8to16(text.begin(), end_it, std::back_inserter(charactors));

  for (auto c : charactors) {
    auto [texture, advance, dest] =
        CreateTextureFromCodePoint(renderer, info, c, scale);

    if (texture != nullptr) {
      dest.x += x;
      dest.y += baseline;

      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
      SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
      SDL_SetTextureAlphaMod(texture, color.a);

      SDL_RenderCopy(renderer, texture, NULL, &dest);
      SDL_DestroyTexture(texture);
    }

    x += advance;
  }
}

void DrawTextHarfbuzz(const std::array<char, bufferSize> &text,
                      const SDL_Color &color, const int &x_start,
                      const int &baseline, const stbtt_fontinfo &info,
                      const float &scale, hb_font_t *hb_font,
                      SDL_Renderer *renderer) {
  hb_buffer_t *buffer = hb_buffer_create();

  hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
  hb_buffer_set_script(buffer, HB_SCRIPT_THAI);

  std::vector<uint16_t> charactors;
  auto end_it = utf8::find_invalid(text.begin(), text.end());
  utf8::utf8to16(text.begin(), end_it, std::back_inserter(charactors));

  hb_buffer_add_utf16(buffer, charactors.data(), charactors.size(), 0,
                      charactors.size());

  hb_shape(hb_font, buffer, NULL, 0);

  unsigned int glyph_count = hb_buffer_get_length(buffer);
  hb_glyph_info_t *glyph_infos = hb_buffer_get_glyph_infos(buffer, NULL);
  hb_glyph_position_t *glyph_positions =
      hb_buffer_get_glyph_positions(buffer, NULL);

  int x = x_start;

  for (unsigned int i = 0; i < glyph_count; i++) {
    auto [texture, advance, dest] =
        CreateTextureFromIndex(renderer, info, glyph_infos[i].codepoint, scale);

    if (texture != nullptr) {
      dest.x += x + (glyph_positions[i].x_offset >> 6);
      dest.y += baseline - (glyph_positions[i].y_offset >> 6);

      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
      SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
      SDL_SetTextureAlphaMod(texture, color.a);

      SDL_RenderCopy(renderer, texture, NULL, &dest);
      SDL_DestroyTexture(texture);
    }

    x += advance;
  }

  hb_buffer_destroy(buffer);
}