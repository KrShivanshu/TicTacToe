#include "GameOver.h"
#include "definItions.h"
#include "GamePlay.h"

GameOver::GameOver(shared_ptr<Content>& content):_content(content)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	_content->_assets->AddTextures("GAME_OVER_BG", GAME_OVER_BG_PATH);
	_background.setTexture(_content->_assets->GetTexture("GAME_OVER_BG"));

	_content->_assets->AddFont("GAME_OVER_TEXT", GAME_OVER_TEXT_PATH);
	_gameOver.setFont(_content->_assets->GetFont("GAME_OVER_TEXT"));
	_gameOver.setString("Game Over");
	_gameOver.setCharacterSize(40.f);
	_gameOver.setOrigin(_gameOver.getGlobalBounds().width / 2, _gameOver.getGlobalBounds().height / 2);
	_gameOver.setPosition(_content->_window->getSize().x/2, _content->_window->getSize().y / 10 * 1);

	_content->_assets->AddTextures("RETRY_BUTTON", RETRY_BUTTON_PATH);
	_retryButton.setTexture(_content->_assets->GetTexture("RETRY_BUTTON"));
	_retryButton.setScale(.5f, .5f);
	//_retryButton.setOrigin(_retryButton.getGlobalBounds().width / 2, _retryButton.getGlobalBounds().height / 2);
	_retryButton.setPosition(_content->_window->getSize().x / 2 - _retryButton.getGlobalBounds().width / 2, _content->_window->getSize().y / 10 * 4 - _retryButton.getGlobalBounds().height / 2);
	
	_content->_assets->AddTextures("EXIT_BUTTON", EXIT_BUTTON_PATH);
	_exitButton.setTexture(_content->_assets->GetTexture("EXIT_BUTTON"));
	_exitButton.setScale(.65f, .65f);
	//_exitButton.setOrigin(_exitButton.getGlobalBounds().width / 2, _exitButton.getGlobalBounds().height / 2);
	_exitButton.setPosition(_content->_window->getSize().x / 2 - _exitButton.getGlobalBounds().width / 2, _content->_window->getSize().y / 10 * 7 - _exitButton.getGlobalBounds().height / 2);
	
}

void GameOver::ProcessInput()
{
	Event event;
	while (_content->_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_retryButton, Mouse::Left, *(_content->_window)))
		{
			_content->_states->AddState(make_unique<GamePlay>(_content), true);
			//_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_exitButton, Mouse::Left, *(_content->_window)))
		{
			//_content->_states->AddState(make_unique<MainMenu>(_content), true);
			_content->_window->close();
		}
	}
}

void GameOver::Update(Time deltaTime)
{
}

void GameOver::Draw()
{
	_content->_window->clear(Color::Red);
	//_content->_window->draw(_background);
	_content->_window->draw(_gameOver);
	_content->_window->draw(_exitButton);
	_content->_window->draw(_retryButton);
	_content->_window->display();
}
