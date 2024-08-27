#include "Renderer.h"
#include "Texture.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

#include <iostream>
#include <SDL.h>

/// <summary>
/// Initializes the components needed for the renderer to work
/// </summary>
/// <returns>False if there is an error initializing, otherwise True</returns>
bool Renderer::Initialize()
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// initialize TTF SDL
	if (TTF_Init() < 0)
	{
		std::cerr << "Error initializing SDL TTF: " << SDL_GetError() << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
	{
		std::cerr << "Error initializing SDL Image: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

/// <summary>
/// Runns all the logic to Shutdown the renderer
/// </summary>
void Renderer::Shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	IMG_Quit();
}

/// <summary>
/// Creates the visual window
/// </summary>
/// <param name="title">The title of the window in the Title Bar</param>
/// <param name="width">The width of the screen</param>
/// <param name="height">The height of the screen</param>
/// <returns>false if there is an error creating the window, otherwise true</returns>
bool Renderer::ECreateWindow(std::string title, int width, int height)
{
	m_width = width;
	m_height = height;

	// create window
	// returns pointer to window if successful or nullptr if failed
	m_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	// create renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return true;
}

/// <summary>
/// Used to designate the beginning of a frame, removing anything from the previous frame
/// </summary>
void Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

/// <summary>
/// Used to designate the end of a frame, displaying anything that was drawn onto the renderer
/// </summary>
void Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}

/// <summary>
/// Used to set the color of the given render
/// </summary>
/// <param name="r">the red value</param>
/// <param name="g">the green value</param>
/// <param name="b">the blue value</param>
/// <param name="a">the alpha value (opacity)</param>
void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

/// <summary>
/// Draws a line connecting two given points
/// </summary>
/// <param name="x1">The x value of the first point</param>
/// <param name="y1">The y value of the first point</param>
/// <param name="x2">The x value of the second point</param>
/// <param name="y2">The y value of the second point</param>
void Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}

/// <summary>
/// Draws a line connecting two given points
/// </summary>
/// <param name="x1">The x value of the first point</param>
/// <param name="y1">The y value of the first point</param>
/// <param name="x2">The x value of the second point</param>
/// <param name="y2">The y value of the second point</param>
void Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
	SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
}

/// <summary>
/// Draws a point at the given coordinates
/// </summary>
/// <param name="x">The x value</param>
/// <param name="y">The y value</param>
void Renderer::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(m_renderer, x, y);
}

/// <summary>
/// Draws a point at the given coordinates
/// </summary>
/// <param name="x">The x value</param>
/// <param name="y">The y value</param>
void Renderer::DrawPoint(float x, float y)
{
	SDL_RenderDrawPointF(m_renderer, x, y);
}

/// <summary>
/// Draws a rectangle at the given point with a given width and height
/// </summary>
/// <param name="x">The x value of the rectangle</param>
/// <param name="y">The y value of the rectangle</param>
/// <param name="w">The width of the rectangle</param>
/// <param name="h">The height of the rectangle</param>
void Renderer::DrawRect(int x, int y, int w, int h)
{
	SDL_Rect rect{ x - w / 2, y - h / 2, w, h };
	SDL_RenderFillRect(m_renderer, &rect);
}

/// <summary>
/// Draws a rectangle at the given point with a given width and height
/// </summary>
/// <param name="x">The x value of the rectangle</param>
/// <param name="y">The y value of the rectangle</param>
/// <param name="w">The width of the rectangle</param>
/// <param name="h">The height of the rectangle</param>
void Renderer::DrawRect(float x, float y, float w, float h)
{
	SDL_FRect rect{ x - w / 2, y - h / 2, w, h };
	SDL_RenderFillRectF(m_renderer, &rect);
}

void Renderer::DrawTexture(std::weak_ptr<Texture> texture, float x, float y, float angle)
{
	Vector2 size = texture.lock()->GetSize();

	SDL_FRect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = size.x;
	destRect.h = size.y;

	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyExF
	SDL_RenderCopyExF(m_renderer, texture.lock()->m_texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void Renderer::DrawTexture(std::weak_ptr<Texture> texture, const Transform& transform, bool hflip)
{
	Vector2 size = texture.lock()->GetSize() * transform.scale;

	SDL_FRect destRect;
	destRect.x = transform.position.x - size.x * 0.5f;
	destRect.y = transform.position.y - size.y * 0.5f;
	destRect.w = size.x;
	destRect.h = size.y;

	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyExF
	SDL_RenderCopyExF(m_renderer, texture.lock()->m_texture, NULL, &destRect, transform.rotation, NULL, (hflip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Renderer::DrawTexture(std::weak_ptr<class Texture> texture, const Transform& transform, const Rect& source, bool hflip)
{
	Vector2 size = Vector2{source.width, source.height} * transform.scale;

	SDL_FRect destRect;
	destRect.x = transform.position.x - size.x * 0.5f;
	destRect.y = transform.position.y - size.y * 0.5f;
	destRect.w = size.x;
	destRect.h = size.y;

	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyExF
	SDL_RenderCopyExF(m_renderer, texture.lock()->m_texture, (SDL_Rect*)&source, &destRect, transform.rotation, NULL, (hflip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
