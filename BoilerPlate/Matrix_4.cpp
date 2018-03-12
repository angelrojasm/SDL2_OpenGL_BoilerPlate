#include "Matrix_4.hpp"


namespace engine {
	namespace math {

		Matrix_4::Matrix_4()
		{
			for (int MatrixColumn = 0; MatrixColumn < 4;MatrixColumn++) {
				for (int MatrixRow = 0; MatrixColumn < 4; MatrixRow++) {
					if (MatrixColumn == MatrixRow)
						mValues[MatrixRow] = 1.0f;
				}
			}
		}

	}
}
