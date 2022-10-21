#ifndef _CONFIG_H_
	#define _CONFIG_H_
	
		/* Vertex Shaders */
		#define VERTEXSHADER "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\vShader.vs"

		/* Fragment Shaders */
		#define starFRAGMENTSHADER  "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\starFShader.fs"
		// House
		#define houseFRAGMENTSHADER "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\houseFShader.fs"
		// Pizza
		#define pizzaFRAGMENTSHADER "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\pizzaFShader.fs"

		/* Window */
		#define WINDOW_WIDTH 700
		#define WINDOW_HEIGHT 600
		#define TITLE "Alfred Chillitupa Quispihuanca"

		/* Classes */
		#include "shader.h"
		#include "star.h"
		#include "house.h"
		#include "pizza.h"

		/* GLM */
		#include <glm/glm.hpp>
		#include <glm/gtc/matrix_transform.hpp>
		#include <glm/gtc/type_ptr.hpp>

#endif
