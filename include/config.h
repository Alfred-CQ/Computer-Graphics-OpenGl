#ifndef _CONFIG_H_
	#define _CONFIG_H_
	
		/* Render */
		#define NUMBER_FIGURES 3
		#define NUMBER_TRANFORMATIONS 7

		/* Vertex Shaders */
		#define VERTEXSHADER        "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\vShader.vs"

		/* Fragment Shaders */
		// Cube
		#define cubeFRAGMENTSHADER  "..\\..\\..\\..\\..\\src\\Tutorial_01\\shaders\\cubeFShader.fs"

		/* Window */
		#define WINDOW_WIDTH    700
		#define WINDOW_HEIGHT   600
        #define WINDOW_ASPECT   float(WINDOW_WIDTH/WINDOW_HEIGHT)
		#define TITLE           "Alfred Chillitupa Quispihuanca"

		/* Classes */
		#include "shader.h"
		
		#include "../rubik/rubik.h"

#endif
