#pragma once
#include "SDL.h"

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};
class Game 
{
public:
	Game();
	//게임 초기화 함수. 생성자 직후에 호출됨
	bool Initialize();
	
	//소멸자 직전에 호출됨, 리소스 정리
	void Shutdown();
	
	//게임 루프
	void RunLoop();


private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* m_window;
	
	// Renderer for 2D drawing
	SDL_Renderer* m_renderer;
	
	bool m_bRunning;

	// Number of ticks since start of game
	Uint32 m_TicksCount;
	
	// Pong specific
	// Direction of paddle
	int m_PaddleDir;
	// Position of paddle
	Vector2 m_PaddlePos;
	// Position of ball
	Vector2 m_BallPos;
	// Velocity of ball
	Vector2 m_BallVel;
};
