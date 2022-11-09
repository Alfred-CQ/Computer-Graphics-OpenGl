#ifndef _GLOBAL_H_
	#define _GLOBAL_H_
		
	   /* Libraries */
		// Glad
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>

		// Glm
		#include <glm/glm.hpp>
		#include <glm/gtc/matrix_transform.hpp>
		#include <glm/gtc/type_ptr.hpp>

		// Stl
		#include <iostream>
		#include <vector>

		// Externals
		#define STB_IMAGE_IMPLEMENTATION
		#include "../stb_image.h"

		// AMZ
		#include "math_entities.h"

	   /* Usings namespaces */
		using std::vector;
		using std::map;
		using std::begin;
		using std::end;

	   /* Typedefs */
		typedef unsigned int uint;
		typedef map<std::string, vector<float>> COLOUR;
		typedef vector<Point<3>>				VERTEXES;
		typedef vector<float>					VERTEX_COLOURS;
		typedef vector<float>					VERTEX_TEXTURES;
		
		#define BLUE	COLOUR{{"blue"  ,{0.1882f, 0.6588f, 0.9568f}}}
		#define RED		COLOUR{{"red"   ,{0.9960f, 0.3529f, 0.3490f}}}
		#define YELLOW	COLOUR{{"yellow",{1.0000f, 0.9921f, 0.3254f}}}
		#define ORANGE	COLOUR{{"orange",{1.0000f, 0.4862f, 0.2745f}}}
		#define GREEN	COLOUR{{"green" ,{0.5372f, 0.9490f, 0.4431f}}}
		#define WHITE	COLOUR{{"white" ,{0.9411f, 0.9254f, 0.9529f}}}
		#define BLACK	COLOUR{{"black" ,{0.1215f, 0.1254f, 0.1254f}}}
		typedef Point<3>     POINT3;
		typedef Vector<3>	 VECT3;
		typedef Matrix<4,4>  MATRIX4;		

		/* Defines */
		constexpr auto F_PI = 3.14159265358979323846f;
		
		#define DOWN  VECT3(0, -0.0001, 0)
		#define UP    VECT3(0, 0.0001, 0)
		#define LEFT  VECT3(-0.0001, 0, 0)
		#define RIGHT VECT3(0.0001, 0, 0)

		/* Main Program */
		std::string root_path		= "..\\..\\..\\..\\..\\src\\Tutorial_01\\";
		std::vector<float> v_colors = { 1.0f, 0.9019f, 0.5058f, 1.0f };

		int primitive				= GL_POINTS;
		uint current_picture		= 0;

		int current_transform		= -1;
		bool enable_transformation	= false;

		/* Callbacks */
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
				current_picture = (current_picture + 1) % NUMBER_FIGURES;

			if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
			{
				current_transform = (current_transform + 1) % NUMBER_TRANFORMATIONS;
				enable_transformation = true;
			}
			
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
		float get_distance(POINT3 A, POINT3 B)
		{
			return sqrt((B.p_x - A.p_x)*(B.p_x - A.p_x) + (B.p_y - A.p_y)* (B.p_y - A.p_y));
		}

#endif
