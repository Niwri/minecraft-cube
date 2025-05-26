#include "camera.h"

using namespace glm;

Camera::Camera() {
    this->velocity = 1.0f;
    this->sensitivity = 0.1f;
    this->aspectRatio = 1.0f;
    this->orientation = vec3(0.0f, 0.0f, -1.0f);
    this->position = vec3(0.0f, 0.0f, 0.0f);
    this->up = vec3(0.0f, 1.0f, 0.0f);
    this->setFOV(45.0f, 0.1f, 10.0f);
}

Camera::Camera(float velocity, float sensitivity, vec3 position, vec3 orientation, float aspectRatio): 
    velocity(velocity),
    sensitivity(sensitivity),
    aspectRatio(aspectRatio),
    position(position),
    orientation(orientation) {
    this->up = vec3(0.0f, 1.0f, 0.0f);
    this->setFOV(45.0f, 0.1f, 10.0f);
}

void Camera::setVelocity(float velocity) { this->velocity = velocity; }
void Camera::setOrientation(vec3 orientation) { this->orientation = orientation; }
void Camera::setSensitivity(float sensitivity) { this->sensitivity = sensitivity; }
void Camera::setPosition(vec3 position) { this->position = position; }
void Camera::setPositionX(float x) { this->position.x = x; }
void Camera::setPositionY(float y) { this->position.y = y; }
void Camera::setPositionZ(float z) { this->position.z = z; }
void Camera::setShaderID(GLuint ID) { this->shaderID = ID; }
void Camera::setAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; }

float Camera::getVelocity() { return velocity; }
float Camera::getSensitivity() { return sensitivity; }

float Camera::getPositionX() { return position.x; }
float Camera::getPositionY() { return position.y; }
float Camera::getPositionZ() { return position.z; }
vec3 Camera::getPosition() { return position; }

vec3 Camera::getOrientation() { return orientation; }
vec3 Camera::getUp() { return up; }

void Camera::updateRender() {
    mat4 view = mat4(1.0f);
	
	view = lookAt(this->position, this->position + this->orientation, this->up);
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "view"), 1, GL_FALSE, value_ptr(view));

}

void Camera::setFOV(float FOVdeg, float nearPlane, float farPlane) {
    mat4 proj = perspective(
        radians(FOVdeg),  
        this->aspectRatio,
        nearPlane,  
        farPlane      
    );
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "proj"), 1, GL_FALSE, value_ptr(proj));
}