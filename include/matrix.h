#ifndef _MATRIX_H_
	#define _MATRIX_H_
		
		#include "math_entities.h"

		template<size_t N, size_t M>
		class Matrix
		{
			public:
				
				float matrix[N][M]		= { 0 };
				
				float vector_norm, m_speed;

				Matrix();
				Matrix(float angle, char type, float speed = 0.1);
				Matrix(Vector<3> TS_vector, char type, float speed = 0.1);
				Matrix(std::vector<Point<3>> vertexes);
				
				void print();
				void clear();
			
			private:

		};
			
		template<size_t N, size_t M>
		Matrix<N, M>::Matrix()
		{
			
		}

		template<size_t N, size_t M>
		Matrix<N, M>::Matrix(float angle, char type, float speed)
		{
			angle = (angle * F_PI) / 180;
			matrix[N - 1][N - 1] = 1.0f;

			if (type == 'x')
			{
				matrix[0][0] = 1.0f;

				matrix[1][1] = cos(angle); matrix[1][2] = -1.f * sin(angle);
				matrix[2][1] = sin(angle); matrix[2][2] = cos(angle);
			}
			else if (type == 'y')
			{
				matrix[1][1] = 1.0f;

				matrix[0][0] = cos(angle);	      matrix[0][2] = sin(angle);
				matrix[2][0] = -1.f * sin(angle); matrix[2][2] = cos(angle);
			}
			else if (type == 'z')
			{
				matrix[2][2] = 1.0f;

				matrix[0][0] = cos(angle); matrix[0][1] = -1.f * sin(angle);
				matrix[1][0] = sin(angle); matrix[1][1] = cos(angle);
			}
		}
		
		template<size_t N, size_t M>
		Matrix<N, M>::Matrix(Vector<3> TS_vector, char type, float speed)
		{
			m_speed = speed * 1000;

			if (type == 'T')
			{ 
				for (int i = 0; i < N; ++i)
				{
					matrix[i][i] = 1.0f;
				}
					
				matrix[0][N - 1] = TS_vector.v_apply.p_x;
				matrix[1][N - 1] = TS_vector.v_apply.p_y;
				matrix[2][N - 1] = TS_vector.v_apply.p_z;
			}
			else if (type == 'S')
			{
				matrix[0][0] = TS_vector.v_apply.p_x;
				matrix[1][1] = TS_vector.v_apply.p_y;
				matrix[2][2] = TS_vector.v_apply.p_z;
				matrix[N - 1][N - 1] = 1.0f;
			}
		}

		template<size_t N, size_t M>
		Matrix<N, M>::Matrix(std::vector<Point<3>> vertexes)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				matrix[0][i] = vertexes[i].p_x;
				matrix[1][i] = vertexes[i].p_y;
				matrix[2][i] = vertexes[i].p_z;
				matrix[3][i] = 1.0f;
			}
			matrix[N - 1][M - 1] = 1.0f;
		}

		template<size_t N, size_t M>
		void Matrix<N, M>::print()
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < M; ++j)
					std::cout << matrix[i][j] << ' ';

				std::cout << '\n';
			}
		}

		template<size_t N, size_t M>
		void Matrix<N, M>::clear()
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					matrix[i][j] = 0;
		}

		template<size_t N, size_t M, size_t N1, size_t M2>
		Matrix<N, M2> operator *(const Matrix<N, M>& first_matrix, const Matrix<N1, M2>& second_matrix)
		{
			Matrix<N, M2> third_matrix;

			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M2; ++j)
					for (int k = 0; k < M; ++k)
						third_matrix.matrix[i][j] += first_matrix.matrix[i][k] * second_matrix.matrix[k][j];

			return third_matrix;
		}

		template<size_t N, size_t M>
		void get_Vertexes_Transform(Matrix<N,M> matrix, std::vector<Point<3>>& vertexes_transform)
		{
			for (int i = 0; i < vertexes_transform.size(); ++i)
			{
				vertexes_transform[i].p_x = matrix.matrix[0][i];
				vertexes_transform[i].p_y = matrix.matrix[1][i];
				vertexes_transform[i].p_z = matrix.matrix[2][i];
			}
		}

#endif