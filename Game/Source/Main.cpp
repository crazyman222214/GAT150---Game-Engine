#include "Engine.h"
#include "Framework/Scene.h"
#include "MyGame.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <SDL_image.h>



int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<Box2DPhysicsComponent>(Box2DPhysicsComponent::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	Factory::Instance().Register<PlayerComponent>(PlayerComponent::GetTypeName());
	Factory::Instance().Register<TextComponent>(TextComponent::GetTypeName());
	Factory::Instance().Register<ButtonComponent>(ButtonComponent::GetTypeName());
	Factory::Instance().Register<AudioComponent>(AudioComponent::GetTypeName());
	Factory::Instance().Register<TilemapComponent>(TilemapComponent::GetTypeName());
	Factory::Instance().Register<TextureAnimationComponent>(TextureAnimationComponent::GetTypeName());

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	std::unique_ptr<MyGame> game = std::make_unique<MyGame>(engine.get());
	game->Initialize();

	std::cout << "Client or server?";
	char c = 0;
	if (std::cin >> c)
	{
		if (c == 'c')
		{
			engine->GetNetwork().ClientFunction();
		}
		else if (c == 's')
		{
			game->isHost = true;
		}
		
	}

	//__LINE__ Prints the line
	//__FILE__ Prints the current file
	//__FUNCTION__ Prints the function

	//Adding another scope that way when we get out of the scope,
	//The font gets correctly deconstructed
	{
		
		while (!engine->IsQuit())
		{

			engine->Update();
			game->Update(engine->GetTime().GetDeltaTime());


			engine->GetRenderer().SetColor(255, 255, 255, 0);
			engine->GetRenderer().BeginFrame();

			game->Draw(engine->GetRenderer());

			if (c == 's')
			{
				engine->GetNetwork().HostCheckForConnection();
			}

			
			engine->GetPS().Update(engine->GetTime().GetDeltaTime());
			engine->GetRenderer().EndFrame();

		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	game->Shutdown();
	return 0;
}