#pragma once
#ifndef EX02_HELP_H
#define EX02_HELP_H

bool IsAlpha(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return true;
	}
	return false;
}

bool IsDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	return false;
}
bool IsAlphaOrNum(char ch)
{
	if(IsAlpha(ch))
	{
		return true;
	}
	if (IsDigit(ch))
	{
		return true;
	}
	return false;
}
#endif //EX02_HELP_H
