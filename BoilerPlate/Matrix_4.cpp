#include "Matrix_4.hpp"


namespace engine {
	namespace math {

		Matrix_4::Matrix_4()
		{
			Initialize();
			set_Identity();
		}

		Matrix_4::Matrix_4(float Column_1_Row_1, float Column_1_Row_2, float Column_1_Row_3, float Column_1_Row_4,
			float Column_2_Row_1, float Column_2_Row_2, float Column_2_Row_3, float Column_2_Row_4,
			float Column_3_Row_1, float Column_3_Row_2, float Column_3_Row_3, float Column_3_Row_4,
			float Column_4_Row_1, float Column_4_Row_2, float Column_4_Row_3, float Column_4_Row_4) {

			Initialize();

			mValues[0][0] = Column_1_Row_1;
			mValues[1][0] = Column_1_Row_2;
			mValues[2][0]= Column_1_Row_3;
			mValues[3][0] = Column_1_Row_4;
			mValues[0][1] = Column_2_Row_1;
			mValues[1][1] = Column_2_Row_2;
			mValues[2][1] = Column_2_Row_3;
			mValues[3][1] = Column_2_Row_4;
			mValues[0][2] = Column_3_Row_1;
			mValues[1][2] = Column_3_Row_2;
			mValues[2][2] = Column_3_Row_3;
			mValues[3][2] = Column_3_Row_4;
			mValues[0][3] = Column_4_Row_1;
			mValues[1][3] = Column_4_Row_2;
			mValues[2][3] = Column_4_Row_3;
			mValues[3][3] = Column_4_Row_4;

		}

		Matrix_4::Matrix_4(float Values[16]) {
			Initialize();

			int valuesCounter = 0;

			for (int MatrixRow = 0;MatrixRow < 4;MatrixRow++) {
				for (int MatrixColumn = 0;MatrixColumn < 4;MatrixColumn++) {
					mValues[MatrixColumn][MatrixRow] = Values[valuesCounter];
					valuesCounter++;
				}
			}
			
		}

		void Matrix_4::Initialize() {
			mValues = new float*[4];

			for (int i = 0;i < 4;i++) {
				mValues[1] = new float[4];
			}
		}

		float* Matrix_4::get_Matrix_Column(int ColumnNumber) {
			float DesiredColumn[4];

			for(int i = 0; i < 4; i++)
			{
				DesiredColumn[i] = mValues[ColumnNumber][i];
			}

			return DesiredColumn;
		}

		float* Matrix_4::get_Matrix_Row(int RowNumber) {
			float DesiredRow[4];

			for (int i = 0; i < 4; i++)
			{
				DesiredRow[i] = mValues[i][RowNumber];
			}

			return DesiredRow;
			}
		
		void Matrix_4::set_Identity() {
			for (int MatrixColumn = 0; MatrixColumn < 4;MatrixColumn++) {
				for (int MatrixRow = 0; MatrixColumn < 4; MatrixRow++) {
					if (MatrixColumn == MatrixRow)
						mValues[MatrixColumn][MatrixRow] = 1.0f;
					else
						mValues[MatrixColumn][MatrixRow] = 0.0f;
				}
			}
		}

		float** Matrix_4::get_Matrix() {
			return mValues;
		}

		Matrix_4 Matrix_4::get_Transposed() {
			Matrix_4 New_Matrix;
			for (int MatrixRow = 0; MatrixRow < 4; MatrixRow++) {

				for (int MatrixColumn = 0; MatrixColumn < 4; MatrixColumn++) {
					New_Matrix.get_Matrix()[MatrixRow][MatrixColumn] = mValues[MatrixColumn][MatrixRow];
				}
			}
			return New_Matrix;
		}
	
		Vector3 Matrix_4::get_Angles() {
			Vector3 Angles;

			if (mValues[0][0] == 1.0f || mValues[0][0] == -1.0f)
			{
				Angles.X_coordinate = 0;
				Angles.Y_coordinate = atan2f(mValues[0][2], mValues[2][3]); 
				Angles.Z_coordinate = 0; 

			}
			else
			{

				Angles.X_coordinate = (float)asin(mValues[1][0]); //pitch
				Angles.Y_coordinate = atan2f(-mValues[2][0], mValues[0][0]); //yaw
				Angles.Z_coordinate= atan2f(-mValues[1][2], mValues[1][1]); //roll
			}

			return Angles;
		}

