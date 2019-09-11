#include "../Include/shader.h"

//构造器
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	//保证文件流能抛出异常
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		//通过文件路径打开文件
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		//数据流，用于存储读取的GLSL代码
		std::stringstream vertexShaderStream, fragmentShaderStream;

		// 读取文件的缓冲内容到数据流中
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		//关闭文件
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//将数据流中数据转换为字符串
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();

	}

	catch (std::ifstream::failure e) 
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	//将所得字符串转化为c的char*？
	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	int success;
	char log[512];

	unsigned int vertexShader;
	unsigned int fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	}


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,&success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, log);
		std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << log << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


//使用、激活着色器程序
void Shader:: use() 
{
	glUseProgram(programID);
}


//设置uniform值（bool）
void Shader::setBool(const std::string &name, bool value) const 
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform1f(location, value);
}

void Shader::set4Int(const std::string &name, int valueX, int valueY, int valueZ, int valueW) const
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform4i(location, valueX,valueY,valueZ,valueW);
}

void Shader::set4Float(const std::string &name, float valueX, float valueY, float valueZ, float valueW) const
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform4f(location, valueX, valueY, valueZ, valueW);
}


void Shader::setMatrix4(const std::string& name, glm::mat4& mat)
{
	unsigned int location = glGetUniformLocation(programID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}