#include "Shuriken.h"

Shuriken::Shuriken() : GamePiece()
{
	scale = 1;
	destroy = false;
	wasHit = false;
}

Shuriken::Shuriken(float length, float windowX, float windowY) : GamePiece(length, windowX, windowY)
{
	scale = 1;
	destroy = false;
	wasHit = false;
}

Shuriken::~Shuriken()
{

}

void Shuriken::setScale(float scale)
{
	if (scale < 0) {
		wasHit = false;
		this->scale = 0;
	}
	else {
		this->scale = scale;
	}
}

void Shuriken::setDestroy(bool destroy)
{
	this->destroy = destroy;
}

bool Shuriken::getWasHit()
{
	return wasHit;
}

float Shuriken::getScale()
{
	return scale;
}

bool Shuriken::isDestroyed()
{
	if (scale <= 0) {
		destroy = true;
	}

	return destroy;
}

bool Shuriken::inCollision(GamePiece* p)
{
	float dx = this->getPositionX() - p->getPositionX();
	float dy = this->getPositionY() - p->getPositionY();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < this->getLength() + p->getLength()) {
		wasHit = true;
		return true;
	}

	return false;
}
