#ifndef _MATH_ENTITIES_H_
	#define _MATH_ENTITIES_H_
		
		#include <iostream>
		
		template <size_t N>
		class Point
		{
			public:
				float p_x, p_y, p_z;

				Point();
				Point(float x, float y, float z) : p_x(x), p_y(y), p_z(z) {}
				
				// Overloads
				Point& operator+(float k);
				Point& operator*(float k);
				Point& operator = (const Point& other);

				void print();
		};

		template<size_t N>		
		class Vector {
		public:

			Point<N> v_origen, v_sentido, v_apply;
			float norm;
			
			Vector(float x, float y, float z);

			Vector(Point<N> origen, Point<N> sentido);

			// Overloads
			Vector& operator+(const Vector& k);
			Vector& operator+(const float k);
			Vector& operator/(const float k);
			Vector& operator = (const Vector& other);
			
			// Getters
			void get_norm();
		};

		
		/* Point */
		template <size_t N>
		Point<N>::Point()
		{
			p_x = 0;
			p_y = 0;
			p_z = 0;
		}
		
		template <size_t N>
		Point<N>& Point<N>::operator+(float k)
		{
			this->p_x += k;
			this->p_y += k;
			this->p_z += k;
			return *this;
		}
		
		template <size_t N>
		Point<N>& Point<N>::operator*(float k)
		{
			this->p_x *= k;
			this->p_y *= k;
			this->p_z *= k;

			return *this;
		}

		template <size_t N>
		Point<N> operator+(const Point<N>& p, const Point<N>& q)
		{
			Point<N> third_point;
			
			third_point.p_x = p.p_x + q.p_x;
			third_point.p_y = p.p_y + q.p_y;
			third_point.p_z = p.p_z + q.p_z;

			return third_point;
		}
		
		template <size_t N>
		Point<N> operator-(const Point<N>& p, const Point<N>& q)
		{
			Point<N> third_point;

			third_point.p_x = p.p_x - q.p_x;
			third_point.p_y = p.p_y - q.p_y;
			third_point.p_z = p.p_z - q.p_z;

			return third_point;
		}

		template <size_t N>
		Point<N> operator/(const Point<N>& p, float k)
		{
			Point<N> third_point;

			third_point.p_x = p.p_x/k;
			third_point.p_y = p.p_y/k;
			third_point.p_z = p.p_z/k;

			return third_point;
		}

		template <size_t N>
		Point<N>& Point<N>::operator = (const Point& other)
		{
			this->p_x = other.p_x;
			this->p_y = other.p_y;
			this->p_z = other.p_z;

			return *this;
		}

		template <size_t N>
		void Point<N>::print()
		{
			std::cout << p_x << " " << p_y << " " << p_z << '\n';
		}

		/* Vector */
		template<size_t N>
		Vector<N>::Vector(float x, float y, float z) 
		{
			v_apply.p_x = x;
			v_apply.p_y = y;
			v_apply.p_z = z;
		}

		template<size_t N>
		Vector<N>::Vector(Point<N> origen, Point<N> sentido)
		{
			v_origen = origen;
			v_sentido = sentido;
			v_apply = v_sentido - v_origen;

			get_norm();
		}

		template<size_t N>
		Vector<N>& Vector<N>::operator+(const Vector& k)
		{
			this->v_apply.p_x += k.v_apply.p_x;
			this->v_apply.p_y += k.v_apply.p_y;
			this->v_apply.p_z += k.v_apply.p_z;

			return *this;
		}

		template<size_t N>
		Vector<N>& Vector<N>::operator+(const float k)
		{
			this->v_apply.p_x *= k;
			this->v_apply.p_y *= k;
			this->v_apply.p_z *= k;

			return *this;
		}

		template<size_t N>
		Vector<N>& Vector<N>::operator/(const float k)
		{
			this->v_apply.p_x /= k;
			this->v_apply.p_y /= k;
			this->v_apply.p_z /= k;

			return *this;
		}

		template<size_t N>
		Vector<N>& Vector<N>::operator = (const Vector& other)
		{
			this->v_origen = other.v_origen;
			this->v_sentido = other.v_sentido;
			this->v_apply = other.v_apply;
			this->norma = other.norma;
			return *this;
		}

		template<size_t N>
		void Vector<N>::get_norm()
		{
			norm = sqrt((v_apply.p_x * v_apply.p_x) + (v_apply.p_y * v_apply.p_y) + (v_apply.p_z * v_apply.p_z));
		}

#endif
