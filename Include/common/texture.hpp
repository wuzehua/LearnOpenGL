#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::to_string;

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);
GLuint loadJPG(const char * imagepath);
GLuint loadTGA(const char * imagepath);

vector<string> GenCubemapList(string a, string b);

GLuint CreateTextureCubeMap(const vector<string>& paths, int& width,  int& height);

GLuint CreateTextureCubeMap_MipMap(const vector<string>& paths);

void LoadPrefilterEnvMap(int width, int height, GLuint envID, string basePath);

#endif