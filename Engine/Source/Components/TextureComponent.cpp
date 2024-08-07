#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Renderer/Actor.h"
#include "Resources/ResourceManager.h"

void TextureComponent::Initialize()
{
	if (!textureName.empty())
	{
		//texture = ResourceManager::Instance().Get<Texture>(textureName);
	}
}

void TextureComponent::Update(float dt)
{
	// This may be used if a texture has an animation
}

void TextureComponent::Draw(Renderer& renderer)
{
	Transform transform = owner->GetTransform();
	renderer.DrawTexture(texture.get(), transform.position.x, transform.position.y, transform.rotation);
}
