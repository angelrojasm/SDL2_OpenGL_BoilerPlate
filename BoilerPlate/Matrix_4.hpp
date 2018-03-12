#pragma once
#ifndef MATRIX_4_HPP

namespace engine {

	namespace math {
		class Matrix_4
		{
		public:
			//Members:
			float mValues[16];

			//Constructors:
			Matrix_4();
			Matrix_4(float Column_1_Row_1, float Column_1_Row_2, float Column_1_Row_3, float Column_1_Row_4,
				float Column_2_Row_1, float Column_2_Row_2, float Column_2_Row_3, float Column_2_Row_4,
				float Column_3_Row_1, float Column_3_Row_2, float Column_3_Row_3, float Column_3_Row_4,
				float Column_4_Row_1, float Column_4_Row_2, float Column_4_Row_3, float Column_4_Row_4);
			Matrix_4(float Values[16]);

		};
	}
}
#endif
