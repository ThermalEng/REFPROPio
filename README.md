# REFPROPio
The refprop program offers a dynamic library for other programs. However, poor encapsulation and lots of pointers made it powerful in functions and difficult when you want to use it. So a new library is being built for easier use. The library is a standard dll  file written in c whitch can be called conveniently by many other languages.
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

原生refprop的使用太不方便了，所以参考refprop.xls重写了一下接口，方便以后使用。纯C风格，VS2015调试通过。可以打包成dll文件。
接口函数都在hrefprop.h文件里面，可以很方便的进行调用。使用时，先用初始化路径，再初始化混合物，再初始化计算，然后就可以调出物性参数了。
下面是用c++写的一个例子：
// This is an example using the "refpropdll.dll" lib with c++
//
#include "stdafx.h"
#include "windows.h"
#include <iostream>
using namespace std;
typedef void(__cdecl *fp_InitialDLLdllTYPE)();
typedef void(__cdecl *fp_SetPathdllTYPE)();
typedef void(__cdecl *fp_SetSubstancedllTYPE)(char* _FluidnameOrMixturenames);
typedef void(__cdecl *fp_SetMixdllTYPE)(char* _mix);
typedef void(__cdecl *fp_SetupCaldllTYPE)(char* _InpCode, double _Prop1, char* _Unit1, double _Prop2, char* _Unit2);
typedef double(__cdecl *fp_MoleWeightdllTYPE)(int _CompFlag);
typedef double(__cdecl *fp_TemperaturedllTYPE)(char* _Unit);
typedef double(__cdecl *fp_PressuredllTYPE)(char* _Unit);
typedef double(__cdecl *fp_DensitydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LiquidDensitydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_VaporDensitydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_VolumedllTYPE)(char* _Unit);
typedef double(__cdecl *fp_EnergydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_EnthalpydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LiquidEnthalpydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_VaporEnthalpydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_EntropydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LiquidEntropydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_VaporEntropydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_CpdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_CvdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_SpeedOfSounddllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LatentHeatdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_VaporizationHeatdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LHVdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_LLVdllTYPE)(char* _Unit);
typedef double(__cdecl *fp_GrossHeatingValuedllTYPE)(char* _Unit);
typedef double(__cdecl *fp_NetHeatingValuedllTYPE)(char* _Unit);
typedef double(__cdecl *fp_JouleThomsondllTYPE)(char* _Unit);
typedef double*(__cdecl *fp_MoleFractiondllTYPE)();
typedef double*(__cdecl *fp_LiquidMoleFractiondllTYPE)();
typedef double*(__cdecl *fp_VaporMoleFractiondllTYPE)();
typedef double(__cdecl *fp_ViscositydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_ThermalConductivitydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_KinematicViscositydllTYPE)(char* _Unit);
typedef double(__cdecl *fp_PrandtldllTYPE)(char* _Unit);
typedef double(__cdecl *fp_SurfaceTensiondllTYPE)(char* _Unit);
typedef double(__cdecl *fp_DielectricConstantdllTYPE)(char* _Unit);
typedef long(__cdecl *fp_IerrdllTYPE)();
typedef char*(__cdecl *fp_HerrdllTYPE)();


