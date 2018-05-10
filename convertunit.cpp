#include "stdafx.h"
#include "convertunit.h"
#include"mystrlib.h"
#include<string.h>
#include<math.h>
#include "initialDLL.h"
#include "hrefprop.h"


const double CtoK = 273.15;                 //Exact conversion
const double FtoR = 459.67;               //Exact conversion
const double RtoK = 5.0 / 9.0;              //Exact conversion
const double HtoS = 3600;              //Exact conversion
const double ATMtoMPa = 0.101325;        //Exact conversion
const double BARtoMPA = 0.1;        //Exact conversion
const double KGFtoN = 98.0665 / 10.0;        //Exact conversion
const double INtoM = 0.0254;       //Exact conversion
const double FTtoM = 12.0 * INtoM;       //Exact conversion
const double LBMtoKG = 0.45359237;       //Exact conversion
const double CALtoJ = 4.184;        //Exact conversion (tc)
//const double CALtoJ  = 4.1868;                //Exact conversion(IT) (Use this one only with pure water)
const double MMHGtoMPA = ATMtoMPa / 760.0;    //Exact conversion
const double INH2OtoMPA = 0.000249082;

const double BTUtoKJ = CALtoJ * LBMtoKG * RtoK;
const double LBFtoN = LBMtoKG * KGFtoN;
const double IN3toM3 = INtoM * INtoM * INtoM;
const double FT3toM3 = FTtoM * FTtoM * FTtoM;
const double GALLONtoM3 = IN3toM3 * 231.0;
const double PSIAtoMPA = LBMtoKG / INtoM / INtoM * KGFtoN / 1000000.0;
const double FTLBFtoJ = FTtoM * LBFtoN;
const double HPtoW = 550.0 * FTLBFtoJ;
const double BTUtoW = BTUtoKJ * 1000.0;
const double LBFTtoNM = LBFtoN / FTtoM;


double UnitConvert(double _inpval, char _unittype, char* _oldunit, char* _newunit, double _molwt)
{
	char UniT = UCaseC(_unittype);

	return UnitConvertDef(UnitConvertDef(_inpval, UniT, _oldunit, 1, _molwt), UniT, _newunit, -1, _molwt);
}

