#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Camera {

	private:
		float velocity;
		float sensitivity;

        float aspectRatio;

		vec3 position;
		vec3 orientation;
		vec3 up;

		GLuint shaderID;

	public:
		
		// Initialize private variable values
		Camera();

        Camera(float velocity, float sensitivity, vec3 position, vec3 orientation, float aspectRatio);

		void updateRender();

		// Setters
		void setVelocity(float velocity);

		void setSensitivity(float sensitivity);

		void setOrientation(vec3 orientation);

		void setShaderID(GLuint ID);

		void setPosition(vec3 position); 
		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);
        
        void setAspectRatio(float aspectRatio);

		void setFOV(float FOVdeg, float nearPlane, float farPlane);

		// Getters
		float getVelocity();
		float getSensitivity();

		float getPositionX();
		float getPositionY();
		float getPositionZ();

		vec3 getOrientation();
		vec3 getUp();
		vec3 getPosition();
};