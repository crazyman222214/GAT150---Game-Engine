#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Color.h"
#include "../Resources/Resource.h"
#include <string>

class Text
{
public:
	Text() = default;
	Text(res_t<Font> font) : m_font{ font } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

	void SetFont(res_t<Font> font) { m_font = font; }
	friend class Font;

private:
	res_t<Font> m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};