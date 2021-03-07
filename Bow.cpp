#include "Bow.h"

Bow::Bow() : GamePiece()
{
	lives = 3;
}

Bow::Bow(float length, float windowX, float windowY) : GamePiece(length, windowX, windowY)
{
	lives = 3;
}

Bow::~Bow()
{
}


int Bow::getLives()
{
	return lives;
}

bool Bow::inCollision(GamePiece* p)
{
	float dx = this->getPositionX() - p->getPositionX();
	float dy = this->getPositionY() - p->getPositionY();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < this->getLength() * 1.5f + p->getLength()) {
		if (!p->getCounted()) {
			lives--;
			printf("You got hit! %i lives remaining!\n", lives);
			p->setCounted(true);
		}
		return true;
	}

	return false;
}
