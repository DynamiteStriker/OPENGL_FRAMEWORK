#ifndef _MESH_H
#define _MESH_H

#include <string>
#include "GL\glew.h"
#include "Vertex.h"

class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string& meshName);
	~Mesh();
	void Render();

	const std::string name;
	DRAW_MODE mode; // mode in which opengl draws
	unsigned int VertaxArrayObjectID;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int indexSize;
	unsigned int textureID;

};


#endif
