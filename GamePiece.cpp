#include <Core/Engine.h>
#include "GamePiece.h"

using namespace std;

GamePiece::GamePiece() {
	origin = glm::vec3(0, 0, 0);
	x = 0;
	y = 0;
	old_x = 0;
	old_y = 0;
	length = 0;
	destroyed = false;
	scale = 1;
	windowX = 0;
	windowY = 0;
	count = false;
	wasHit = false;
}

GamePiece::GamePiece(float length, float windowX, float windowY) {
	origin = glm::vec3(0, 0, 0);
	x = 0;
	y = 0;
	old_x = 0;
	old_y = 0;
	scale = 1;
	destroyed = false;
	wasHit = false;
	count = false;
	this->length = length;
	this->windowX = windowX;
	this->windowY = windowY;
}

GamePiece::~GamePiece() {

}

float GamePiece::getLength()
{
	return length;
}

float GamePiece::getWindowX() {
	return windowX;
}

float GamePiece::getWindowY() {
	return windowY;
}

void GamePiece::setPositionX(float x) {
	this->x = x;
}

void GamePiece::setPositionY(float y) {
	this->y = y;
}

void GamePiece::setOldPositionX(float x) {
	old_x = x;
}

void GamePiece::setOldPositionY(float y) {
	old_y = y;
}


void GamePiece::setScale(float scale) {
	if (scale < 0) {
		wasHit = false;
		this->scale = 0;
	}
	else {
		this->scale = scale;
	}
}

void GamePiece::setDestroy(bool destroyed) {
	this->destroyed = destroyed;
}

void GamePiece::setCounted(bool count)
{
	this->count = count;
}

float GamePiece::getPositionX() {
	return x;
}

float GamePiece::getPositionY() {
	return y;
}

float GamePiece::getOldPositionX() {
	return old_x;
}

float GamePiece::getOldPositionY() {
	return old_y;
}

float GamePiece::getScale() {
	return scale;
}

bool GamePiece::getWasHit() {
	return wasHit;
}

bool GamePiece::getCounted()
{
	return count;
}

bool GamePiece::isDestroyed() {
	if (scale <= 0) {
		destroyed = true;
		count = false;
	}
	
	return destroyed;
}

bool GamePiece::inCollision(GamePiece *pos) {
	float dx = x - pos->x;
	float dy = y - pos->y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < length + pos->length) {
		wasHit = true;
		return true;
	}

	return false;
}
