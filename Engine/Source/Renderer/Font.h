#pragma once
#include "../Resources/Resource.h"
#include <string>
#include <SDL_ttf.h>
class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Create(std::string filename, ...) override;
	bool Load(const std::string& name, int fontSize);

	_TTF_Font* GetTTFFont() { return m_ttfFont; }

	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };

};