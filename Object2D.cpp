#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = bottomLeftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), // stanga jos
		VertexFormat(corner + glm::vec3(length, 0, 0), color), // dreapta jos
		VertexFormat(corner + glm::vec3(length, length, 0), color), // dreapta sus
		VertexFormat(corner + glm::vec3(0, length, 0), color) // stanga sus
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	return CreateMesh(square, vertices, indices);
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = bottomLeftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), // baza stanga
		VertexFormat(corner + glm::vec3(length, 0,  0), color), // baza dreapta
		VertexFormat(corner + glm::vec3(length / 2, length,  0), color)  // varf 
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}

	return CreateMesh(triangle, vertices, indices);
}

Mesh* Object2D::CreateLine(std::string name, glm::vec3 leftStartPoint, float length, glm::vec3 color) {
	glm::vec3 corner = leftStartPoint;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), // punct stanga
		VertexFormat(corner + glm::vec3(length, 0,  0), color), // punct dreapta
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1};

	line->SetDrawMode(GL_LINES);

	return CreateMesh(line, vertices, indices);
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 circleOrigin, float length, glm::vec3 color, bool fill) {
	glm::vec3 origin = circleOrigin;

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};
	
	for (int i = 0; i < 360; i++) {
		vertices.push_back(VertexFormat(origin + glm::vec3(cos(RADIANS(i))*length, sin(RADIANS(i))*length, 0), color));
		indices.push_back(i);
	}

	Mesh* circle = new Mesh(name);

	// adauga si full circle colorat cu triangle ceva
	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		circle->SetDrawMode(GL_TRIANGLE_FAN);
	}
	

	return CreateMesh(circle, vertices, indices);
}

Mesh* Object2D::CreateCircleArc(std::string name, glm::vec3 circleOrigin, float length, glm::vec3 color) {
	glm::vec3 origin = circleOrigin;

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	for (int i = 0; i <= 180; i++) {
		vertices.push_back(VertexFormat(origin + glm::vec3(cos(RADIANS(i)) * length, sin(RADIANS(i)) * length, 0), color));
		indices.push_back(i);
	}

	Mesh* circle = new Mesh(name);

	circle->SetDrawMode(GL_LINE_STRIP);

	return CreateMesh(circle, vertices, indices);
}

Mesh* Object2D::CreatePolyline(std::string name, glm::vec3 leftStartPoint, float length, int points, glm::vec3 color) {
	double PI = 2*acos(0.0);
	double segment = length / points;

	glm::vec3 corner = leftStartPoint;

	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};

	for (int i = 0; i <= points; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3(segment * i, sin(((double)i + 1) * PI/2) * segment, 0), color)); // PI/4 are efect mai smooth
		indices.push_back(i);
	}

	Mesh* polyline = new Mesh(name);

	polyline->SetDrawMode(GL_LINE_STRIP);

	return CreateMesh(polyline, vertices, indices);
}

Mesh* Object2D::CreateMesh(Mesh *mesh, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices) {
	// VAO
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// IBO
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return mesh;
}