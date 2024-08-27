#pragma once
#include "RenderComponent.h"
#include "Renderer/Text.h"
class TextComponent : public RenderComponent
{
public:
	TextComponent() = default;
	TextComponent(const TextComponent& other);

	CLASS_DECLARATION(TextComponent)
	CLASS_PROTOTYPE(TextComponent)
	// Inherited via RenderComponent
	void Initialize() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;
	void SetText(const std::string& text);

public:
	std::string text;
	std::string fontName;
	int fontSize = 8;
	Color color{ 1,1,1,1 };

private:
	std::unique_ptr<Text> m_text;
	bool changed = true;
};