#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace JREngine {
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_W = SDL_SCANCODE_W;
	const uint32_t key_S = SDL_SCANCODE_S;
	const uint32_t key_A = SDL_SCANCODE_A;
	const uint32_t key_D = SDL_SCANCODE_D;
	const uint32_t key_esc = SDL_SCANCODE_ESCAPE;

	const uint32_t buttonLeft = 0;
	const uint32_t buttonMiddle = 1;
	const uint32_t buttonRight = 2;

	void InputSystem::Initialize(){
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown(){

	}

	void InputSystem::Update(){
		SDL_Event event;
		SDL_PollEvent(&event);
		//Save prev keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevMouseButtonState = m_mouseButtonState;

		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePos = JREngine::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
	}

	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPrevKeyDown(key);

		if (keyDown == true && prevKeyDown == true) {
			keyState = KeyState::Held;
		}
		if (keyDown && !prevKeyDown) {
			keyState = KeyState::Pressed;
		}
		if (!keyDown && prevKeyDown) {
			keyState = KeyState::Released;
		}
		if (!keyDown && !prevKeyDown) {
			keyState = KeyState::Idle;
		}

		return keyState;
	}

	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keyState = KeyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPrevButtonDown(button);

		if (buttonDown && prevButtonDown) {
			keyState = KeyState::Held;
		}
		if (buttonDown && !prevButtonDown) {
			keyState = KeyState::Pressed;
		}
		if (!buttonDown && prevButtonDown) {
			keyState = KeyState::Released;
		}
		if (!buttonDown && !prevButtonDown) {
			keyState = KeyState::Idle;
		}

		return keyState;
	}

	bool InputSystem::onKeyLeft(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_A) == state) {
			return true;
		} else {
			return false;
		}
	}

	bool InputSystem::onKeyRight(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_D) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onKeyUp(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_W) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onKeyDown(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_S) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onKeyEsc(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_esc) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onKeySpace(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(key_space) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onRightClick(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(buttonRight) == state) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputSystem::onLeftClick(JREngine::InputSystem::KeyState state)
	{
		if (GetKeyState(buttonLeft) == state) {
			return true;
		}
		else {
			return false;
		}
	}
}