fp_InitialDLLdllTYPE InitialDLL;
fp_SetPathdllTYPE SetPath;
fp_SetSubstancedllTYPE SetSubstance;
fp_SetMixdllTYPE SetMix;
fp_SetupCaldllTYPE SetupCal;
fp_MoleWeightdllTYPE MoleWeight;
fp_TemperaturedllTYPE Temperature;
fp_PressuredllTYPE Pressure;
fp_DensitydllTYPE Density;
fp_LiquidDensitydllTYPE LiquidDensity;
fp_VaporDensitydllTYPE VaporDensity;
fp_VolumedllTYPE Volume;
fp_EnergydllTYPE Energy;
fp_EnthalpydllTYPE Enthalpy;
fp_LiquidEnthalpydllTYPE LiquidEnthalpy;
fp_VaporEnthalpydllTYPE VaporEnthalpy;
fp_EntropydllTYPE Entropy;
fp_LiquidEntropydllTYPE LiquidEntropy;
fp_VaporEntropydllTYPE VaporEntropy;
fp_CpdllTYPE Cp;
fp_CvdllTYPE Cv;
fp_SpeedOfSounddllTYPE SpeedOfSound;
fp_LatentHeatdllTYPE LatentHeat;
fp_VaporizationHeatdllTYPE VaporizationHeat;
fp_LHVdllTYPE LHV;
fp_LLVdllTYPE LLV;
fp_GrossHeatingValuedllTYPE GrossHeatingValue;
fp_NetHeatingValuedllTYPE NetHeatingValue;
fp_JouleThomsondllTYPE JouleThomson;
fp_MoleFractiondllTYPE MoleFraction;
fp_LiquidMoleFractiondllTYPE LiquidMoleFraction;
fp_VaporMoleFractiondllTYPE VaporMoleFraction;
fp_ViscositydllTYPE Viscosity;
fp_ThermalConductivitydllTYPE ThermalConductivity;
fp_KinematicViscositydllTYPE KinematicViscosity;
fp_PrandtldllTYPE Prandtl;
fp_SurfaceTensiondllTYPE SurfaceTension;
fp_DielectricConstantdllTYPE DielectricConstant;
fp_IerrdllTYPE ierr;
fp_HerrdllTYPE herr;

