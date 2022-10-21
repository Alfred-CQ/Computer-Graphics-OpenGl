#ifndef _PIZZA_H_
	#define _PIZZA_H_
	
		#include "picture.h"

		class Pizza: public Picture 
		{
			public:
				
				uint second_EBO;

				Pizza(size_t tips, float radius);

				void get_Vertexes();
				void get_Idx_Lines();
				void get_Idx_Triangles();
				
				void draw_divisions();
				void begin_Textures();

			private:

				size_t p_tips;
				float  p_radius, p_location_x, p_location_y, p_rotation;

		};
		
		Pizza::Pizza(size_t tips, float radius)
		{
			p_tips = tips;
			p_radius = radius;
			p_rotation = (2.f * F_PI) / p_tips;

			get_Vertexes();
			get_Idx_Lines();
			get_Idx_Triangles();

			bind_Buffers();
			// Texture
			bind(texture, 2, 2); // 2 texture attribute

			set_Texture(root_path + "textures\\pizzaa.jpg", 0);
			set_Texture(root_path + "textures\\logo.png", 1, GL_RGBA);

		}

		void Pizza::begin_Textures()
		{
			shader->use();
			shader->setInt("texture_1", 0);
			shader->setInt("texture_2", 1);
		}

		void Pizza::get_Vertexes()
		{
			float begin = 0.0f, x_value, y_value;;

			for (int i = 0; i < p_tips; ++i)
			{
				x_value = sin(begin) * p_radius;
				y_value = cos(begin) * p_radius;
				
				vertexes.push_back( {x_value, y_value, 0.0f} );
				
				texture.push_back((x_value * 0.5) + 0.5);
				texture.push_back((y_value * 0.5) + 0.5);

				begin += p_rotation;
			}

			vertexes.push_back( {0.0f, 0.0f, 0.0f} );

			texture.push_back(0.5);
			texture.push_back(0.5);

			size_vertexes = vertexes.size();
		}

		void Pizza::get_Idx_Lines()
		{
			for (int i = 0, j = 0; i < (size_vertexes - 1) / 3; ++i, j += 3)
			{
				idx_lines.push_back(j);
				idx_lines.push_back(36);
			}
			size_idx_lines = idx_lines.size();

			glGenBuffers(1, &this->second_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, second_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_idx_lines * sizeof(this->idx_lines), &(this->idx_lines.front()), GL_STATIC_DRAW);
		}

		void Pizza::get_Idx_Triangles()
		{
			for (int i = 0; i < size_vertexes - 1 ; ++i)
			{
				idx_triangles.push_back(i);
				idx_triangles.push_back(36);
				idx_triangles.push_back((i + 1) % (size_vertexes - 1));
			}

			size_idx_triangles = idx_triangles.size();
		}

		void Pizza::draw_divisions()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->second_EBO);
			glDrawElements(GL_LINE_LOOP, 24, GL_UNSIGNED_INT, 0);
		}

#endif
