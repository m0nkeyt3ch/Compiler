#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

//#define CODE "H:\\GitHub\\Compiler\\Homework\\ConsoleApplication1\\Debug\\76066001_test.txt"
//#define RESULT "H:\\GitHub\\Compiler\\Homework\\ConsoleApplication1\\Debug\\76066001_res3.txt"

char *prog, token[10]; //source program input (prog), word storage (token)
char ch;
char sym[10];
//syn word number
int syn, p, m = 0, n, line, sum = 0;

//rwtab is keyword list
const char *rwtab1[10] = { "begin","if","then","while","do","end" };
const char *rwtab2[5] = { "const","var","procedure","call", "odd" };

void scaner()
{
	//function for scan the file
	for (n = 0; n < 10; n++)
		//token store the word
		token[n] = NULL;
	ch = prog[p++];

	//remove space
	while (ch == ' ')
	{
		ch = prog[p];
		p++;
	}

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))  //must alphabeth because this is The Header
	{
		m = 0;
		//after Header can be number / alphabeth
		while ((ch >= '0'&&ch <= '9') || (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		//Identity
		token[m++] = '\0';
		p--;
		syn = 10;
		strcpy(sym, "IDEN");

		//decalre is a keyword or a label
		for (n = 0; n < 6; n++)
			if (strcmp(token, rwtab1[n]) == 0)
			{
				syn = n + 1;
				strcpy(sym, "TKN");
				break;
			}
		for (n = 0; n < 5; n++)
		{
			if (strcmp(token, rwtab2[n]) == 0)
			{
				syn = n + 31;
				strcpy(sym, "TKN");
				break;
			}
		}
	}
	else if ((ch >= '0'&&ch <= '9'))  //if number put in sum
	{
		sum = 0;
		while ((ch >= '0'&&ch <= '9'))
		{
			//Process decimal Number (整数)
			sum = sum * 10 + ch - '0';
			ch = prog[p++];
		}
		p--;
		syn = 11;
		strcpy(sym, "NUM");
		//If greater than 32767 will error
		if (sum > 32767)
			syn = -1;
	}
	else switch (ch)   //Another symbol
	{
	case '<':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '>')
		{
			//Is Not Same
			syn = 21;
			strcpy(sym, "NEQ");
			token[m++] = ch;
		}
		else if (ch == '=')
		{
			//Less Equal
			syn = 22;
			strcpy(sym, "LEQ");
			token[m++] = ch;
		}
		else
		{
			//Is Less Than
			syn = 23;
			strcpy(sym, "LSS");
			p--;
		}
		break;
	case '>':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			//greater equal
			syn = 24;
			strcpy(sym, "GEQ");
			token[m++] = ch;
		}
		else
		{
			//greater than
			syn = 20;
			strcpy(sym, "GTR"); 
			p--;
		}
		break;
	case ':':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			//Is Becomes (:=)
			syn = 18;
			strcpy(sym, "BECOMES");
			token[m++] = ch;
		}
		else
		{
			//Is Colon (:)
			syn = 17;
			strcpy(sym, "COLON");
			p--;
		}
		break;
	case '*':
		syn = 13;
		strcpy(sym, "MULTI");
		token[0] = ch;
		break;
	case '/':
		syn = 14;
		strcpy(sym, "DIVIDE");
		token[0] = ch;
		break;
	case '+':
		syn = 15;
		strcpy(sym, "PLUS");
		token[0] = ch;
		break;
	case '-':
		syn = 16;
		strcpy(sym, "MINUS");
		token[0] = ch;
		break;
	case '=':
		syn = 25;
		strcpy(sym, "SYMBOL");
		token[0] = ch;
		break;
	case ';':
		syn = 26;
		strcpy(sym, "SEMICOLON");
		token[0] = ch;
		break;
	case '(':
		syn = 27;
		strcpy(sym, "LPAREN");
		token[0] = ch;
		break;
	case ')':
		syn = 28;
		strcpy(sym, "RPAREN");
		token[0] = ch;
		break;
	case ',':
		syn = 29;
		strcpy(sym, "COMMA");
		token[0] = ch;
		break;
	case '!':
		syn = 30;
		strcpy(sym, "SYMBOL");
		token[0] = ch;
		break;
	case '.':
		//if 
		syn = 0;
		strcpy(sym, "PERIOD");
		token[0] = ch;
		break;
	case '\'':
		syn = 31;
		strcpy(sym, "QUOTATION");
		token[0] = ch;
		break;
	case '\n':
		//if new line , line + 1, syn = -2
		syn = -2;
		break;
	default:
		//if not symbol / anything will error
		syn = -1;
		break;
	}
}

/*
read the source file(.txt)
*/
int read(char fname[])
{
	FILE *fp;
	fp = fopen(fname, "r");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		int file_size;
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		prog = (char *)malloc(file_size * sizeof(char));
		fread(prog, file_size, sizeof(char), fp);
		//close the file stream
		fclose(fp);
		return 1;
	}
	else
		return 0;
}

int main()
{
	int p = 0;
	int line = 1;
	char result[20], fname[150];
	cout<< "Input your input and output file name (.txt)" << endl;
	cin >> fname;
	cout<<"\n";
	cin >> result;
	ofstream outfile(result);

	cout << "loading......" << endl;
	//Sleep(3000);
	//read the source file
	
	if(read(fname))
	{
		p = 0;
		outfile << "Result of the analyse :" << endl;
		outfile << "line" << " " << "Code" << " " << "Category" << " " << "Value" <<endl;
		outfile <<"\n";
		do
		{
			scaner();
			switch (syn)
			{
			case 11:
				cout << line << " " << syn << ": " << sym << " " << sum << endl;
				outfile << line << " " << syn  << ": " << sym << " " << sum << endl;
				break;
			case -1:
				cout << "Error in line" << " " << line << "!" << endl;
				outfile << "Error in line" << " " << line << "!" << endl;
				break;
			case -2:
				line = line++;
				break;
			default:
				cout << line << " " << syn << ": " << sym << " " << token << endl;
				outfile << line << " " << syn << ": " << sym << " " << token << endl;
				break;
			}
		} while (syn != 0);
		outfile.close();
		cout << "Analyse Complete, please check the result file"<< endl;
	}
	else
	{
		cout << "File Not Found" <<endl;
	}
	system("pause");
	return 0;
}