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
	gameState = STATE_PLAYING;
	turn = PLAYER_PIECE;
	ai = new AI(turn, _content);

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

	_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);

	_content->_assets->AddTextures("X PIECE", X_PIECE_PATH);
	//_background.setTexture(_content->_assets->GetTexture("RESTART_BUTTON"));
	_content->_assets->AddTextures("O PIECE", O_PIECE_PATH);

	_content->_assets->AddTextures("X WIN", X_WIN_PATH);

	_content->_assets->AddTextures("O WIN", O_WIN_PATH);

	InitGridPieces();

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			_gridArray[x][y] = EMPTY_PIECE;


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
			//_content->_states->AddState(make_unique<GameOver>(_content), true);

			_content->_states->AddState(make_unique<GamePause>(_content), false);
			//_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_restartButton, Mouse::Left, *(_content->_window)))
		{
			//_content->_window->close();
			_content->_states->AddState(make_unique<GamePlay>(_content), true);

		}
		else if (_content->_inputs->IsSpriteClicked(_gridSprite, Mouse::Left, *(_content->_window)))
		{
			if (STATE_PLAYING == gameState)
				CheckAndPlacePiece();
		}
	}
}

void GamePlay::Update(Time deltaTime)
{
	if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
	{
		if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
		{
			_content->_states->AddState(make_unique<GameOver>(_content), true);
		}
	}
}

void GamePlay::Draw()
{
	_content->_window->clear();
_content->_window->draw(_background);
_content->_window->draw(_pauseButton);
_content->_window->draw(_restartButton);
_content->_window->draw(_gridSprite);
for (int x = 0; x < 3; x++)
	for (int y = 0; y < 3; y++)
		_content->_window->draw(_gridPieces[x][y]);
_content->_window->display();
}

void GamePlay::InitGridPieces()
{
	//Vector2u spriteSize = _content->_assets->GetTexture("X PIECE").getSize();
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
		{
			_gridPieces[x][y].setTexture(_content->_assets->GetTexture("X PIECE"));
			_gridPieces[x][y].setOrigin(_gridPieces[x][y].getGlobalBounds().width / 2, _gridPieces[x][y].getGlobalBounds().height / 2);
			_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + _gridSprite.getGlobalBounds().width / 6 * ((2 * x) + 1), _gridSprite.getPosition().y + _gridSprite.getGlobalBounds().height / 6 * ((2 * y) + 1));
			_gridPieces[x][y].setColor(Color(255, 255, 255, 0));
		}
}

void GamePlay::CheckAndPlacePiece()
{
	Vector2i touchPoint = _content->_inputs->GetMousePosition(*(_content->_window));
	FloatRect gridSize = _gridSprite.getGlobalBounds();
	Vector2f gapOutsideOfGrid = Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
	Vector2f gridLocalTouchPos = Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
	Vector2f gridSectionSize = Vector2f(gridSize.width / 3, gridSize.height / 3);

	int column, row;
	if (gridLocalTouchPos.x < gridSectionSize.x)
		column = 1;
	else if (gridLocalTouchPos.x < gridSectionSize.x * 2)
		column = 2;
	else if (gridLocalTouchPos.x < gridSectionSize.x * 3)
		column = 3;

	if (gridLocalTouchPos.y < gridSectionSize.y)
		row = 1;
	else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
		row = 2;
	else if (gridLocalTouchPos.y < gridSectionSize.y * 3)
		row = 3;

	if (_gridArray[column - 1][row - 1] == EMPTY_PIECE)
	{
		_gridArray[column - 1][row - 1] = turn;
		if (PLAYER_PIECE == turn)
		{
			_gridPieces[column - 1][row - 1].setTexture(_content->_assets->GetTexture("X PIECE"));
			CheckHasPlayerWon(turn);
		}
		_gridPieces[column - 1][row - 1].setColor(Color(255, 255, 255, 255));
	}
}

void GamePlay::CheckHasPlayerWon(int player)
{
	Chech3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
	Chech3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
	Chech3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
	Chech3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
	Chech3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
	Chech3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
	Chech3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
	Chech3PiecesForMatch(0, 2, 1, 1, 2, 0, player);
	if (STATE_WON != gameState)
	{
		gameState = STATE_AI_PLAYING;
		ai->PlacePiece(&_gridArray, _gridPieces, &gameState);
		Chech3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
		Chech3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
		Chech3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
		Chech3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
		Chech3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
		Chech3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
		Chech3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
		Chech3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);

	}

	int emptyNum = 9;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			if (EMPTY_PIECE != _gridArray[x][y])
				emptyNum--;

	if (emptyNum == 0 && STATE_WON != gameState && STATE_LOSE != gameState)
		gameState = STATE_DRAW;

	if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
		_clock.restart();
	cout << gameState << endl;
}

void GamePlay::Chech3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
{
	if (pieceToCheck == _gridArray[x1][y1] && pieceToCheck == _gridArray[x2][y2] && pieceToCheck == _gridArray[x3][y3])
	{
		string winningPieceStr;
		if (O_PIECE == pieceToCheck)
			winningPieceStr = "O WIN";
		else
			winningPieceStr = "X WIN";

		_gridPieces[x1][y1].setTexture(_content->_assets->GetTexture(winningPieceStr));
		_gridPieces[x2][y2].setTexture(_content->_assets->GetTexture(winningPieceStr));
		_gridPieces[x3][y3].setTexture(_content->_assets->GetTexture(winningPieceStr));

		if (PLAYER_PIECE == pieceToCheck)
			gameState = STATE_WON;
		else
			gameState = STATE_LOSE;

	}
}
