#include "GamePause.h"
#include "definItions.h"
#include "GamePlay.h"
#include "MainMenu.h"

GamePause::GamePause(shared_ptr<Content>&content):_content(content)
{
}

GamePause::~GamePause()
{
}

void GamePause::Init()
{
	_content->_assets->AddTextures("GAME_PAUSE_BG", GAME_PAUSE_BG_PATH);
	_background.setTexture(_content->_assets->GetTexture("GAME_PAUSE_BG"));

	_content->_assets->AddFont("GAME_PAUSE_TEXT", GAME_PASUE_TEXT_PATH);
	_gamePause.setFont(_content->_assets->GetFont("GAME_PAUSE_TEXT"));
	_gamePause.setString("Game Paused");
	_gamePause.setCharacterSize(40.f);
	_gamePause.setOrigin(_gamePause.getGlobalBounds().width / 2, _gamePause.getGlobalBounds().height / 2);
	_gamePause.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 10 * 1);

	_content->_assets->AddTextures("RESUME_BUTTON", RESUME_BUTTON_PATH);
	_resumeButton.setTexture(_content->_assets->GetTexture("RESUME_BUTTON"));
	_resumeButton.setScale(.7f, .7f);
	_resumeButton.setPosition(_content->_window->getSize().x / 2 - _resumeButton.getGlobalBounds().width / 2, _content->_window->getSize().y/10*4 - _resumeButton.getGlobalBounds().height / 2);

	_content->_assets->AddTextures("HOME_BUTTON", HOME_BUTTON_PATH);
	_homeButton.setTexture(_content->_assets->GetTexture("HOME_BUTTON"));
	_homeButton.setScale(.7f, .7f);
	_homeButton.setPosition(_content->_window->getSize().x / 2 - _homeButton.getGlobalBounds().width / 2, _content->_window->getSize().y / 10 * 7 - _homeButton.getGlobalBounds().height / 2);


}

void GamePause::ProcessInput()
{

	Event event;
	while (_content->_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_resumeButton, Mouse::Left, *(_content->_window)))
		{
			_content->_states->PopCurrentState();
			//_content->_states->AddState(make_unique<GamePlay>(_content), true);
			//_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_homeButton, Mouse::Left, *(_content->_window)))
		{
			_content->_states->AddState(make_unique<MainMenu>(_content), true);
			//_content->_window->close();
		}
	}
}

void GamePause::Update(Time deltaTime)
{
}

void GamePause::Draw()
{
	_content->_window->clear();
	_content->_window->draw(_background);
	_content->_window->draw(_gamePause);
	_content->_window->draw(_resumeButton);
	_content->_window->draw(_homeButton);
	_content->_window->display();
}
