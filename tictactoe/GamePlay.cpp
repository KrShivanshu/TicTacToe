#include "GamePlay.h"
#include "definItions.h"
#include <sstream>
#include <iostream>
#include "GamePause.h"
#include "GameOver.h"
GamePlay::GamePlay(shared_ptr<Content>&content):_content(content)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	_content->_assets->AddTextures("GAMEPLAY_BG", GAMEPLAY_BG_PATH);
	_background.setTexture(_content->_assets->GetTexture("GAMEPLAY_BG"));

	_content->_assets->AddTextures("PAUSE_BUTTON", PAUSE_BUTTON_PATH);
	_pauseButton.setTexture(_content->_assets->GetTexture("PAUSE_BUTTON"));
	_pauseButton.setScale(0.5f, 0.5f);
	_pauseButton.setPosition(_content->_window->getSize().x - (_pauseButton.getGlobalBounds().width), 0);
	

	_content->_assets->AddTextures("RESTART_BUTTON", RESTART_BUTTON_PATH);
	_restartButton.setTexture(_content->_assets->GetTexture("RESTART_BUTTON"));
	_restartButton.setScale(0.38f, 0.38f);
	_restartButton.setPosition(7.f, 7.f);

	_content->_assets->AddTextures("GRID_SPRITE", GRID_SPRITE_PATH);
	_gridSprite.setTexture(_content->_assets->GetTexture("GRID_SPRITE"));

	_content->_assets->AddTextures("X PIECE", X_PIECE_PATH);
	//_background.setTexture(_content->_assets->GetTexture("RESTART_BUTTON"));
	_content->_assets->AddTextures("O PIECE", O_PIECE_PATH);

	_content->_assets->AddTextures("X WIN", X_WIN_PATH);

	_content->_assets->AddTextures("O WIN", O_WIN_PATH);




}

void GamePlay::ProcessInput()
{
	Event event;
	while (_content->_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_pauseButton, Mouse::Left, *(_content->_window)))
		{
			_content->_states->AddState(make_unique<GameOver>(_content), true);

			//_content->_states->AddState(make_unique<GamePause>(_content), false);
			//_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_restartButton, Mouse::Left, *(_content->_window)))
		{
			//_content->_window->close();
			_content->_states->AddState(make_unique<GamePlay>(_content), true);

		}
	}
}

void GamePlay::Update(Time deltaTime)
{
}

void GamePlay::Draw()
{
	_content->_window->clear();
	_content->_window->draw(_background);
	_content->_window->draw(_pauseButton);
	_content->_window->draw(_restartButton);
	_content->_window->display();
}

void GamePlay::InitgridPieces()
{
}

void GamePlay::ChechAndPlacePiece()
{
}

void GamePlay::CheckHasPlayerWon(int turn)
{
}

void GamePlay::Chech3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
{
}
