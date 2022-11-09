#ifndef _VECTOR_H_
	#define _VECTOR_H_
		
		#include "point.h"		
	
		template<size_t N>
		struct Vector
		{
			Point<N> v_origen, v_sentido, v_apply;
			float norm;
		
			Vector();
			Vector(float x, float y, float z);
		
			Vector(Point<N> origen, Point<N> sentido);
		
			// Overloads
			Vector& operator+(const Vector& k);
			Vector& operator+(const float k);
			Vector& operator = (const Vector& other);
		
			// Getters
			void		get_norm();
		
			// Utils
			Vector<N>	norm_Vector();
			void		print();
		};
		
		/* Vector */
		template<size_t N>
		Vector<N>::Vector()
		{
		
		}
		
		template<size_t N>
		Vector<N>::Vector(float x, float y, float z)
		{
			v_apply.p_x = x;
			v_apply.p_y = y;
			v_apply.p_z = z;
			get_norm();
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
		Vector<N> operator/(Vector<N>& other, float k)
		{
			Vector<N> third_vector(other.v_apply.p_x / k, other.v_apply.p_y / k, other.v_apply.p_z / k);
			return third_vector;
		}
		
		template<size_t N>
		Vector<N>& Vector<N>::operator = (const Vector& other)
		{
			this->v_origen = other.v_origen;
			this->v_sentido = other.v_sentido;
			this->v_apply = other.v_apply;
			this->norm = other.norm;
			return *this;
		}
		
		template<size_t N>
		void Vector<N>::get_norm()
		{
			norm = sqrt((v_apply.p_x * v_apply.p_x) + (v_apply.p_y * v_apply.p_y) + (v_apply.p_z * v_apply.p_z));
		}
		
		template<size_t N>
		Vector<N> Vector<N>::norm_Vector()
		{
			return Vector<N>(v_apply.p_x, v_apply.p_y, v_apply.p_z) / norm;
		}
		
		template<size_t N>
		void Vector<N>::print()
		{
			this->v_origen.print();
			this->v_sentido.print();
			this->v_apply.print();
		}
		
#endif