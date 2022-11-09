#ifndef _POINT_H_
	#define _POINT_H_
		
		template <size_t N>
		struct Point
		{
			float p_x, p_y, p_z;
		
			Point();
			Point(float x, float y, float z) : p_x(x), p_y(y), p_z(z) {}
		
			// Overloads
			Point& operator+(float k);
			Point& operator*(float k);
			Point& operator+(const Point& k);
			Point& operator-(Point& B);
			Point& operator/(float k);
			Point& operator=(const Point& other);
		
			// Utils
			void print();
		};

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
		Point<N>& Point<N>::operator+(const Point& k)
		{
			this->p_x += k.p_x;
			this->p_y += k.p_y;
			this->p_z += k.p_z;

			return *this;
		}

		template <size_t N>
		Point<N>& Point<N>::operator-(Point& B)
		{
			this->p_x -= k.p_x;
			this->p_y -= k.p_y;
			this->p_z -= k.p_z;

			return *this;
		}

		template <size_t N>
		Point<N>& Point<N>::operator/(float k)
		{
			this->p_x /= k;
			this->p_y /= k;
			this->p_z /= k;

			return *this;
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

#endif



