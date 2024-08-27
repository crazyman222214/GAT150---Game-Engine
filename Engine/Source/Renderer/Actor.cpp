#include "Actor.h"
#include "../Input/Input.h"
#include "Components/RenderComponent.h"
#include "Core/Factory.h"
#include <iostream>

FACTORY_REGISTER(Actor)

void Actor::Initialize()
{
	for (auto& component : components)
	{
		component->Initialize();
	}
}

void Actor::Update(float dt)
{
	if (lifespan != 0)
	{
		lifespan -= dt;
		if (lifespan <= 0)
		{
			destroyed = true;
		}
	}


	for (auto& component : components)
	{
		component->Update(dt);
	}


}

void Actor::Draw(Renderer& renderer)
{
	if (destroyed) return;
	
	for (auto& component : components)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		
		if (renderComponent)
		{
			renderComponent->Draw(renderer);
		}
	}
}

void Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->owner = this;
	components.push_back(std::move(component));
}

void Actor::UpdateTransformToMouse(Input& input, Vector2 previousPosition)
{
	transform.position = input.GetMousePosition();

	if (input.GetMouseButtonDown(1))
	{
		transform.scale = 4;
	}

	if (input.GetMouseButtonDown(2))
	{
		transform.position = previousPosition;
	}
	
}
Actor::Actor(const Actor& other)
{
	tag = other.tag;
	lifespan = other.lifespan;
	destroyed = other.destroyed;
	transform = other.transform;
	scene = other.scene;

	for (auto& component : other.components)
	{
		auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
		AddComponent(std::move(clone));
	}
}

void Actor::Read(const json_t& value)
{
	Object::Read(value);

	READ_DATA(value, tag);
	READ_DATA(value, lifespan);

	if (HAS_DATA(value, transform))
	{
		transform.Read(GET_DATA(value, transform));
	}

	//Read components
	if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
	{
		for (auto& componentValue : GET_DATA(value, components).GetArray())
		{
			std::string type;
			READ_DATA(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);
			if (!component)
			{
				std::cerr << "Could not create component: " << type << std::endl;
				continue;
			}

			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
	//READ_DATA(value, tag);
}

void Actor::Write(json_t& value)
{
	if (HAS_DATA(value, transform))
	{
		transform.Write(GET_DATA(value, transform));
	}
	else
	{
		std::cerr << "Doesn't have transform or you are bad :0";
	}
}