#include "model.hpp"
#include "text2D.hpp"
#include "texture.hpp"
#include <vector>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/tangentspace.hpp>

#include <glm/glm.hpp>


Mesh::Mesh(const std::string & file_name, bool tangent /*= false*/) :Mesh()
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	glm::vec3 _max,_min;
	bool res = loadOBJ(file_name.c_str(), vertices, uvs, normals,_max,_min);
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<unsigned short> indices;
	if (tangent == true)
	{

		computeTangentBasis(
			vertices, uvs, normals, // input
			tangents, bitangents    // output
			);
		std::vector<glm::vec3> indexed_vertices;
		std::vector<glm::vec2> indexed_uvs;
		std::vector<glm::vec3> indexed_normals;
		std::vector<glm::vec3> indexed_tangents;
		std::vector<glm::vec3> indexed_bitangents;
		indexVBO_TBN(
			vertices, uvs, normals, tangents, bitangents,
			indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
			);
		vertices.swap(indexed_vertices);
		uvs.swap(indexed_uvs);
		normals.swap(indexed_normals);
		tangents.swap(indexed_tangents);
		bitangents.swap(indexed_bitangents);
	}

	vertex_size = vertices.size();
	
	if (vertices.size() != 0)
	{
		setAtrribute(Pos, &vertices[0], vertices.size() * sizeof(glm::vec3));
	}
	if (uvs.size() != 0)
	{
		setAtrribute(Uv, &uvs[0], uvs.size() * sizeof(glm::vec2));
	}
	if (normals.size() != 0)
	{
		setAtrribute(Normal, &normals[0], normals.size() * sizeof(glm::vec3));
	}

	if (tangents.size() != 0)
	{
		setAtrribute(Tangent, &tangents[0], tangents.size() * sizeof(glm::vec3));
	}

	if (bitangents.size() != 0)
	{
		setAtrribute(BiTangent, &bitangents[0], bitangents.size() * sizeof(glm::vec3));
	}

	if (indices.size() != 0)
	{
		setAtrribute(Index, &indices[0], indices.size() * sizeof(unsigned short));
		face_size = indices.size() / 3;
	}
	else
	{
		face_size = vertex_size / 3;
	}



}

void Mesh::setAtrribute(AttributeSem sem, void * data, unsigned int size)
{
	
	GLuint vertex_buffer = 0;
	glGenBuffers(1, &vertex_buffer);
	GLenum buffer_type;
	switch (sem)
	{
	case Pos:
		pos_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case Color:
		color_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case Uv:
		uv_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case Normal:
		normal_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case BiTangent:
		binormal_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case Tangent:
		tangent_id = vertex_buffer;
		buffer_type = GL_ARRAY_BUFFER;
		break;
	case Index:
		index_id = vertex_buffer;
		buffer_type = GL_ELEMENT_ARRAY_BUFFER;
		break;
	}
	glBindBuffer(buffer_type, vertex_buffer);
	glBufferData(buffer_type, size, data, GL_STATIC_DRAW);

}

void Mesh::LoadTexture(AttributeSem sem, const std::string & file_name)
{
	std::string file_type = file_name.substr(file_name.find_last_of('.')+1);
	GLuint texture_id = 0;
	if (file_type == "BMP" || file_type == "bmp")
		texture_id = loadBMP_custom(file_name.c_str());
	else if (file_type == "DDS" || file_type == "dds")
	{
		texture_id = loadDDS(file_name.c_str());
	}
	else if (file_type == "jpg" || file_type == "png")
	{
		texture_id = loadJPG(file_name.c_str());
	}
	else if(file_type == "tga")
		texture_id = loadTGA(file_name.c_str());
	
	switch (sem)
	{

	case Diffuse:
		diffuse_texture_id = texture_id;
		break;
	case Normal_Map:
		normal_texture_id = texture_id;
		break;
	case Displace:
		displace_texture_id = texture_id;
		break;
	case Roughness:
		roughness_texture_id = texture_id;
	case Metallic:
		metallic_texture_id = texture_id;
	default:
		break;
	}

}
