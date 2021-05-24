#define _USE_MATH_DEFINES
#include <math.h>
#include "sphere.h"

Sphere::Sphere(glm::vec3 pos, int r, int res)
{
	position = pos;
	radius = r;
	nbSectors = res;
	nbStacks = res / 2;
	vertices = std::vector<float>();
	indices = std::vector<unsigned int>();

	computeVertices();
}

void Sphere::computeVertices()
{
	float x, y, z, xy;
	
	float sectorStep = 2 * M_PI / nbSectors;
	float stackStep = M_PI / nbStacks;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= nbStacks; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= nbSectors; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			vertices.push_back(x + position.x);
			vertices.push_back(y + position.y);
			vertices.push_back(z + position.z);
		}
	}

	unsigned int k1, k2;

	for (int i = 0; i < nbStacks; ++i)
	{
		k1 = i * (nbSectors + 1);
		k2 = k1 + nbSectors + 1;

		for (int j = 0; j < nbSectors; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (nbStacks - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}

std::vector<float> Sphere::getVertices()
{
	return vertices;
}

std::vector<unsigned int> Sphere::getIndices()
{
	return indices;
}
