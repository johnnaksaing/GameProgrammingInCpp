#pragma once

#include "Game.h"
#include <cstdio>

const int thickness = 15;
const float paddleH = 150.f;
Game::Game() : m_window(nullptr),m_bRunning(true), m_TicksCount(0)
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

	
	m_BallPos.x = 1024.0f / 2.0f;
	m_BallPos.y = 768.0f / 2.0f;
	m_BallVel.x = -200.0f;
	m_BallVel.y = 235.0f;
	m_PaddlePos.x = 10.0f;
	m_PaddlePos.y = 768.0f / 2.0f;

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
	// Update paddle direction based on W/S keys
	m_PaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		m_PaddleDir += -1;
	}
	if (state[SDL_SCANCODE_S])
	{
		m_PaddleDir += 1;
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
	//target FPS : 60
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16))
		;

	//update time
	float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.f;
	m_TicksCount = SDL_GetTicks();

	//fix deltaTime to maximum
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}




	//update game world
	
	//ball moving
	m_BallPos.x += m_BallVel.x * deltaTime;
	m_BallPos.y += m_BallVel.y * deltaTime;
	
	//paddle moving
	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = m_PaddlePos.y - m_BallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		m_BallPos.x <= 25.0f && m_BallPos.x >= 20.0f &&
		// The ball is moving to the left
		m_BallVel.x < 0.0f)
	{
		m_BallVel.x *= -1.0f;
	}
	if (m_PaddleDir != 0)
	{
		m_PaddlePos.y += m_PaddleDir * 300.0f * deltaTime;
		
		if (m_PaddlePos.y < (paddleH / 2.f + thickness))
		{
			m_PaddlePos.y = (paddleH / 2.f + thickness);
		}
		else if (m_PaddlePos.y > 768.f - (paddleH / 2.f + thickness))
			m_PaddlePos.y = 768.f - (paddleH / 2.f + thickness);
	}

	// Did the ball collide with the right wall?
	else if (m_BallPos.x >= (1024.0f - thickness) && m_BallVel.x > 0.0f)
	{
		m_BallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (m_BallPos.y <= thickness && m_BallVel.y < 0.0f)
	{
		m_BallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (m_BallPos.y >= (768 - thickness) &&
		m_BallVel.y > 0.0f)
	{
		m_BallVel.y *= -1;
	}










}
void Game::GenerateOutput()
{
	////////////////////background/////////////
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
	

	// Draw walls
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(m_renderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(m_renderer, &wall);
	
	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(m_renderer, &wall);
	
	
	//drawing actors
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
	SDL_Rect paddle
	{
		static_cast<int>(m_PaddlePos.x),
		static_cast<int>(m_PaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(m_renderer, &paddle);


	SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
	SDL_Rect ball
	{
		static_cast<int>(m_BallPos.x - thickness/2),
		static_cast<int>(m_BallPos.y - thickness/2),
		thickness,
		thickness
	};


	SDL_RenderFillRect(m_renderer,&ball);



	// Swap front buffer and back buffer
	SDL_RenderPresent(m_renderer);
}