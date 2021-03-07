#include "Balloon.h"

Balloon::Balloon() : GamePiece()
{
	scale = 1;
	destroy = false;
	wasHit = false;
}

Balloon::Balloon(float length, float windowX, float windowY) : GamePiece(length, windowX, windowY)
{
	scale = 1;
	destroy = false;
	wasHit = false;
}

Balloon::~Balloon()
{

}

void Balloon::setScale(float scale)
{
	if (scale < 0) {
		wasHit = false;
		this->scale = 0;
	}
	else {
		this->scale = scale;
	}
}

void Balloon::setDestroy(bool destroy)
{
	this->destroy = destroy;
}

bool Balloon::getWasHit()
{
	return wasHit;
}

float Balloon::getScale()
{
	return scale;
}

bool Balloon::isDestroyed()
{
	if (scale == 0) {
		destroy = true;
	}

	return destroy;
}

bool Balloon::inCollision(GamePiece* p)
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
