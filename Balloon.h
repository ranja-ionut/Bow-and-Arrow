#pragma once

#include <Core/Engine.h>
#include "GamePiece.h"

class Balloon : public GamePiece {
public:
	Balloon();
	Balloon(float length, float windowX, float windowY);
	~Balloon();

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