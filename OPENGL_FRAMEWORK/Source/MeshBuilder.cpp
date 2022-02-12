#include "MeshBuilder.h"

Mesh* MeshBuilder::GenerateQuad(const std::string& meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal = Eigen::Vector3f(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal = Eigen::Vector3f(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal = Eigen::Vector3f(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal = Eigen::Vector3f(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);

	Mesh* mesh = new Mesh(meshName);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	//select VAO
	glBindVertexArray(mesh->VertaxArrayObjectID);
	//select vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // color
	glEnableVertexAttribArray(2); // normals
	if (mesh->textureID > 0)
	{
		glEnableVertexAttribArray(3);
	}

	//set buffer structure id,amt of points,type,normalize,vertex size,stride
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position)); //color 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color))); //normals

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (mesh->textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	//unselect VAO
	glBindVertexArray(0);
	//unselect vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	if(mesh)
		return mesh;
    return nullptr;
}
