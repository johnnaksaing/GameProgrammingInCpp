#pragma once

#include "Game.h"

Game::Game() : m_window(nullptr),m_bRunning(true)
{

}

bool Game::Initialize() 
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) 
	{
		SDL_Log("Unable to initialize SDL: %s",SDL_GetError());
		return false;
	}

	// Create an SDL Window
	m_window = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);
	if (nullptr == m_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// Create SDL renderer
	m_renderer = SDL_CreateRenderer(
		m_window, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!m_renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}


	return true;
}

void Game::Shutdown() 
{
	//SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Game::RunLoop() 
{
	while (m_bRunning) 
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		}
	}
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_bRunning = false;
	}

	/*
	// Get state of mouse
	int x, y;
	const Uint32 currbuttons = SDL_GetMouseState(&x, &y);
	if ((currbuttons & SDL_BUTTON_LMASK) != 0 && (mPrevButtons & SDL_BUTTON_LMASK) == 0)
	{
		mGameManager->LeftClickDown(Coordinates2(x, y));
	}

	mPrevButtons = currbuttons;
	*/
}
void Game::UpdateGame()
{

}
void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		m_renderer,
		100,		// R
		100,		// G 
		200,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(m_renderer);

	/*
	for (auto sprite : mSpriteComponents)
	{
		sprite->Draw(m_renderer);
	}
	*/
	// Swap front buffer and back buffer
	SDL_RenderPresent(m_renderer);
}