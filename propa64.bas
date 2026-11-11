Attribute VB_Name = "Propa"
Declare PtrSafe Function Agaz Lib "propa64.dll" Alias "gaseous_attenuation" (ByVal freq As Double, ByVal Elevation As Double, ByVal Temperature As Double, ByVal ro As Double) As Double
Declare PtrSafe Function Acloud Lib "propa64.dll" Alias "cloud_attenuation" (ByVal freq As Double, ByVal Elevation As Double, ByVal L As Double) As Double
Declare PtrSafe Function Arain Lib "propa64.dll" Alias "rain_attenuation" (ByVal lat As Double, ByVal freq As Double, ByVal Elevation As Double, ByVal Indispo As Double, ByVal hstation As Double, ByVal hpluie As Double, ByVal R001 As Double, ByVal polar As Double) As Double
Declare PtrSafe Function Iscint Lib "propa64.dll" Alias "scintillation" (ByVal Nwet As Double, ByVal freq As Double, ByVal Elevation As Double, ByVal Indispo As Double, ByVal hstation As Double, ByVal eta As Double, ByVal Diam As Double) As Double
Declare PtrSafe Function Nwet Lib "propa64.dll" Alias "NWET" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare PtrSafe Function TTC Lib "propa64.dll" Alias "LWCC" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare PtrSafe Function rain_height Lib "propa64.dll" Alias "rain_height" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare PtrSafe Function rain_intensity Lib "propa64.dll" Alias "rain_intensity" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare PtrSafe Function Temperature Lib "propa64.dll" Alias "temperature" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare PtrSafe Function WVC Lib "propa64.dll" Alias "SWVD" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare PtrSafe Function iwvc Lib "propa64.dll" Alias "IWVC" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare PtrSafe Function Agaz_exceeded Lib "propa64.dll" Alias "gaseous_attenuation_exc" (ByVal freq As Double, ByVal Elevation As Double, ByVal Temperature As Double, ByVal iwvc As Double) As Double
Declare PtrSafe Function EFSR Lib "propa64.dll" Alias "EFSR" (ByVal freq1 As Double, ByVal freq2 As Double, ByVal Att_1 As Double) As Double
Declare PtrSafe Function XPD Lib "propa64.dll" Alias "XPD" (ByVal Arain As Double, ByVal titl_deg As Double, ByVal freq As Double, ByVal elev_deg As Double, ByVal prob As Double) As Double
Declare PtrSafe Function Tmr Lib "propa64.dll" Alias "TMR" (ByVal Ts As Double) As Double
Declare PtrSafe Function Tnoise Lib "propa64.dll" Alias "noise_temperature" (ByVal A_total As Double, ByVal Tmr As Double) As Double
Public Declare PtrSafe Function version Lib "propa64.dll" Alias "version" () As Long