#pragma once
void PInit(int);
void PStart(void);
void PStartTimer(void);
void PRun(double);
void PBeacon(int, int,double, int);
double PPatternSig(double, int, double);
double PPattern(double, int, double);
bool PWarning(double, double, int, int, double, int);
void EBInit(int);
void EBStart(void);
void EBReset(void);
void RunEB(int, double);


int BrakeNotch;
int PowerNotch;
int Reverser;
int time;
int deltaT;
int emgBrake;
double speed;
int ATSNotch;
bool pilotlamp;
double Sndistance;
int TyreSize;

ATSIni g_ini;

class ATSP
{
public:
	int ATSBrake;
	bool ATSRed;
	double PatternSig;
	double PatternRed;
	double PatternLim1;
	double PatternLim2;
	double PatternLim3;
	double PatternLim4;
	double PatternLim5;
	int PatternSpeed1;
	int PatternSpeed2;
	int PatternSpeed3;
	int PatternSpeed4;
	int PatternSpeed5;
	double PatternSpeed;
	double ReleaseSpeed;
	int BrakeTimer;
	bool WarningLamp;
	bool BrakeLamp;
	bool ATSPower;
	int ATSChime;
	int PatternStart;
	int PatternEnd;
	int Warning;
	int Brake;
	bool ATSPattern;
	double Release;
	int ATSData;
	int ATSCut;
	bool ATSCutLamp;
	int BeaconNumber;
	int WarningSound1;
	int WarningSound2;
	bool WarningSoundX;
	int WarningTimer;
	bool WestPattern;
	int SignalWarning;
};
ATSP P;
class ATSEB
{
public:
	bool EBPower;
	bool EBLamp;
	int EBTimer;
	bool EBBrake;
	int EBSound;
};
ATSEB EB;