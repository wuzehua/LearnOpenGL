#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/text2D.hpp>

#include <common/model.hpp>


#include <iostream>

#include <vector>


#include "Include/shader.h"







GLFWwindow* createWindow(char* title, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

int main(int argc, char** argv) {

    static const GLfloat g_vertex_buffer_data[] =
            {-0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

    char* title = (char *) "Demo";

    auto window = createWindow(title, SRC_WIDTH, SRC_HEIGHT);

    if(window == nullptr)
    {
        return -1;
    }



    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);


    // Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    mat4 View = lookAt(
            vec3(0, 0, 5), // Camera is at (4,3,-3), in World Space
            vec3(0, 0, 0), // and looks at the origin
            vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    mat4 Model = mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    mat4 MVP = Projection * View * Model;

    Mesh ninjaHead("ninjaHead.obj");
    vector<vec3> colors(ninjaHead.vertex_size);
    for(auto &color: colors)
    {
        color.r = 0.7f;
        color.g = 0.8f;
        color.b = 0.6f;
    }

    ninjaHead.setAtrribute(Color, (void*)&colors[0], (unsigned int) (colors.size() * sizeof(vec3)));

    //用于标示我们的顶点缓冲
//    GLuint vertextBuffer;
//    glGenBuffers(1, &vertextBuffer);//生成一个缓冲区，并将该缓冲区的标识给vertexBuffer
//    glBindBuffer(GL_ARRAY_BUFFER, vertextBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);//将顶点传给OpenGL

    Shader shader("shader/vertexshader.glsl", "shader/fragmentshader.glsl");



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMatrix4("matrix", MVP);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, ninjaHead.pos_id);
        glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, ninjaHead.color_id);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // Draw the triangle !

        glDrawArrays(GL_TRIANGLES, 0, ninjaHead.vertex_size); // 12*3 indices starting at 0 -> 12 triangles

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;

}

GLFWwindow* createWindow(char* title, int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //不用老版本的OpenGL





    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif



    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if(window == nullptr)
    {
        std::cout<<"Create window fail"<<std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        std::cout<<"Fail to initialize glew"<<std::endl;
        return nullptr;
    }

    return window;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE)
    {
        glfwSetWindowShouldClose(window, true);
    }
}