		Matrix_4 Matrix_4::operator+(Matrix_4& rhs) {
			Matrix_4 Final_Matrix;

			for (int Matrix_Row = 0; Matrix_Row < 4; Matrix_Row++) {
				for (int Matrix_Column = 0; Matrix_Column < 4; Matrix_Column++) {
					Final_Matrix.get_Matrix()[Matrix_Column][Matrix_Row] = mValues[Matrix_Column][Matrix_Row] + rhs.get_Matrix()[Matrix_Column][Matrix_Row];
				}
			}
			return Final_Matrix;
		}

		Matrix_4 Matrix_4::operator-(Matrix_4& rhs) {
			Matrix_4 Final_Matrix;

			for (int Matrix_Row = 0; Matrix_Row < 4; Matrix_Row++) {
				for (int Matrix_Column = 0; Matrix_Column < 4; Matrix_Column++) {
					Final_Matrix.get_Matrix()[Matrix_Column][Matrix_Row] = mValues[Matrix_Column][Matrix_Row] - rhs.get_Matrix()[Matrix_Column][Matrix_Row];
				}
			}
			return Final_Matrix;
		}

		void Matrix_4::operator=(Matrix_4& rhs) {

			for (int Matrix_Row = 0; Matrix_Row < 4; Matrix_Row++) {
				for (int Matrix_Column = 0; Matrix_Column < 4; Matrix_Column++) {
					mValues[Matrix_Column][Matrix_Row] = rhs.get_Matrix()[Matrix_Column][Matrix_Row];
				}
			}
		}

		float& Matrix_4::operator[]( int rhs)
		{
			int Matrix_Column = rhs % 4;
			int Matrix_Row = rhs / 4;

			return mValues[Matrix_Column][Matrix_Row];
		}

		 std::ostream& operator<<(std::ostream& ostream_tool, Matrix_4 rhs) {
			for (int Matrix_Row = 0; Matrix_Row < 4; Matrix_Row++) {

				for (int Matrix_Column = 0; Matrix_Column < 4; Matrix_Column++) {

					ostream_tool << rhs.get_Matrix()[Matrix_Row][Matrix_Column] << " ";
				}
				ostream_tool << "\n";
			}
			return ostream_tool;
		}

