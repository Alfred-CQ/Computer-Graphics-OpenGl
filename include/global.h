#ifndef _GLOBAL_H_
	#define _GLOBAL_H_
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>

		#include <iostream>
		#include <vector>
		
		#include "vectors.h"

		/* Typedefs */
		typedef unsigned int uint;

		/* Callbacks */
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}

#endif