#ifndef _SQUARE_H_
	#define _SQUARE_H_
	
		#include "../include/math_entities.h"	
		#include "../include/global.h"

		class Square
		{
			public:

				/* Constructors */
				Square(float radius, Point<3>center, COLOUR color);
				Square(Point<3> near_1, Point<3> near_2, Point<3> far_1, Point<3> far_2, COLOUR color);

				/* Variables */
				float			s_radius;
				const uint		s_sides		= 4;
				Point<3>		s_center	= { 0.0f, 0.0f, 0.0f };
				COLOUR			s_colour;

				VERTEXES		s_vertexes;
				VERTEX_COLOURS	s_colours;
				VERTEX_TEXTURES s_textures;

				/* Methods */
				// Setters
				void set_Vertexes();
				void set_Colours();
				void set_Textures();

				// Getters
				
				// Utils

			private:
		

		};

		Square::Square(float radius, Point<3> center, COLOUR color)
		{
			s_radius = radius;
			s_colour = color;
			s_center = center;
			
			set_Vertexes();
			set_Colours();
			set_Textures();
		}
		
		Square::Square(Point<3> near_1, Point<3> near_2, Point<3> far_1, Point<3> far_2, COLOUR colour)
		{
			s_radius	= abs(near_1.p_x);
			s_colour	= colour;
			s_center	= (near_1 + far_2)/2;
			s_vertexes	= { near_1, near_2, far_2, far_1};
			
			set_Colours();
			set_Textures();
		}

		void Square::set_Vertexes()
		{
			float first{ -1.0f * s_radius }, second{ s_radius };
			for (size_t i = 0; i < s_sides; ++i)
			{
				s_vertexes.push_back({first + s_center.p_x, second + s_center.p_y, s_center.p_z});

				first *= -1.0f;

				if (i == 1)
				{
					first *= -1.0f;
					second *= -1.0f;
				}
			}
		}

		void Square::set_Colours()
		{
			for (size_t i = 0; i < s_sides; ++i)
				for (size_t j = 0; j < 3; ++j)
					s_colours.push_back(s_colour.begin()->second[j]);
		}

		void Square::set_Textures()
		{
			float first{ 0.0f }, second{ 1.0f };
			for (size_t i = 0; i < s_sides; ++i)
			{
				s_textures.push_back(first); s_textures.push_back(second);

				first = 1.0f;

				if (i == 1)
					second = 0.0f;
				else if (i == 2)
					first = 0.0f;
			}
		}

#endif
