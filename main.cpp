// ������������ ����/����� ������


#include <iostream>
#include <algorithm> // ��� std::sort
#include <fstream>   // �������� ����/�����


/*
	����� �������� �������
	1. ���� ����������� �,�,� � ������� (�� �����)
	2. �������� ��������� ������������ �������� �,�,�
	3. ���������� �,�,� � ������� (�� �����)
	4. ������� �� � ������������ �� ��������� ���� �� ������ ������� �� ������� �
		4.1 ���� ��������� �� ���������, ������� �� � ���������� � �
		4.2 ���� ���������� ���������, ������� � � ������� �������
	5. ���������� ������ 4 �� ���������� ������� �
	6. ���������� � ����� ��������� � (�� ������� ��� � ����)

	� = |9 6|	� = |5 9|	-->		C = |0 6|	-->		�����: 0,6
		|9 6|		|5 9|				|0 6|

	� = |5 4|	� = |1 5|	-->		C = |5 4|	-->		�����: 4,5,8
		|8 4|		|8 4|				|8 4|
*/


// ���� ������ ������� �� ������� � ��������� � ����� ���� �������� �� ������� �, �� ���������� true
bool checkCols(int** matrixA, int** matrixB, int col, int size)
{
	for (int count = 0; count < size; ++count)
	{
		for (int row = 0; row < size; ++row)
		{
			if (matrixA[row][col] != matrixB[row][count]) // ��� ������ ����� ������� ������������� �������� � ������� ������ � � �
				break;									  // ��������� � ���������� ������� ������� �
			if (row+1 == size)							  // ���� ����� ��������� �������� � �������, �� ����� � ��� ����������
				return true;							  // ����� �� �������� �������� break
														  // ��� ������ ������� ���������� �������, �������� ������ ��������� �� �����
														  // ��������� ������� �� � �������
		}
	}
	return false;
}


int main()
{
	// ������������� ��������� ����� ������, ������������ �� Matrix.txt
	std::ifstream fin ("Matrix.txt");
	if (!fin)
	{
		std::cout << "Can't open file for reading!\n";
		return -1;
	}


	// ����������� ������ ������� ��������� �� Matrix.txt
	int size = 0;
	fin.ignore(255, ':');
	fin >> size;


	// ��� ������, ����������� ������� ������� ������������� �� ����� ���������� ���������, ������ ������� �������� �����������
	// � �������� ���������� ������� (�������) ����� ������� ��������� �� ������ ����������
	int** arrayA = new int* [size], ** arrayB = new int* [size], ** arrayC = new int* [size];

	
	// � ���� �������, ������ ����� ��������� ����� ��������� �� ������ �����
	// � ����� �� ���������� ������� ����� ������� ������� ������� size*size
	for (int i = 0; i < size; ++i)
	{
		arrayA[i] = new int[size]{};
		arrayB[i] = new int[size]{}; // �������������� ��������� ������� ������
		arrayC[i] = new int[size]{};
	}

	
	// ������� � ����������� ���������� �� Matrix.txt
	fin.ignore(255, ':');
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
			fin >> arrayA[row][col];
	}


	// ������� B ����������� ���������� �� Matrix.txt
	fin.ignore(255, ':');
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
			fin >> arrayB[row][col];
	}


	// ������ ������� ������� � ��������� �� ������������ � ������ ������� ������� �
	// ���� ������������ �� �����������, ���������� ���� ������� � ������� �
	for (int col = 0; col < size; ++col)
	{
		if (!checkCols(arrayA,arrayB,col,size))
		{
			for (int row = 0; row < size; ++row)
				arrayC[row][col] = arrayA[row][col];
		}
	}
	

	// ������� ��������� ������� � � ���������� ������ ��� �������� ����������
	int* sorted = new int[size * size];
	int count = 0;
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col, ++count)
			sorted[count] = arrayC[row][col];
	}


	// �������� std::sort ���������� �������� � ������� �����������
	std::sort(sorted, sorted + size * size);


	// ������������� ��������� ������ ������, �������������� � Result.txt
	std::ofstream fout("Result.txt");
	if (!fout)
	{
		std::cout << "Can't open file for writing!\n";
		return -2;
	}
	fout << "The Result is: ";


	// ����� ���� ��������� ������� � ��� ����������
	for (int kkk = 0; kkk < size * size - 1; ++kkk)
	{
		if (sorted[kkk] != sorted[kkk + 1])
			fout << sorted[kkk] << ", ";
	}
	fout << sorted[size*size-1];


	// ������������ ������ �� ��������� ������������ ����������
	for (int i = 0; i < size; ++i)
	{
		delete[] arrayA[i];
		delete[] arrayB[i];
		delete[] arrayC[i];
	}
	delete[] arrayA;
	delete[] arrayB;
	delete[] arrayC;
	return 0;
}