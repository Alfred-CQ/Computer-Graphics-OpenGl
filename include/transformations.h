#ifndef _TRANSFORM_H_
	#define _TRANSFORM_H_

		#include "global.h"
		#include "vector"

		template <size_t V> 
		class Transformation
		{
			public:
			   /* Constructors and Destructor */
				Transformation(float rotation_x, float rotation_y, float rotation_z, VECT3 translation, VECT3 scale, float speed = 0.1);
				
				MATRIX4* X_Rotation_Matrix		= nullptr;
				MATRIX4* Y_Rotation_Matrix		= nullptr;
				MATRIX4* Z_Rotation_Matrix		= nullptr;
				MATRIX4* Translation_Matrix		= nullptr;
				MATRIX4* Scale_Matrix			= nullptr;

				MATRIX4	transform;
				Matrix<4,V>*     vertex_Matrix  = nullptr;

				std::vector<POINT3>        vertexes_transform;

				void copy_Vertexes(std::vector<POINT3> vertexes);
				void reset(std::vector<POINT3> vertexes);

				bool make_Translation(uint id_transform, bool use_history = true);
				bool make_Scale(uint id_transform, bool use_history = true);
				bool make_Rotation(uint id_transform, char type, bool use_history = true);

			private:

				float t_rotation_x, t_rotation_y, t_rotation_z;
				VECT3 t_scale, t_translation;

				float t_animation_counter = 1, t_speed, t_speed_rot;
				
				std::vector<MATRIX4>    history_transformation;
		};

		template<size_t V>
		Transformation<V>::Transformation(float rotation_x, float rotation_y, float rotation_z, VECT3 translation, VECT3 scale, float speed)
		{
			t_speed		  = speed * 1000;
			t_speed_rot   = speed / 100;
			t_rotation_x  = rotation_x;
			t_rotation_z  = rotation_z;
			t_translation = translation;
			t_scale		  = scale;

			X_Rotation_Matrix	= new MATRIX4(rotation_x / t_speed, 'x');
			Y_Rotation_Matrix	= new MATRIX4(rotation_y / t_speed, 'y');
			Z_Rotation_Matrix	= new MATRIX4(rotation_z / t_speed, 'z');
			Translation_Matrix	= new MATRIX4(translation.norm_Vector(), 'T', speed);
			Scale_Matrix		= new MATRIX4(scale.norm_Vector(), 'S', speed);
		}

		template<size_t V>
		void Transformation<V>::copy_Vertexes(std::vector<POINT3> vertexes)
		{
			vertex_Matrix = new Matrix<4, V>(vertexes);
			vertexes_transform = vertexes;
		}

		template<size_t V>
		void Transformation<V>::reset(std::vector<POINT3> vertexes)
		{
			vertexes_transform = vertexes;
		}

		template<size_t V>
		bool Transformation<V>::make_Translation(uint id_transform, bool use_history)
		{
			if (t_animation_counter < t_speed + 1)
			{
				transform = k_Translation(*Translation_Matrix,t_animation_counter * t_translation.norm);

				if (use_history)
					transform = history_transformation[id_transform - 1] * transform;

				get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

				t_animation_counter++;
				
				return false;
			}
			transform.print();
			t_animation_counter = 1;
			history_transformation.push_back(transform);
	
			return true;
		}

		template<size_t V>
		bool Transformation<V>::make_Scale(uint id_transform, bool use_history)
		{
			if (t_animation_counter < t_speed + 1)
			{
				transform = k_Scale(*Scale_Matrix, t_animation_counter * t_scale.norm);

				if (use_history)
					transform = history_transformation[id_transform - 1] * transform;

				get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

				t_animation_counter++;

				return false;
			}
			transform.print();
			t_animation_counter = 1;
			history_transformation.push_back(transform);

			return true;
		}

		template<size_t V>
		bool Transformation<V>::make_Rotation(uint id_transform, char type, bool use_history)
		{
			if (type == 'x')
			{
				if (t_animation_counter < t_rotation_x + 1)
				{
					transform = k_Rotation(*X_Rotation_Matrix, t_animation_counter);

					if (use_history)
						transform = history_transformation[id_transform - 1] * transform;

					get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

					t_animation_counter += t_speed_rot;

					return false;
				}
			}
			else if (type == 'y')
			{
				if (t_animation_counter < t_rotation_y + 1)
				{
					transform = k_Rotation(*Y_Rotation_Matrix, t_animation_counter);

					if (use_history)
						transform = history_transformation[id_transform - 1] * transform;

					get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

					t_animation_counter += t_speed_rot;

					return false;
				}
			}
			else if (type == 'z')
			{
				if (t_animation_counter < t_rotation_z + 1)
				{
					transform = k_Rotation(*Z_Rotation_Matrix, t_animation_counter);

					if (use_history)
						transform = history_transformation[id_transform - 1] * transform;

					get_Vertexes_Transform(transform * (*vertex_Matrix), vertexes_transform);

					t_animation_counter += t_speed_rot;

					return false;
				}
			}
			transform.print();
			t_animation_counter = 1;
			history_transformation.push_back(transform);

			return true;
		}

#endif 
