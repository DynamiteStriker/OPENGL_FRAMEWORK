#include "Mesh.h"

Mesh::Mesh(const std::string& meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
	, textureID(0)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glGenVertexArrays(1, &VertaxArrayObjectID);


	//TODO put ALL this in meshabuilder

	
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1,&VertaxArrayObjectID);

	if (textureID > 0)
		glDeleteTextures(1, &textureID);
}

void Mesh::Render()
{



	//select the mesh vao
	glBindVertexArray(VertaxArrayObjectID);
	//select indexBuffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);




	//enable all the attributes
	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // color
	glEnableVertexAttribArray(2); // normals

	if (textureID > 0)
	{// if there is a texture enable texCoord pointer
		glEnableVertexAttribArray(3); // texcoord
	}

	//Draw mesh according to mode selected
	if (mode == DRAW_LINES)
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);



	//deselect the mesh vao
	glBindVertexArray(0);
	//deselect indexBuffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//disable all the enableed attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}

}

