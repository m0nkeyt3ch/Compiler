// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pl0.h"
#define _CRT_SECURE_NO_WARNINGS 1

void error(int n)
{
	char space[81];
	memset(space, 32, 81);
	space[cc-1] = 0;
	printf("****Error\n");
	fprintf(fa1, "****Error\n");
	err++;
}

int getch()
{
	if (cc == ll)
	{
		if (feof(fin))
		{
			printf("Read Complete");
			return -1;
		}
		ll = 0;
		cc = 0;
		//printf("%d ", cx);
		//fprintf(fa1, "%d", cx);
		ch = ' ';
		while(ch != 10)
		{
			if(fscanf(fin, "%c", &ch) == EOF)
			{
				line[ll] = 0;
				break;
			}
			printf("%c", ch);
			fprintf(fa1, "%c", ch);
			line[ll] = ch;
			ll++;
		}
		printf("\n");
		//fprintf(fa1, "\n");
	}
	ch = line[cc];
	cc++;
	return 0;
}

int getsym()
{
	int i, j, k;
	while(ch == ' ' || ch == 10 || ch == 9)
	{
		getchdo;
	}

	if(ch >= 'a' && ch <= 'z')
	{
		k = 0;
		do
		{
			if (k < al)
			{
				a[k] = ch;
				k++;
			}
			getchdo;
		}while(ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
		
		a[k] = 0;
		strcpy(id, a);
		i = 0;
		j = norw - 1;
		do
		{
			k = (i + j) / 2;
			if(strcmp(id, word[k]) <= 0)
				j = k - 1;
			if(strcmp(id, word[k]) >= 0)
				i = k + 1;
		} while (i <= j);
		
		if(i -1 > j)
		{
			sym = wsym[k];
		}
		else
		{
			sym = ident;
		}
	}
	else
	{
		if (ch >= '0' && ch <= '9')
		{
			k = 0;
			num = 0;
			sym = number;
			do
			{
				num = num * 10 + ch - '0';
				k++;
				getchdo;
			}while(ch >= '0' && ch <= '9');
			k--;
			if (k > nmax)
			{
				error(30);
			}
		}
		else
		{
			if (ch == ':')
			{
				getchdo;
				if (ch == '=')
				{
					sym = becomes;
					getchdo;
				}
				else
				{
					sym = nul;
				}
			}
			else
			{
				if (ch == '<')
				{
					getchdo;
					if (ch == '=')
					{
						sym = leq;
						getchdo;
						printf("%s", sym);
					}
					else
					{
						sym = lss;
					}
				}
				else
				{
					if (ch == '>')
					{
						getchdo;
						if (ch == '=')
						{
							sym = geq;
							getchdo;
						}
						else
						{
							sym = gtr;
						}
					}
					else
					{
						sym = ssym[ch];
						if (sym != period)
						{
							getchdo;
						}
						else
							return -1;
					}
				}
			}
		}
	}
	return 0;
}

void init()
{
	int i;
	for(i = 0; i < 256; i++)
	ssym[i] = nul;
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym['='] = eql;
	ssym[','] = comma;
	ssym['.'] = period;
	ssym['#'] = neq;
	ssym[';'] = semicolon;

	strcpy(&(word[0][0]), "begin");
	strcpy(&(word[1][0]), "call");
	strcpy(&(word[2][0]), "const");
	strcpy(&(word[3][0]), "do");
	strcpy(&(word[4][0]), "end");
	strcpy(&(word[5][0]), "if");
	strcpy(&(word[6][0]), "odd");
	strcpy(&(word[7][0]), "procedure");
	strcpy(&(word[8][0]), "read");
	strcpy(&(word[9][0]), "then");
	strcpy(&(word[10][0]), "var");
	strcpy(&(word[11][0]), "while");
	strcpy(&(word[12][0]), "write");

	wsym[0] = beginsym;
	wsym[1] = callsym;
	wsym[2] = constsym;
	wsym[3] = dosym;
	wsym[4] = endsym;
	wsym[5] = ifsym;
	wsym[6] = oddsym;
	wsym[7] = procsym;
	wsym[8] = readsym;
	wsym[9] = thensym;
	wsym[10] = varsym;
	wsym[11] = whilesym;
	wsym[12] = writesym;

}
int main()
{
	printf("Insert Your File\n");
	scanf("%s", fname);
	fin = fopen(fname, "r");
	if (fin)
	{
		printf("Insert Result File Name\n");
		scanf("%s", fname);
		fa1 = fopen(fname, "w");
		init();
		err = 0;
		cc = cx = ll = 0;
		ch = ' ';
		while (getsym() != -1)
		{

		}
		printf("Analyse Complete ");
	}
	else
	{
		printf("File Not Found\n");
	}
	printf("\n");
    return 0;
}

