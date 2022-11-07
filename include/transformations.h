#ifndef _TRANSFORM_H_
	#define _TRANSFORM_H_

		#include "math_entities.h"
		#include "matrix.h"
		#include "vector"

		template <size_t V> 
		class Transformation
		{
			public:
			   /* Constructors and Destructor */
				Transformation(float rotation_x, float rotation_y, float rotation_z, Vector<3> translation, Vector<3> scale, float speed = 0.1);
				
				Matrix<4, 4>* X_Rotation_Matrix		= nullptr;
				Matrix<4, 4>* Y_Rotation_Matrix		= nullptr;
				Matrix<4, 4>* Z_Rotation_Matrix		= nullptr;
				Matrix<4, 4>* Translation_Matrix	= nullptr;
				Matrix<4, 4>* Scale_Matrix			= nullptr;
				
				Matrix<4, 4>		transform;
				Matrix<4, V>*        vertex_Matrix  = nullptr;
				std::vector<Point<3>>        vertexes_transform;

				void copy_Vertexes(std::vector<Point<3>> vertexes);

				bool make_Translation(uint id_transform);

			private:

				float t_animation_counter = 1, t_speed;
				

				std::vector<Matrix<4, 4>>    history_transformation;
		};

		template<size_t V>
		Transformation<V>::Transformation(float rotation_x, float rotation_y, float rotation_z, Vector<3> translation, Vector<3> scale, float speed)
		{
			t_speed = speed * 1000;
			X_Rotation_Matrix	= new Matrix<4, 4>(rotation_x, 'x');
			Y_Rotation_Matrix	= new Matrix<4, 4>(rotation_y, 'y');
			Z_Rotation_Matrix	= new Matrix<4, 4>(rotation_z, 'z');
			Translation_Matrix	= new Matrix<4, 4>(translation.norm_Vector(), 'T', speed);
			Scale_Matrix		= new Matrix<4, 4>(scale, 'S');
		}

		template<size_t V>
		void Transformation<V>::copy_Vertexes(std::vector<Point<3>> vertexes)
		{
			vertex_Matrix = new Matrix<4, 11>(vertexes);
			vertexes_transform = vertexes;
		}

		template<size_t V>
		bool Transformation<V>::make_Translation(uint id_transform)
		{
			if (t_animation_counter != t_speed + 1)
			{
				Matrix<4, 4> identy({ 1.0f, 1.0f, 1.0f }, 'S');
				transform = (*Translation_Matrix * t_animation_counter) * identy;

				get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

				t_animation_counter++;
				return false;
			}
			t_animation_counter = 1;
			history_transformation.push_back(transform);
			transform.print();
			return true;
		}

#endif 
