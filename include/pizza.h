#ifndef _PIZZA_H_
	#define _PIZZA_H_
	
		#include "picture.h"

		class Pizza: public Picture 
		{
			public:
				
				Pizza(size_t tips, float radius);

				void get_Vertexes();
				void get_Idx_Lines();
				void get_Idx_Triangles();

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
		}

		void Pizza::get_Vertexes()
		{
			float begin = 0.0f;

			for (int i = 0; i < p_tips; ++i)
			{
				vertexes.push_back( {sin(begin) * p_radius, cos(begin) * p_radius, 0.0f} );

				begin += p_rotation;
			}

			vertexes.push_back( {0.0f, 0.0f, 0.0f} );

			size_vertexes = vertexes.size();
		}

		void Pizza::get_Idx_Lines()
		{
			for (int i = 0; i < size_vertexes - 1; ++i)
				idx_lines.push_back(i);
			/*int j = 0;
			for (int i = 0; i < (size_vertexes - 1) / 3; ++i, j += 3)
			{
				idx_lines.push_back(j);
				idx_lines.push_back(36);
			}

			size_idx_lines = idx_lines.size();**/
		}

		void Pizza::get_Idx_Triangles()
		{
			idx_triangles.push_back(0);
			idx_triangles.push_back(31);
			idx_triangles.push_back(1);
		}

#endif
