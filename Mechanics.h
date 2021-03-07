#pragma once

#include <string>
#include <unordered_map>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Transform2D.h"
#include "GamePiece.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Shuriken.h"
#include "Bow.h"

namespace Mechanics
{
	std::unordered_map<std::string, glm::mat3> getArrowMatrix(Arrow *p, float arrowLength, float translateY, float mouseX, float mouseY);
	std::unordered_map<std::string, glm::mat3> getMovingArrowMatrix(Arrow *p, float arrowLength, float translateX, float angle, float power);
	std::unordered_map<std::string, glm::mat3> getBowMatrix(Bow *p, float bowLength, float translateY, float mouseX, float mouseY, float power);
	std::unordered_map<std::string, glm::mat3> getBalloonMatrix(Balloon *p, float balloonLength, float translateX, float translateY, float deltaTime, Arrow* arrow);
	std::unordered_map<std::string, glm::mat3> getShurikenMatrix(Shuriken *p, float shurikenLength, float translateX, float translateY, 
																 float angle, float deltaTime, Arrow* arrow, Bow* bow);
	std::unordered_map<std::string, glm::mat3> getHeartMatrix(float heartLength, float posX, float posY);

	void isPlayerHit(Bow* p, Shuriken* shuriken);
	void isBalloonHit(Arrow* p, Balloon* balloon, int balloonType);
	void isShurikenHit(Arrow* p, Shuriken* shuriken, bool moveArrow);
}

