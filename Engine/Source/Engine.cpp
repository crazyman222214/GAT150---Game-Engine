#include "Engine.h"
#include <crtdbg.h>

bool Engine::Initialize()
{
    //Enable memory leak check :-0
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    m_renderer = std::make_unique<Renderer>();
    m_input = std::make_unique<Input>();
    m_audio = std::make_unique<Audio>();
    m_time = std::make_unique<Time>();
    m_ps = std::make_unique<ParticleSystem>();

    m_renderer->Initialize();
    m_renderer->CreateWindow("Game Engine", 800, 600);

    m_input->Initialize();
    m_audio->Initialize();


    return true;
}

void Engine::Shutdown()
{
    m_renderer->Shutdown();
    m_input->Shutdown();
    m_audio->Shutdown();

    //Display memory leaks
    _CrtMemDumpAllObjectsSince(NULL);

}

void Engine::Update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            quit = true;
        }
    }
    

    m_time->Tick();
    m_input->Update();
    m_audio->Update();
    
}


