#ifndef _PICTURE_H_
	#define _PICTURE_H_
		
		#include "global.h"
		#include "openglmanager.h"
		#include "math_entities.h"

		class Picture 
		{
			public:
				
				vector<Point<3>> vertexes;
				vector<uint> idx_lines;
				vector<uint> idx_triangles;
				
				size_t size_vertexes, size_idx_lines, size_idx_triangles;

				// OpenGL Variables
				uint VAO, VBO, EBO;
				
				Picture();
				~Picture();

				// Setters

				// Getters
				virtual void get_Vertexes() = 0;
				virtual void get_Idx_Lines() = 0;
				virtual void get_Idx_Triangles() = 0;

				// Core
				void draw(int primitive);

			protected:

				// Binds
				void bind_Buffers();

			private:			
				
				float location_x, location_y;
		};

		Picture::Picture() 
		{
			
		}

		Picture::~Picture()
		{
			glDeleteVertexArrays(1, &(this->VAO));
			glDeleteBuffers(1, &(this->VBO));
			glDeleteBuffers(1, &(this->EBO));
		}

		void Picture::draw(int primitive)
		{
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			
			if (primitive == GL_TRIANGLES)
				glDrawElements(GL_TRIANGLES, size_idx_triangles, GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(primitive, 0, this->size_vertexes - 1);
		}

		void Picture::bind_Buffers()
		{
			glGenVertexArrays(1, &(this->VAO));
			glGenBuffers(1, &(this->VBO));
			glGenBuffers(1, &(this->EBO));

			glBindVertexArray(this->VAO);

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->size_vertexes * 3 * sizeof(this->vertexes), &(this->vertexes.front()), GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->size_idx_triangles * sizeof(this->idx_triangles), &(this->idx_triangles.front()), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(0);
		}

#endif
