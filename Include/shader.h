#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
	
	

	//着色器构造器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//激活、使用着色程序
	void use();

	//设置uniform
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void set4Int(const std::string &name, int valueX, int valueY, int valueZ, int valueW) const;
	void set4Float(const std::string &name, float valueX, float valueY, float valueZ, float valueW) const;

	void setMatrix4(const std::string& name, glm::mat4& mat);

private:
	//着色器程序ID
	unsigned int programID;

};



#endif // !SHADER_H

