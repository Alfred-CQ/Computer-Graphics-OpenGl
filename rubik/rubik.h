#ifndef _RUBIK_H_
	#define _RUBIK_H_

		#include "../include/picture.h"
		#include "cube.h"

		class Rubik : public Picture
		{
			public:
			   /* Constructors and Destructor */
				Rubik(float radius, float separation);

			   /* Variables */
				float			r_radius;
				float			r_separation_cubes, r_separation_p, r_separation_n;
				const uint		r_ncubes = 27;
				Point<3>		r_center = { 0, 0, 0 };
				vector<COLOUR>	r_face_colours;
				VERTEXES		r_centers;

				vector<Cube*>	r_wheel_1;
				vector<Cube*>	r_wheel_2;
				vector<Cube*>	r_wheel_3;

			   /* Methods */
			   // Setters

			   // Getters
				void get_Vertexes();
				void get_Idx_Lines();
				void get_Idx_Triangles();
				void get_Local_Transformation(int current_transform);

				void get_Wheel(vector<Cube*>& r_wheel, float z_index, COLOUR near_face, COLOUR far_face);

			   // Binders
				void bind_Transform(bool& enable, int current_transform);

			   // Senders
				void send_VShader_Transform();
				
			private:
				
		};

		Rubik::Rubik(float radius, float separation_cubes)
		{
			r_radius		   = radius;
			r_separation_cubes = separation_cubes;
			r_separation_p	   = (radius * 2) + separation_cubes;
			r_separation_n	   = -1.0f * r_separation_p;

			get_Vertexes();
			get_Idx_Triangles();

			bind_Buffers();
			bind(colors, 1);
		}

		void Rubik::get_Vertexes()
		{
			get_Wheel(r_wheel_1, 0.0f, BLUE, BLACK);
			for (size_t i = 0; i < r_wheel_1.size(); i++)
			{
				vertexes.insert(end(vertexes), begin((*r_wheel_1[i]).c_vertexes), end((*r_wheel_1[i]).c_vertexes));
				colors.insert(end(colors), begin((*r_wheel_1[i]).c_colours), end((*r_wheel_1[i]).c_colours));
				texture.insert(end(texture), begin((*r_wheel_1[i]).c_textures), end((*r_wheel_1[i]).c_textures));
			}

			get_Wheel(r_wheel_2, r_separation_n, BLACK, BLACK);
			for (size_t i = 0; i < r_wheel_2.size(); i++)
			{
				vertexes.insert(end(vertexes), begin((*r_wheel_2[i]).c_vertexes), end((*r_wheel_2[i]).c_vertexes));
				colors.insert(end(colors), begin((*r_wheel_2[i]).c_colours), end((*r_wheel_2[i]).c_colours));
				texture.insert(end(texture), begin((*r_wheel_2[i]).c_textures), end((*r_wheel_2[i]).c_textures));
			}
			
			get_Wheel(r_wheel_3, r_separation_n * 2.0f, BLACK, GREEN);
			for (size_t i = 0; i < r_wheel_3.size(); i++)
			{
				vertexes.insert(end(vertexes), begin((*r_wheel_3[i]).c_vertexes), end((*r_wheel_3[i]).c_vertexes));
				colors.insert(end(colors), begin((*r_wheel_3[i]).c_colours), end((*r_wheel_3[i]).c_colours));
				texture.insert(end(texture), begin((*r_wheel_3[i]).c_textures), end((*r_wheel_3[i]).c_textures));
			}

			size_vertexes = vertexes.size();

			std::cout << "RUBIK VERTEXES POS: " << size_vertexes << "\n";

		}

		void Rubik::get_Idx_Lines()
		{
			
		}

		void Rubik::get_Idx_Triangles()
		{
			idx_triangles =
			{
				0, 1, 2,
				2, 3, 0,
			};

			for (size_t i = 0, window = 0; i < (10 + (r_ncubes*12)); ++i)
			{
				for (size_t j = 0; j < 3; ++j)
					idx_triangles.push_back(idx_triangles[window + j] + 4);

				window += 3;
			}

			size_idx_triangles = idx_triangles.size();
		}

		void Rubik::get_Local_Transformation(int current_transform)
		{

		}

		void Rubik::get_Wheel(vector<Cube*>& r_wheel, float z_index, COLOUR near_face, COLOUR far_face)
		{
			r_wheel =
			{
				new Cube(r_radius, {			  0,		      0, z_index }, { near_face, far_face,  BLACK, BLACK, BLACK,  BLACK }),
				new Cube(r_radius, {			  0, r_separation_p, z_index }, { near_face, far_face, YELLOW, BLACK, BLACK,  BLACK }),
				new Cube(r_radius, {			  0, r_separation_n, z_index }, { near_face, far_face,  BLACK, BLACK, WHITE,  BLACK }),
				new Cube(r_radius, { r_separation_p,			  0, z_index }, { near_face, far_face,  BLACK,   RED, BLACK,  BLACK }),
				new Cube(r_radius, { r_separation_n,			  0, z_index }, { near_face, far_face,  BLACK, BLACK, BLACK, ORANGE }),
				new Cube(r_radius, { r_separation_n, r_separation_n, z_index }, { near_face, far_face,  BLACK, BLACK, WHITE, ORANGE }),
				new Cube(r_radius, { r_separation_p, r_separation_p, z_index }, { near_face, far_face, YELLOW,   RED, BLACK,  BLACK }),
				new Cube(r_radius, { r_separation_n, r_separation_p, z_index }, { near_face, far_face, YELLOW, BLACK, BLACK, ORANGE }),
				new Cube(r_radius, { r_separation_p, r_separation_n, z_index }, { near_face, far_face,  BLACK,   RED, WHITE,  BLACK })
			};
		}

		void Rubik::bind_Transform(bool& enable, int current_transform)
		{

		}

		void Rubik::send_VShader_Transform()
		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.3f, 0.3f, 0.0f));

			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));
			projection = glm::perspective(glm::radians(45.0f), WINDOW_ASPECT, 0.1f, 100.0f);

			shader->setMat4("model", model);
			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
		}

#endif