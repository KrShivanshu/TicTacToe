#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
using namespace sf;
using namespace Engine;
class GameOver :
	public State
{
public:
	GameOver(shared_ptr<Content>& content);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

private:
	shared_ptr<Content>_content;
	Text _gameOver;
	Sprite _background;
	Sprite _retryButton;
	Sprite _exitButton;

};

