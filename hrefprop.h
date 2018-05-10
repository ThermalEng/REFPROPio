#pragma once
#define EXPORT _declspec(dllexport)
//// C program written by;
// LI Minchao
// Tech Center of DongfangBoilerCo.
// Chengdu,Sichuan,China
// minchao_li@126.com

//This c program rewrote the demonstrates explicitly linking to the subroutines available in
// refprop.dll. You can call the subroutines the same way as in the refprop.xls. In order to
//link this code hrefprop.h  must be available in the current directory. And Environment
//Variable "Rpprefix" should first be definated the REFPROP path. You can also package it 
//into a dll dynamic library to conveniently call the subroutines.

//// Some constants...
const int MaxComps = 20;
const int lengthofstring = 255;
const int lengthofinp = 8;

const long lengthofreference = 3;
//hrf--reference state for thermodynamic calculations[character * 3]
//"DEF":  default reference state as specified in fluid file
// is applied to each pure component
// "NBP" : h, s = 0 at pure component normal boiling point(s)
//"ASH" : h, s = 0 for sat liquid at - 40 C(ASHRAE convention)
//"IIR" : h = 200, s = 1.0 for sat liq at 0 C(IIR convention)
// other choices are possible, but these require a separate
// call to SETREF

const long ncmax = 20;		// Note: ncmax is the max number of components
const long numparams = 72;
const long maxcoefs = 50;

const char HRF[] = "DEF";
extern char hrf[lengthofreference + 1];
//  reference state for thermodynamic calculations[character * 3]
//  'DEF':  default reference state as specified in fluid file
//          is applied to each pure component
//  'NBP' : h, s = 0 at pure component normal boiling point(s)
//  'ASH' : h, s = 0 for sat liquid at - 40 C(ASHRAE convention)
//  'IIR' : h = 200, s = 1.0 for sat liq at 0 C(IIR convention)
//  other choices are possible, but these require a separate
//  call to SETREF
const char HFMIX[] = "hmx.bnc";
extern char hfmix[lengthofstring];
//mixture coefficients. File name containing coefficients for mixture model. Usually in the fluids directory.

extern char FluidsDirectory[lengthofstring];
extern char MixtureDirectory[lengthofstring];
extern char PATH[lengthofstring];
extern long ierr;
extern char herr[lengthofstring];



//properties
extern char fldname[ncmax*lengthofstring];
extern char fldold[ncmax*lengthofstring];

//temperature,pressure,density,liquid density,vapor density,dryness,energy,enthalpy,entropy,speed of sound,isenthalpic Joule-Thomson coefficient,specific heat(control volume),specific pressure(control pressure),
extern double  t, p, d, Dl, Dv, q, e, h, s, w, hjt, Cvcalc, Cpcalc;
//liquid &vapor properties
extern double Cvl, Cpl, Cvv, Cpv, el, ev, hl, hv, sl, sv, wl, wv;

//mole weight,
extern double wm, tz, pz, dz, dd;
//Viscosity,thermal conductivity,DielectricConstant
extern double eta, tcx, de;

extern double wmm, ttrp, tnbpt, tc, pc, Dc, Zc, acf, dip, Rgas;
//  property of a composition
//      wmm--molecular weight[g / mol]
//     ttrp--triple point temperature[K]
//    tnbpt--normal boiling point temperature[K]
//       tc--critical temperature[K]
//       pc--critical pressure[kPa]
//       Dc--critical density[mol / L]
//       Zc--compressibility at critical point[pc / (Rgas*Tc*Dc)]
//      acf--acentric factor[-]
//      dip--dipole moment[debye]
//     Rgas--gas constant[J / mol - K]

//mixture mole fractions
extern double x[ncmax], xliq[ncmax], xvap[ncmax];
//number of components
extern long nc;
//true=molefraction definited;false= not
extern bool molefracflag;

//
extern "C"
{
	EXPORT void InitialDLL();
	EXPORT void SetPath();
	EXPORT void SetSubstance(char* _FluidnameOrMixturenames);
	EXPORT void SetMix(char* _mix);
	
	EXPORT char* Herr();
	EXPORT long Ierr();

	//MUST be runned after substances are set, before calculating any property.
	//InpCode   = name and order of Prop1 and Prop2.
	//            "TP" would mean Prop1 is Temperature, Prop2 is Pressure (need quotes)
	//            Valid InpCodes:  TP,TD,TH,TS,TE,TQ,PD,PH,PS,PE,PQ,DH,DS,DE,HS(HT has 2 solutions, HT for the higher density root, TH for the lower root
	//            To define saturated liquid or vapor inputs:  TLIQ, TVAP, PLIQ, PVAP, DSAT,  DLIQ, DVAP, etc.
	//            Other:  Crit, Trip, TMelt, PMelt, TSubl, PSubl
	//
	//
	//Units     = eg. "MPa" "m/s2" "J/mol-K"
	//Prop1     = numerical value of the first input property (in the units of the previous line)
	//Prop2     = numerical value of the second input property (if required).
	//
	EXPORT void SetupCal(char* _InpCode, double _Prop1, char* _Unit1, double _Prop2, char* _Unit2);


	//Properties, run after SetupCal is called 
	//_CompFlag 0£ºbulk 1:liquidphase 2:vapor phase
	EXPORT double MoleWeight(int _CompFlag);
	EXPORT double Temperature(char* _Unit);
	EXPORT double Pressure(char* _Unit);
	EXPORT double Density(char* _Unit);
	EXPORT double LiquidDensity(char* _Unit);
	EXPORT double VaporDensity(char* _Unit);
	EXPORT double Volume(char* _Unit);
	EXPORT double Energy(char* _Unit);
	EXPORT double Enthalpy(char* _Unit);
	EXPORT double LiquidEnthalpy(char* _Unit);
	EXPORT double VaporEnthalpy(char* _Unit);
	EXPORT double Entropy(char* _Unit);
	EXPORT double LiquidEntropy(char* _Unit);
	EXPORT double VaporEntropy(char* _Unit);
	EXPORT double Cp(char* _Unit);
	EXPORT double Cv(char* _Unit);
	EXPORT double SpeedOfSound(char* _Unit);
	EXPORT double LatentHeat(char* _Unit);
	EXPORT double VaporizationHeat(char* _Unit);
	EXPORT double LHV(char* _Unit);
	EXPORT double LLV(char* _Unit);
	EXPORT double GrossHeatingValue(char* _Unit);
	EXPORT double NetHeatingValue(char* _Unit);
	EXPORT double JouleThomson(char* _Unit);
	EXPORT double* MoleFraction();
	EXPORT double* LiquidMoleFraction();
	EXPORT double* VaporMoleFraction();
	EXPORT double Viscosity(char* _Unit);
	EXPORT double ThermalConductivity(char* _Unit);
	EXPORT double KinematicViscosity(char* _Unit);
	EXPORT double Prandtl(char* _Unit);
	EXPORT double SurfaceTension(char* _Unit);
	EXPORT double DielectricConstant(char* _Unit);
}
