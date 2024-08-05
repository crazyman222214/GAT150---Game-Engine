#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Actor.h"
#include "Renderer/Texture.h"
#include "Core/EAssert.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <SDL_image.h>
#include <Renderer/Text.h>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();
	//__LINE__ Prints the line
	//__FILE__ Prints the current file
	//__FUNCTION__ Prints the function

	

	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Murio.jpg", engine->GetRenderer());
	res_t<Font> font = ResourceManager::Instance().Get<Font>("Blockletter.otf", 20);
	std::unique_ptr<Text> text = std::make_unique<Text>(font);
	text->Create(engine->GetRenderer(), "Game Over Loser", { 1, 0, 0, 1 });
	
	while (!engine->IsQuit())
	{
		engine->Update();
		engine->GetRenderer().SetColor(255, 255, 255, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
		text->Draw(engine->GetRenderer(), engine->GetRenderer().GetWidth() - 200, 20);

		engine->GetPS().Update(engine->GetTime().GetDeltaTime());

		engine->GetRenderer().EndFrame();

	}

	engine->Shutdown();
	return 0;
}