void dll()
{
	HINSTANCE HInstance;
	HInstance = LoadLibrary(L"refpropdll.dll");
	InitialDLL = (fp_InitialDLLdllTYPE)GetProcAddress(HInstance, "InitialDLL");
	SetPath = (fp_SetPathdllTYPE)GetProcAddress(HInstance, "SetPath");
	SetSubstance = (fp_SetSubstancedllTYPE)GetProcAddress(HInstance, "SetSubstance");
	SetMix = (fp_SetMixdllTYPE)GetProcAddress(HInstance, "SetMix");
	SetupCal = (fp_SetupCaldllTYPE)GetProcAddress(HInstance, "SetupCal");
	MoleWeight = (fp_MoleWeightdllTYPE)GetProcAddress(HInstance, "MoleWeight");
	Temperature = (fp_TemperaturedllTYPE)GetProcAddress(HInstance, "Temperature");
	Pressure = (fp_PressuredllTYPE)GetProcAddress(HInstance, "Pressure");
	Density = (fp_DensitydllTYPE)GetProcAddress(HInstance, "Density");
	LiquidDensity = (fp_LiquidDensitydllTYPE)GetProcAddress(HInstance, "LiquidDensity");
	VaporDensity = (fp_VaporDensitydllTYPE)GetProcAddress(HInstance, "VaporDensity");
	Volume = (fp_VolumedllTYPE)GetProcAddress(HInstance, "Volume");
	Energy = (fp_EnergydllTYPE)GetProcAddress(HInstance, "Energy");
	Enthalpy = (fp_EnthalpydllTYPE)GetProcAddress(HInstance, "Enthalpy");
	LiquidEnthalpy = (fp_LiquidEnthalpydllTYPE)GetProcAddress(HInstance, "LiquidEnthalpy");
	VaporEnthalpy = (fp_VaporEnthalpydllTYPE)GetProcAddress(HInstance, "VaporEnthalpy");
	Entropy = (fp_EntropydllTYPE)GetProcAddress(HInstance, "Entropy");
	LiquidEntropy = (fp_LiquidEntropydllTYPE)GetProcAddress(HInstance, "LiquidEntropy");
	VaporEntropy = (fp_VaporEntropydllTYPE)GetProcAddress(HInstance, "VaporEntropy");
	Cp = (fp_CpdllTYPE)GetProcAddress(HInstance, "Cp");
	Cv = (fp_CvdllTYPE)GetProcAddress(HInstance, "Cv");
	SpeedOfSound = (fp_SpeedOfSounddllTYPE)GetProcAddress(HInstance, "SpeedOfSound");
	LatentHeat = (fp_LatentHeatdllTYPE)GetProcAddress(HInstance, "LatentHeat");
	VaporizationHeat = (fp_VaporizationHeatdllTYPE)GetProcAddress(HInstance, "VaporizationHeat");
	LHV = (fp_LHVdllTYPE)GetProcAddress(HInstance, "LHV");
	LLV = (fp_LLVdllTYPE)GetProcAddress(HInstance, "LLV");
	GrossHeatingValue = (fp_GrossHeatingValuedllTYPE)GetProcAddress(HInstance, "GrossHeatingValue");
	NetHeatingValue = (fp_NetHeatingValuedllTYPE)GetProcAddress(HInstance, "NetHeatingValue");
	JouleThomson = (fp_JouleThomsondllTYPE)GetProcAddress(HInstance, "JouleThomson");
	MoleFraction = (fp_MoleFractiondllTYPE)GetProcAddress(HInstance, "MoleFraction");
	LiquidMoleFraction = (fp_LiquidMoleFractiondllTYPE)GetProcAddress(HInstance, "LiquidMoleFraction");
	VaporMoleFraction = (fp_VaporMoleFractiondllTYPE)GetProcAddress(HInstance, "VaporMoleFraction");
	Viscosity = (fp_ViscositydllTYPE)GetProcAddress(HInstance, "Viscosity");
	ThermalConductivity = (fp_ThermalConductivitydllTYPE)GetProcAddress(HInstance, "ThermalConductivity");
	KinematicViscosity = (fp_KinematicViscositydllTYPE)GetProcAddress(HInstance, "KinematicViscosity");
	Prandtl = (fp_PrandtldllTYPE)GetProcAddress(HInstance, "Prandtl");
	SurfaceTension = (fp_SurfaceTensiondllTYPE)GetProcAddress(HInstance, "SurfaceTension");
	DielectricConstant = (fp_DielectricConstantdllTYPE)GetProcAddress(HInstance, "DielectricConstant");
	ierr= (fp_IerrdllTYPE)GetProcAddress(HInstance, "Ierr");
	herr = (fp_HerrdllTYPE)GetProcAddress(HInstance, "Herr");
}
int main()
{
	dll();
	SetPath();
	InitialDLL();
	cout<<ierr()<<herr()<<endl;
	//strcpy_s(fldname,"air");	
	SetSubstance("nitrogen,oxygen,argon");
	//cout << fldname<<endl<<nc<<endl<< ierr() << herr() << endl;
	SetMix("0.78,0.21,0.01");
	for (int i = 0; i < 3; i++)
	{
		cout << "molefrac"<<(double)*(MoleFraction() + i)<<endl;
	}

	SetupCal("PT", 101.3, "kPa", 20, "C");
	//cout << ierr() << herr() << endl;
		cout << MoleWeight(0) << endl
		<< Pressure("MPa") << endl
		<< Temperature("K") << endl
		<< Density("kg/m^3") << endl
		<< Enthalpy("kJ/kg") << endl
		<< Entropy("kj/kg-K") << endl
		<< Cv("kJ/kg-K") << endl
		<< Cp("kJ/kg-K") << endl;
	//cout << ierr() << herr() << endl;


	SetSubstance("water");
	SetupCal("TLIQ", 100, "C", 0, "");
	//cout << ierr() << herr() << endl;

	cout << MoleWeight(0) << endl
		<< Pressure("MPa") << endl
		<< Temperature("C") << endl
		<< Density("kg/m^3") << endl
		<< Enthalpy("kJ/kg") << endl
		<< Entropy("kj/kg-K") << endl
		<< Cv("kJ/kg-K") << endl
		<< Cp("kJ/kg-K") << endl;
	//cout << ierr() << herr() << endl;


	SetupCal("TQ", 100, "C", 0.5, "");
	//cout << ierr() << herr() << endl;

	cout << MoleWeight(0) << endl
		<< Pressure("MPa") << endl
		<< Temperature("C") << endl
		<< Density("kg/m^3") << endl
		<< Enthalpy("kJ/kg") << endl
		<< Entropy("kj/kg-K") << endl
		<< Cv("kJ/kg-K") << endl
		<< Cp("kJ/kg-K") << endl;
	//cout << ierr() << herr() << endl;
}

