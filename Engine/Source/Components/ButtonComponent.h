#pragma once
#include "RenderComponent.h"
#include <functional>
class ButtonComponent : public RenderComponent
{
public:
	CLASS_DECLARATION(ButtonComponent)
	CLASS_PROTOTYPE(ButtonComponent)
	void OnClick(Renderer& renderer, std::function<bool()> clickMethod);

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
public:
	std::string text;

};