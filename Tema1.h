#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <unordered_map>
#include "Object2D.h"
#include "Mechanics.h"
#include "Defines.h"

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		
		

	protected:
		glm::mat3 modelMatrix;
		bool move_arrow;
		int targets, shurikens;
		float arrowTranslateX, arrow_power, shurikenAngle;
		float mouseX, mouseY, bowTranslateY, power;
		int balloonType[MAXTARGETS];
		float balloonTranslateX[MAXTARGETS], balloonTranslateY[MAXTARGETS];
		float shurikenTranslateX[MAXSHURIKENS], shurikenTranslateY[MAXSHURIKENS];
		std::unordered_map<std::string, glm::mat3> bow, arrow, red_balloon, yellow_balloon, shuriken, heart;
		Bow* bow_gp;
		Balloon* balloon_gp[MAXTARGETS];
		Shuriken* shuriken_gp[MAXSHURIKENS];
		Arrow* arrow_gp;
		float timer;
};
