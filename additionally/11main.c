#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define LETTER 1
#define NOT_THE_LETTER 077
#define MAXLEN 1000

int main(void)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // Получить стандартный дескриптор консольного окна
	FILE* fp; // входной файл

	char line[MAXLEN]; // строчка из файла
	char word[MAXLEN]; // слово
	int i;
	int flag; // флаг слово/разделитель
	int prev_flag; // предыдущее значение флага
	char* ptr; // указатель на строчку

	// определить цвета символов, разделителей и фона
	WORD foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN /*| FOREGROUND_RED*/; // цвет слов
	WORD foregroundColor1 = FOREGROUND_INTENSITY | FOREGROUND_RED; // цвет разделителей
	WORD backgroundColor = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED; // цвет фона
	WORD foregroundColor; // цвет символа
	WORD textAttribute; // атрибут текста - цвет символа и фона

	SetConsoleTextAttribute(hStdout, foregroundColor0 | backgroundColor);

	// открыть файл для чтения
	fp = fopen("C:\\Users\\User\\source\\repos\\file.txt", "rt");
	if (fp == NULL)
	{
		return; // ошибка при открытии файла
	}

	while (!feof(fp))
	{
		ptr = fgets(line, MAXLEN, fp);
		if (ptr == NULL)
		{
			break;
		}

		i = 0;
		prev_flag = flag = NOT_THE_LETTER;
		word[0] = '\0';

		while (*ptr != 0)
		{
			prev_flag = flag;// запомнить флаг
			if (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '\n')
			{
				flag = NOT_THE_LETTER;
			}
			else
			{
				flag = LETTER;
			}

			if (flag != prev_flag) // если слово закончилось
			{
				word[i] = '\0'; // закрыть слово
				foregroundColor = (prev_flag == LETTER) ? foregroundColor0 : foregroundColor1; // установить цвет символа (буква или разделитель)
				textAttribute = foregroundColor | backgroundColor;
				SetConsoleTextAttribute(hStdout, textAttribute);
				printf("%s", word); // вывести слово
				i = 0; // начать новое слово
			}
			word[i++] = *ptr++; // запомнить символ
		}

		
		if (i != 0) // если, выведено последнее слово в строке
		{
			word[i] = '\0'; // закрыть слово
			foregroundColor = (prev_flag == LETTER) ? foregroundColor0 : foregroundColor1; // установить цвет символа (буква или разделитель)
			textAttribute = foregroundColor | backgroundColor;

			SetConsoleTextAttribute(hStdout, textAttribute);
			printf("%s", word); // вывести слово
		}
	}
	printf("\n");
	// белые символы, черный фон
	SetConsoleTextAttribute(hStdout, 7);
	return 0;
}
