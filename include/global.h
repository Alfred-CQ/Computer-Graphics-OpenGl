#ifndef _GLOBAL_H_
	#define _GLOBAL_H_
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>

		#include <iostream>
		#include <vector>
		
		#include "vectors.h"

		/* Usings */
		using std::vector;

		/* Defines */
		#define F_PI 3.14159265358979323846

		/* Globals */
		int primitive = GL_POINTS;

		/* Typedefs */
		typedef unsigned int uint;

		/* Callbacks */
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
				primitive = GL_LINE_LOOP;

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}

#endif
