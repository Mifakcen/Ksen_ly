// Ksen_Ly.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <fstream>
   // Про исходные данные нам не говорят
  // По этому будем предпологать, что у нас только три процесса
 //Также будем считать, что первая цифра данных процеса указывает на количество значений 
//Из этого следует, что у нас будет на одно значение больше 
Process *ProcessArray;
Command *command = NULL;
ifstream fileHelp;

int main()
{
	WriteProcces(ProcessArray);
	        //Наша строка содержит команду, которая делится на три значения :
	       //Первое это идентификатор функции (SUM)
		  //Второе это значение (на)которое мы собираемся (делить/умножать)прибавлять 
		 //Третье это номера процессов к которым мы будем применять действие
	setlocale(0, "RUS"); //Это делается для того что бы консоль говорила по русски
	do {
		cout << "\n Для получения справки введите '-help'  \nВведите команду : \n";
		command = out();
		if (command->com == "-INF") {
			inp(ProcessArray);
		}
		if (command->com == "-CLEAR") {
			system("CLS");
			continue;
		}
		if (command->com == "-SUM" || command->com == "-DIV" || command->com == "-MULTI") {
			for (int y = 1; y <= command->addressProc[0]; y++) {
				if ((command->addressProc[y]) < N) {
					if (ProcessArray[command->addressProc[y]].calculated) {
						if (command->com == "-SUM") {
							cout << "Sum\n";
							for (int i = 1; i <= ProcessArray[(command->addressProc[y])].Data[0]; i++) {
								ProcessArray[(command->addressProc[y])].Data[i] += (command->data);								
							}
							continue;
						}
						if (command->com == "-DIV") {
							if ((command->data) == 0) {
								cout << "      \n Деление на ноль ! \n";
								break;
							}
							cout << "Div\n";
							for (int i = 1; i <= ProcessArray[(command->addressProc[y])].Data[0]; i++) {
								ProcessArray[(command->addressProc[y])].Data[i] /= (command->data);								
							}
							continue;
						}
						if (command->com == "-MULTI") {
							if ((command->addressProc[y]) < N) {
								cout << "Multi\n";
								for (int i = 1; i <= ProcessArray[(command->addressProc[y])].Data[0]; i++) {
									ProcessArray[(command->addressProc[y])].Data[i] *= (command->data);									
								}
								continue;
							}
						}
						
					}
					else { cout << "\n  Доступ закрыт.\n"; continue; }
				}
				else cout << "   Ошибка!   Адрес процесса за пределами массива ! \n";

			}inp(ProcessArray);
		}
		if (command->com == "-HELP") {
			fileHelp.open("ReadME.txt");
			if (!fileHelp) {
				cout << "\n Файл не найден \n";
			}
			else {
				string str;
				while (getline(fileHelp,str))
				{
					cout << str<<endl;
				}
			}
			cout << "Help\n";
			continue;
		}
		delete[]command->addressProc;
	} while (command->com != "-EXIT");
	clear(command, ProcessArray);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
