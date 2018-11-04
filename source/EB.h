void EBInit(int Param)
{
	if (Param == 0)
		EB.EBPower = false;
	else
		EB.EBPower = true;
	EB.EBBrake = false;
	EB.EBLamp = false;
	EB.EBTimer = 0;
	EB.EBSound = ATS_SOUND_STOP;
}
void EBStart(void)
{
	EB.EBPower = true;
	EB.EBBrake = false;
	EB.EBLamp = false;
	EB.EBTimer = 0;
	EB.EBSound = ATS_SOUND_STOP;
}
void RunEB(int deltaT,double speed)
{
	if (speed > 10)
	{
		if (EB.EBTimer < 60000)
		{
			EB.EBSound = ATS_SOUND_STOP;
			EB.EBTimer += deltaT;
			EB.EBLamp = false;
		}
		else if (EB.EBTimer < 65000)
		{
			EB.EBSound = ATS_SOUND_PLAYLOOPING;
			EB.EBTimer += deltaT;
			EB.EBLamp = true;
		}
		else
		{
			EB.EBSound = ATS_SOUND_PLAYLOOPING;
			EB.EBTimer += deltaT;
			EB.EBLamp = true;
			EB.EBBrake = true;
		}
	}
	else
		EB.EBTimer = 0;
}
void EBReset(void)
{
	if (!EB.EBBrake)
	{
		EB.EBLamp = false;
		EB.EBTimer = 0;
		EB.EBSound = ATS_SOUND_STOP;
	}
}