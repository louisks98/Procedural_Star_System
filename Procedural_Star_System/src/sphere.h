#pragma once
#include <glm/glm.hpp>
#include <vector>

class Sphere
{
public:
	Sphere(glm::vec3 pos, int r, int res);

	void draw();

private:

	void computeVertices();

	glm::vec3 position;
	int radius;
	int nbSectors;
	int nbStacks;
	std::vector<float> vertices;
	std::vector<float> indices;
};
