#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Actor.h"
#include "Renderer/Texture.h"
#include "Core/EAssert.h"
#include "Renderer/Text.h"
#include "Core/EFile.h"
#include "Core/Json.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <SDL_image.h>



int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>("Actor");
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();
	//__LINE__ Prints the line
	//__FILE__ Prints the current file
	//__FUNCTION__ Prints the function

	std::string s;
	File::ReadFile("text.txt", s);
	std::cout << s;
	
	rapidjson::Document document;
	Json::Load("text.txt", document);

	// read the data from the json
	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;


	//READ_DATA(document, age);
	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);


	std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;

	//Adding another scope that way when we get out of the scope,
	//The font gets correctly deconstructed
	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Murio.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("Blockletter.otf", 20);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Game Over Loser", { 1, 0, 0, 1 });

		Transform t{ {30, 30} };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));


		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(255, 255, 255, 0);
			engine->GetRenderer().BeginFrame();

			//engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			text->Draw(engine->GetRenderer(), engine->GetRenderer().GetWidth() - 200, 20);
			actor->Draw(engine->GetRenderer());
			engine->GetPS().Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().EndFrame();

		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}