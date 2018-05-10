#include "stdafx.h"
#include "hrefprop.h"
#include "mystrlib.h"
#include "convertunit.h"
#include "initialDLL.h"
#include <string.h>
void SetupCal(char* _InpCode, double _Prop1, char* _Unit1, double _Prop2, char* _Unit2)
{
	//initialize state
	q = 0; t = 0; p = 0; d = 0; Dl = 0; Dv = 0; e = 0; h = 0; s = 0; Cvcalc = 0; Cpcalc = 0; w = 0;
	Cvl = 0; Cpl = 0; Cvv = 0; Cpv = 0; el = 0; ev = 0; hl = 0; hv = 0; sl = 0; sv = 0; wl = 0; wv = 0;
	ierr = 0;
	char UInpCode[lengthofinp];
	strcpy_s(UInpCode, _InpCode);
	UCase(UInpCode);
	wm = MoleWeight(0);
	long phase;
	//input phase flag : 1 = input x is liquid composition(bubble point)
	//             2 = input x is vapor composition(dew point)
	//             3 = input x is liquid composition(freezing point)
	//             4 = input x is vapor composition(sublimation point)
	long kr;
	//output phase flag : 1 = input state is liquid
	//			   2 = input state is vapor in equilibrium with liq
	//             3 = input state is liquid in equilibrium with solid
	//             4 = input state is vapor in equilibrium with solid
	long v0 = 0, v1 = 1, v2 = 2;//some constants
	if (UInpCode[1] == 'L')
		phase = 1;
	else phase = 2;
	if (strlen(UInpCode) == 2)
	{
		switch (UInpCode[0])
		{
		case 'T': t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm); break;
		case 'P': p = UnitConvertDef(_Prop1, 'P', _Unit1, 1, wm) * 1000.0; break;
		case 'D': d = UnitConvertDef(_Prop1, 'D', _Unit1, 1, wm); break;
		case 'V': d = 1 / UnitConvertDef(_Prop1, 'D', _Unit1, 1, wm); UInpCode[0] = 'D'; break;
		case 'H': h = UnitConvertDef(_Prop1, 'H', _Unit1, 1, wm); break;
		case 'S': s = UnitConvertDef(_Prop1, 'S', _Unit1, 1, wm); break;
		case 'Q': q = _Prop1; break;
		}
		switch (UInpCode[1])
		{
		case 'T': t = UnitConvertDef(_Prop2, 'T', _Unit2, 1, wm); break;
		case 'P': p = UnitConvertDef(_Prop2, 'P', _Unit2, 1, wm) * 1000.0; break;
		case 'D': d = UnitConvertDef(_Prop2, 'D', _Unit2, 1, wm); break;
		case 'V': d = 1 / UnitConvertDef(_Prop2, 'D', _Unit2, 1, wm); UInpCode[1] = 'D'; break;
		case 'H': h = UnitConvertDef(_Prop2, 'H', _Unit2, 1, wm); break;
		case 'S': s = UnitConvertDef(_Prop2, 'S', _Unit2, 1, wm); break;
		case 'Q': q = _Prop2; break;
		}
		if (strcmp(UInpCode, "TP") == 0 || strcmp(UInpCode, "PT") == 0)
		{
			TPFLSHdll(t, p, x, d, Dl, Dv, xliq, xvap, q, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
			if (ierr == -16 && nc == 1)
			{
				char herr2[lengthofstring];
				strcmp(herr2, herr);
				//Point is below triple point, call SATT to see if a sublimation line is available and to check if the input p is less than the sublimation pressure.
				double pp;
				SATTdll(t, x, v2, pp, Dl, Dv, xliq, xvap, ierr, herr, 255);
				if (p < pp && ierr <= 0)
					TPRHOdll(t, p, x, v2, v0, d, ierr, herr, 255);
				else
				{
					ierr = -16;
					strcpy_s(herr, herr2);
				}
				q = 998;
			}
		}
		else if (strcmp(UInpCode, "TD") == 0 || strcmp(UInpCode, "DT") == 0)
			TDFLSHdll(t, d, x, p, Dl, Dv, xliq, xvap, q, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);

		else if (strcmp(UInpCode, "TS") == 0 || strcmp(UInpCode, "ST") == 0)
			TSFLSHdll(t, s, x, v1, p, d, Dl, Dv, xliq, xvap, q, e, h, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "TQ") == 0 || strcmp(UInpCode, "QT") == 0)
			TQFLSHdll(t, q, x, v1, p, d, Dl, Dv, xliq, xvap, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "PD") == 0 || strcmp(UInpCode, "DP") == 0)
			PDFLSHdll(p, d, x, t, Dl, Dv, xliq, xvap, q, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "PH") == 0 || strcmp(UInpCode, "HP") == 0)
			PHFLSHdll(p, h, x, t, d, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "PS") == 0 || strcmp(UInpCode, "SP") == 0)
			PSFLSHdll(p, s, x, t, d, Dl, Dv, xliq, xvap, q, e, h, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "PE") == 0 || strcmp(UInpCode, "EP") == 0)
			PEFLSHdll(p, e, x, t, d, Dl, Dv, xliq, xvap, q, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "PQ") == 0 || strcmp(UInpCode, "QP") == 0)
			PQFLSHdll(p, q, x, v1, t, d, Dl, Dv, xliq, xvap, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "DH") == 0 || strcmp(UInpCode, "HD") == 0)
			DHFLSHdll(d, h, x, t, p, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "DS") == 0 || strcmp(UInpCode, "SD") == 0)
			DSFLSHdll(d, s, x, t, p, Dl, Dv, xliq, xvap, q, e, h, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "DE") == 0 || strcmp(UInpCode, "ED") == 0)
			DEFLSHdll(d, e, x, t, p, Dl, Dv, xliq, xvap, q, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
		else if (strcmp(UInpCode, "HS") == 0 || strcmp(UInpCode, "SH") == 0)
			HSFLSHdll(h, s, x, t, p, d, Dl, Dv, xliq, xvap, q, e, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(UInpCode, "TH1"))
	{
		t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm);
		h = UnitConvertDef(_Prop2, 'H', _Unit2, 1, wm);
		THFLSHdll(t, h, x, v1, p, d, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(UInpCode, "TH2"))
	{
		t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm);
		h = UnitConvertDef(_Prop2, 'H', _Unit2, 1, wm);
		THFLSHdll(t, h, x, v2, p, d, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(UInpCode, "HT1"))
	{
		h = UnitConvertDef(_Prop1, 'H', _Unit1, 1, wm);
		t = UnitConvertDef(_Prop2, 'T', _Unit2, 1, wm);
		THFLSHdll(t, h, x, v1, p, d, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(UInpCode, "HT2"))
	{
		h = UnitConvertDef(_Prop1, 'H', _Unit1, 1, wm);
		t = UnitConvertDef(_Prop2, 'T', _Unit2, 1, wm);
		THFLSHdll(t, h, x, v2, p, d, Dl, Dv, xliq, xvap, q, e, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (strcmp(UInpCode, "TLIQ") == 0 || strcmp(UInpCode, "TVAP") == 0)
	{
		t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm);
		SATTdll(t, x, phase, p, Dl, Dv, xliq, xvap, ierr, herr, 255);
		if ((p == 0 || Dl == 0) && ierr == 0)
		{
			ierr = 1;
			strcpy_s(herr, "Inputs are out of range");
			return;
		}
		if (phase == 1)
		{
			d = Dl;
			q = 0;
		}
		else if (phase == 2)
		{
			d = Dv;
			q = 1;
		}
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
	}
	else if (strcmp(UInpCode, "PLIQ") == 0 || strcmp(UInpCode, "PVAP") == 0)
	{
		p = UnitConvertDef(_Prop1, 'P', _Unit1, 1, wm) * 1000.0;
		SATPdll(p, x, phase, t, Dl, Dv, xliq, xvap, ierr, herr, 255);
		if ((p == 0 || Dl == 0) && ierr == 0)
		{
			ierr = 1;
			strcpy_s(herr, "Inputs are out of range");
			return;
		}
		if (phase == 1)
		{
			d = Dl;
			q = 0;
		}
		else if (phase == 2)
		{
			d = Dv;
			q = 1;
		}
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
	}

	else if (strcmp(UInpCode, "DSAT") == 0 || strcmp(UInpCode, "DLIQ") == 0 || strcmp(UInpCode, "DVAP") == 0 || strcmp(UInpCode, "VSAT") == 0 || strcmp(UInpCode, "VLIQ") == 0 || strcmp(UInpCode, "VVAP") == 0)
	{
		d = UnitConvertDef(_Prop1, 'D', _Unit1, 1, wm);
		SATDdll(d, x, v1, kr, t, p, Dl, Dv, xliq, xvap, ierr, herr, 255);
		THERMdll(t, d, x, p, e, h, s, Cvcalc, Cpcalc, w, hjt);
		q = kr - 1;
	}
	else if (!strcmp(_InpCode, "TMELT"))
	{
		t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm);
		MELTTdll(t, x, p, ierr, herr, 255);
		if (ierr == 0)
			TPFLSHdll(t, p, x, d, Dl, Dv, xliq, xvap, q, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(_InpCode, "PMELT"))
	{
		p = UnitConvertDef(_Prop1, 'P', _Unit1, 1, wm) * 1000.0;
		if (!p)
		{
			ierr = 1;
			strcpy_s(herr, "Input pressure is zero");
			return;
		}
		MELTPdll(p, x, t, ierr, herr, 255);
		if (!ierr)
			TPFLSHdll(t, p, x, d, Dl, Dv, xliq, xvap, q, e, h, s, Cvcalc, Cpcalc, w, ierr, herr, 255);
	}
	else if (!strcmp(_InpCode, "TSUBL"))
	{
		t = UnitConvertDef(_Prop1, 'T', _Unit1, 1, wm);
		SUBLTdll(t, x, p, ierr, herr, 255);
		if (ierr == 0 && p == 0)
		{
			ierr = 1;
			strcpy_s(herr, "No sublimation line available");
		}
		if (ierr == 0)
		{
			q = 1;
			d = p / 8.314472 / t;
			double pp;
			TPRHOdll(t, p, x, v2, v1, d, ierr, herr, 255);
			THERMdll(t, d, x, pp, e, h, s, Cvcalc, Cpcalc, w, hjt);
		}
	}
	else if (!strcmp(_InpCode, "PSUBL"))
	{
		p = UnitConvertDef(_Prop1, 'P', _Unit1, 1, wm) * 1000.0;
		if (!p)
		{
			ierr = 1;
			strcpy_s(herr, "Input pressure is zero");
			return;
		}
		SUBLPdll(p, x, t, ierr, herr, 255);
		if (ierr == 0 && t == 0)
		{
			ierr = 1;
			strcpy_s(herr, "No sublimation line available");
			if (!ierr)
			{
				q = 1;
				d = p / 8.314472 / t;
				double pp;
				TPRHOdll(t, p, x, v2, v1, d, ierr, herr, 255);
				THERMdll(t, d, x, pp, e, h, s, Cvcalc, Cpcalc, w, hjt);
			}
		}
		else
		{
			ierr = 4;
			strcmp(herr, "Unexpected InputCode.");
		}
		return;
	}
}