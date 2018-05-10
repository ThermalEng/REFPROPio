#include "stdafx.h"
#include "hrefprop.h"
#include <string.h>
#include <stdlib.h>
void SetPath()
{
	char* env;
	size_t lengthofenv = (size_t)lengthofstring;
	if((_dupenv_s(&env,&lengthofenv,"Rpprefix")==0)&&(env!=NULL))
	{
		strcpy_s(PATH, env);
		free(env);
	}
	else
	{
		strcpy_s(PATH, "D:\\Program Files (x86)\\REFPROP");
	}

	if (PATH[strlen(PATH) - 1] == '\\')
		PATH[strlen(PATH) - 1] = '\0';
	strcpy_s(FluidsDirectory, PATH);
	strcpy_s(MixtureDirectory, PATH);

	strcat_s(FluidsDirectory, "\\fluids\\");
	strcat_s(MixtureDirectory, "\\mixtures\\");
}