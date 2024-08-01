#include "Input.h"
#include <SDL.h>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);
	
	//Copy current keyboard state into our keyboard state
	std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{
	//PooPoo
}

void Input::Update()
{
	//Keyboard Input
	m_prevKeyboardState = m_keyboardState;
	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());
	
	//Mouse Input
	int x, y;
	uint32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePosition.x = (float)x;
	m_mousePosition.y = (float)y;

	m_prevMouseButtonStates = m_mouseButtonStates;

	m_mouseButtonStates[0] = buttonState & SDL_BUTTON_LMASK;
	m_mouseButtonStates[1] = buttonState & SDL_BUTTON_MMASK;
	m_mouseButtonStates[2] = buttonState & SDL_BUTTON_RMASK;

}
