#pragma once

#include <Core/Engine.h>
#include "GamePiece.h"

class Shuriken : public GamePiece {
	public:
		Shuriken();
		Shuriken(float length, float windowX, float windowY);
		~Shuriken();

		void setScale(float scale);
		void setDestroy(bool destroy);

		bool getWasHit();
		float getScale();

		bool isDestroyed();
		bool inCollision(GamePiece* p) override;

	private:
		float scale;
		bool destroy, wasHit;
};