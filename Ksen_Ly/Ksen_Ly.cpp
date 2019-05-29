// Ksen_Ly.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <list>
/*

*/
struct Process
{
	float *Data;      // данные процесса, в случае отсутствия данных Data==NULL
	bool calculated; // флаг, true в случае если данные вычислены по формуле
};
struct Command
{
	string com;           //Команда которую вводит пользователь
	float data;         // Данные которое пользователь указывает как первый параметр 
	int  *addressProc; //Адреса процессов которые хочет изменить пользователь 
};
Command *out();
void inp(Process *);
int N = 3;                        //Количество доступных процессов
Process *ProcessArray = new Process[N];
   // Про исходные данные нам не говорят
  // По этому будем предпологать, что у нас только три процесса
 //Также будем считать, что первая цифра данных процеса указывает на количество значений 
//Из этого следует, что у нас будет на одно значение больше 

int main()
{
	string str;
	Command *command = NULL;        //Наша строка содержит команду, которая делится на три значения :
	setlocale(0, "RUS");           //Первое это идентификатор функции (SUM)
								  //Второе это значение (на)которое мы собираемся (делить/умножать)прибавлять 
								 //Третье это номера процессов к которым мы будем применять действие
	ProcessArray[0].Data = new float[6]{ 5, 1.1111, 11.488, 11, 0, 0.123 };
	ProcessArray[0].calculated = true;
	ProcessArray[1].Data = new float[6]{ 5, 56, 2.2222 , 23.1241, 1, 0 };
	ProcessArray[1].calculated = false;
	ProcessArray[2].Data = new float[6]{ 5, -38 ,23,3.3333333333 ,0, 1 };
	ProcessArray[2].calculated = true;

	do {
		cout << "\n Для получения справки введите '-help'  \nВведите команду : \n";
		command = out();
		cout <<command->addressProc[0];
		cout <<command->addressProc[1];
		cout <<command->addressProc[2];
		cout <<command->addressProc[3];
		if (command->com == "-INF") {
			inp(ProcessArray);
		}
		if (command->com == "-clear") {
			system("CLS");
			continue;
		}
		if (command->com == "-SUM" || command->com == "-DIV" || command->com == "MULTI") {
			for (int y = 1; y <= command->addressProc[0]; y++) {
				if ((command->addressProc[y]) < N) {
					if (ProcessArray[command->addressProc[y]].calculated) {
						if (command->com == "-SUM") {
							cout << "Sum\n";
							for (int i = 1; i < ProcessArray[(command->addressProc[y])].Data[0]; i++) {
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
							for (int i = 1; i < ProcessArray[(command->addressProc[y])].Data[0]; i++) {
								ProcessArray[(command->addressProc[y])].Data[i] /= (command->data);								
							}
							continue;
						}
						if (command->com == "-MULTI") {
							if ((command->addressProc[y]) < N) {
								cout << "Multi\n";
								for (int i = 1; i < ProcessArray[(command->addressProc[y])].Data[0]; i++) {
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
		if (command->com == "-help") {
			cout << "Help\n";
			continue;
		}
	} while (command->com != "-exit");
}

Command *out() {
	string str;
	string s;
	getline(cin, s,';');

	char flagC = ' ';

	int R_L = 0; //счетчик количества скобок (Если отличен от нуля, то скобок не хватает)
	int Size = 0; //cчетчик количества процессов
	flagC = ' ';

	int flagI = 1;      //флаг для этапа функции
	string flagD = ""; //флаг для стрингов
	int flagSize = 1; //флаг для оперантов

	for (int i = 0; i < s.size(); i++) {
		flagC = s[i];
		if (flagC != ' '  && flagC!='\n')
			str += flagC;
		if (flagC == '(') {
			R_L++;
			continue;
		}
		if (flagC == ')') {
			R_L--;
			continue;
		}
		if (flagC == '$') {
			Size++;
			continue;
		}
	}
	Command *comand = new Command;

	for (int i = 0; i < str.size(); i++) {
		flagC = str[i];
		if (flagC == '(') {
			flagI = 2;
			continue;
		};
		//if (flagC == '$') {flagI = 3;}
		if (flagI == 1) { 
			comand->com += flagC; 
			continue;
		};
		if (flagI == 2) {
			if (flagC == ',') {
				comand->data = stoi(flagD);
				flagI = 3;
				flagD = "";
				comand->addressProc = new int[Size + 1];//Выделили место
				comand->addressProc[0] = Size;     //определили количество оперантов
				cout << comand->addressProc[0];
				flagD = "";
				continue;
			}
			flagD += flagC;
			//comand->data += flagC;
			continue;
		};
		if (flagI == 3) {
			if (flagC == ',') {
				comand->addressProc[flagSize] = stoi(flagD);
				flagSize++;
				continue;
			}
			
			if (flagC == '$') {
				flagD = "";
				continue;
			}
			if (flagC == ')') {
				comand->addressProc[flagSize] = stoi(flagD);
				break;
			}
			//comand->addressProc += flagC;
			flagD += flagC;
			continue;
		};
	}
	return comand;
}

void inp(Process *ProcessArray) {
	for (int i = 0; i < N; i++) {
		cout<<"\n   Process #"<< i<< ":"<<endl;
		for (int j = 1; j < ProcessArray[i].Data[0]; j++) {
			cout << "       Data[" << j << "] = " << ProcessArray[i].Data[j];
		}
	}
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
