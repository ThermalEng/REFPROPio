//// CPP programmed by;
// LI Minchao
// tech center of DBC
// chengdu,sichuan,China
// minchao_li@126.com

//This c program rewrote the demonstrates explicitly linking to the subroutines available in
// refprop.dll. You can call the subroutines the same way as in the refprop.xls. In order to
//link this code hrefprop.h  must be available in the current directory. And PATH in 
//hrefrop.h should first be definated the REFPROP path. You can also package it into a dll 
//dynamic library to conveniently call the subroutines.
//
#include "stdafx.h"
#include "hrefprop.h"
#include "initialDLL.h"
#include "convertunit.h"
#include <string.h>



//_CompFlag 0£ºbulk 1:liquidphase 2:vapor phase
double MoleWeight(int _CompFlag)
{
	double MolWt;
	switch (_CompFlag)
	{
	case 0:
		WMOLdll(x, MolWt);
		break;
	case 1:
		WMOLdll(xliq, MolWt);
		break;
	case 2:
		WMOLdll(xvap, MolWt);
		break;
	}
	return MolWt;
}
double Temperature(char* _Unit)
{
	return UnitConvertDef(t, 'T', _Unit, -1, 0);
}
double Pressure(char* _Unit)
{
	return UnitConvertDef(p / 1000.0, 'P', _Unit, -1, 0);
}
double Density(char* _Unit)
{
	return UnitConvertDef(d, 'D', _Unit, -1, MoleWeight(0));
}
double LiquidDensity(char* _Unit)
{
	return UnitConvertDef(Dl, 'D', _Unit, -1, MoleWeight(1));
}
double VaporDensity(char* _Unit)
{
	return UnitConvertDef(Dv, 'D', _Unit, -1, MoleWeight(2));
}
double Volume(char* _Unit)
{
	return UnitConvertDef(d, 'D', _Unit, -1, MoleWeight(0));
}
double Energy(char* _Unit)
{
	return UnitConvertDef(e, 'H', _Unit, -1, MoleWeight(0));
}
double Enthalpy(char* _Unit)
{
	return UnitConvertDef(h, 'H', _Unit, -1, MoleWeight(0));
}
double LiquidEnthalpy(char* _Unit)
{

	if (q < 0.0 || q > 1.0)
	{
		strcpy_s(herr, "Inputs are single phase");
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		return UnitConvertDef(h, 'H', _Unit, -1, MoleWeight(0));
	}
	else
	{
		THERMdll(t, Dl, xliq, p, el, hl, sl, Cvl, Cpl, wl, hjt);
		return UnitConvertDef(hl, 'H', _Unit, -1, MoleWeight(1));
	}
}
double VaporEnthalpy(char* _Unit)
{

	if (q < 0.0 || q > 1.0)
	{
		strcpy_s(herr, "Inputs are single phase");
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		return UnitConvertDef(h, 'H', _Unit, -1, MoleWeight(0));
	}
	else
	{
		THERMdll(t, Dv, xvap, p, ev, hv, sv, Cvv, Cpv, wv, hjt);
		return UnitConvertDef(hv, 'H', _Unit, -1, MoleWeight(2));
	}
}
double Entropy(char* _Unit)
{
	return UnitConvertDef(s, 'S', _Unit, -1, MoleWeight(0));
}
double LiquidEntropy(char* _Unit)
{

	if (q < 0.0 || q > 1.0)
	{
		strcpy_s(herr, "Inputs are single phase");
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		return UnitConvertDef(s, 'S', _Unit, -1, MoleWeight(0));
	}
	else
	{
		THERMdll(t, Dl, xliq, p, el, hl, sl, Cvl, Cpl, wl, hjt);
		return UnitConvertDef(sl, 'S', _Unit, -1, MoleWeight(1));
	}
}
double VaporEntropy(char* _Unit)
{

	if (q < 0.0 || q > 1.0)
	{
		strcpy_s(herr, "Inputs are single phase");
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		return UnitConvertDef(s, 'S', _Unit, -1, MoleWeight(0));
	}
	else
	{
		THERMdll(t, Dv, xvap, p, ev, hv, sv, Cvv, Cpv, wv, hjt);
		return UnitConvertDef(sv, 'S', _Unit, -1, MoleWeight(2));
	}
}
double Cp(char* _Unit)
{
	return UnitConvertDef(Cpcalc, 'S', _Unit, -1, MoleWeight(0));
}
double Cv(char* _Unit)
{
	return UnitConvertDef(Cvcalc, 'S', _Unit, -1, MoleWeight(0));
}
double SpeedOfSound(char* _Unit)
{
	return UnitConvertDef(w, 'W', _Unit, -1, MoleWeight(0));
}
double LatentHeat(char* _Unit)
{
	if (q < 0.0 || q > 1.0)
	{
		strcpy_s(herr, "Inputs are single phase");
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		return 0;
	}
	else return VaporEnthalpy(_Unit) - LiquidEnthalpy(_Unit);
}
double VaporizationHeat(char* _Unit)
{
	return LatentHeat(_Unit);
}
double LHV(char* _Unit)
{
	double hg, hn;
	HEATdll(t, d, x, hg, hn, ierr, herr, 255);
	return UnitConvertDef(hg, 'H', _Unit, -1, MoleWeight(0));
}
double LLV(char* _Unit)
{
	double hg, hn;
	HEATdll(t, d, x, hg, hn, ierr, herr, 255);
	return UnitConvertDef(hn, 'H', _Unit, -1, MoleWeight(0));
}
double GrossHeatingValue(char* _Unit)
{
	return LHV(_Unit);
}
double NetHeatingValue(char* _Unit)
{
	return LLV(_Unit);
}
double JouleThomson(char* _Unit)
{
	THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
	return UnitConvertDef(hjt*1000.0, 'J', _Unit, -1, 0);
}
double* MoleFraction()
{
	return x;
}
double* LiquidMoleFraction()
{
	return xliq;
}
double* VaporMoleFraction()
{
	return xvap;
}
double Viscosity(char* _Unit)
{
	TRNPRPdll(t, d, x, eta, tcx, ierr, herr, 255);
	if (q > 0 && q < 1)
	{
		eta = -9999999;
		strcpy_s(herr, "Not pure fluid.");
	}
	if (!eta) strcpy_s(herr, "Unable to calculate property");
	return  UnitConvertDef(eta*0.000001, 'U', _Unit, -1, MoleWeight(0));
}
double ThermalConductivity(char* _Unit)
{
	TRNPRPdll(t, d, x, eta, tcx, ierr, herr, 255);
	if (q > 0 && q < 1)
	{
		tcx = -9999999;
		strcpy_s(herr, "Not pure fluid.");
	}
	return UnitConvertDef(tcx * 1000, 'K', _Unit, -1, MoleWeight(0));
}
double KinematicViscosity(char* _Unit)
{
	TRNPRPdll(t, d, x, eta, tcx, ierr, herr, 255);
	if (!eta)
	{
		strcpy_s(herr, "Unable to calculate property");
		return 0;
	}
	if (q > 0 && q < 1)
	{
		tcx = -9999999;
		strcpy_s(herr, "Not pure fluid.");
	}
	else
		eta = eta / d / MoleWeight(0) / 1000000;//m^2/s
	return UnitConvertDef(eta, 'I', _Unit, -1, MoleWeight(0));
}
double Prandtl(char* _Unit)
{
	TRNPRPdll(t, d, x, eta, tcx, ierr, herr, 255);
	if (q > 0 && q < 1)
	{
		strcpy_s(herr, "Not pure fluid.");
		return 0;
	}

	if (tcx == 0 || eta == 0)
	{

		strcpy_s(herr, "Unable to calculate property");
		return 0;
	}
	THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
	return eta * Cpcalc / tcx / MoleWeight(0) / 1000;
}
double SurfaceTension(char* _Unit)
{
	double sigma;
	if (q >= 0 && q <= 1)
	{
		SURFTdll(t, Dl, xliq, sigma, ierr, herr, 255);
		wm = MoleWeight(1);
	}
	else
	{
		SURFTdll(t, d, x, sigma, ierr, herr, 255);
		wm = MoleWeight(0);
	}
	return UnitConvertDef(sigma, 'N', _Unit, -1, wm);
}
double DielectricConstant(char* _Unit)
{
	if (q > 0 && q < 1)
	{
		strcpy_s(herr, "Undefined");
		return 0;
	}
	if (!t)
	{
		strcpy_s(herr, "Inputs out of range");
		return 0;
	}
	DIELECdll(t, d, x, de);
	return de;
}

