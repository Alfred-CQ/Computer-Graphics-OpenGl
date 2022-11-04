#ifndef _CUBE_H_
	#define _CUBE_H_
		
		#include "square.h"

		class Cube
		{
			public:

				/* Constructors */
				Cube			();
				Cube			(float radius, Point<3> center, vector<COLOUR> face_colours);

				/* Variables */
				float			c_radius;
				const uint		c_nfaces   = 6;
				Point<3>		c_center  = {0, 0, 0};
				vector<COLOUR>	c_face_colours;
				VERTEXES		c_centers;
				
				VERTEXES		c_vertexes;
				VERTEX_COLOURS	c_colours;
				VERTEX_TEXTURES	c_textures;
				vector<uint>	c_idx_triangles;

				vector<Square*>	c_faces;

				/* Methods */
				// Setters

				// Getters
				void get_Vertexes();

			private:
				
		};
		
		Cube::Cube()
		{
			std::cout << "Cube says hello\n"; 
		}

		Cube::Cube(float radius, Point<3> center, vector<COLOUR> face_colours)
		{
			c_radius		= radius;
			c_center		= center;
			c_face_colours	= face_colours;
			

			get_Vertexes();
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
					c_faces.push_back(new Square(c_radius, c_centers[i], c_face_colours[i]));
				else
				{
					c_faces.push_back(new Square((*c_faces[0]).s_vertexes[first], (*c_faces[0]).s_vertexes[second],
												 (*c_faces[1]).s_vertexes[first], (*c_faces[1]).s_vertexes[second], c_face_colours[i]));
					first = second; second = (second + 1) % 4;
					
					c_centers.push_back((*c_faces[i]).s_center);
				}
			}
				
			for (size_t i = 0; i < c_faces.size(); ++i)
			{
				c_vertexes.insert(end(c_vertexes), begin((*c_faces[i]).s_vertexes), end((*c_faces[i]).s_vertexes));
				c_colours.insert(end(c_colours), begin((*c_faces[i]).s_colours), end((*c_faces[i]).s_colours));
				c_textures.insert(end(c_textures), begin((*c_faces[i]).s_textures), end((*c_faces[i]).s_textures));
			}
		
			int size_vertexes = c_vertexes.size();
			
		}
#endif