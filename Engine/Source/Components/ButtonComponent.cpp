#include "ButtonComponent.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
void ButtonComponent::OnClick(Renderer& renderer, std::function<bool()> clickMethod)
{
	//If I click within the bounds of the button, (x -> width, y -> height)
	//it should call the clickMethod
	owner->scene->engine->GetInput().GetMousePosition();
	clickMethod;
}


void ButtonComponent::Initialize()
{
}

void ButtonComponent::Update(float dt)
{
}

void ButtonComponent::Draw(Renderer& renderer)
{
	//renderer.DrawTexture(m_text->GetTexture(), owner->transform);
}

void ButtonComponent::Read(const json_t& value)
{

}

void ButtonComponent::Write(json_t& value)
{
}