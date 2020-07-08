#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace Engine;
class GamePause :
	public State
{
public:
	GamePause(shared_ptr<Content>&content);
	~GamePause();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

private:
	shared_ptr<Content>_content;
	Sprite _background;
	Sprite _resumeButton;
	Sprite _homeButton;

};

