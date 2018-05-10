#include "stdafx.h"
#include "hrefprop.h"
char FluidsDirectory[lengthofstring];
char MixtureDirectory[lengthofstring];
char PATH[lengthofstring];
long ierr;
char herr[lengthofstring];


char hrf[lengthofreference + 1];
char hfmix[lengthofstring];

char fldname[ncmax*lengthofstring];
char fldold[ncmax*lengthofstring];
//properties
//temperature,pressure,density,liquid density,vapor density,dryness,energy,enthalpy,entropy,specific heat(control volume),specific pressure(control pressure),speed of sound,
double  t, p, d, Dl, Dv, q, e, h, s, Cvcalc, Cpcalc, w;
double Cvl, Cpl, Cvv, Cpv, el, ev, hl, hv, sl, sv, wl, wv;
//isenthalpic Joule-Thomson coefficient
double hjt;
double wm, tz, pz, dz, dd;
double eta, tcx, de;
double wmm, ttrp, tnbpt, tc, pc, Dc, Zc, acf, dip, Rgas;


//mixture mole fractions
double x[ncmax], xliq[ncmax], xvap[ncmax];
//number of components
long nc;

long Ierr()
{
	return ierr;
}
char* Herr()
{
	return herr;
}