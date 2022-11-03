#ifndef _CUBE_H_
	#define _CUBE_H_
		
		#include "../include/picture.h"
		#include "square.h"

		class Cube : public Picture
		{
			public:

				/* Constructors */
				Cube			(float radius, Point<3> center, vector<COLOUR> face_colours);

				/* Variables */
				float			c_radius;
				const uint		c_nfaces   = 6;
				Point<3>		c_center  = {0, 0, 0};
				vector<COLOUR>	c_face_colours;
				VERTEXES		c_centers;
				vector<Square>	c_faces;

				/* Methods */
				// Setters

				// Getters
				void get_Vertexes();
				void get_Idx_Lines();
				void get_Idx_Triangles();
				void get_Local_Transformation(int current_transform);

				// Binders
				void bind_Transform(bool& enable, int current_transform);

				// Senders
				void send_VShader_Transform();

			private:
				
		};

		Cube::Cube(float radius, Point<3> center, vector<COLOUR> face_colours)
		{
			c_radius		= radius;
			c_center		= center;
			c_face_colours	= face_colours;
			

			get_Vertexes();
			get_Idx_Triangles();

			bind_Buffers();
			bind(colors, 1);
		}

		void Cube::get_Vertexes()
		{
			c_centers = 
			{
				c_center, c_center - Point<3>(0, 0, c_radius*2),
			};

			size_t first = 0, second = 1;
			for (size_t i = 0; i < c_nfaces; ++i)
			{
				if (i < 2)
					c_faces.push_back(Square(c_radius, c_centers[i], c_face_colours[i]));
				else
				{
					c_faces.push_back(Square(c_faces[0].s_vertexes[first], c_faces[0].s_vertexes[second],
											 c_faces[1].s_vertexes[first], c_faces[1].s_vertexes[second], c_face_colours[i]));
					first = second; second = (second + 1) % 4;
					
					c_centers.push_back(c_faces[i].s_center);
				}
			}
				
			for (size_t i = 0; i < c_faces.size(); ++i)
			{
				vertexes.insert(end(vertexes), begin(c_faces[i].s_vertexes), end(c_faces[i].s_vertexes));
				colors.insert(end(colors), begin(c_faces[i].s_colours), end(c_faces[i].s_colours));
				texture.insert(end(texture), begin(c_faces[i].s_textures), end(c_faces[i].s_textures));
			}
		
			size_vertexes = vertexes.size();
			
			std::cout << size_vertexes << "\n";

		}

		void Cube::get_Idx_Lines()
		{
			std::cout << "No Lines Idx\n";
		}

		void Cube::get_Idx_Triangles()
		{
			idx_triangles =
			{
				0, 1, 2,
				2, 3, 0,
			};

			for (size_t i = 0, window = 0; i < (c_nfaces - 1) * 2; ++i)
			{
				for (size_t j = 0; j < 3; ++j)
					idx_triangles.push_back(idx_triangles[window + j] + 4);

				window += 3;
			}

			size_idx_triangles = idx_triangles.size();
		}

		void Cube::get_Local_Transformation(int current_transform)
		{
		
		}

		void Cube::bind_Transform(bool& enable, int current_transform)
		{

		}

		void Cube::send_VShader_Transform()
		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));
			projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

			shader->setMat4("model", model);
			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
		}

#endif