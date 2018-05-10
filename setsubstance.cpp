#include "stdafx.h"
#include "hrefprop.h"
#include <string.h>
#include "setsubstance.h" 
#include "initialDLL.h"
#include "mystrlib.h"
#include <stdlib.h>
#include <stdio.h>

char tempfld[lengthofstring];
char tempfldname[lengthofstring*ncmax];
bool molefracflag;

void SetSubstance(char* _FluidnameOrMixturenames)
{
	strcpy_s(fldname, _FluidnameOrMixturenames);
	molefracflag = false;
	ierr = 0;
	strcpy_s(hrf, HRF);
	strcpy_s(hfmix, FluidsDirectory);
	strcat_s(hfmix, HFMIX);
	GenerateName();
	if (!strchr(fldname, '|'))//not exposed as mixture,may be a directory or pure
	{
		char flddir[lengthofstring];
		strcpy_s(flddir, MixtureDirectory);
		strcat_s(flddir, fldname);
		char* r = Right(fldname, 4);
		if (strcmp(r, ".MIX"))
			strcat_s(flddir, ".MIX");
		free(r);
		FILE* mixfile;
		if (!fopen_s(&mixfile, flddir, "r"))//if mixture directory
		{
			molefracflag = true;
			char buffer[ncmax][lengthofstring];
			int i, j;
			char* buf;
			for (i = 0; fgets(buffer[i], lengthofstring, mixfile); i++)//read file
				Trim(buffer[i], '\n');
			buf = Right(buffer[3], 4);
			strcpy_s(fldname, "");
			for (i = 0; !strcmp(buf, ".FLD");)//read fluids
			{
				free(buf);
				strcat_s(fldname, buffer[i + 3]);
				strcat_s(fldname, "|");
				i++;
				buf = Right(buffer[3 + i], 4);
			}
			if (i != atol(buffer[2]))
			{
				ierr = 3;
				strcpy_s(herr, ".MIX file errer!");
				return;
			}
			for (j = 0; j < i; j++)//read mole fraction
			{
				x[j] = atof(buffer[j + i+3]);
			}
			free(buf);
			fclose(mixfile);
		}
	}
	CheckFldName();
	SETUPdll(nc, fldname, hfmix, hrf, ierr, herr, lengthofstring*ncmax, lengthofstring, lengthofreference, lengthofstring);
}
void SetMix(char* mix)
{
	char mixture[lengthofstring];
	strcpy_s(mixture, mix);
	Replace(mixture, ' ', '|');
	Replace(mixture, ',', '|');
	Replace(mixture, ';', '|');
	if (mixture[0] == '|')
		for (int i = 0; mixture[i]; i++)
			mixture[i] = mixture[i + 1];
	char buffer[ncmax][lengthofstring];
	int m = 0, n = 0;
	for (int i = 0; mixture[i]; i++)
	{

		if (mixture[i] == '|')
		{
			if (mixture[i - 1] != '|')
			{
				buffer[m][n] = '\0';
				m++;
				n = 0;
			}
		}
		else
		{
			buffer[m][n] = mixture[i];
			n++;
		}
	}
	buffer[m][n] = '\0';
	m++;
	for (int i = 0; i < m; i++)
		x[i] = atof(buffer[i]);
	
}
void GenerateName()
{
	UCase(fldname);
	Trim(fldname, ' ');
	Trim(fldname, '\'');
	Trim(fldname, '\"');
	Replace(fldname, ';', '|');
	Replace(fldname, ',', '|');
}
void CheckFldName()
{
	nc = 0;
	tempfldname[0] = '\0';
	int ptcf = 0, ptcb = -1, i;
	for (; fldname[ptcf]; ptcf++)
	{
		if (fldname[ptcf] == '|')
		{
			i = 0;
			ptcb++;
			while (ptcb < ptcf)
			{
				tempfld[i] = fldname[ptcb];
				i++;
				ptcb++;
			}
			tempfld[i] = '\0';
			if (i)
			{
				CheckName();
				strcat_s(tempfldname, tempfld);
				strcat_s(tempfldname, "|");
				nc++;
			}

		}

	}
	i = 0;
	ptcb++;
	while (ptcb < ptcf)
	{
		tempfld[i] = fldname[ptcb];
		i++;
		ptcb++;
	}
	tempfld[i] = '\0';
	if (i)
	{
		CheckName();
		strcat_s(tempfldname, tempfld);
		nc++;
	}
	else
	{
		for (; tempfldname[i]; i++);
		tempfldname[i - 1] = '\0';
	}
	strcpy_s(fldname, tempfldname);

}
void CheckName()
{
	//if (!strcmp(tempfld, "AIR"))strcpy_s(tempfld, "nitrogen;7812;argon b;0092;oxygen;2096");
	if (!strcmp(tempfld, "CARBONDIOXIDE"))strcpy_s(tempfld, "CO2");
	if (!strcmp(tempfld, "CARBONMONOXIDE"))strcpy_s(tempfld, "CO");
	if (!strcmp(tempfld, "CARBONYLSULFIDE"))strcpy_s(tempfld, "COS");
	if (!strcmp(tempfld, "CYCLOHEXANE"))strcpy_s(tempfld, "CYCLOHEX");
	if (!strcmp(tempfld, "CYCLOPROPANE"))strcpy_s(tempfld, "CYCLOPRO");
	if (!strcmp(tempfld, "DEUTERIUM"))strcpy_s(tempfld, "D2");
	if (!strcmp(tempfld, "HEAVYWATER"))strcpy_s(tempfld, "D2O");
	if (!strcmp(tempfld, "HYDROGENSULFIDE"))strcpy_s(tempfld, "H2S");
	if (!strcmp(tempfld, "IBUTANE"))strcpy_s(tempfld, "ISOBUTAN");
	if (!strcmp(tempfld, "ISOBUTANE"))strcpy_s(tempfld, "ISOBUTAN");
	if (!strcmp(tempfld, "ISOPENTANE"))strcpy_s(tempfld, "IPENTANE");
	if (!strcmp(tempfld, "NEOPENTANE"))strcpy_s(tempfld, "NEOPENTN");
	if (!strcmp(tempfld, "ISOHEXANE"))strcpy_s(tempfld, "IHEXANE");
	if (!strcmp(tempfld, "NITROUSOXIDE"))strcpy_s(tempfld, "N2O");
	if (!strcmp(tempfld, "PARAHYDROGEN"))strcpy_s(tempfld, "PARAHYD");
	if (!strcmp(tempfld, "PROPYLENE"))strcpy_s(tempfld, "PROPYLEN");
	if (!strcmp(tempfld, "SULFURHEXAFLUORIDE"))strcpy_s(tempfld, "SF6");
	if (!strcmp(tempfld, "DIMETHYLETHER"))strcpy_s(tempfld, "DME");
	if (!strcmp(tempfld, "BUTENE"))strcpy_s(tempfld, "1BUTENE");
	if (!strcmp(tempfld, "ISOBUTENE"))strcpy_s(tempfld, "IBUTENE");
	if (!strcmp(tempfld, "CIS-BUTENE"))strcpy_s(tempfld, "C2BUTENE");
	if (!strcmp(tempfld, "TRANS-BUTENE"))strcpy_s(tempfld, "T2BUTENE");
	if (!strcmp(tempfld, "TRif(LUOROIODOMETHANE"))strcpy_s(tempfld, "CF3I");
	if (!strcmp(tempfld, "PERFLUOROBUTANE"))strcpy_s(tempfld, "C4F10");
	if (!strcmp(tempfld, "PERFLUOROPENTANE"))strcpy_s(tempfld, "C5F12");
	if (!strcmp(tempfld, "NITROGEN TRif(LUORIDE"))strcpy_s(tempfld, "NF3");
	if (!strcmp(tempfld, "SULFURDIOXIDE"))strcpy_s(tempfld, "SO2");
	if (!strcmp(tempfld, "SULFURHEXAFLUORIDE"))strcpy_s(tempfld, "SF6");
	if (!strcmp(tempfld, "DODECANE"))strcpy_s(tempfld, "C12");
	if (!strcmp(tempfld, "DIMETHYLETHER"))strcpy_s(tempfld, "DME");
	char temp[lengthofstring];
	char* p = Right(tempfld, 4);
	strcpy_s(temp, tempfld);
	strcpy_s(tempfld, FluidsDirectory);
	strcat_s(tempfld, temp);
	if (strcmp(p, ".FLD"))
		strcat_s(tempfld, ".FLD");
	free(p);

}
