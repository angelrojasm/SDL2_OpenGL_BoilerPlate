#pragma once
#ifndef MATRIX_4_HPP
#include <cmath>
#include <iostream>
#include "Vector3.hpp"

namespace engine {

	namespace math {
		class Matrix_4
		{
		public:
	
			

			//Constructors:
			Matrix_4();
			Matrix_4(float Column_1_Row_1, float Column_1_Row_2, float Column_1_Row_3, float Column_1_Row_4,
				float Column_2_Row_1, float Column_2_Row_2, float Column_2_Row_3, float Column_2_Row_4,
				float Column_3_Row_1, float Column_3_Row_2, float Column_3_Row_3, float Column_3_Row_4,
				float Column_4_Row_1, float Column_4_Row_2, float Column_4_Row_3, float Column_4_Row_4);
			Matrix_4(float Values[16]);

			//Public Functions:
			float **get_Matrix(void);
			float *get_Matrix_Row(int );
			float *get_Matrix_Column(int);
			void set_Identity(void);
			Matrix_4 get_Transposed();
			Vector3 get_Angles();
			Matrix_4 get_Inverse();
			Matrix_4 operator+(Matrix_4&);
			Matrix_4 operator-(Matrix_4&);
			void operator=(Matrix_4&);
			Matrix_4 operator*(Matrix_4&);
			float& operator[](int rhs);
			friend std::ostream& operator<<(std::ostream&,Matrix_4);
			

 


			//Private Member: BiDimensional Array to Represent Matrix
			float **mValues;

			//Private Function: Should only be Accessed during Matrix Construction
			void Initialize();
		};
	}
}
#endif
