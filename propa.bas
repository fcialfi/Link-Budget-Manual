Attribute VB_Name = "Propa"
Declare Function Agaz Lib "propa.dll" Alias "gaseous_attenuation@32" (ByVal freq As Double, ByVal Elevation As Double, ByVal Temperature As Double, ByVal ro As Double) As Double
Declare Function Acloud Lib "propa.dll" Alias "cloud_attenuation@24" (ByVal freq As Double, ByVal Elevation As Double, ByVal L As Double) As Double
Declare Function Arain Lib "propa.dll" Alias "rain_attenuation@64" (ByVal lat As Double, ByVal freq As Double, ByVal Elevation As Double, ByVal Indispo As Double, ByVal hstation As Double, ByVal hpluie As Double, ByVal R001 As Double, ByVal polar As Double) As Double
Declare Function Iscint Lib "propa.dll" Alias "scintillation@56" (ByVal Nwet As Double, ByVal freq As Double, ByVal Elevation As Double, ByVal Indispo As Double, ByVal hstation As Double, ByVal eta As Double, ByVal Diam As Double) As Double
Declare Function Nwet Lib "propa.dll" Alias "NWET@16" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare Function TTC Lib "propa.dll" Alias "LWCC@24" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare Function rain_height Lib "propa.dll" Alias "rain_height@16" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare Function rain_intensity Lib "propa.dll" Alias "rain_intensity@24" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare Function Temperature Lib "propa.dll" Alias "temperature@16" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare Function WVC Lib "propa.dll" Alias "SWVD@16" (ByVal latitude As Double, ByVal longitude As Double) As Double
Declare Function iwvc Lib "propa.dll" Alias "IWVC@24" (ByVal latitude As Double, ByVal longitude As Double, ByVal Indispo As Double) As Double
Declare Function Agaz_exceeded Lib "propa.dll" Alias "gaseous_attenuation_exc@32" (ByVal freq As Double, ByVal Elevation As Double, ByVal Temperature As Double, ByVal iwvc As Double) As Double
Declare Function EFSR Lib "propa.dll" Alias "EFSR@24" (ByVal freq1 As Double, ByVal freq2 As Double, ByVal Att_1 As Double) As Double
Declare Function XPD Lib "propa.dll" Alias "XPD@40" (ByVal Arain As Double, ByVal titl_deg As Double, ByVal freq As Double, ByVal elev_deg As Double, ByVal prob As Double) As Double
Declare Function Tmr Lib "propa.dll" Alias "TMR@8" (ByVal Ts As Double) As Double
Declare Function Tnoise Lib "propa.dll" Alias "noise_temperature@16" (ByVal A_total As Double, ByVal Tmr As Double) As Double
Public Declare Function version Lib "propa.dll" Alias "version@0" () As Long


