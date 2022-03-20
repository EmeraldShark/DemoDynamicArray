// Динамический ввод/вывод данных


#include <iostream>
#include <algorithm> // для std::sort
#include <fstream>   // файловый ввод/вывод


/*
	Общий алгоритм решения
	1. Ввод размерности А,В,С с консоли (из файла)
	2. Создание двумерных динамических массивов А,В,С
	3. Заполнение А,В,С с консоли (из файла)
	4. Столбец из А сравнивается на равенство хотя бы одному столбцу из матрицы В
		4.1 Если равенство не выполнено, столбец из А копируется в С
		4.2 Если равеноство выполнено, столбец в С остаётся нулевым
	5. Повторение пунтка 4 до последнего столбца А
	6. Сортировка и вывод элементов С (на консоль или в файл)

	А = |9 6|	В = |5 9|	-->		C = |0 6|	-->		Ответ: 0,6
		|9 6|		|5 9|				|0 6|

	А = |5 4|	В = |1 5|	-->		C = |5 4|	-->		Ответ: 4,5,8
		|8 4|		|8 4|				|8 4|
*/


// если данный столбец из матрицы А совпадает с каким либо столбцом из матрицы В, то возвращаем true
bool checkCols(int** matrixA, int** matrixB, int col, int size)
{
	for (int count = 0; count < size; ++count)
	{
		for (int row = 0; row < size; ++row)
		{
			if (matrixA[row][col] != matrixB[row][count]) // как только будут найдены различающиеся элементы в столбце матриц А и В
				break;									  // переходим к следующему столбцу матрицы В
			if (row+1 == size)							  // если равны последние элементы в столбце, то равны и все предыдущие
				return true;							  // иначе бы сработал оператор break
														  // как только нашлись одинаковые столбцы, проверку дальше проводить не нужно
														  // оставляем столбец из С нулевым
		}
	}
	return false;
}


int main()
{
	// осуществление файлового ввода данных, собирающихся из Matrix.txt
	std::ifstream fin ("Matrix.txt");
	if (!fin)
	{
		std::cout << "Can't open file for reading!\n";
		return -1;
	}


	// размерность матриц задаётся значением из Matrix.txt
	int size = 0;
	fin.ignore(255, ':');
	fin >> size;


	// для матриц, размерность которых задаётся пользователем во время выполнения программы, память следует выделять динамически
	// в качестве двумерного массива (матрицы) будет служить указатель на массив указателей
	int** arrayA = new int* [size], ** arrayB = new int* [size], ** arrayC = new int* [size];

	
	// в свою очередь, каждый такой указатель будет ссылаться на массив чисел
	// в итоге по завершении данного цикла получим матрицы размера size*size
	for (int i = 0; i < size; ++i)
	{
		arrayA[i] = new int[size]{};
		arrayB[i] = new int[size]{}; // предварительно заполняем массивы нулями
		arrayC[i] = new int[size]{};
	}

	
	// матрица А заполняется значениями из Matrix.txt
	fin.ignore(255, ':');
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
			fin >> arrayA[row][col];
	}


	// матрица B заполняется значениями из Matrix.txt
	fin.ignore(255, ':');
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
			fin >> arrayB[row][col];
	}


	// каждый столбец матрицы А проверяем на соответствие с каждым стобцом матрицы В
	// если соответствие не выполняется, записываем этот столбец в матрицу С
	for (int col = 0; col < size; ++col)
	{
		if (!checkCols(arrayA,arrayB,col,size))
		{
			for (int row = 0; row < size; ++row)
				arrayC[row][col] = arrayA[row][col];
		}
	}
	

	// перенос элементов матрицы С в одномерный массив для удобства сортировки
	int* sorted = new int[size * size];
	int count = 0;
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col, ++count)
			sorted[count] = arrayC[row][col];
	}


	// функцией std::sort распредяем элементы в порядке возрастания
	std::sort(sorted, sorted + size * size);


	// осуществление файлового вывода данных, записывающихся в Result.txt
	std::ofstream fout("Result.txt");
	if (!fout)
	{
		std::cout << "Can't open file for writing!\n";
		return -2;
	}
	fout << "The Result is: ";


	// вывод всех элементов матрицы С без повторений
	for (int kkk = 0; kkk < size * size - 1; ++kkk)
	{
		if (sorted[kkk] != sorted[kkk + 1])
			fout << sorted[kkk] << ", ";
	}
	fout << sorted[size*size-1];


	// освобождение памяти от созданных динамических переменных
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