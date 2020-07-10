#pragma once
#include "State.h"
#include "Game.h"
#include "AI.h"
#include "SFML/Graphics.hpp"
using namespace Engine;
class GamePlay :
	public State
{
public:
	GamePlay(shared_ptr<Content>&content);
	~GamePlay();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

private:
	void InitGridPieces();
	void CheckAndPlacePiece();
	void CheckHasPlayerWon(int turn);
	void Chech3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
	shared_ptr<Content>_content;
	Sprite _background;
	Sprite _pauseButton;
	Sprite _restartButton;
	Sprite _gridSprite;
	Sprite _gridPieces[3][3];
	int _gridArray[3][3];
	int turn;
	int gameState;
	AI *ai;
	sf::Clock _clock;

};

