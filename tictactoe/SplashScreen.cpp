#include "SplashScreen.h"
#include "MainMenu.h"
#include "definItions.h"
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iostream>

	SplashScreen::SplashScreen(shared_ptr<Content>& content) :_content(content)
	{
	}

	SplashScreen::~SplashScreen()
	{
	}

	void SplashScreen::Init()
	{
		_content->_assets->AddTextures("SPLASH_SCREEN_BG", SPLASH_SCREEN_BG_PATH);
		_backGround.setTexture(_content->_assets->GetTexture("SPLASH_SCREEN_BG"));
		_backGround.setOrigin(_backGround.getGlobalBounds().width / 2, _backGround.getGlobalBounds().height / 2);
		_backGround.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 2);
	}

	void SplashScreen::ProcessInput()
	{
		Event event;
		while (_content->_window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				_content->_window->close();
			}
		}
	}

	void SplashScreen::Update(Time deltaTime)
	{
		if (_clock.getElapsedTime().asSeconds() > SPALSH_SCREEN_TIME)
		{
			_content->_states->AddState(make_unique<MainMenu>(_content),true);
		}
	}

	void SplashScreen::Draw()
	{
		_content->_window->clear();
		_content->_window->draw(_backGround);
		_content->_window->display();

	}
