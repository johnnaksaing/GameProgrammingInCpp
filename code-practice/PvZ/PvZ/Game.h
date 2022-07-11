#pragma once
#include "SDL.h"
#include <unordered_map>
#include <memory>

#include "Actor.h"

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
	//���� �ʱ�ȭ �Լ�. ������ ���Ŀ� ȣ���
	bool Initialize();
	
	//�Ҹ��� ������ ȣ���, ���ҽ� ����
	void Shutdown();
	
	//���� ����
	void RunLoop();


private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();


	/*
	void LoadData();
	void UnLoadData();

	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_Textures;

	std::vector<std::shared_ptr<class Actor>> m_Actors;
	std::vector<std::shared_ptr<class Actor>> m_PendingActors;

	*/

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	
	bool m_bRunning;
	
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
