#include "Tema1.h"

#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema1::Tema1() {
	bow_gp = new Bow(BOW_LENGTH, WINDOWX, WINDOWY);
	arrow_gp = new Arrow(ARROW_LENGTH, WINDOWX, WINDOWY);

	targets = MAXTARGETS;
	shurikens = 1;

	for (int i = 0; i < MAXTARGETS; i++) {
		balloon_gp[i] = new Balloon(BALLOON_LENGTH, WINDOWX, WINDOWY);
		balloonTranslateX[i] = rand() % (int)(WINDOWX - WINDOWX / 8) + WINDOWX / 4;
		balloonTranslateY[i] = 0;
		balloonType[i] = rand() % 2;
	}

	for (int i = 0; i < MAXSHURIKENS; i++) {
		shuriken_gp[i] = new Shuriken(SHURIKEN_LENGTH, WINDOWX, WINDOWY);
		shurikenTranslateY[i] = rand() % (int)(WINDOWY - WINDOWY / 4) + WINDOWY / 8;
		shurikenTranslateX[i] = 0;
	}

	move_arrow = false;
	arrow_power = 0;
	arrowTranslateX = 0;
	power = 0;

	bowTranslateY = 0;

	shurikenAngle = 0;
	
	mouseX = window->GetCursorPosition().x;
	mouseY = window->GetCursorPosition().y;
	
	timer = 0;
}

Tema1::~Tema1() {
	
}

