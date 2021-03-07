#pragma once

#include <Core/Engine.h>
#include "GamePiece.h"

class Bow : public GamePiece {
	public:
		Bow();
		Bow(float length, float windowX, float windowY);
		~Bow();

		int getLives();

		bool inCollision(GamePiece* p) override;

	private:
		int lives;
};