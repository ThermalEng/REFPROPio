#pragma once

//_inpval is the value to be converted from OldUnit to NewUnit
//UnitType is one of the following letters (one character only in most cases):
//The subroutine UnitConvertDef will convert units to Default units or just the opposite way
//(Determined by the direction flag) 
//And mention that the Default units are NOT the defaut ones for dll subroutines 
//UnitType     Unit name                          Default units
//  T         Temperature                            K
//  P         Pressure                               MPa
//  D         Density or specific volume            mol/L
//  H         Enthalpy or specific energy          J/mol
//  S         Entropy or heat capacity              J/mol-K
//  W         Speed of sound                         m/s
//  U         Viscosity                              Pa-s
//  K         Thermal conductivity                  mW/m-K (milli NOT million)
//  J        Joule Thomson                          K/mPa(million NOT milli)
//  L         Length                                 m
//  A         Area                                   m^2
//  V         Volume                                 m^3
//  M         Mass                                   kg
//  F         Force                                  N
//  E         Energy                                 J
//  Q         Power                                  W
//  N         Surface tension                        N/m
//  I         KinematicViscosity					m^2/s
// Gage pressures can be used by adding "_g" to the unit, e.g., "MPa_g"
// The different inputs for OldUnits and NewUnits can be found scattered in the text below.
// Several examples are given below:
// T=UnitConvert(323.15,'T',"K","F",MoleWeight)
// P=UnitConvert(1.01325,'P',"bar","mmHg",MoleWeight)
// V=UnitConvert(1000.,'D',"kg/m^3","cm^3/mol",MoleWeight)
//MoleWeight is optional, when the unit has no relationship with MoleWeight, any value is acceptble and has no affect on the result. 

double UnitConvert(double _inpval, char _unittype,char* _oldunit, char* _newunit,double _MolWt);

double UnitConvertDef(double _inpval, char _unittype, char* _unit, int _directionflag, double _MolWt);
//direction flag=1,unit to SI;=-1,SI to unit