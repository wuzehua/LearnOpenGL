#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <glad/glad.h>

enum AttributeSem
{
	Pos = 0x0,
	Color = 0x1,
	Uv = 0x2,
	Normal = 0x3,
	BiTangent = 0x4,
	Tangent = 0x5,
	Index = 0x6,

	Diffuse = 0x7,
	Normal_Map = 0x8,
	Displace = 0x9,
	Roughness = 0x10,
	Metallic = 0x11
};


#define  delete_id(x) \
if ((x) != 0) glDeleteBuffers(1,&(x));

#define  delete_texture(x) \
if ((x != 0)) glDeleteTextures(1, &(x));

struct Mesh
{
	GLuint pos_id;
	GLuint uv_id;
	GLuint normal_id;
	GLuint binormal_id;
	GLuint tangent_id;
	GLuint color_id;
	
	GLuint index_id;


	GLuint diffuse_texture_id;
	GLuint displace_texture_id;
	GLuint normal_texture_id;
	GLuint roughness_texture_id;
	GLuint metallic_texture_id;


	int vertex_size;
	int face_size;

	Mesh() :pos_id(0), uv_id(0), normal_id(0), binormal_id(0), tangent_id(0), color_id(0), index_id(0),displace_texture_id(0),diffuse_texture_id(0),
	normal_texture_id(0){}

	Mesh(const std::string & file_name, bool tangent = false);

	void setAtrribute(AttributeSem sem,void * data, unsigned int size);

	void LoadTexture(AttributeSem sem, const std::string  & file_name);

	~Mesh()
	{
		delete_id(pos_id);
		delete_id(color_id);
		delete_id(uv_id);
		delete_id(normal_id);
		delete_id(binormal_id);
		delete_id(tangent_id);
		delete_id(index_id);

		delete_texture(diffuse_texture_id);
		delete_texture(displace_texture_id);
		delete_texture(normal_texture_id);


	}

};

#endif