double UnitConvertDef(double _inpval, char _unittype, char* _unit, int _directionflag, double _molwt)
{
	char unittype = UCaseC(_unittype);
	char unit[255];
	strcpy_s(unit, _unit);
	UCase(unit);
	Trim(unit, ' ');

	//-----------------------------------------------------------------------
	//   Temperature Conversion
	//-----------------------------------------------------------------------
	switch (unittype)
	{
	case 'T':
		if (!strcmp(unit, "K"))
			return _inpval;
		else if (!strcmp(unit, "C"))
			return _inpval + _directionflag * CtoK;
		else if (!strcmp(unit, "R"))
			return _inpval* pow(RtoK, _directionflag);
		else if (!strcmp(unit, "F"))
		{
			if (_directionflag == 1)
				//return RtoK * (_inpval + FtoR)    //Does not give exactly zero at 32 F
				return (_inpval - 32) * RtoK + CtoK;
			else
				//return _inpval / RtoK - FtoR      //Does not give exactly 32 at 273.15 K
				return (_inpval - CtoK) / RtoK + 32;
		}
		break;

		//-----------------------------------------------------------------------
		//   Pressure Conversion
		//-----------------------------------------------------------------------
	case 'P':
		if (!strcmp(unit, "PA"))
			return _inpval / pow(1000000, _directionflag);
		else if (!strcmp(unit, "KPA"))
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "MPA"))
			return _inpval;
		else if (!strcmp(unit, "GPA"))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "BAR"))
			return _inpval *pow(BARtoMPA, _directionflag);
		else if (!strcmp(unit, "KBAR"))
			return _inpval * pow((BARtoMPA * 1000), _directionflag);
		else if (!strcmp(unit, "ATM"))
			return _inpval * pow(ATMtoMPa, _directionflag);
		else if (!strcmp(unit, "KGF/CM^2") || (!strcmp(unit, "KG/CM^2")) || (!strcmp(unit, "ATA")) || (!strcmp(unit, "AT")) || (!strcmp(unit, "ATMA")))
			return _inpval * pow((KGFtoN / 100), _directionflag);
		else if (!strcmp(unit, "PSI") || (!strcmp(unit, "PSIA")))
			return _inpval * pow(PSIAtoMPA, _directionflag);
		else if (!strcmp(unit, "PSF"))
			return _inpval * pow((PSIAtoMPA / 144), _directionflag);
		else if (((!strcmp(unit, "MMHG")) || (!strcmp(unit, "TORR"))))
			return _inpval * pow(MMHGtoMPA, _directionflag);
		else if (!strcmp(unit, "CMHG"))
			return _inpval * pow((MMHGtoMPA * 10), _directionflag);
		else if (!strcmp(unit, "INHG"))
			return _inpval * pow((MMHGtoMPA * INtoM * 1000), _directionflag);
		else if (!strcmp(unit, "INH2O"))
			return _inpval * pow(INH2OtoMPA, _directionflag);
		else if (!strcmp(unit, "PSIG"))
		{
			if (_directionflag == 1)
				return PSIAtoMPA * _inpval + ATMtoMPa;
			else return (_inpval - ATMtoMPa) / PSIAtoMPA;
		}
		break;

		//-----------------------------------------------------------------------
		//   Density Conversion
		//-----------------------------------------------------------------------
	case 'D':
		if (_inpval == 0) return 1E-50;
		else if ((!strcmp(unit, "MOL/DM^3")) || (!strcmp(unit, "MOL/L")) || (!strcmp(unit, "KMOL/M^3")))
			return _inpval;
		else if ((!strcmp(unit, "MOL/CM^3")) || (!strcmp(unit, "MOL/CC")))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "MOL/M^3"))
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "KG/M^3"))
			return _inpval / pow(_molwt, _directionflag);
		else if ((!strcmp(unit, "KG/DM^3")) || (!strcmp(unit, "KG/L")))
			return _inpval * pow((1000 / _molwt), _directionflag);
		else if ((!strcmp(unit, "G/DM^3")) || (!strcmp(unit, "G/L")))
			return _inpval * pow((1 / _molwt), _directionflag);
		else if ((!strcmp(unit, "G/CC")) || (!strcmp(unit, "G/CM^3")) || (!strcmp(unit, "G/ML")))
			return _inpval * pow((1000 / _molwt), _directionflag);
		else if (!strcmp(unit, "G/DM^3"))
			return _inpval * pow((1 / _molwt), _directionflag);
		else if ((!strcmp(unit, "LBM/FT^3")) || (!strcmp(unit, "LB/FT^3")))
			return _inpval * pow((LBMtoKG / FT3toM3 / _molwt), _directionflag);
		else if (!strcmp(unit, "LBMOL/FT^3"))
			return _inpval * pow((LBMtoKG / FT3toM3), _directionflag);
		else if (!strcmp(unit, "SLUG/FT^3"))
			return _inpval * pow((LBMtoKG / FT3toM3 / _molwt * KGFtoN / FTtoM), _directionflag);
		else if (!strcmp(unit, "LBMOL/GAL"))
			return _inpval * pow((LBMtoKG / GALLONtoM3), _directionflag);
		else if ((!strcmp(unit, "LB/GAL")) || (!strcmp(unit, "LBM/GAL")))
			return _inpval * pow((LBMtoKG / GALLONtoM3 / _molwt), _directionflag);

		//-----------------------------------------------------------------------
		//   Specific Volume Conversion
		//-----------------------------------------------------------------------

		else if ((!strcmp(unit, "DM^3/MOL")) || (!strcmp(unit, "L/MOL")) || (!strcmp(unit, "M^3/KMOL")))
			return 1 / _inpval;
		else if ((!strcmp(unit, "CM^3/MOL")) || (!strcmp(unit, "CC/MOL")) || (!strcmp(unit, "ML/MOL")))
			return 1000 / _inpval;
		else if (!strcmp(unit, "M^3/MOL"))
			return 1 / _inpval / 1000;
		else if (!strcmp(unit, "M^3/KG"))
			return 1 / _inpval / _molwt;
		else if ((!strcmp(unit, "DM^3/KG")) || (!strcmp(unit, "L/KG")))
			return 1000 / _inpval / _molwt;
		else if ((!strcmp(unit, "CC/G")) || (!strcmp(unit, "CM^3/G")) || (!strcmp(unit, "ML/G")))
			return 1000 / _inpval / _molwt;
		else if (!strcmp(unit, "DM^3/G"))
			return 1 / _inpval / _molwt;
		else if ((!strcmp(unit, "FT^3/LBM")) || (!strcmp(unit, "FT^3/LB")))
			return 1 / _inpval * (LBMtoKG / FT3toM3 / _molwt);
		else if (!strcmp(unit, "FT^3/LBMOL"))
			return 1 / _inpval * (LBMtoKG / FT3toM3);
		else if (!strcmp(unit, "FT^3/SLUG"))
			return 1 / _inpval * (LBMtoKG / FT3toM3 / _molwt * KGFtoN / FTtoM);
		else if (!strcmp(unit, "GAL/LBMOL"))
			return 1 / _inpval * (LBMtoKG / GALLONtoM3);
		else if ((!strcmp(unit, "GAL/LB")) || (!strcmp(unit, "GAL/LBM")))
			return 1 / _inpval * (LBMtoKG / GALLONtoM3 / _molwt);
		break;

		//-----------------------------------------------------------------------
		//   Specific Energy and Enthalpy Conversions
		//-----------------------------------------------------------------------
	case 'H':
		if ((!strcmp(unit, "J/MOL")) || (!strcmp(unit, "KJ/KMOL")))
			return _inpval;
		else if (!strcmp(unit, "KJ/MOL"))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "MJ/MOL"))
			return _inpval * pow(1000000, _directionflag);
		else if ((!strcmp(unit, "KJ/KG")) || (!strcmp(unit, "J/G")))
			return pow(_molwt, _directionflag) * _inpval;
		else if (!strcmp(unit, "J/KG"))
			return pow((_molwt / 1000), _directionflag) * _inpval;
		else if (!strcmp(unit, "M^2/S^2"))
			return pow((_molwt / 1000), _directionflag)* _inpval;
		else if (!strcmp(unit, "FT^2/S^2"))
			return pow((_molwt / 1000 * FTtoM *FTtoM), _directionflag) * _inpval;
		else if ((!strcmp(unit, "CAL/MOL")) || (!strcmp(unit, "KCAL/KMOL")))
			return pow(CALtoJ, _directionflag) * _inpval;
		else if ((!strcmp(unit, "CAL/G")) || (!strcmp(unit, "KCAL/KG")))
			return pow((CALtoJ * _molwt), _directionflag)* _inpval;
		else if ((!strcmp(unit, "BTU/LBM")) || (!strcmp(unit, "BTU/LB")))
			return pow((BTUtoKJ / LBMtoKG * _molwt), _directionflag) * _inpval;
		else if (!strcmp(unit, "BTU/LBMOL"))
			return pow((BTUtoKJ / LBMtoKG), _directionflag)* _inpval;
		break;

		//-----------------------------------------------------------------------
		//   Entropy and Heat Capacity Conversions
		//-----------------------------------------------------------------------
	case 'S':
		if ((!strcmp(unit, "J/MOL-K")) || (!strcmp(unit, "KJ/KMOL-K")))
			return _inpval;
		else if (!strcmp(unit, "KJ/MOL-K"))
			return _inpval * pow(1000, _directionflag);
		else if ((!strcmp(unit, "KJ/KG-K")) || (!strcmp(unit, "J/G-K")))
			return pow(_molwt, _directionflag) * _inpval;
		else if (!strcmp(unit, "J/KG-K"))
			return pow((_molwt / 1000), _directionflag)* _inpval;
		else if ((!strcmp(unit, "BTU/LBM-R")) || (!strcmp(unit, "BTU/LB-R")))
			return pow((BTUtoKJ / LBMtoKG / RtoK * _molwt), _directionflag) * _inpval;
		else if (!strcmp(unit, "BTU/LBMOL-R"))
			return pow((BTUtoKJ / LBMtoKG / RtoK), _directionflag) * _inpval;
		else if ((!strcmp(unit, "CAL/G-K")) || (!strcmp(unit, "CAL/G-C")) || (!strcmp(unit, "KCAL/KG-K")) || (!strcmp(unit, "KCAL/KG-C")))
			return pow((CALtoJ * _molwt), _directionflag) * _inpval;
		else if ((!strcmp(unit, "CAL/MOL-K")) || (!strcmp(unit, "CAL/MOL-C")))
			return pow(CALtoJ, _directionflag)* _inpval;
		else if (!strcmp(unit, "FT-LBF/LBMOL-R"))
			return pow((FTLBFtoJ / LBMtoKG / RtoK / 1000), _directionflag) * _inpval;
		break;

		//-----------------------------------------------------------------------
		//   Speed of Sound Conversion
		//-----------------------------------------------------------------------
	case 'W':
		if (!strcmp(unit, "M/S"))
			return _inpval;
		else if (!strcmp(unit, "M^2/S^2"))
			return sqrt(_inpval);
		else if (!strcmp(unit, "CM/S"))
			return _inpval / pow(100, _directionflag);
		else if (!strcmp(unit, "KM/H"))
			return _inpval * pow((1000 / HtoS), _directionflag);
		else if (!strcmp(unit, "FT/S"))
			return _inpval *pow(FTtoM, _directionflag);
		else if (!strcmp(unit, "IN/S"))
			return _inpval * pow(INtoM, _directionflag);
		else if ((!strcmp(unit, "MILE/H")) || (!strcmp(unit, "MPH")))
			return _inpval * pow((INtoM * 63360 / HtoS), _directionflag);
		else if (!strcmp(unit, "KNOT"))
			return _inpval * pow(0.5144444444, _directionflag);
		else if (!strcmp(unit, "MACH"))
			return _inpval * pow(sqrt(1.4 * 298.15 * 8314.51 / 28.95853816), _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Viscosity Conversion	//-----------------------------------------------------------------------
	case 'U':
		if ((!strcmp(unit, "PA-S")) || (!strcmp(unit, "KG/M-S")))
			return _inpval;
		else if (!strcmp(unit, "MPA-S"))      //Note:  This is milliPa-s, not MPa-s
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "UPA-S"))
			return _inpval / pow(1000000, _directionflag);
		else if ((!strcmp(unit, "G/CM-S")) || (!strcmp(unit, "POISE")))
			return _inpval / pow(10, _directionflag);
		else if (!strcmp(unit, "CENTIPOISE"))
			return _inpval / pow(1000, _directionflag);
		else if ((!strcmp(unit, "MILLIPOISE")) || (!strcmp(unit, "MPOISE")))
			return _inpval / pow(10000, _directionflag);
		else if ((!strcmp(unit, "MICROPOISE")) || (!strcmp(unit, "UPOISE")))
			return _inpval / pow(10000000, _directionflag);
		else if ((!strcmp(unit, "LBM/FT-S")) || (!strcmp(unit, "LB/FT-S")))
			return _inpval * pow((LBMtoKG / FTtoM), _directionflag);
		else if (!strcmp(unit, "LBF-S/FT^2"))
			return _inpval * pow((LBFtoN / FTtoM / FTtoM), _directionflag);
		else if ((!strcmp(unit, "LBM/FT-H")) || (!strcmp(unit, "LB/FT-H")))
			return _inpval * pow((LBMtoKG / FTtoM / HtoS), _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Thermal Conductivity Conversion
		//-----------------------------------------------------------------------
	case 'K':
		if (!strcmp(unit, "MW/M-K"))
			return _inpval;
		else if (!strcmp(unit, "W/M-K"))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "G-CM/S^3-K"))
			return _inpval / pow(100, _directionflag);
		else if (!strcmp(unit, "KG-M/S^3-K"))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "CAL/S-CM-K"))
			return _inpval * pow((CALtoJ * 100000), _directionflag);
		else if (!strcmp(unit, "KCAL/HR-M-K"))
			return _inpval * pow((CALtoJ * 100000.0 * 1000.0 / 100.0 / 3600.0), _directionflag);
		else if ((!strcmp(unit, "LBM-FT/S^3-F")) || (!strcmp(unit, "LB-FT/S^3-F")))
			return _inpval * pow((1000 * LBMtoKG * FTtoM / RtoK), _directionflag);
		else if (!strcmp(unit, "LBF/S-F"))
			return _inpval * pow((1000 * LBFtoN / RtoK), _directionflag);
		else if (!strcmp(unit, "BTU/H-FT-F"))
			return _inpval * pow((1000 * BTUtoW / HtoS / FTtoM / RtoK), _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Joule-Thomson Conversion
		//-----------------------------------------------------------------------
	case 'J':
		if ((!strcmp(unit, "K/MPA")) || (!strcmp(unit, "C/MPA")))
			return _inpval;
		else if ((!strcmp(unit, "K/KPA")) || (!strcmp(unit, "C/KPA")))
			return _inpval * pow(1000, _directionflag);
		else if ((!strcmp(unit, "K/PA")) || (!strcmp(unit, "C/PA")))
			return _inpval * pow(1000000, _directionflag);
		else if (!strcmp(unit, "C/ATM"))
			return _inpval / pow(ATMtoMPa, _directionflag);
		else if (!strcmp(unit, "C/BAR"))
			return _inpval / pow(BARtoMPA, _directionflag);
		else if ((!strcmp(unit, "K/PSI")) || (!strcmp(unit, "K/PSIA")))
			return _inpval / pow(PSIAtoMPA, _directionflag);
		else if ((!strcmp(unit, "F/PSI")) || (!strcmp(unit, "F/PSIA")) || (!strcmp(unit, "R/PSIA")))
			return _inpval / pow((PSIAtoMPA / RtoK), _directionflag);
		break;
		//-----------------------------------------------------------------------
		//   Length Conversion
		//-----------------------------------------------------------------------
	case 'L':
		if ((!strcmp(unit, "METER")) || (!strcmp(unit, "M")))
			return _inpval;
		else if (!strcmp(unit, "DM"))
			return _inpval / pow(10, _directionflag);
		else if (!strcmp(unit, "CM"))
			return _inpval / pow(100, _directionflag);
		else if (!strcmp(unit, "MM"))
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "KM"))
			return _inpval * pow(1000, _directionflag);
		else if ((!strcmp(unit, "INCH")) || (!strcmp(unit, "IN")))
			return _inpval * pow(INtoM, _directionflag);
		else if ((!strcmp(unit, "FOOT")) || (!strcmp(unit, "FT")))
			return _inpval * pow(FTtoM, _directionflag);
		else if ((!strcmp(unit, "YARD")) || (!strcmp(unit, "YD")))
			return _inpval * pow(INtoM * 36, _directionflag);
		else if ((!strcmp(unit, "MILE")) || (!strcmp(unit, "MI")))
			return _inpval * pow(INtoM * 63360, _directionflag);
		else if (!strcmp(unit, "LIGHT YEAR"))
			return _inpval * pow(9.46055E+15, _directionflag);
		else if (!strcmp(unit, "ANGSTROM"))
			return _inpval / pow(10000000000, _directionflag);
		else if (!strcmp(unit, "FATHOM"))
			return _inpval * pow(FTtoM * 6, _directionflag);
		else if (!strcmp(unit, "MIL"))
			return _inpval * pow(INtoM / 1000, _directionflag);
		else if (!strcmp(unit, "ROD"))
			return _inpval * pow(INtoM * 16.5 * 12, _directionflag);
		else if (!strcmp(unit, "PARSEC"))
			return _inpval * pow(30837400000000 * 1000, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Area Conversion
		//-----------------------------------------------------------------------
	case 'A':
		if ((!strcmp(unit, "METER^2")) || (!strcmp(unit, "M^2")))
			return _inpval;
		else if (!strcmp(unit, "CM^2"))
			return _inpval / pow(10000, _directionflag);
		else if (!strcmp(unit, "MM^2"))
			return _inpval / pow(1000000, _directionflag);
		else if (!strcmp(unit, "KM^2"))
			return _inpval * pow(1000000, _directionflag);
		else if ((!strcmp(unit, "INCH^2")) || (!strcmp(unit, "IN^2")))
			return _inpval * pow(INtoM * INtoM, _directionflag);
		else if ((!strcmp(unit, "FOOT^2")) || (!strcmp(unit, "FT^2")))
			return _inpval * pow(FTtoM *FTtoM, _directionflag);
		else if ((!strcmp(unit, "YARD^2")) || (!strcmp(unit, "YD^2")))
			return _inpval * pow(((INtoM * 36) *(INtoM * 36)), _directionflag);
		else if ((!strcmp(unit, "MILE^2")) || (!strcmp(unit, "MI^2")))
			return _inpval * pow((INtoM * 63360) *(INtoM * 63360), _directionflag);
		else if (!strcmp(unit, "ACRE"))
			return _inpval * pow((INtoM * 36) *(INtoM * 36) * 4840, _directionflag);
		else if (!strcmp(unit, "BARN"))
			return _inpval * pow(1E-28, _directionflag);
		else if (!strcmp(unit, "HECTARE"))
			return _inpval * pow(10000, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Volume Conversion (Note: not specific volume)
		//-----------------------------------------------------------------------
	case 'V':
		if ((!strcmp(unit, "METER^3")) || (!strcmp(unit, "M^3")))
			return _inpval;
		else if (!strcmp(unit, "CM^3"))
			return _inpval / pow(1000000, _directionflag);
		else if ((!strcmp(unit, "LITER")) || (!strcmp(unit, "L")) || (!strcmp(unit, "DM^3")))
			return _inpval / pow(1000, _directionflag);
		else if ((!strcmp(unit, "INCH^3")) || (!strcmp(unit, "IN^3")))
			return _inpval * pow(IN3toM3, _directionflag);
		else if ((!strcmp(unit, "FOOT^3")) || (!strcmp(unit, "FT^3")))
			return _inpval * pow(IN3toM3 * 12.0 * 12.0 * 12.0, _directionflag);
		else if ((!strcmp(unit, "YARD^3")) || (!strcmp(unit, "YD^3")))
			return _inpval * pow(IN3toM3 * 36.0 * 36.0 * 36.0, _directionflag);
		else if ((!strcmp(unit, "GALLON")) || (!strcmp(unit, "GAL")))
			return _inpval * pow(GALLONtoM3, _directionflag);
		else if ((!strcmp(unit, "QUART")) || (!strcmp(unit, "QT")))
			return _inpval * pow(GALLONtoM3 / 4.0, _directionflag);
		else if ((!strcmp(unit, "PINT")) || (!strcmp(unit, "PT")))
			return _inpval * pow(GALLONtoM3 / 8.0, _directionflag);
		else if (!strcmp(unit, "CUP"))
			return _inpval * pow(GALLONtoM3 / 16.0, _directionflag);
		else if (!strcmp(unit, "OUNCE"))
			return _inpval * pow(GALLONtoM3 / 128.0, _directionflag);
		else if ((!strcmp(unit, "TABLESPOON")) || (!strcmp(unit, "TBSP")))
			return _inpval * pow(GALLONtoM3 / 256.0, _directionflag);
		else if ((!strcmp(unit, "TEASPOON")) || (!strcmp(unit, "TSP")))
			return _inpval * pow(GALLONtoM3 / 768.0, _directionflag);
		else if (!strcmp(unit, "CORD"))
			return _inpval * pow(FT3toM3 * 128.0, _directionflag);
		else if (!strcmp(unit, "BARREL"))
			return _inpval * pow(GALLONtoM3 * 42.0, _directionflag);
		else if (!strcmp(unit, "BOARD FOOT"))
			return _inpval * pow(IN3toM3 * 144.0, _directionflag);
		else if (!strcmp(unit, "BUSHEL"))
			return _inpval * pow(0.03523907016688, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Mass Conversion
		//-----------------------------------------------------------------------
	case 'M':
		if (!strcmp(unit, "KG"))
			return _inpval;
		else if (!strcmp(unit, "G"))
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "MG"))            //milligram
			return _inpval / pow(1000000, _directionflag);
		else if ((!strcmp(unit, "LBM")) || (!strcmp(unit, "LB")))
			return _inpval * pow(LBMtoKG, _directionflag);
		else if (!strcmp(unit, "GRAIN"))
			return _inpval * pow(LBMtoKG / 7000.0, _directionflag);
		else if (!strcmp(unit, "SLUG"))
			return _inpval * pow(KGFtoN * LBMtoKG / FTtoM, _directionflag);
		else if (!strcmp(unit, "TON"))
			return _inpval * pow(LBMtoKG * 2000, _directionflag);
		else if (!strcmp(unit, "TONNE"))
			return _inpval * pow(1000, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Force Conversion
		//-----------------------------------------------------------------------
	case 'F':
		if ((!strcmp(unit, "NEWTON")) || (!strcmp(unit, "N")))
			return _inpval;
		else if (!strcmp(unit, "MN")) //milliNewtons
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "KGF"))
			return _inpval * pow(KGFtoN, _directionflag);
		else if (!strcmp(unit, "DYNE"))
			return _inpval / pow(100000, _directionflag);
		else if (!strcmp(unit, "LBF"))
			return _inpval * pow(LBFtoN, _directionflag);
		else if (!strcmp(unit, "POUNDAL"))
			return _inpval * pow(LBMtoKG * FTtoM, _directionflag);
		else if (!strcmp(unit, "OZF"))
			return _inpval * pow(LBFtoN / 16, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Energy Conversion
		//-----------------------------------------------------------------------
	case 'E':
		if ((!strcmp(unit, "JOULE")) || (!strcmp(unit, "J")))
			return _inpval;
		else if (!strcmp(unit, "KJ"))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "MJ"))
			return _inpval * pow(1000000, _directionflag);
		else if (!strcmp(unit, "KW-H"))
			return _inpval * pow(HtoS * 1000, _directionflag);
		else if (!strcmp(unit, "CAL"))
			return pow(CALtoJ, _directionflag) * _inpval;
		else if (!strcmp(unit, "KCAL"))
			return _inpval * pow(CALtoJ * 1000, _directionflag);
		else if (!strcmp(unit, "ERG"))
			return _inpval / pow(10000000, _directionflag);
		else if (!strcmp(unit, "BTU"))
			return _inpval * pow(BTUtoKJ * 1000, _directionflag);
		else if (!strcmp(unit, "FT-LBF"))
			return _inpval * pow(FTLBFtoJ, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Power Conversion
		//-----------------------------------------------------------------------
	case 'Q':
		if ((!strcmp(unit, "WATT")) || (!strcmp(unit, "W")))
			return _inpval;
		else if ((!strcmp(unit, "KWATT")) || (!strcmp(unit, "KW")))
			return _inpval * pow(1000, _directionflag);
		else if (!strcmp(unit, "BTU/S"))
			return _inpval * pow(BTUtoW, _directionflag);
		else if (!strcmp(unit, "BTU/MIN"))
			return _inpval * pow(BTUtoW / 60, _directionflag);
		else if (!strcmp(unit, "BTU/H"))
			return _inpval * pow(BTUtoW / HtoS, _directionflag);
		else if (!strcmp(unit, "CAL/S"))
			return _inpval * pow(CALtoJ, _directionflag);
		else if (!strcmp(unit, "KCAL/S"))
			return _inpval * pow(CALtoJ * 1000, _directionflag);
		else if (!strcmp(unit, "CAL/MIN"))
			return _inpval * pow(CALtoJ / 60, _directionflag);
		else if (!strcmp(unit, "KCAL/MIN"))
			return _inpval * pow(CALtoJ / 60.0 * 1000, _directionflag);
		else if (!strcmp(unit, "FT-LBF/S"))
			return _inpval * pow(FTLBFtoJ, _directionflag);
		else if (!strcmp(unit, "FT-LBF/MIN"))
			return _inpval * pow(FTLBFtoJ / 60, _directionflag);
		else if (!strcmp(unit, "FT-LBF/H"))
			return _inpval * pow(FTLBFtoJ / HtoS, _directionflag);
		else if (!strcmp(unit, "HP"))
			return _inpval * pow(HPtoW, _directionflag);
		break;

		//-----------------------------------------------------------------------
		//   Surface Tension Conversion
		//-----------------------------------------------------------------------
	case 'N':
		if (!strcmp(unit, "N/M"))
			return _inpval;
		else if (!strcmp(unit, "MN/M"))
			return _inpval / pow(1000, _directionflag);
		else if ((!strcmp(unit, "DYNE/CM")) || (!strcmp(unit, "DYN/CM")))
			return _inpval / pow(1000, _directionflag);
		else if (!strcmp(unit, "LBF/FT"))
			return _inpval * pow(LBFTtoNM, _directionflag);
		break;
	case 'I'://KinematicViscosity
		char unitW[lengthofstring], unitL[lengthofstring];
		int i;
		for (i = 0; unit[i] != '^'; i++)
			unitL[i] = unit[i];
		unitL[i] = '\0';
		strcpy_s(unitW, unit);
		Trim(unitW, '^');
		Trim(unitW, '2');
		return _inpval*(UnitConvertDef(2, 'L', unitL, _directionflag, _molwt) - UnitConvertDef(1, 'L', unitL, _directionflag, _molwt)) * (UnitConvertDef(2, 'W', unitW, _directionflag, _molwt) - UnitConvertDef(1, 'W', unitW, _directionflag, _molwt));
		break;

	}
	strcpy_s(herr, "Undefined input unit");
	ierr = 5;
	return 0;
}