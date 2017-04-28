#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "hashtab.h"

#define HASHTAB_SIZE 10000
#define HASHTAB_MUL  10

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main ()
{
	char words[51203][60], *w;
	int i, j, kol = 0;
	//int *col = &kol;
	double t, t2 = 0;
	FILE *f;
	struct listnode *node;
	struct listnode *hashtab[HASHTAB_SIZE];

	f=fopen("Dictionary.txt", "r");

	for(i = 0; i < 51203; i++)
		fgets(words[i], 51203, f);
	fclose(f);
	t = wtime();      
	hashtab_init(hashtab);
	printf("%d %x\n", kol, &kol);
	for(i = 1; i <= 51203; i++){
		hashtab_add(hashtab, words[i%51203], i, &kol);
		t = wtime() - t;
		if(i%5000 == 0){
			for(j=0;j<10000000;j++){
				w = words[rand()%51203];
				node = hashtab_lookup(hashtab, w);
				//hashtab_delete(hashtab, w);
			}
		printf("n = %d;\tElapsed time: %.8f sec. collision = %d\n", i, t, kol);
		kol = 0;
		}
	}
 	return 0;
}