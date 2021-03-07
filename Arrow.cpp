#include "Arrow.h"

Arrow::Arrow() : GamePiece()
{
	angle = 0;
	score = 0;
	wasHit = false;
}

Arrow::Arrow(float length, float windowX, float windowY) : GamePiece(length, windowX, windowY)
{
	angle = 0;
	score = 0;
	wasHit = false;
}

Arrow::~Arrow()
{
}

void Arrow::setAngle(float angle)
{
	this->angle = angle;
}

void Arrow::setScore(int score)
{
	this->score = score;
}

float Arrow::getAngle()
{
	return angle;
}


int Arrow::getScore()
{
	return score;
}

bool Arrow::getWasHit()
{
	return wasHit;
}

bool Arrow::inCollision(GamePiece* p, int score)
{
	float dx = this->getPositionX() - p->getPositionX();
	float dy = this->getPositionY() - p->getPositionY();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < this->getLength() + p->getLength()) {
		if (!p->getCounted()) {
			this->score += score;
			p->setCounted(true);
		}
		return true;
	}

	return false;
}
