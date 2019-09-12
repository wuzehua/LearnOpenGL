#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getPosition();
glm::vec3 getViewDir();
float getRoughness();
void setPosition(glm::vec3 pos);
void setViewDir(glm::vec3 dir);




#endif