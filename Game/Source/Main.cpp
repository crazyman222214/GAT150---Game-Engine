#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Actor.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();
	int i = 5;
	assert(i == 5);	

#ifdef _DEBUG
	std::cout << "debug\n";
#endif
	int* p = nullptr;
	


	//__LINE__ Prints the line
	//__FILE__ Prints the current file
	//__FUNCTION__ Prints the function

	while (!engine->IsQuit())
	{
		engine->Update();
		engine->GetRenderer().SetColor(255, 255, 255, 0);
		engine->GetRenderer().BeginFrame();

		//game->Draw(engine->GetRenderer());
		engine->GetPS().Update(engine->GetTime().GetDeltaTime());
		engine->GetRenderer().EndFrame();

	}

	engine->Shutdown();
	return 0;
}