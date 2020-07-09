#pragma once
#include "State.h"
#include "Game.h"
using namespace Engine;
class MainMenu :
	public State
{
public:
	MainMenu(shared_ptr<Content>&content);
	~MainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

private:
	shared_ptr<Content>_content;
	Text _gameTitle;
	Sprite _backGround;
	Sprite _playButton;
	//Sprite _exitButton;
};

