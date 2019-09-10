#pragma warning(disable : 4996) //необходимо для использования устаревших функций (scanf)
#include <stdio.h>
/*определение символических констант*/
#define YES 1
#define NO 0
#define MAXLINE 1000
int N; // наибольшее количество букв в строке
void process_line(char buffer[]); // объявляем функцию

int main(void)
{
	char line[MAXLINE];
	printf ("Please, enter some words\nWARNING: words which consist of more than N letters will be deleted\n");
	gets (line);
	printf ("Enter N=");
	scanf ("%d", &N);
	process_line (line);
	printf ("Result:\n");
	puts (line);
	return 0;
}

void process_line (char buffer[])
{
	/*объявление и инициализация*/
	char c; // текущий символ
	int word = NO; // признак слова
	int overkill = NO; // индикатор перебора букв в слове
	int symb = NO; // индикатор наличия лишних символов
	char *in_ptr = buffer; // указатель на текущий символ входной строки
	char *out_ptr = buffer; // указатель на текущий символ выходной строки
	char *word_ptr = buffer; // указатель на начало слова

	do
	{
		c = *in_ptr; // взять текущий символ из буфера
		if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0' || c == '?' || c == '!' || c == ';' || c == ':' || 
			c == '-' || c == '_' || c == '(' || c == ')' || c == '\t' || c == '/' || c == '&' || c == '"') // разделитель найден
		{
			if (symb == NO && word == YES && overkill == NO || symb == YES && word == YES) // если подходит по-1му/2му условию выполнить...
			{
				while (word_ptr < in_ptr)  // слово не подлежит удалению оно копируется в результирующую строку
				{
					*out_ptr++ = *word_ptr++;  // копирование слова
				}
			}

			word = NO;
			symb = NO;
			overkill = NO;
			*out_ptr++ = c; // вставляем разделитель
		}

		else
		{
			if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // проверить не является ли этот символ лишним
			{
				symb = YES; // в слове есть лишний символ
			}
			if (word == NO) // найдена первая буква слова
			{
				word_ptr = in_ptr; // запомнить адрес начала слова
			}
			if (in_ptr - word_ptr + 1 > N) // проверка на <перебор> букв
			{
				overkill = YES; // перебор
			}
			word = YES;
		}
		in_ptr++;
	}
	while (c != '\0'); // продолжать до конца строки
}