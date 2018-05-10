#include "stdafx.h"
#include "mystrlib.h"
#include "hrefprop.h"
#include <stdlib.h>
#include <string.h>

char UCaseC(char _ch)
{
	if ((_ch >= 'a') && (_ch <= 'z'))
		return _ch-32;
	else return _ch;
}
void UCase(char* _str)
{
	int i;
	for (i = 0; _str[i]; i++)
		if ((_str[i] >= 'a') && (_str[i] <= 'z'))
			_str[i] -= 32;
}
void Replace(char* _str, char _de, char _re)
{
	for (int i = 0; _str[i]; i++)
		if (_str[i] == _de)
			_str[i] = _re;
}


char* Left(const char* _str, int _i)
{
	char* p = (char*)malloc((_i + 1) * sizeof(char));
	if ((int)strlen(_str) < _i)
	{
		int n = 0;
		for (; _str[n]; n++)
			p[n] = _str[n];
		p[n] = '\0';
	}
	else
	{
		for (int n = 0; n < _i; n++)
			p[n] = _str[n];
		p[_i] = '\0';
	}
	return p;
}
char* Right(const char* _str, int _i)
{
	char* p = (char*)malloc((_i + 1) * sizeof(char));
	int m = strlen(_str);
	if (m < _i)
	{
		int n = 0;
		for (; _str[n]; n++)
			p[n] = _str[n];
		p[n] = '\0';
	}
	else
	{
		for (int n = m; n > m - _i - 1; n--)
			p[n - m + _i] = _str[n];
	}
	return p;
}
void Trim(char* _str, char _ch)
{
	int i = 0, j = 0;
	for (i = 0; _str[i]; i++)
	{
		if (_str[i] == _ch)
		{
			for (j = i; _str[j]; j++)
				_str[j] = _str[j + 1];
		}
	}
}
