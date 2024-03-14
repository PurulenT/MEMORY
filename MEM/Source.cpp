#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

const int rows = 2;
const int cols = 8;


void hideX(int(*mainArr)[cols], int rows) //спрятать лампочку (после неправильного ответа)
{
	for (int i = 0; i == 0; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mainArr[i][j] = 0;
		}
	}
}

void establishValue(int(*mainArr)[cols], int rows)
{
	int freeNum[]{ 1,2,3,4,5,6,7,8 };
	int tempIndex;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0)
				mainArr[i][j] = 0;
			else
			{
				tempIndex = rand() % 8;
				while (freeNum[tempIndex] == 0)
					tempIndex = (tempIndex + 1) % 8;
				mainArr[i][j] = freeNum[tempIndex];
				freeNum[tempIndex] = 0;
			}
		}
	}
}

void printCircle(int(*mainArr)[cols], int rows)
{
	cout << mainArr[0][0] << " " << mainArr[0][1] << " " << mainArr[0][2] << " " << mainArr[0][3] << " " <<
		mainArr[0][4] << " " << mainArr[0][5] << " " << mainArr[0][6] << " " << mainArr[0][7] << " " << endl;
	cout << "Используйте цифры от 1 до 8..." << endl;
}

void firstClick(int(*mainArr)[cols], int rows, int *fValue, int *fValuePos) //обработка первичного ввода
{

	for (int i = 1; i == 1; i++)  // i всегда 1 так как подбирается значение для j (main[i][j])
	{
		for (int j = 0; j < cols; j++)
		{
			if (mainArr[i][j] == *fValue)
			{
				*fValuePos = j;
				mainArr[0][j] = 1;
			}
		}
		printCircle(mainArr, rows);
	}


}


void furtherClick(int(*mainArr)[cols], int rows, int *fValuePos) //обработка вторичного ввода
{
	mainArr[0][*fValuePos + 1] = 1;
	*fValuePos = (*fValuePos) + 1;
	printCircle(mainArr, rows);

}

bool OutOfCicle(int(*mainArr)[cols], bool end) //проверка что все элементы отгаданы
{
	end = true;
	for (int i = 0; i == 0; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mainArr[i][j] == 0)
				end = false;
		}
	}
	return end;
}




int Rekurs(int(*mainArr)[cols], int sValue, int fValuePos, bool end, int fValue)
{
	if (OutOfCicle(mainArr, end) == true)
	{
		cout << "return 1";
		return 1;
	}

	printCircle(mainArr, rows);
	cin >> fValue;
	firstClick(mainArr, rows, &fValue, &fValuePos);

	while (OutOfCicle(mainArr, end) == false)
	{

		cin >> sValue;
		if (fValuePos + 1 == 8)
		{
			fValuePos = -1;
		}
		if (mainArr[1][fValuePos + 1] == sValue)
		{
			furtherClick(mainArr, rows, &fValuePos);
		}
		else
		{
			printCircle(mainArr, rows);
			cout << "Fail!" << endl;
			Sleep(1000);
			system("cls");
			hideX(mainArr, rows);
			Rekurs(mainArr, sValue, fValuePos, end, fValue);
		}
	}


}


int main()
{
	bool end = true;



	setlocale(LC_ALL, "rus");
	srand(time(0));

	int mainArr[rows][cols];
	int fValue = 0;
	int fValuePos = 0;
	int sValue = 0;

	establishValue(mainArr, rows);

	Rekurs(mainArr, sValue, fValuePos, end, fValue); //вызов рекурсивной функции (ввод чисел игроком)


	cout << "COMPLETED";
	return 0;
}