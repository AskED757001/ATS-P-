#include "ATSIni.h"
#include "ats.h"
#include "MT.h"
#include "dllmain.hpp"
#include "ATS-P.h"
#include "EB.h"

/// このATSプラグインの、コンピュータ上の絶対パス
char g_module_dir[MAX_PATH];

/// DLLのメイン関数
BOOL WINAPI DllMain(
					HINSTANCE hinstDLL,  ///< DLL モジュールのハンドル
					DWORD fdwReason,     ///< 関数を呼び出す理由
					LPVOID lpvReserved   ///< 予約済み
					)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
        {
            char fullpath[MAX_PATH];
            char drive[MAX_PATH],
                    dir[MAX_PATH];
			char *posIni;

            GetModuleFileNameA(hinstDLL, fullpath, MAX_PATH);
            _splitpath_s(fullpath, drive, MAX_PATH, dir, MAX_PATH, 0, 0, 0, 0);

            strcpy(g_module_dir, drive);
            strcat(g_module_dir, dir);

			//パスから.dllの位置を検索
			posIni = strstr(fullpath, ".dll");

			// .dllを.iniに置換
			memmove(posIni, ".ini", 4);

			// INIファイルをロードして結果を取得
			if (!g_ini.load(fullpath))
				g_ini.save(fullpath);
	}

        break;

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:	
        break;
	}

	return true;
}

/// このプラグインがBVEによって読み込まれた時に呼び出される。
void WINAPI atsLoad()
{
}

/// このプラグインがBVEから解放された時に呼び出される。
void WINAPI atsDispose()
{
}

/// BVEがこのATSプラグインのバージョン値を取得しようとした時に呼び出される。
/// \return ATSプラグインのバージョン値
int WINAPI atsGetPluginVersion()
{
	return ATS_VERSION;
}

/// BVEに列車が読み込まれた時に呼び出される。
/// \param[in] vspec 車両の諸元
void WINAPI atsSetVehicleSpec(ATS_VEHICLESPEC vspec)
{
	emgBrake = vspec.BrakeNotches + 1;
	ATSNotch = vspec.AtsNotch;
	TyreSize = 860 - sqrt(genrand_int32() % (6561));
	if (g_ini.DATA.West != 0)
		g_ini.DATA.West = 1;
}

/// BVEのシナリオが開始された時に呼び出される。
/// \param[in] param ブレーキハンドルの位置
void WINAPI atsInitialize(int param)
{
	speed = 0;
	P.ATSData = 0;
	if (g_ini.DATA.PEnabled != 0)
	PInit(g_ini.DATA.ATSStart);
	if (g_ini.DATA.EBEnabled != 0)
		EBInit(g_ini.DATA.ATSStart);
}

/// BVEがシナリオ実行中に毎フレームごとに呼び出される。
/// \param[in] vs 毎処理ごとの車両の状態
/// \param[out] p_panel 運転台へ送る値の配列 (配列の範囲: 0-255)
/// \param[out] p_sound サウンド命令の値の配列 (配列の範囲: 0-255)
/// \return 列車の操縦命令
ATS_HANDLES WINAPI atsElapse(ATS_VEHICLESTATE vs, int *p_panel, int *p_sound)
{
	speed = fabs(vs.Speed);
	deltaT = vs.Time - time;
	double deltaL = vs.Speed * deltaT / 3600;
	time = vs.Time;
	ATS_HANDLES ret;
	if (P.ATSBrake == 2 || EB.EBBrake)
		ret.Brake = emgBrake;
	else if (P.ATSBrake == 1 && BrakeNotch < emgBrake)
		ret.Brake = emgBrake - 1;
	else
		ret.Brake = BrakeNotch;

	if (Reverser * vs.Speed < -7 && P.ATSPower)
		P.ATSBrake = 2;

	if (g_ini.DATA.DIR != 0 && !pilotlamp || P.ATSBrake != 0 || EB.EBBrake)
		ret.Power = 0;
	else
		ret.Power = PowerNotch;
	ret.Reverser = Reverser;
	if (g_ini.DATA.PEnabled != 0)
	{
		if (p_panel[53] == 0 && BrakeNotch < emgBrake && !P.ATSPower)
			PStart();
		else if (p_panel[53] != 0 && P.ATSPower)
			PInit(0);
		PStartTimer();
		if (P.ATSPower)
			PRun(deltaL * 860 / TyreSize);
		if (Sndistance < 0)
		{
			P.PatternSig = 0;
			Sndistance = 0;
			if(P.ATSData == 1)
			P.ATSData = 0;
		}
		if (Sndistance > 0)
		{
			Sndistance -= deltaL;
		}
	}
	if (g_ini.DATA.EBEnabled != 0)
	{
		if (BrakeNotch < emgBrake && !EB.EBPower)
			EBStart();

		RunEB(deltaT,speed);
	}

	if (g_ini.DATA.PEnabled != 0)
	{
		p_panel[2] = P.ATSPower;
		p_panel[3] = P.WarningLamp;
		p_panel[4] = P.ATSCutLamp;
		p_panel[5] = P.BrakeLamp;
		if (P.ATSData == 1)
			p_panel[6] = 1;
		else if (P.ATSData == 2 && g_ini.DATA.West == 1 || P.ATSData == 2 && g_ini.DATA.West == 2 && P.WestPattern)
			p_panel[6] = 2;
		else if (P.ATSPattern && g_ini.DATA.West == 1 || P.ATSPattern && g_ini.DATA.West == 2 && P.WestPattern)
			p_panel[6] = 2;
		else
			p_panel[6] = 0;

		p_panel[7] = P.ATSRed;
		if (g_ini.DATA.West == 1)
		{
			p_sound[2] = P.WarningSound1;
			p_sound[23] = P.WarningSound2;
			p_sound[4] = P.ATSChime;
		}
		else if (g_ini.DATA.West == 2 && P.WestPattern)
		{
			p_sound[2] = P.WarningSound1;
			p_sound[23] = P.WarningSound2;
		}
		else
			p_sound[4] = P.ATSChime;
	}
	
	if (g_ini.DATA.EBEnabled != 0)
	{
		p_panel[10] = EB.EBLamp;
		p_sound[3] = EB.EBSound;
	}

	if (P.ATSPower && !P.ATSCutLamp && g_ini.DATA.PEnabled != 0)
	{
		if (speed < g_ini.DATA.BarFullGauge)
			p_panel[8] = speed * g_ini.DATA.BarFullNumber / g_ini.DATA.BarFullGauge;
		else
			p_panel[8] = g_ini.DATA.BarFullNumber;

		if (P.PatternSpeed < g_ini.DATA.BarFullGauge)
			p_panel[9] = P.PatternSpeed * g_ini.DATA.BarFullNumber / g_ini.DATA.BarFullGauge;
		else
			p_panel[9] = g_ini.DATA.BarFullNumber;
	}
	else if(g_ini.DATA.PEnabled != 0)
	{
		p_panel[8] = 0;
		p_panel[9] = g_ini.DATA.BarFullNumber;
	}

	return ret;
}

