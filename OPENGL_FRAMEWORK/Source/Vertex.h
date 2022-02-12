#ifndef _VERTEX_H
#define _VERTEX_H

#include <Eigen/Dense>

struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

struct Color
{
	float r, g, b, a;
	Color(float r = 1, float g = 1, float b = 1, float a = 1) { Set(r, g, b,a); }
	void Set(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
};

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};

struct Vertex
{
	Position pos;
	Color color;
	Eigen::Vector3f normal;
	TexCoord texCoord;
	Vertex() {}
};

#endif