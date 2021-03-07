#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	// Creeaza o primitiva geometrica cu parametrii specificat fiind centrata pe coltul din stanga jos
	Mesh* CreateTriangle(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateLine(std::string name, glm::vec3 leftStartPoint, float length, glm::vec3 color);
	Mesh* CreateCircle(std::string name, glm::vec3 circleOrigin, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircleArc(std::string name, glm::vec3 circleOrigin, float length, glm::vec3 color);
	Mesh* CreatePolyline(std::string name, glm::vec3 leftStartPoint, float length, int points, glm::vec3 color);

	// Creeaza un mesh
	Mesh* CreateMesh(Mesh *mesh, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
}