/// プレイヤーによって力行ノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後の力行ノッチ位置
void WINAPI atsSetPower(int notch)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
	PowerNotch = notch;
}

/// プレイヤーによってブレーキノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後のブレーキノッチ位置
void WINAPI atsSetBrake(int notch)
{
	if (g_ini.DATA.EBEnabled != 0)
	{
		if (notch == emgBrake)
			EBStart();
		EBReset();
	}
	BrakeNotch = notch;
}

/// プレイヤーによってレバーサーの位置が変更された時に呼び出される。
/// \param[in] pos 変更後のレバーサーの位置
void WINAPI atsSetReverser(int pos)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
	Reverser = pos;
}

/// プレイヤーによってATSプラグインで使用するキーが押された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
void WINAPI atsKeyDown(int ats_key_code)
{
	if (ats_key_code == ATS_KEY_B1 && BrakeNotch == emgBrake && speed == 0)
	{
		P.ATSBrake = 0;
	}
	if (ats_key_code == ATS_KEY_B2)
	{
		if (P.ATSCut > time)
			P.ATSCut = 0;
		else
			P.ATSCut = time + 60000;
	}
	if (ats_key_code == ATS_KEY_A2)
	{
		if (g_ini.DATA.EBEnabled != 0)
			EBReset();
	}
}

/// プレイヤーによってATSプラグインで使用するキーが押されていて、それが離された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
void WINAPI atsKeyUp(int ats_key_code)
{
}

/// プレイヤーによって警笛が取り扱われた時に呼び出される。
/// \param[in] ats_horn 警笛の種類
void WINAPI atsHornBlow(int ats_horn)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
}

/// BVEによって列車のドアが開かれた時に呼び出される。
void WINAPI atsDoorOpen()
{
	pilotlamp = false;
}

/// BVEによって列車のドアが閉じられた時に呼び出される。
void WINAPI atsDoorClose()
{
	pilotlamp = true;
}

/// BVEによって現在の信号現示が変更された時に呼び出される。
/// \param[in] signal 信号現示のインデックス
void WINAPI atsSetSignal(int signal)
{
}

/// BVEによって地上子を通過した際に呼び出される。
/// \param[in] beacon_data 地上子の情報
void WINAPI atsSetBeaconData(ATS_BEACONDATA beacon_data)
{
	if (g_ini.DATA.PEnabled != 0 && speed != 0 && P.ATSPower)
		PBeacon(beacon_data.Type, beacon_data.Signal, beacon_data.Distance, beacon_data.Optional);
	if (beacon_data.Type == 10 && beacon_data.Optional < 1000)
		Sndistance = beacon_data.Optional;
	if (beacon_data.Type == 25 && speed != 0)
	{
		if (beacon_data.Optional == 0)
		{
			P.ATSData = beacon_data.Optional;
			if (P.PatternSig != 0)
				Sndistance = -1;
		}
		else if (beacon_data.Optional == 1)
			P.ATSData = beacon_data.Optional;
		else if (beacon_data.Optional == 2)
		{
			P.ATSData = beacon_data.Optional;
			if (P.PatternSig != 0)
				P.PatternSig = 0;
		}
		else if (beacon_data.Optional == 5)
			P.WestPattern = true;
		else if (beacon_data.Optional == 6)
			P.WestPattern = false;
	}
}