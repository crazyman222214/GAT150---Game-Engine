#include "Engine.h"
#include "Scene.h"
#include "Actor.h"

#include <iostream>
#include <cstdlib>
#include <vector>


int main(int argc, char* argv[])
{
	g_engine.Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();


		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		g_engine.GetRenderer().BeginFrame();

		//game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Update(g_engine.GetTime().GetDeltaTime());
		g_engine.GetRenderer().EndFrame();

	}

	g_engine.Shutdown();
	return 0;
}