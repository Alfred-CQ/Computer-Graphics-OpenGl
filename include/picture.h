#ifndef _PICTURE_H_
	#define _PICTURE_H_
		
		#include "global.h"

		class Picture 
		{
			public:
				
				vector<float> vertexes;
				vector<uint> idx_lines;
				vector<uint> idx_triangles;
				
				size_t size_vertexes, size_idx_lines, size_idx_triangles;
				
				Picture();
				// Setters
				// Getters
				virtual void get_Vertexes() = 0;
				virtual void get_Idx_Lines() = 0;
				virtual void get_Idx_Triangles() = 0;

			private:			
				
				float location_x, location_y;
		};

		Picture::Picture() 
		{
			std::cout << "Hola" << std::endl;
		}

#endif
