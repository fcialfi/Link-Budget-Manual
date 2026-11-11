#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCallNWET) (double lat, double lon);
typedef double (WINAPI * DllCallrain_height) (double lat, double lon);
typedef double (WINAPI * DllCalltemperature)  (double lat,double lon);
typedef double (WINAPI * DllCallrain_intensity) (double lat, double lon, double p);
typedef double (WINAPI * DllCallrain_probability) (double lat, double lon);
typedef double (WINAPI * DllCallLWCC) (double lat, double lon, double p);
typedef double (WINAPI * DllCallIWVC) (double lat, double lon, double p) ;
typedef double (WINAPI * DllCallSWVD) (double lat, double lon);
typedef double (WINAPI * DllCallgaseous_attenuation) (double f,double E,double Temp, double ro);
typedef double (WINAPI * DllCallgaseous_attenuation_exc)(double f,double E,double Temp, double WVC);
typedef double (WINAPI * DllCallcloud_attenuation) (double f,double E,double L);
typedef double (WINAPI * DllCallrain_attenuation) (double lat,double f,double E,double p,double hs,double hr,double R001, double to);
typedef double (WINAPI * DllCallscintillation) (double Nwet, double f,double E,double p,double hs,double eta, double D);
typedef double (WINAPI * DllCallXPD) (double A_rain, double to,double f, double elev, double p);
typedef double (WINAPI * DllCallnoise_temperature) (double A_total, double Tmr);
typedef double (WINAPI * DllCallTMR) (double Ts);
typedef double (WINAPI * DllCallEFSR) (double f1, double f2, double A1);

