#pragma once

#include <Core/Engine.h>
#include "GamePiece.h"

class Arrow : public GamePiece {
	public:
		Arrow();
		Arrow(float length, float windowX, float windowY);
		~Arrow();

		void setAngle(float angle);
		void setScore(int score);

		float getAngle();
		int getScore();
		bool getWasHit();

		bool inCollision(GamePiece* p, int score);

	private:
		float angle, oldMouseY;
		int score;
		bool wasHit;
};