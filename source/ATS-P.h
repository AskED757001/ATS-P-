void PInit(int Param)
{
	P.ATSBrake = 0;
	P.ATSRed = false;
	P.ATSData = 0;
	P.ATSPattern = false;
	P.PatternSig = 0;
	P.PatternRed = 0;
	P.PatternLim1 = 0;
	P.PatternLim2 = 0;
	P.PatternLim3 = 0;
	P.PatternLim4 = 0;
	P.PatternLim5 = 0;
	P.PatternSpeed1 = 0;
	P.PatternSpeed2 = 0;
	P.PatternSpeed3 = 0;
	P.PatternSpeed4 = 0;
	P.PatternSpeed5 = 0;
	P.PatternSpeed = g_ini.DATA.PMaxspeed;
	P.ReleaseSpeed = g_ini.DATA.PMaxspeed - 5;
	P.BrakeTimer = 0;
	P.ATSCut = 0;
	P.ATSCutLamp = false;
	P.WarningLamp = false;
	P.BrakeLamp = false;
	if (Param == 1)
		P.ATSPower = true;
	else
		P.ATSPower = false;
}
void PStart(void)
{
	P.ATSPower = true;
	P.ATSRed = true;
	if (P.BrakeTimer == 0)
		P.BrakeTimer = time + 5000;
}
void PStartTimer(void)
{
	if (P.BrakeTimer > 0 && P.BrakeTimer < time)
	{
		P.ATSPower = true;
		P.ATSRed = false;
		P.ATSBrake = 0;
		P.BrakeTimer = 0;
	}
}
void PRun(double deltaL)
{
	P.WarningSound1 = ATS_SOUND_CONTINUE;
	P.WarningSound2 = ATS_SOUND_CONTINUE;
	P.ATSChime = ATS_SOUND_CONTINUE;
	P.Brake = ATS_SOUND_CONTINUE;
	P.PatternStart = ATS_SOUND_CONTINUE;
	P.PatternEnd = ATS_SOUND_CONTINUE;
	P.Warning = ATS_SOUND_CONTINUE;
	if (P.PatternSig != 0)
	{
		P.PatternSig -= deltaL;
		if (P.ATSData < 1)
			P.ATSData = 1;
	}

	if (P.PatternRed > 0)
		P.PatternRed -= deltaL;
	else
		P.PatternRed = 0;
	if (P.PatternLim1 > -26 && P.PatternLim1 != 0)
		P.PatternLim1 -= deltaL;
	else
		P.PatternLim1 = 0;
	if (P.PatternLim2 != 0)
		P.PatternLim2 -= deltaL;
	if (P.PatternLim3 != 0)
		P.PatternLim3 -= deltaL;
	if (P.PatternLim4 != 0)
		P.PatternLim4 -= deltaL;
	if (P.PatternLim5 != 0)
		P.PatternLim5 -= deltaL;

	if (P.PatternLim1 != 0 || P.PatternLim2 != 0 || P.PatternLim3 != 0 || P.PatternLim4 != 0 || P.PatternLim5 != 0 || P.PatternRed != 0 || P.ATSData != 0)
	{
		if (!P.ATSPattern)
		{
			P.ATSChime = ATS_SOUND_PLAY;
			P.PatternStart = ATS_SOUND_PLAY;
		}
		P.ATSPattern = true;
	}
	else
	{
		if (P.ATSPattern)
		{
			P.ATSChime = ATS_SOUND_PLAY;
			P.PatternEnd = ATS_SOUND_PLAY;
		}
		P.ATSPattern = false;
	}
	P.PatternSpeed = g_ini.DATA.PMaxspeed;
	if (P.PatternSpeed > PPattern(P.PatternLim1 + 1, P.PatternSpeed1, g_ini.DATA.Pdecelerate) && P.PatternLim1 != 0)
		P.PatternSpeed = PPattern(P.PatternLim1 + 1, P.PatternSpeed1, g_ini.DATA.Pdecelerate);
	if (P.PatternSpeed > PPattern(P.PatternLim2, P.PatternSpeed2, g_ini.DATA.Pdecelerate) && P.PatternLim2 != 0)
		P.PatternSpeed = PPattern(P.PatternLim2, P.PatternSpeed2, g_ini.DATA.Pdecelerate);
	if (P.PatternSpeed > PPattern(P.PatternLim3, P.PatternSpeed3, g_ini.DATA.Pdecelerate) && P.PatternLim3 != 0)
		P.PatternSpeed = PPattern(P.PatternLim3, P.PatternSpeed3, g_ini.DATA.Pdecelerate);
	if (P.PatternSpeed > PPattern(P.PatternLim4, P.PatternSpeed4, g_ini.DATA.Pdecelerate) && P.PatternLim4 != 0)
		P.PatternSpeed = PPattern(P.PatternLim4, P.PatternSpeed4, g_ini.DATA.Pdecelerate);
	if (P.PatternSpeed > PPattern(P.PatternLim5, P.PatternSpeed5, g_ini.DATA.Pdecelerate) && P.PatternLim5 != 0)
		P.PatternSpeed = PPattern(P.PatternLim5, P.PatternSpeed5, g_ini.DATA.Pdecelerate);
	if (P.PatternSpeed > 15 && P.PatternRed > 0)
		P.PatternSpeed = 15;

	P.ReleaseSpeed = g_ini.DATA.PMaxspeed - 5;
	if (P.ReleaseSpeed > PPattern(P.PatternLim1, P.PatternSpeed1, g_ini.DATA.Pdecelerate) - 5 && P.PatternLim1 != 0)
		P.ReleaseSpeed = PPattern(P.PatternLim1, P.PatternSpeed1, g_ini.DATA.Pdecelerate) - 5;
	if (P.ReleaseSpeed > PPattern(P.PatternLim2, P.PatternSpeed2, g_ini.DATA.Pdecelerate) - 5 && P.PatternLim2 != 0)
		P.ReleaseSpeed = PPattern(P.PatternLim2, P.PatternSpeed2, g_ini.DATA.Pdecelerate) - 5;
	if (P.ReleaseSpeed > PPattern(P.PatternLim3, P.PatternSpeed3, g_ini.DATA.Pdecelerate) - 5 && P.PatternLim3 != 0)
		P.ReleaseSpeed = PPattern(P.PatternLim3, P.PatternSpeed3, g_ini.DATA.Pdecelerate) - 5;
	if (P.ReleaseSpeed > PPattern(P.PatternLim4, P.PatternSpeed4, g_ini.DATA.Pdecelerate) - 5 && P.PatternLim4 != 0)
		P.ReleaseSpeed = PPattern(P.PatternLim4, P.PatternSpeed4, g_ini.DATA.Pdecelerate) - 5;
	if (P.ReleaseSpeed > PPattern(P.PatternLim5, P.PatternSpeed5, g_ini.DATA.Pdecelerate) - 5 && P.PatternLim5 != 0)
		P.ReleaseSpeed = PPattern(P.PatternLim5, P.PatternSpeed5, g_ini.DATA.Pdecelerate) - 5;

	if (P.ATSBrake > 0 && P.Release > P.ReleaseSpeed)
		P.Release = P.ReleaseSpeed;
	else if (P.ATSBrake == 0)
		P.Release = g_ini.DATA.PMaxspeed - 5;
	if (g_ini.DATA.West == 0)
		P.SignalWarning = -5;
	else if (g_ini.DATA.West == 1 || g_ini.DATA.West == 2 && P.WestPattern)
		P.SignalWarning = 5;
	if (PWarning(P.PatternSig, speed, 0, P.SignalWarning, g_ini.DATA.Pdecelerate, g_ini.DATA.Margin)
		|| PWarning(P.PatternLim1, speed, P.PatternSpeed1, P.PatternSpeed1 - 5, g_ini.DATA.Pdecelerate, 0)
		|| PWarning(P.PatternLim2, speed, P.PatternSpeed2, P.PatternSpeed2 - 5, g_ini.DATA.Pdecelerate, 0)
		|| PWarning(P.PatternLim3, speed, P.PatternSpeed3, P.PatternSpeed3 - 5, g_ini.DATA.Pdecelerate, 0)
		|| PWarning(P.PatternLim4, speed, P.PatternSpeed4, P.PatternSpeed4 - 5, g_ini.DATA.Pdecelerate, 0)
		|| PWarning(P.PatternLim5, speed, P.PatternSpeed5, P.PatternSpeed5 - 5, g_ini.DATA.Pdecelerate, 0)
		|| P.PatternRed > 0 && speed > 10 || g_ini.DATA.PMaxspeed - 5 < speed)
	{
		if(!P.WarningLamp)
		{
			P.ATSChime = ATS_SOUND_PLAY;
			P.Warning = ATS_SOUND_PLAY;
			P.WarningSoundX = false;
			P.WarningTimer = time;
		}
		P.WarningLamp = true;
		if (P.WarningTimer <= time && !P.WarningSoundX && P.ATSBrake == 0)
		{
			P.WarningSound1 = ATS_SOUND_PLAY;
			P.WarningSoundX = true;
			P.WarningTimer += 4000;
		}
		else if (P.WarningTimer <= time && P.ATSBrake == 0)
		{
			P.WarningSound2 = ATS_SOUND_PLAY;
			P.WarningSoundX = false;
			P.WarningTimer += 4000;
		}
	}
	else
	{
		if (P.WarningLamp)
		{
			P.ATSChime = ATS_SOUND_PLAY;
			P.Warning = ATS_SOUND_PLAY;
		}
		P.WarningLamp = false;
	}
	if (P.ATSCut > time)
	{
		if(!P.ATSCutLamp)
			P.ATSChime = ATS_SOUND_PLAY;
		P.ATSCutLamp = true;
	}
	else
	{
		if (P.ATSCutLamp)
			P.ATSChime = ATS_SOUND_PLAY;
		P.ATSCutLamp = false;
	}
	if (P.ATSRed)
		P.ATSBrake = 2;
	else if (15 < speed && P.PatternRed > 0 && P.ATSBrake <= 1 && !P.ATSCutLamp)
		P.ATSBrake = 2;
	else if (PPatternSig(P.PatternSig, 10, g_ini.DATA.Pdecelerate) < speed && PPatternSig(P.PatternSig, 10, g_ini.DATA.Pdecelerate) > 0 && P.ATSBrake <= 1 && !P.ATSCutLamp)
	{
		if (g_ini.DATA.PEnabled > 0)
			P.ATSBrake = 1;
		else if (g_ini.DATA.PEnabled < 0)
			P.ATSBrake = 2;
		P.Release = 0;
	}
	else if (P.PatternSpeed < speed && P.ATSBrake < 1 && !P.ATSCutLamp)
	{
		if (g_ini.DATA.PEnabled > 0)
			P.ATSBrake = 1;
		else if (g_ini.DATA.PEnabled < 0)
			P.ATSBrake = 2;
	}
	else if (P.Release > speed && P.ATSBrake == 1)
	{
		P.ATSBrake = 0;
	}
	if (P.ATSCutLamp)
	{
		P.ATSBrake = 0;
	}
	if (P.ATSBrake != 0)
	{
		if (!P.BrakeLamp)
		{
			P.ATSChime = ATS_SOUND_PLAY;
			P.Brake = ATS_SOUND_PLAY;
			P.WarningSoundX = false;
			P.WarningTimer = time;
		}
		P.BrakeLamp = true;
		if (P.WarningTimer <= time && !P.WarningSoundX && speed != 0)
		{
			P.WarningSound1 = ATS_SOUND_PLAY;
			P.WarningSoundX = true;
			P.WarningTimer += 1500;
		}
		else if (P.WarningTimer <= time && speed != 0)
		{
			P.WarningSound2 = ATS_SOUND_PLAY;
			P.WarningSoundX = false;
			P.WarningTimer += 1500;
		}
	}
	else
	{
		if (P.BrakeLamp)
			P.ATSChime = ATS_SOUND_PLAY;
		P.BrakeLamp = false;
	}
	if (P.PatternSpeed > PPatternSig(P.PatternSig, 10, g_ini.DATA.Pdecelerate) && P.PatternSig != 0)
		P.PatternSpeed = PPatternSig(P.PatternSig, 10, g_ini.DATA.Pdecelerate);
}
double PPatternSig(double distance, int speed, double decelerate)
{
	double PatternSpeed;

	if (distance - g_ini.DATA.Margin > 0)
	{
		PatternSpeed = sqrt(7.2 * decelerate * (distance - g_ini.DATA.Margin));
		if (speed > PatternSpeed)
			PatternSpeed = speed;
	}
	else if (distance > 0)
	{
		PatternSpeed = speed;
	}
	else
	{
		PatternSpeed = 0;
	}

	return PatternSpeed;
}
double PPattern(double distance, int speed, double decelerate)
{
	double PatternSpeed;

	if (distance > 0)
	{
		PatternSpeed = sqrt((speed * speed) + (7.2 * decelerate * distance));
	}
	else if (distance < 0)
	{
		PatternSpeed = speed;
	}
	else
	{
		PatternSpeed = 0;
	}

	return PatternSpeed;
}
bool PWarning(double distance, double speed, int Limit, int ReleaseSpeed, double decelerate, int Margin)
{
	bool Warning;
	double Pattern = (speed * speed - Limit * Limit) / 7.2 / decelerate + Margin;

	if (distance - 50 < Pattern && speed > ReleaseSpeed && distance != 0)
		Warning = true;
	else
		Warning = false;
	return Warning;
}
void PBeacon(int Type, int Signal, double distance, int Optional)
{
	if (Type == 3)
	{
		if (P.ATSData < 1)
			P.ATSData = 1;
		if (Signal == 0 && distance > 0)
		{
			P.PatternSig = distance;
			if (Optional != 0)
			P.BeaconNumber = Optional;
		}
		else if (Optional == P.BeaconNumber && Optional != 0 && Signal != 0)
		{
			P.PatternSig = 0;
			P.BeaconNumber = Optional;
		}
		else if (P.PatternSig + 5 > distance && P.PatternSig - 5 < distance && Signal != 0)
		{
			P.PatternSig = 0;
			if (Optional != 0)
			P.BeaconNumber = Optional;
		}
		else if (Optional == 9 && P.PatternSig == 0)
			P.BeaconNumber = Optional;
		if (Optional != 0)
			P.WestPattern = true;
		else
			P.WestPattern = false;
	}
	if (Type == 4 && distance > 0)
	{
		if (Signal == 0)
		{
			P.PatternSig = distance;
			if (distance < 50)
				P.ATSBrake = 2;
		}
		if (P.ATSData < 1)
			P.ATSData = 1;
	}
	if (Type == 5 && distance > 0)
	{
		if (Signal == 0)
		{
			P.PatternSig = distance;
			if (distance < 50)
			{
				P.ATSBrake = 1;
				P.PatternRed = 80;
			}
		}
		if (P.ATSData < 1)
			P.ATSData = 1;
	}
	if (Type == 6 && Optional > 1000)
	{
		P.PatternLim1 = Optional / 1000 - 1;
		P.PatternSpeed1 = Optional % 1000;

	}
	if (Type == 7 && Optional > 2)
	{
		if (Optional / 1000 != 0)
			P.PatternLim2 = Optional / 1000;
		else
			P.PatternLim2 = -5;
		P.PatternSpeed2 = Optional % 1000;
	}
	if (Type == 8 && Optional > 1000)
	{
		if (Optional / 1000 != 0)
			P.PatternLim3 = Optional / 1000;
		else
			P.PatternLim3 = -5;
		P.PatternSpeed3 = Optional % 1000;
	}
	if (Type == 9 && Optional > 1000)
	{
		if (Optional / 1000 != 0)
			P.PatternLim4 = Optional / 1000;
		else
			P.PatternLim4 = -5;
		P.PatternSpeed4 = Optional % 1000;
	}
	if (Type == 10 && Optional > 1000)
	{
		if (Optional / 1000 != 0)
			P.PatternLim5 = Optional / 1000;
		else
			P.PatternLim5 = -5;
		P.PatternSpeed5 = Optional % 1000;
	}
	if (Type == 16 && Optional == 0)
	{
		P.PatternLim1 = 0;
		P.PatternSpeed1 = 0;
	}
	if (Type == 17 && Optional == 0)
	{
		P.PatternLim2 = 0;
		P.PatternSpeed2 = 0;
	}
	if (Type == 18 && Optional == 0)
	{
		P.PatternLim3 = 0;
		P.PatternSpeed3 = 0;
	}
	if (Type == 19 && Optional == 0)
	{
		P.PatternLim4 = 0;
		P.PatternSpeed4 = 0;
	}
	if (Type == 20 && Optional == 0)
	{
		P.PatternLim5 = 0;
		P.PatternSpeed5 = 0;
	}
}