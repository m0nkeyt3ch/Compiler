#pragma once
#define norw 13 /*no. of reserved words*/
#define tmax 100 /*Lenght of identifier table*/
#define nmax 14	/*max. no. of digits in numbers*/
#define al 10 /*length of identifiers*/
#define amax 2047 /*maximum address*/
#define levmax 3 /*maximum depth of block nesting*/
#define cxmax 200 /*size of code array*/

enum symbol {
	nul, ident, number, plus, minus, times, slash, oddsym, eql, neq,
	lss, leq, gtr, geq, lparen, rparen, comma, semicolon, period, becomes,
	beginsym, endsym, ifsym, thensym, whilesym, writesym, readsym, dosym,
	callsym, constsym, varsym, procsym,
};

FILE* fa1;
char ch; //last character read
enum symbol sym; //last symbol read
char id[al+1]; //las indetifier read
int num; //last number read
int cc, ll; // character and line count 
int cx; //code allocation address
char line[81];
char a[al+1]; //temporary

char word[norw][al]; //keep symbol
enum symbol wsym[norw]; //keep the identity
enum symbol ssym[256]; //the value 

FILE* fin;
FILE* fout;
char fname[al]; //file input name
int err;

#define getchdo			if(-1 == getch()) return -1;

void error(int n);