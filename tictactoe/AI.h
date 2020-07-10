#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.h"
using namespace sf;
using namespace std;
namespace Engine {
	class AI
	{
	public:
		AI(int playerPiece, shared_ptr<Content> &content);
		~AI();
		void PlacePiece(int(*gridArray)[3][3], Sprite gridPieces[3][3], int *gameState);

	private:
		void CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], Sprite gridPieces[3][3]);
		void CheckIfPieceIsEmpty(int X, int Y, int (*gridArray)[3][3], Sprite gridPieces[3][3]);
		int _aiPiece;
		int _playerPiece;
		vector<array<int, 6>>checkMatchVector;
		shared_ptr<Content>_content;
	};

}