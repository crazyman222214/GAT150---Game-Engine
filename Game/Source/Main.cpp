#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Actor.h"
#include "Renderer/Texture.h"
#include "Core/EAssert.h"
#include "Renderer/Text.h"
#include "Core/EFile.h"
#include "Core/Json.h"
#include "Core/Net.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <SDL_image.h>



int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	Factory::Instance().Register<PlayerComponent>(PlayerComponent::GetTypeName());
	Factory::Instance().Register<TextComponent>(TextComponent::GetTypeName());
	Factory::Instance().Register<ButtonComponent>(ButtonComponent::GetTypeName());

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();
	std::cout << "Client or server?";
	char c = 0;
	if (std::cin >> c)
	{
		if (c == 'c')
		{
			engine->GetNetwork().ClientFunction();
		}
		
	}

	//__LINE__ Prints the line
	//__FILE__ Prints the current file
	//__FUNCTION__ Prints the function

	std::string s;
	File::ReadFile("Scene/scene.json", s);
	//std::cout << s;
	
	rapidjson::Document document;
	Json::Load("Scene/scene.json", document);

	//engine->GetNetwork().ClientFunction();
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();



	//Adding another scope that way when we get out of the scope,
	//The font gets correctly deconstructed
	{
		/*res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Murio.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("Blockletter.otf", 20);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Game Over Loser", { 1, 0, 0, 1 });

		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->transform = { {70, 30} };
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));*/


		auto* actor = scene->GetActor<Actor>("text");
		while (!engine->IsQuit())
		{
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			if (actor)
			{
				actor->transform.rotation += 10;
			}

			ButtonComponent* btnComp = new ButtonComponent();
			btnComp->OnClick(engine->GetRenderer(), []() -> bool {return true; });

			engine->GetRenderer().SetColor(255, 255, 255, 0);
			engine->GetRenderer().BeginFrame();

			if (c == 's')
			{
				engine->GetNetwork().HostCheckForConnection();
			}

			scene->Draw(engine->GetRenderer());
			engine->GetPS().Update(engine->GetTime().GetDeltaTime());
			engine->GetRenderer().EndFrame();

		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}