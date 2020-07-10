#include "AI.h"
#include "definItions.h"
#include <iostream>
Engine::AI::AI(int playerPiece, shared_ptr<Content>& content):_content(content),_playerPiece(playerPiece)
{
	if (O_PIECE == playerPiece)
		_aiPiece = X_PIECE;
	else
		_aiPiece = O_PIECE;

	checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
	checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
	checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
	checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
	checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
	checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
	checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
	checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
	checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
	checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
	checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
	checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
	checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
	checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
	checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
	checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
	checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
	checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
	checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
	checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
	checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
	checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
	checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
	checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
}

Engine::AI::~AI()
{
}

void Engine::AI::PlacePiece(int(*gridArray)[3][3], Sprite gridPieces[3][3], int * gameState)
{
	try
	{
		for (int i = 0; i < checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], AI_PIECE, gridArray, gridPieces);
		}
		for (int i = 0; i < checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], PLAYER_PIECE, gridArray, gridPieces);
		}
		CheckIfPieceIsEmpty(1,1, gridArray, gridPieces);

		CheckIfPieceIsEmpty(0,2, gridArray, gridPieces);
		CheckIfPieceIsEmpty(0,0, gridArray, gridPieces);
		CheckIfPieceIsEmpty(2,2, gridArray, gridPieces);
		CheckIfPieceIsEmpty(2,0, gridArray, gridPieces);

		CheckIfPieceIsEmpty(1,2, gridArray, gridPieces);
		CheckIfPieceIsEmpty(0,1, gridArray, gridPieces);
		CheckIfPieceIsEmpty(2,1, gridArray, gridPieces);
		CheckIfPieceIsEmpty(1,0, gridArray, gridPieces);
	}
	catch (int error)
	{

	}
	*gameState = STATE_PLAYING;
}

void Engine::AI::CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], Sprite gridPieces[3][3])
{
	if ((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck)
	{
		if (EMPTY_PIECE == (*gridArray)[X][Y])
		{
			(*gridArray)[X][Y] = AI_PIECE;
			gridPieces[X][Y].setTexture(_content->_assets->GetTexture("O PIECE"));
			gridPieces[X][Y].setColor(Color(255, 255, 255, 255));
			throw -1;
		}
	}
}

void Engine::AI::CheckIfPieceIsEmpty(int X, int Y, int (*gridArray)[3][3], Sprite gridPieces[3][3])
{
	if (EMPTY_PIECE == (*gridArray)[X][Y])
	{
		(*gridArray)[X][Y] = AI_PIECE;
		gridPieces[X][Y].setTexture(_content->_assets->GetTexture("O PIECE"));
		gridPieces[X][Y].setColor(Color(255, 255, 255, 255));
		throw -2;
	}
}
