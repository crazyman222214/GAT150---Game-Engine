#pragma once
#include "../Resources/Resource.h"
#include "../Math/Vector2.h"
#include "Renderer.h"

class Texture : public Resource
{
public:
	Texture() = default;
	~Texture();

	bool Load(const std::string& filename, class Renderer& renderer);

	Vector2 GetSize();

	friend class Renderer;

	bool Create(std::string filename, ...) override;
private:
	struct SDL_Texture* m_texture{ nullptr };

};