int main(void) {


  HMODULE propaDLL;
  DllCallNWET NWET;
  DllCallrain_height rain_height;
  DllCalltemperature temperature;
  DllCallrain_intensity rain_intensity;
  DllCallrain_probability rain_probability;
  DllCallLWCC LWCC;
  DllCallIWVC IWVC;
  DllCallSWVD SWVD;
  DllCallgaseous_attenuation gaseous_attenuation;
  DllCallgaseous_attenuation_exc gaseous_attenuation_exc;
  DllCallcloud_attenuation cloud_attenuation;
  DllCallrain_attenuation rain_attenuation;
  DllCallscintillation scintillation;
  DllCallXPD XPD; 
  DllCallnoise_temperature noise_temperature; 
  DllCallTMR TMR;
  DllCallEFSR EFSR; 
  
  propaDLL = LoadLibrary("propa64.dll");
  NWET = (DllCallNWET) GetProcAddress(propaDLL,"NWET");
  rain_height = (DllCallrain_height) GetProcAddress(propaDLL,"rain_height");
  temperature = (DllCalltemperature) GetProcAddress(propaDLL,"temperature");
  rain_intensity = (DllCallrain_intensity) GetProcAddress(propaDLL,"rain_intensity");
  rain_probability = (DllCallrain_probability) GetProcAddress(propaDLL,"rain_probability");
  LWCC = (DllCallLWCC) GetProcAddress(propaDLL,"LWCC");
  IWVC = (DllCallIWVC) GetProcAddress(propaDLL,"IWVC");
  SWVD = (DllCallSWVD) GetProcAddress(propaDLL,"SWVD");
  gaseous_attenuation = (DllCallgaseous_attenuation) GetProcAddress(propaDLL,"gaseous_attenuation");
  gaseous_attenuation_exc = (DllCallgaseous_attenuation_exc) GetProcAddress(propaDLL,"gaseous_attenuation_exc");
  cloud_attenuation = (DllCallcloud_attenuation) GetProcAddress(propaDLL,"cloud_attenuation");
  rain_attenuation = (DllCallrain_attenuation) GetProcAddress(propaDLL,"rain_attenuation");
  scintillation = (DllCallscintillation) GetProcAddress(propaDLL,"scintillation");
  XPD = (DllCallXPD) GetProcAddress(propaDLL,"XPD") ; 
  noise_temperature = (DllCallnoise_temperature)  GetProcAddress(propaDLL,"noise_temperature") ; 
  TMR = (DllCallTMR)  GetProcAddress(propaDLL,"TMR");
  EFSR = (DllCallEFSR) GetProcAddress(propaDLL,"EFSR");
  
  if ((propaDLL == NULL) || (NWET == NULL) || (rain_height == NULL) ||
	  (temperature == NULL) || (rain_intensity == NULL) ||
	(rain_probability == NULL) || (LWCC == NULL) || (IWVC == NULL) ||
  (SWVD == NULL) || (gaseous_attenuation == NULL) || (gaseous_attenuation_exc == NULL) ||
  (cloud_attenuation == NULL) || (rain_attenuation == NULL) || (scintillation == NULL) || 
  (XPD == NULL) || (noise_temperature == NULL) || (TMR == NULL) || (EFSR == NULL)) { printf("Problem while loading the PROPA DLL\n"); return 1; }


  double lat, lon, f1, p, E, hs, to, eta, D, f2;
  double Temp, ro, WVC, LWC,  hr, R001, Nwet, XPOL, NoiseTemp, MeanRTemp;
  double Agaseous, Agaseous_exc, Aclouds, Arain, Arain2, Iscint, Atotal;


  lat = 46.217;		// Latitude (°)
  lon = 6.12;		// Logitude (°)

  hs = 0.8140;			// Earth station altitude (km)
  E = 33.0*M_PI/180;	// Link elevation angle (°)

  f1= 12.0;			// Link frequency (GHz)
  f2 = 30; 			// Second link frequency f2 > f1 (for Frequency scaling) (GHz)  
  to = 45.0;		// Tilt polarization angle (°)

  D = 1.0;			// Earth station antenna diameter (m)
  eta = 0.5;		// Earth station antenna efficiency

  p = 1;			// Percentage of the time

  // Intermediate parameters computation
  hr = rain_height(lat,lon);
  R001 = rain_intensity(lat,lon,0.01);
  Temp = temperature(lat,lon);
  ro = SWVD(lat,lon);
  if (p>=1) {
	WVC = IWVC(lat,lon,p);
	LWC = LWCC(lat,lon,p);
  }
  else {
	WVC= IWVC(lat,lon,1);
    LWC = LWCC(lat,lon,1);
  }
  Nwet = NWET(lat,lon);

  printf("\n==========================\n" ); 
  printf("Link frequency %.2lf GHz \n", f1); 
  printf("==========================\n" ); 
  
  // GASEOUS ATTENUATION
  Agaseous = gaseous_attenuation(f1,E,Temp,ro);
  printf("\nGaseous attenuation = %.2lf dB\n",Agaseous);

  // GASEOUS ATTENUATION EXCEEDED FOR p% OF THE TIME
  Agaseous_exc = gaseous_attenuation_exc(f1,E,Temp,WVC);
  printf("\nGaseous attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Agaseous_exc);

  // CLOUD ATTENUATION EXCEEDED FOR p% OF THE TIME
  Aclouds = cloud_attenuation(f1,E,LWC);
  printf("\nClouds attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Aclouds);

  // IMPAIRMENT DUE TO SCINTILLATION EXCEEDED FOR p% OF THE TIME
  Iscint = scintillation(Nwet,f1,E,p,hs,eta,D);
  printf("\nScintillation impairment exceeded for %.2lf %% of the time = %.2lf dB\n",p,Iscint);

  // RAIN ATTENUATION EXCEEDED FOR p% OF THE TIME
  Arain = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);
  printf("\nRain attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Arain);
  
  // TOTAL ATTENUATION 
  Atotal = Agaseous_exc + sqrt((Arain+ Aclouds)*(Arain+ Aclouds) + Iscint*Iscint); 
  printf("\nTotal attenuation exceeded for %.2lf %% of the time = %.2lf dB\n", p, Atotal);
  
  // SKY NOISE TEMPERATURE FOR A GIVEN TOTAL ATTENUATION 
  MeanRTemp = TMR(Temp); 
  NoiseTemp =noise_temperature (Agaseous_exc+Arain+Aclouds,MeanRTemp);  // total attenuation except scintillation 
  printf("\nSky noise temperature for the total attenuation without scintillation %.2lf dB = %.2lf K\n", Agaseous_exc+Arain+Aclouds, NoiseTemp);
  
  // CROSS POLAR DISCRIMINATION EXCEEDED FOR p% OF THE TIME 
  XPOL = XPD(Arain,to,f1,E*180.0/M_PI,p);  // elevation in degrees here
  printf("\nCross polar discrimination exceeded for %.2lf %% of the time = %.2lf dB\n", p, XPOL);
  
  printf("\n====================================\n" ); 
  printf("Link frequency scaling to %.2lf GHz \n", f2); 
  printf("====================================\n" ); 
  // RAIN ATTENUATION ON FREQ 2 FROM FREQ 1 (using frequency scaling) 
  Arain2 = EFSR(f1, f2, Arain); 
  printf("\nRain attenuation exceeded on freq. %.2lf GHZ based on freq. %.2lf GHZ = %.2lf dB\n",f2, f1, Arain2);

  
 FreeLibrary(propaDLL);

 return 0;

 }