		 Matrix_4 Matrix_4::get_Inverse() {
			
				
			 Matrix_4 Temp_Matrix;
			 Matrix_4 Final_Matrix;

				 float Matrix_Determinant;

				 for (int Matrix_Row = 0; Matrix_Row < 4; Matrix_Row++)
				 {
					 for (int Matrix_Column = 0; Matrix_Column < 4; Matrix_Column++)
					 {
						 Temp_Matrix.get_Matrix()[Matrix_Row][Matrix_Column] = mValues[Matrix_Row][Matrix_Column];
					 }
				 }

				 Final_Matrix[0] = Temp_Matrix[5] * Temp_Matrix[10] * Temp_Matrix[15] -
					 Temp_Matrix[5] * Temp_Matrix[11] * Temp_Matrix[14] -
					 Temp_Matrix[9] * Temp_Matrix[6] * Temp_Matrix[15] +
					 Temp_Matrix[9] * Temp_Matrix[7] * Temp_Matrix[14] +
					 Temp_Matrix[13] * Temp_Matrix[6] * Temp_Matrix[11] -
					 Temp_Matrix[13] * Temp_Matrix[7] * Temp_Matrix[10];

				 Final_Matrix[1] = -Temp_Matrix[1] * Temp_Matrix[10] * Temp_Matrix[15] +
					 Temp_Matrix[1] * Temp_Matrix[11] * Temp_Matrix[14] +
					 Temp_Matrix[9] * Temp_Matrix[2] * Temp_Matrix[15] -
					 Temp_Matrix[9] * Temp_Matrix[3] * Temp_Matrix[14] -
					 Temp_Matrix[13] * Temp_Matrix[2] * Temp_Matrix[11] +
					 Temp_Matrix[13] * Temp_Matrix[3] * Temp_Matrix[10];

				 Final_Matrix[2] = Temp_Matrix[1] * Temp_Matrix[6] * Temp_Matrix[15] -
					 Temp_Matrix[1] * Temp_Matrix[7] * Temp_Matrix[14] -
					 Temp_Matrix[5] * Temp_Matrix[2] * Temp_Matrix[15] +
					 Temp_Matrix[5] * Temp_Matrix[3] * Temp_Matrix[14] +
					 Temp_Matrix[13] * Temp_Matrix[2] * Temp_Matrix[7] -
					 Temp_Matrix[13] * Temp_Matrix[3] * Temp_Matrix[6];

				 Final_Matrix[3] = -Temp_Matrix[1] * Temp_Matrix[6] * Temp_Matrix[11] +
					 Temp_Matrix[1] * Temp_Matrix[7] * Temp_Matrix[10] +
					 Temp_Matrix[5] * Temp_Matrix[2] * Temp_Matrix[11] -
					 Temp_Matrix[5] * Temp_Matrix[3] * Temp_Matrix[10] -
					 Temp_Matrix[9] * Temp_Matrix[2] * Temp_Matrix[7] +
					 Temp_Matrix[9] * Temp_Matrix[3] * Temp_Matrix[6];

				 Final_Matrix[4] = -Temp_Matrix[4] * Temp_Matrix[10] * Temp_Matrix[15] +
					 Temp_Matrix[4] * Temp_Matrix[11] * Temp_Matrix[14] +
					 Temp_Matrix[8] * Temp_Matrix[6] * Temp_Matrix[15] -
					 Temp_Matrix[8] * Temp_Matrix[7] * Temp_Matrix[14] -
					 Temp_Matrix[12] * Temp_Matrix[6] * Temp_Matrix[11] +
					 Temp_Matrix[12] * Temp_Matrix[7] * Temp_Matrix[10];

				 Final_Matrix[5] = Temp_Matrix[0] * Temp_Matrix[10] * Temp_Matrix[15] -
					 Temp_Matrix[0] * Temp_Matrix[11] * Temp_Matrix[14] -
					 Temp_Matrix[8] * Temp_Matrix[2] * Temp_Matrix[15] +
					 Temp_Matrix[8] * Temp_Matrix[3] * Temp_Matrix[14] +
					 Temp_Matrix[12] * Temp_Matrix[2] * Temp_Matrix[11] -
					 Temp_Matrix[12] * Temp_Matrix[3] * Temp_Matrix[10];

				 Final_Matrix[6] = -Temp_Matrix[0] * Temp_Matrix[6] * Temp_Matrix[15] +
					 Temp_Matrix[0] * Temp_Matrix[7] * Temp_Matrix[14] +
					 Temp_Matrix[4] * Temp_Matrix[2] * Temp_Matrix[15] -
					 Temp_Matrix[4] * Temp_Matrix[3] * Temp_Matrix[14] -
					 Temp_Matrix[12] * Temp_Matrix[2] * Temp_Matrix[7] +
					 Temp_Matrix[12] * Temp_Matrix[3] * Temp_Matrix[6];

				 Final_Matrix[7] = Temp_Matrix[0] * Temp_Matrix[6] * Temp_Matrix[11] -
					 Temp_Matrix[0] * Temp_Matrix[7] * Temp_Matrix[10] -
					 Temp_Matrix[4] * Temp_Matrix[2] * Temp_Matrix[11] +
					 Temp_Matrix[4] * Temp_Matrix[3] * Temp_Matrix[10] +
					 Temp_Matrix[8] * Temp_Matrix[2] * Temp_Matrix[7] -
					 Temp_Matrix[8] * Temp_Matrix[3] * Temp_Matrix[6];

				 Final_Matrix[8] = Temp_Matrix[4] * Temp_Matrix[9] * Temp_Matrix[15] -
					 Temp_Matrix[4] * Temp_Matrix[11] * Temp_Matrix[13] -
					 Temp_Matrix[8] * Temp_Matrix[5] * Temp_Matrix[15] +
					 Temp_Matrix[8] * Temp_Matrix[7] * Temp_Matrix[13] +
					 Temp_Matrix[12] * Temp_Matrix[5] * Temp_Matrix[11] -
					 Temp_Matrix[12] * Temp_Matrix[7] * Temp_Matrix[9];

				 Final_Matrix[9] = -Temp_Matrix[0] * Temp_Matrix[9] * Temp_Matrix[15] +
					 Temp_Matrix[0] * Temp_Matrix[11] * Temp_Matrix[13] +
					 Temp_Matrix[8] * Temp_Matrix[1] * Temp_Matrix[15] -
					 Temp_Matrix[8] * Temp_Matrix[3] * Temp_Matrix[13] -
					 Temp_Matrix[12] * Temp_Matrix[1] * Temp_Matrix[11] +
					 Temp_Matrix[12] * Temp_Matrix[3] * Temp_Matrix[9];

				 Final_Matrix[10] = Temp_Matrix[0] * Temp_Matrix[5] * Temp_Matrix[15] -
					 Temp_Matrix[0] * Temp_Matrix[7] * Temp_Matrix[13] -
					 Temp_Matrix[4] * Temp_Matrix[1] * Temp_Matrix[15] +
					 Temp_Matrix[4] * Temp_Matrix[3] * Temp_Matrix[13] +
					 Temp_Matrix[12] * Temp_Matrix[1] * Temp_Matrix[7] -
					 Temp_Matrix[12] * Temp_Matrix[3] * Temp_Matrix[5];

				 Final_Matrix[11] = -Temp_Matrix[0] * Temp_Matrix[5] * Temp_Matrix[11] +
					 Temp_Matrix[0] * Temp_Matrix[7] * Temp_Matrix[9] +
					 Temp_Matrix[4] * Temp_Matrix[1] * Temp_Matrix[11] -
					 Temp_Matrix[4] * Temp_Matrix[3] * Temp_Matrix[9] -
					 Temp_Matrix[8] * Temp_Matrix[1] * Temp_Matrix[7] +
					 Temp_Matrix[8] * Temp_Matrix[3] * Temp_Matrix[5];

				 Final_Matrix[12] = -Temp_Matrix[4] * Temp_Matrix[9] * Temp_Matrix[14] +
					 Temp_Matrix[4] * Temp_Matrix[10] * Temp_Matrix[13] +
					 Temp_Matrix[8] * Temp_Matrix[5] * Temp_Matrix[14] -
					 Temp_Matrix[8] * Temp_Matrix[6] * Temp_Matrix[13] -
					 Temp_Matrix[12] * Temp_Matrix[5] * Temp_Matrix[10] +
					 Temp_Matrix[12] * Temp_Matrix[6] * Temp_Matrix[9];

				 Final_Matrix[13] = Temp_Matrix[0] * Temp_Matrix[9] * Temp_Matrix[14] -
					 Temp_Matrix[0] * Temp_Matrix[10] * Temp_Matrix[13] -
					 Temp_Matrix[8] * Temp_Matrix[1] * Temp_Matrix[14] +
					 Temp_Matrix[8] * Temp_Matrix[2] * Temp_Matrix[13] +
					 Temp_Matrix[12] * Temp_Matrix[1] * Temp_Matrix[10] -
					 Temp_Matrix[12] * Temp_Matrix[2] * Temp_Matrix[9];

				 Final_Matrix[14] = -Temp_Matrix[0] * Temp_Matrix[5] * Temp_Matrix[14] +
					 Temp_Matrix[0] * Temp_Matrix[6] * Temp_Matrix[13] +
					 Temp_Matrix[4] * Temp_Matrix[1] * Temp_Matrix[14] -
					 Temp_Matrix[4] * Temp_Matrix[2] * Temp_Matrix[13] -
					 Temp_Matrix[12] * Temp_Matrix[1] * Temp_Matrix[6] +
					 Temp_Matrix[12] * Temp_Matrix[2] * Temp_Matrix[5];

				 Final_Matrix[15] = Temp_Matrix[0] * Temp_Matrix[5] * Temp_Matrix[10] -
					 Temp_Matrix[0] * Temp_Matrix[6] * Temp_Matrix[9] -
					 Temp_Matrix[4] * Temp_Matrix[1] * Temp_Matrix[10] +
					 Temp_Matrix[4] * Temp_Matrix[2] * Temp_Matrix[9] +
					 Temp_Matrix[8] * Temp_Matrix[1] * Temp_Matrix[6] -
					 Temp_Matrix[8] * Temp_Matrix[2] * Temp_Matrix[5];



				 Matrix_Determinant = Temp_Matrix[0] * Final_Matrix[0] + Temp_Matrix[1] * Final_Matrix[4] + Temp_Matrix[2] * Final_Matrix[8] + Temp_Matrix[3] * Final_Matrix[12];


				 Matrix_Determinant = 1.0f / Matrix_Determinant;

				 for (int i = 0; i < 16; i++)
				 {
					 Final_Matrix[i] *= Matrix_Determinant;
				 }

				 if (Matrix_Determinant != 0) {
					 return Final_Matrix;
				 }
				 else
					 return NULL;
			 }

		 }
	} 



	


