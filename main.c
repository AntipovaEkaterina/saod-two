#include <ctype.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "bstree.h"
#include "hashtab.h"


int getrand(int min, int max) //Рандом
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() //Подсчет времени
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

//#define IFILE "dictionaryns.dat"
//#define WordsCount 1259840
#define WordsCount 1283313  //Максимальное количесво слов

char *Words[WordsCount]; //Массив содержаший слова

void Read(char *IFILE)
{
	char word[100]= {' '};  //Одно слово
	uint32_t CountWord = 0, CountSpace = 0;
	FILE* f;
	printf("\tОткрытие файла: %s\n", IFILE);
	// Попытка открыть файл
	if((f = fopen(IFILE, "r")) == NULL)
	{
		// Провалилась
		perror("fopen");
		exit(1);
	}
	printf("\tЧтение файла\n");
	register int inWord = 0;
	int c;
	int WLen = 0;
	double tN = 0;
	tN = wtime();
	while((c = getc(f)) != EOF)
	{
		if(isspace(c) || c == '\n')
		{
			inWord = 0;
			++CountSpace;
			if (WLen)
			{
				word[WLen] = '\0';
				Words[CountWord - 1] = (char*)malloc((WLen + 1) * sizeof(char));
				strcpy(Words[CountWord - 1], word);
			}
			WLen = 0;
		}
		else
		{
			word[WLen] = c;
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
	tN = wtime() - tN;
	printf("\tФайл прочитан за %.8f сек. Содержит %d слов.\n", tN, CountWord);
//	printf("\tПрочитано слов: %d. Найдено пробелов/переносов: %d\n", CountWord, CountSpace-1);	
}

//Определение равномерности хеширования (Колизии)
unsigned int expe0(unsigned int Limit, int mode)
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i;
	unsigned int CollisionCount = 0;
	int *CollisionMas = (int*)malloc(HASHTAB_SIZE * sizeof(int));
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		CollisionMas[i] = 0;
	}
	for (i = 0; i < Limit; i++)
	{
		switch (mode)
		{
			case 1:
				CollisionMas[KP_Hash(Words[i])] += 1;
				break;
			case 0:
				CollisionMas[ADD_Hash(Words[i])] += 1;
				break;
		}
	}
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		if (CollisionMas[i] > 0)
		{
			CollisionMas[i]--;
			CollisionCount += CollisionMas[i];
			//printf("%d\t%d\n", i, CollisionMas[i]);
		}
			
	}
	return CollisionCount;
}

void expe1(unsigned int Limit) //Поиск элементов в среднем случае
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i, r, n;
	hashtab_init(hashtab);
	double tN = 0;
	
	// Создание хеш таблицы
	tN = wtime();
	printf("\tСоздание хеш таблицы из %d элементов: ", Limit);
  	for (i = 0; (i < WordsCount)&&(i < Limit) ; i++)
  	{
		hashtab_add(hashtab, Words[i], i, 0);
	}
	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	double rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = hashtab_lookup(hashtab, Words[r], 0)->value;
		rd += wtime() - tN;
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);



	// Создание бинарного дерева
	printf("\tСоздание бинарного дерева из %d элементов: ", Limit);
	struct bstree *tree ,*node;
	tree = bstree_create(Words[0],0);
	
	tN = wtime();
	for (i = 1; (i < WordsCount)&&(i < Limit) ; i++)
	{
		bstree_add(tree, Words[i], i);
	}

	tN = wtime() - tN;
	printf("Создано за %.8f сек.\n", tN);
	
	rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = bstree_lookup(tree, Words[r])->value;
		rd += wtime() - tN;
	//	printf("%d %d\n", n, r);
	//	printf("%d, %s за %.8f сек.\n", n, rd, Words[r]);
	//	printf("%.8f\n",wtime() - tN);
	//	
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);
}

void expe2(unsigned int Limit)  //Добавление элементов
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i, r, n;
	hashtab_init(hashtab);
	double tN = 0;
	
	// Создание хеш таблицы
	tN = wtime();
	printf("\tСоздание хеш таблицы из %d элементов: ", Limit);
  	for (i = 0; (i < WordsCount)&&(i < Limit) ; i++)
  	{
		hashtab_add(hashtab, Words[i], i, 0);
	}
	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	double rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = hashtab_lookup(hashtab, Words[r], 0)->value;
		rd += wtime() - tN;
	}
	//printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);
	tN = wtime();
		hashtab_add(hashtab, Words[++i], ++i, 0);
	tN = wtime() - tN;
	printf("\tДобавление нового элемента за %.8f сек.\n", tN);

	// Создание бинарного дерева
	printf("\tСоздание бинарного дерева из %d элементов: ", Limit);
	struct bstree *tree , *node;
	tree = bstree_create(Words[0],0);
	
	tN = wtime();
	for (i = 1; (i < WordsCount)&&(i < Limit) ; i++)
	{
		bstree_add(tree, Words[i], i);
	}

	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = bstree_lookup(tree, Words[r])->value;
		rd += wtime() - tN;

	}
	//printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);
	tN = wtime();
		bstree_add(tree, Words[++i], ++i);
	tN = wtime() - tN;
	printf("\tДобавление нового элемента за %.8f сек.\n", tN);
}


void expe6(unsigned int Limit, int hashmode) //Анализ эффективности хеш-функций
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i, n, r;
	hashtab_init(hashtab);
	double tN = 0;
	
	// Создание хеш таблицы
	tN = wtime();
	printf("\tСоздание хеш таблицы из %d элементов: ", Limit);
  	for (i = 0; (i < WordsCount)&&(i < Limit) ; i++)
  	{
		hashtab_add(hashtab, Words[i], i, hashmode);
	}
	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	double rd = 0;
	for (i = 0; i < 500000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = hashtab_lookup(hashtab, Words[r], hashmode)->value;
//	printf("%s %s\n", Words[n], Words[r]);
		rd += wtime() - tN;
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/500000, clNormal);
}

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
	if (4 > argc)
		return 1;

	int mode = atoi(argv[2]);
	unsigned int Lim = atol(argv[3]);

	Read(argv[1]);


	switch (mode)
	{
		case 0:
		 	printf("\tКолизий: %d для %d\n" ,expe0(Lim, atoi(argv[4])) , Lim);
		 	break;
		case 1:
			expe1(Lim);
			break;
		case 2:
			expe2(Lim);
			break;

		case 6:
			expe6(Lim, atoi(argv[4]));
			break;
	}


	return 0;
}