void Tema1::Init()
{
	printf("Score: %i\n", arrow_gp->getScore());
	printf("Lives: %i\n", bow_gp->getLives());

	//glLineWidth(line_width);
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// bow
	{
		Mesh* bow = Object2D::CreateCircleArc("bow", ORIGIN, BOW_LENGTH, BROWN);
		AddMeshToList(bow);

		Mesh* bow_string = Object2D::CreateLine("bow_string", ORIGIN, BOW_LENGTH, LIGHT_GRAY);
		AddMeshToList(bow_string);

		Mesh* bow_power = Object2D::CreateSquare("bow_power", ORIGIN, POWER_LENGTH, glm::vec3(0), true);
		AddMeshToList(bow_power);
	}

	// arrow
	{
		Mesh* arrow_head = Object2D::CreateTriangle("arrow_head", ORIGIN, ARROW_LENGTH, GRAY, true);
		AddMeshToList(arrow_head);
		
		Mesh* arrow_body = Object2D::CreateSquare("arrow_body", ORIGIN, ARROW_LENGTH, BROWN, true);
		AddMeshToList(arrow_body);
	}

	// slow balloon
	{
		Mesh* red_balloon_body = Object2D::CreateCircle("red_balloon_body", ORIGIN, BALLOON_LENGTH, RED, true);
		AddMeshToList(red_balloon_body);

		Mesh* red_balloon_tail = Object2D::CreateTriangle("red_balloon_tail", ORIGIN, BALLOON_LENGTH, RED, true);
		AddMeshToList(red_balloon_tail);

		Mesh* red_balloon_string = Object2D::CreatePolyline("red_balloon_string", ORIGIN, BALLOON_LENGTH, BALLOON_STRING_POINTS, GRAY);
		AddMeshToList(red_balloon_string);
	}

	// fast balloon
	{
		Mesh* yellow_balloon_body = Object2D::CreateCircle("yellow_balloon_body", ORIGIN, BALLOON_LENGTH, YELLOW, true);
		AddMeshToList(yellow_balloon_body);

		Mesh* yellow_balloon_tail = Object2D::CreateTriangle("yellow_balloon_tail", ORIGIN, BALLOON_LENGTH, YELLOW, true);
		AddMeshToList(yellow_balloon_tail);

		Mesh* yellow_balloon_string = Object2D::CreatePolyline("yellow_balloon_string", ORIGIN, BALLOON_LENGTH, BALLOON_STRING_POINTS, GRAY);
		AddMeshToList(yellow_balloon_string);
	}

	// shuriken
	{
		Mesh* shuriken_up = Object2D::CreateTriangle("shuriken_up", ORIGIN, SHURIKEN_LENGTH, DARK_GRAY, true);
		AddMeshToList(shuriken_up);

		Mesh* shuriken_down = Object2D::CreateTriangle("shuriken_down", ORIGIN, SHURIKEN_LENGTH, DARK_GRAY, true);
		AddMeshToList(shuriken_down);

		Mesh* shuriken_left = Object2D::CreateTriangle("shuriken_left", ORIGIN, SHURIKEN_LENGTH, DARK_GRAY, true);
		AddMeshToList(shuriken_left);

		Mesh* shuriken_right = Object2D::CreateTriangle("shuriken_right", ORIGIN, SHURIKEN_LENGTH, DARK_GRAY, true);
		AddMeshToList(shuriken_right);
	}

	// life heart
	{
		Mesh* left_heart_circle = Object2D::CreateCircle("left_heart_circle", ORIGIN, HEART_LENGTH, RED, true);
		AddMeshToList(left_heart_circle);

		Mesh* right_heart_circle = Object2D::CreateCircle("right_heart_circle", ORIGIN, HEART_LENGTH, RED, true);
		AddMeshToList(right_heart_circle);

		Mesh* heart_base = Object2D::CreateTriangle("heart_base", ORIGIN, HEART_LENGTH, RED, true);
		AddMeshToList(heart_base);
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (arrow_gp->getScore() >= 300) {
		targets = MAXTARGETS - TARGETDEC;
		shurikens = 2;
	}

	if (arrow_gp->getScore() >= 700) {
		targets = MAXTARGETS - 2 * TARGETDEC;
		shurikens = 1 + SHURIKENINC;
	}

	if (arrow_gp->getScore() >= 1000) {
		targets = MAXTARGETS - 3 * TARGETDEC;
		shurikens = 1 + 2 * SHURIKENINC;
	}

	if (arrow_gp->getScore() > 1500) {
		shurikens = 1 + 3 * SHURIKENINC;
	}

	timer += deltaTimeSeconds;

	if (timer >= 10) {
		timer = 0;
		printf("Score: %i Lives: %i\n", arrow_gp->getScore(), bow_gp->getLives());
	}

	if (bow_gp->getLives() <= 0) {
		printf("GAME OVER!\n");
		printf("Final Score: %i\n", arrow_gp->getScore());
		exit(0);
	}

	mouseX = window->GetCursorPosition().x;
	mouseY = WINDOWY - window->GetCursorPosition().y;
	if (move_arrow) {
		arrowTranslateX += deltaTimeSeconds * min(arrow_power + 75.f, 150.f) * 7.5f;
	}
	else {
		arrowTranslateX = 0;
	}

	if (arrow_gp->getPositionX() > WINDOWX || (arrow_gp->getPositionY() < 0 || arrow_gp->getPositionY() > WINDOWY)) {
		move_arrow = false;
	}

	if (bow_gp->getLives() >= 1) {
		heart = Mechanics::getHeartMatrix(HEART_LENGTH, HEART_X, HEART_Y);
		RenderMesh2D(meshes["heart_base"], shaders["VertexColor"], heart["heart_base"]);
		RenderMesh2D(meshes["left_heart_circle"], shaders["VertexColor"], heart["left_heart_circle"]);
		RenderMesh2D(meshes["right_heart_circle"], shaders["VertexColor"], heart["right_heart_circle"]);
	}

	if (bow_gp->getLives() >= 2) {
		heart = Mechanics::getHeartMatrix(HEART_LENGTH, HEART_X + 2 * HEART_LENGTH, HEART_Y);
		RenderMesh2D(meshes["heart_base"], shaders["VertexColor"], heart["heart_base"]);
		RenderMesh2D(meshes["left_heart_circle"], shaders["VertexColor"], heart["left_heart_circle"]);
		RenderMesh2D(meshes["right_heart_circle"], shaders["VertexColor"], heart["right_heart_circle"]);
	}

	if (bow_gp->getLives() == 3) {
		heart = Mechanics::getHeartMatrix(HEART_LENGTH, HEART_X + 4 * HEART_LENGTH, HEART_Y);
		RenderMesh2D(meshes["heart_base"], shaders["VertexColor"], heart["heart_base"]);
		RenderMesh2D(meshes["left_heart_circle"], shaders["VertexColor"], heart["left_heart_circle"]);
		RenderMesh2D(meshes["right_heart_circle"], shaders["VertexColor"], heart["right_heart_circle"]);
	}

	bow = Mechanics::getBowMatrix(bow_gp, BOW_LENGTH, bowTranslateY, mouseX, mouseY, power / 100);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], bow["bow"]);
	RenderMesh2D(meshes["bow_string"], shaders["VertexColor"], bow["bow_string"]);
	RenderMesh2D(meshes["bow_power"], bow["bow_power"], glm::vec3(power / 100, 1 - power / 100, 0));

	if (!move_arrow) {
		arrow = Mechanics::getArrowMatrix(arrow_gp, ARROW_LENGTH, bowTranslateY, mouseX, mouseY);
		RenderMesh2D(meshes["arrow_head"], shaders["VertexColor"], arrow["arrow_head"]);
		RenderMesh2D(meshes["arrow_body"], shaders["VertexColor"], arrow["arrow_body"]);
	}
	else {
		arrow = Mechanics::getMovingArrowMatrix(arrow_gp, ARROW_LENGTH, arrowTranslateX / max(1, (int)abs(tan(arrow_gp->getAngle()))), arrow_gp->getAngle(), arrow_power);
		RenderMesh2D(meshes["arrow_head"], shaders["VertexColor"], arrow["arrow_head"]);
		RenderMesh2D(meshes["arrow_body"], shaders["VertexColor"], arrow["arrow_body"]);
	}

	for (int i = 0; i < targets; i++) {
		Mechanics::isBalloonHit(arrow_gp, balloon_gp[i], balloonType[i]);

		if (!balloon_gp[i]->isDestroyed()) {
			balloonTranslateY[i] += deltaTimeSeconds * 80;

			if (!balloonType[i]) {
				red_balloon = Mechanics::getBalloonMatrix(balloon_gp[i], BALLOON_LENGTH, balloonTranslateX[i], balloonTranslateY[i], deltaTimeSeconds, arrow_gp);
				RenderMesh2D(meshes["red_balloon_body"], shaders["VertexColor"], red_balloon["balloon_body"]);
				RenderMesh2D(meshes["red_balloon_tail"], shaders["VertexColor"], red_balloon["balloon_tail"]);
				RenderMesh2D(meshes["red_balloon_string"], shaders["VertexColor"], red_balloon["balloon_string"]);
			}
			else {
				yellow_balloon = Mechanics::getBalloonMatrix(balloon_gp[i], BALLOON_LENGTH, balloonTranslateX[i], balloonTranslateY[i], deltaTimeSeconds, arrow_gp);
				RenderMesh2D(meshes["yellow_balloon_body"], shaders["VertexColor"], yellow_balloon["balloon_body"]);
				RenderMesh2D(meshes["yellow_balloon_tail"], shaders["VertexColor"], yellow_balloon["balloon_tail"]);
				RenderMesh2D(meshes["yellow_balloon_string"], shaders["VertexColor"], yellow_balloon["balloon_string"]);
			}
		}
		else {
			balloonTranslateX[i] = rand() % (int)(WINDOWX - WINDOWX / 8) + WINDOWX / 4;
			balloonTranslateY[i] = 0;
			balloon_gp[i]->setDestroy(false);
			balloon_gp[i]->setCounted(false);
			balloon_gp[i]->setScale(1);
			balloonType[i] = rand() % 2;
		}
	}

	shurikenAngle += deltaTimeSeconds * SHURIKEN_SPEED;

	for (int i = 0; i < shurikens; i++) {
		Mechanics::isShurikenHit(arrow_gp, shuriken_gp[i], move_arrow);

		if (!shuriken_gp[i]->isDestroyed()) {
			shurikenTranslateX[i] += deltaTimeSeconds * 150 * 3;

			shuriken = Mechanics::getShurikenMatrix(shuriken_gp[i], SHURIKEN_LENGTH, WINDOWX - shurikenTranslateX[i], shurikenTranslateY[i],
													shurikenAngle, deltaTimeSeconds, arrow_gp, bow_gp);
			RenderMesh2D(meshes["shuriken_up"], shaders["VertexColor"], shuriken["shuriken_up"]);
			RenderMesh2D(meshes["shuriken_down"], shaders["VertexColor"], shuriken["shuriken_down"]);
			RenderMesh2D(meshes["shuriken_left"], shaders["VertexColor"], shuriken["shuriken_left"]);
			RenderMesh2D(meshes["shuriken_right"], shaders["VertexColor"], shuriken["shuriken_right"]);

			Mechanics::isPlayerHit(bow_gp, shuriken_gp[i]);
		}
		else {
			shurikenTranslateX[i] = 0;
			shurikenTranslateY[i] = rand() % (int)(WINDOWY - WINDOWY / 4) + WINDOWY / 8;
			shuriken_gp[i]->setDestroy(false);
			shuriken_gp[i]->setCounted(false);
			shuriken_gp[i]->setScale(1);
		}
	}
}

void Tema1::FrameEnd()
{

}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (bowTranslateY < WINDOWY / 2) {
			bowTranslateY += deltaTime * BOW_SPEED;
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (bowTranslateY > - WINDOWY / 2) {
			bowTranslateY -= deltaTime * BOW_SPEED;
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (power <= 100 && !move_arrow) {
			power += deltaTime * 80;
		}
	}
};

void Tema1::OnKeyPress(int key, int mods)
{

};

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_2 && !move_arrow) {
		arrow_power = power;
		power = 0;
		move_arrow = true;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
