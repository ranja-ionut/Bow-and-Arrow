#include "Mechanics.h"
#include "Transform2D.h"
#include <Core/Engine.h>


std::unordered_map<std::string, glm::mat3> Mechanics::getArrowMatrix(Arrow* p, float arrowLength, float translateY, float mouseX, float mouseY) {
	std::unordered_map<std::string, glm::mat3> arrow;
	float scaleX = 3, scaleY = 0.25f, startX = 10, startY = p->getWindowY()/2, start_angle = RADIANS(90);
	float powerScale = 2.3f;
	float y = (mouseY - (startY + translateY)), x = (mouseX - startX);
	float angle = atan(y / x);

	p->setPositionX(startX);
	p->setPositionY(startY + translateY);
	p->setOldPositionX(startX);
	p->setOldPositionY(startY + translateY);
	p->setAngle(angle);

	glm::mat3 arrowModelMatrix = glm::mat3(1);
	arrowModelMatrix *= Transform2D::Translate(startX, startY + translateY);
	arrowModelMatrix *= Transform2D::Rotate(-start_angle + angle);
	arrowModelMatrix *= Transform2D::Translate(0, arrowLength * 2);
	arrowModelMatrix *= Transform2D::Translate(-arrowLength / 2, -arrowLength / 2);
	arrow["arrow_head"] = arrowModelMatrix;

	glm::mat3 modelMatrix = arrowModelMatrix;
	modelMatrix *= Transform2D::Translate((arrowLength + arrowLength * scaleY) / 2, -arrowLength * scaleX);
	modelMatrix *= Transform2D::Rotate(start_angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	arrow["arrow_body"] = modelMatrix;

	return arrow;
}

std::unordered_map<std::string, glm::mat3> Mechanics::getMovingArrowMatrix(Arrow* p, float arrowLength, float translateX, float angle, float power) {
	std::unordered_map<std::string, glm::mat3> arrow;
	float scaleX = 3, scaleY = 0.25f, startX = 10, start_angle = RADIANS(90);
	float powerScale = 2.3f;
	float translateY = tan(angle) * translateX - 2.45f * pow((translateX / (power * cos(RADIANS(angle)))), 2) + tan(RADIANS(angle)) * translateX;
	float newX = (translateX - p->getOldPositionX());
	float new_angle = atan(translateY / newX);

	p->setPositionX(startX + translateX);
	p->setPositionY(p->getOldPositionY() + translateY);

	glm::mat3 arrowModelMatrix = glm::mat3(1);
	arrowModelMatrix *= Transform2D::Translate(startX + translateX, p->getOldPositionY() + translateY);
	arrowModelMatrix *= Transform2D::Rotate(-start_angle + new_angle);
	arrowModelMatrix *= Transform2D::Translate(0, arrowLength * 2);
	arrowModelMatrix *= Transform2D::Translate(-arrowLength / 2, -arrowLength / 2);
	arrow["arrow_head"] = arrowModelMatrix;

	glm::mat3 modelMatrix = arrowModelMatrix;
	modelMatrix *= Transform2D::Translate((arrowLength + arrowLength * scaleY) / 2, -arrowLength * scaleX);
	modelMatrix *= Transform2D::Rotate(start_angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	arrow["arrow_body"] = modelMatrix;

	return arrow;
};

std::unordered_map<std::string, glm::mat3> Mechanics::getBowMatrix(Bow* p, float bowLength, float translateY, float mouseX, float mouseY, float power) {
	std::unordered_map<std::string, glm::mat3> bow;
	float scaleX = 1.5f, scaleY = 1, startX = 10, startY = p->getWindowY() / 2, start_angle = RADIANS(90);
	float powerScale = 2.3f;
	float y = (mouseY - (startY + translateY)), x = (mouseX - startX);
	float angle = atan(y / x);

	p->setPositionX(startX);
	p->setPositionY(startY + translateY);

	glm::mat3 bowModelMatrix = glm::mat3(1);
	bowModelMatrix *= Transform2D::Translate(startX, startY + translateY);
	bowModelMatrix *= Transform2D::Rotate(-start_angle + angle);
	bowModelMatrix *= Transform2D::Scale(scaleX, scaleY);
	bow["bow"] = bowModelMatrix;

	glm::mat3 modelMatrix = bowModelMatrix;
	modelMatrix *= Transform2D::Translate(-bowLength, 0);
	modelMatrix *= Transform2D::Scale(2, scaleY);
	bow["bow_string"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(startX, startY + translateY);
	modelMatrix *= Transform2D::Translate(0, - bowLength * powerScale);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Scale(power, 0.2f);
	bow["bow_power"] = modelMatrix;

	return bow;
};

void Mechanics::isPlayerHit(Bow* p, Shuriken* shuriken)
{	
	if (p->inCollision(shuriken) && !shuriken->isDestroyed()) {
		// nothing
	}
}

void Mechanics::isBalloonHit(Arrow* p, Balloon* balloon, int balloonType)
{	
	if (!balloonType) {
		if (p->inCollision(balloon, 10) && !balloon->isDestroyed()) {
			// nothing
		}
	}
	else {
		if (p->inCollision(balloon, -10) && !balloon->isDestroyed()) {
			// nothing
		}
	}
}

void Mechanics::isShurikenHit(Arrow* p, Shuriken* shuriken, bool moveArrow)
{	
	if (moveArrow) {
		if (p->inCollision(shuriken, 30) && !shuriken->isDestroyed()) {
			// nothing
		}
	}
}

std::unordered_map<std::string, glm::mat3> Mechanics::getBalloonMatrix(Balloon* p, float balloonLength, float translateX, float translateY, float deltaTime, Arrow *arrow) {
	std::unordered_map<std::string, glm::mat3> balloon;

	float scaleX = 1, scaleY = 1.5f, tailScaleX = 0.5f, tailScaleY = 0.3f, start_angle = RADIANS(90);
	static float offset = 0;
	offset += deltaTime * 10;

	if (!p->getWasHit()) {
		p->setPositionX(translateX + cos(RADIANS(offset)) * balloonLength);
		p->setPositionY(translateY);
		p->setOldPositionX(translateX + cos(RADIANS(offset)) * balloonLength);
		p->setOldPositionY(translateY);
	}

	if (p->getPositionY() > p->getWindowY() + balloonLength * 3 || p->getPositionX() > p->getWindowX()) {
		p->setDestroy(true);
	}

	glm::mat3 bodyMatrix = glm::mat3(1);
	bodyMatrix *= Transform2D::Translate(p->getOldPositionX(), p->getOldPositionY());
	bodyMatrix *= Transform2D::Scale(scaleX, scaleY);
	if (p->inCollision(arrow) || p->getWasHit()) {
		bodyMatrix *= Transform2D::Scale(p->getScale(), p->getScale());
		p->setScale(p->getScale() - deltaTime);
	}
	balloon["balloon_body"] = bodyMatrix;
	
	glm::mat3 modelMatrix = bodyMatrix;
	modelMatrix *= Transform2D::Translate(0, -balloonLength);
	modelMatrix *= Transform2D::Translate(-balloonLength * tailScaleX / 2, -balloonLength * tailScaleY / 2);
	modelMatrix *= Transform2D::Scale(tailScaleX, tailScaleY);
	balloon["balloon_tail"] = modelMatrix;

	modelMatrix = bodyMatrix;
	modelMatrix *= Transform2D::Translate(0, -balloonLength);
	modelMatrix *= Transform2D::Rotate(-start_angle);
	balloon["balloon_string"] = modelMatrix;

	return balloon;
}

std::unordered_map<std::string, glm::mat3> Mechanics::getShurikenMatrix(Shuriken* p, float shurikenLength, float translateX, float translateY,
																		float angle, float deltaTime, Arrow* arrow, Bow* bow) {
	std::unordered_map<std::string, glm::mat3> shuriken;

	float scaleX = 1.7f, scaleY = 0.8f, tailScaleX = 0.5f, tailScaleY = 0.3f, start_angle = 90;
	bool hit = false;

	if (!p->getWasHit()) {
		p->setPositionX(translateX);
		p->setPositionY(translateY);
		p->setOldPositionX(translateX);
		p->setOldPositionY(translateY);
	}

	if (p->getPositionX() < shurikenLength * 2 || p->getPositionY() > p->getWindowY() || p->getPositionY() < 0) {
		p->setDestroy(true);
	}

	if (p->inCollision(bow)) {
		p->setScale(0);
	}

	if (p->inCollision(arrow) || p->getWasHit()) {
		hit = true;
	}

	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(p->getOldPositionX(), p->getOldPositionY());
	modelMatrix *= Transform2D::Rotate(RADIANS(start_angle * 0) + angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	if (hit) {
		modelMatrix *= Transform2D::Scale(p->getScale(), p->getScale());
		p->setScale(p->getScale() - deltaTime);
	}
	shuriken["shuriken_up"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(p->getOldPositionX(), p->getOldPositionY());
	modelMatrix *= Transform2D::Rotate(RADIANS(start_angle * 1) + angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	if (hit) {
		modelMatrix *= Transform2D::Scale(p->getScale(), p->getScale());
	}
	shuriken["shuriken_down"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(p->getOldPositionX(), p->getOldPositionY());
	modelMatrix *= Transform2D::Rotate(RADIANS(start_angle * 2) + angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	if (hit) {
		modelMatrix *= Transform2D::Scale(p->getScale(), p->getScale());
	}
	shuriken["shuriken_left"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(p->getOldPositionX(), p->getOldPositionY());
	modelMatrix *= Transform2D::Rotate(RADIANS(start_angle * 3) + angle);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	if (hit) {
		modelMatrix *= Transform2D::Scale(p->getScale(), p->getScale());
	}
	shuriken["shuriken_right"] = modelMatrix;

	return shuriken;
}

std::unordered_map<std::string, glm::mat3> Mechanics::getHeartMatrix(float heartLength, float posX, float posY)
{
	float scale = 0.5f, scaleBase = 1.3f;

	std::unordered_map<std::string, glm::mat3> heart;

	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(posX - heartLength / 2 + heartLength / 6, posY - heartLength / 2 + heartLength / 12);
	modelMatrix *= Transform2D::Rotate(RADIANS(180));
	modelMatrix *= Transform2D::Scale(scaleBase, 1.1f);
	heart["heart_base"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(posX - heartLength - heartLength / 3, posY);
	modelMatrix *= Transform2D::Scale(scale, scale);
	heart["left_heart_circle"] = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(posX - heartLength + heartLength / 3, posY);
	modelMatrix *= Transform2D::Scale(scale, scale);
	heart["right_heart_circle"] = modelMatrix;

	return heart;
}
