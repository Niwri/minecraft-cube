#pragma once

#include "../graphic/camera.h"
#include <GLFW/glfw3.h>



class MouseInputController {

	public:
		// Controls camera rotation via x and y movement
		void cameraControl(Camera* camera, GLFWwindow* window, int width, int height);
		
};
