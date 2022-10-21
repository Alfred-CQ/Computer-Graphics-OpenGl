#ifndef _GLOBAL_H_
	#define _GLOBAL_H_
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>

		#include <iostream>
		#include <vector>
		
		#include "math_entities.h"

		/* External Libraries */
		#define STB_IMAGE_IMPLEMENTATION
		#include "../stb_image.h"

		/* Usings */
		using std::vector;

		/* Defines */
		#define F_PI 3.14159265358979323846f
		
		#define DOWN  Vector<3>(0, -0.0001, 0)
		#define UP    Vector<3>(0, 0.0001, 0)
		#define LEFT  Vector<3>(-0.0001, 0, 0)
		#define RIGHT Vector<3>(0.0001, 0, 0)

		// config
		#define NUMBER_FIGURES 3

		/* Typedefs */
		typedef unsigned int uint;

		/* Globals */
			// Environment
			std::string root_path = "..\\..\\..\\..\\..\\src\\Tutorial_01\\";
			// Default Vertex Colors
			vector<float> vertex_colors = { 1.0f, 0.9019f, 0.5058f, 1.0f };
		
		// Program
		int primitive = GL_POINTS;
		uint current_picture = 0;
		float star_speed = 1.0f, house_speed = 1.0f, pizza_speed = 1.0f;

		/* Callbacks */
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
				current_picture = (current_picture + 1) % NUMBER_FIGURES;
			
			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
				primitive = GL_POINTS;
			
			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
				primitive = GL_LINE_LOOP;
			
			if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
				primitive = GL_TRIANGLES;


			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}
		
		/* Utility Functions */
		float get_distance(Point<3> A, Point<3> B)
		{
			return sqrt((B.p_x - A.p_x)*(B.p_x - A.p_x) + (B.p_y - A.p_y)* (B.p_y - A.p_y));
		}

#endif
