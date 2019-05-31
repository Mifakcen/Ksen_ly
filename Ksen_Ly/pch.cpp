// pch.cpp: исходный файл, соответствующий предкомпилированному заголовку; нужен для компиляции

#include "pch.h"

void WriteProcces(Process *&ProcessArray) {
	ProcessArray = new Process[N];
	for (int i = 4; i < N; i++) {
		ProcessArray[i].Data = new float[6]{-1,};
		ProcessArray[i].Data[0] = 5;
		ProcessArray[i].calculated = false;
	}
	ProcessArray[0].Data = new float[6]{ 5, 1.1111, 11.488, 11, 0, 0.123 };
	ProcessArray[0].calculated = true;
	ProcessArray[1].Data = new float[6]{ 5, 56, 2.2222 , 23.1241, 1, 0 };
	ProcessArray[1].calculated = false;
	ProcessArray[2].Data = new float[3]{ 2 ,23,3.3333333333 };
	ProcessArray[2].calculated = true;
	ProcessArray[3].Data = new float[11]{ 10 ,23,3.3333333333 };
	ProcessArray[3].calculated = false;
};
Command *out() {
	string str;
	string s;
	getline(cin, s, ';');

	char flagC = ' ';

	int R_L = 0; //счетчик количества скобок (Если отличен от нуля, то скобок не хватает)
	int Size = 0; //cчетчик количества процессов
	flagC = ' ';

	int flagI = 1;      //флаг для этапа функции
	string flagD = ""; //флаг для стрингов
	int flagSize = 1; //флаг для оперантов

	for (int i = 0; i < s.size(); i++) {
		flagC = s[i];
		if (flagC != ' '  && flagC != '\n')
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
	comand->addressProc = NULL;

	for (int i = 0; i < str.size(); i++) {
		flagC = str[i];
		if (flagC == '(') {
			flagI = 2;
			continue;
		};
		//if (flagC == '$') {flagI = 3;}
		if (flagI == 1) {
			comand->com += toupper(flagC);
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
		cout << "\n   Process #" << i << ":" << endl;
		for (int j = 1; j <= ProcessArray[i].Data[0]; j++) {
			cout << "       Data[" << j << "] = " << ProcessArray[i].Data[j];

		}
		cout << "\n                 Calculated -> "; //<< ProcessArray[i].calculated;
		ProcessArray[i].calculated ? cout << "True" : cout << "False";
	}
}
void clear(Command *command, Process *ProcessArray) { //Функция освобождение памяти выделенной через "new"
	delete[]command->addressProc;
	delete command;
	for (int i = 0; i < N; i++) {
		delete[]ProcessArray[i].Data;
	}
	delete ProcessArray;
}

// В целом этот файл можно пропустить, но не удаляйте его, если вы используете предкомпилированные заголовки.
