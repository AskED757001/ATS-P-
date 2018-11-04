/**
 * \file ats_define.hpp
 * \brief ATSプラグインで使用する構造体・マクロ等の定義をしている。
 * \author mackoy, Takuya Itoh
 */

#ifndef ATS_DEFINE_HPP_INCLUDED
#define ATS_DEFINE_HPP_INCLUDED

/// ATSプラグインのバージョン
#define ATS_VERSION	0x00020000

/// ATSプラグインで使用するキーのインデックスの定義
#define ATS_KEY_S	0	///< S Key
#define ATS_KEY_A1	1	///< A1 Key
#define ATS_KEY_A2	2	///< A2 Key
#define ATS_KEY_B1	3	///< B1 Key
#define ATS_KEY_B2	4	///< B2 Key
#define ATS_KEY_C1	5	///< C1 Key
#define ATS_KEY_C2	6	///< C2 Key
#define ATS_KEY_D	7	///< D Key
#define ATS_KEY_E	8	///< R Key
#define ATS_KEY_F	9	///< F Key
#define ATS_KEY_G	10	///< G Key
#define ATS_KEY_H	11	///< H Key
#define ATS_KEY_I	12	///< I Key
#define ATS_KEY_J	13	///< J Key
#define ATS_KEY_K	14	///< K Key
#define ATS_KEY_L	15	///< L Key

/// atsInitialize() の引数 param に設定されるブレーキハンドルの位置
#define ATS_INIT_REMOVED	2			///< 抜き取り位置
#define ATS_INIT_EMG		1			///< 非常ブレーキ位置
#define ATS_INIT_SVC		0			///< 常用ブレーキ位置

/// サウンド制御の命令
#define ATS_SOUND_STOP			-10000	///< 停止
#define ATS_SOUND_PLAY			1		///< 一度だけ再生（ワンショット）
#define ATS_SOUND_PLAYLOOPING	-1		///< 繰り返し再生
#define ATS_SOUND_CONTINUE		2		///< ワンショット再生中の状態を継続する。

/// 警笛の種類
#define ATS_HORN_PRIMARY	0			///< 警笛1
#define ATS_HORN_SECONDARY	1			///< 警笛2
#define ATS_HORN_MUSIC		2			///< ミュージックホーン

/// 定速度制御の命令
#define ATS_CONSTANTSPEED_CONTINUE	0	///< 定速度制御を継続する。
#define ATS_CONSTANTSPEED_ENABLE	1	///< 有効にする。
#define ATS_CONSTANTSPEED_DISABLE	2	///< 無効にする。

/// 車両の諸元
struct ATS_VEHICLESPEC
{
	int BrakeNotches;		///< ブレーキノッチの数
	int PowerNotches;		///< 力行ノッチの数
	int AtsNotch;			///< ATSをキャンセル可能なブレーキノッチ位置
	int B67Notch;			///< 80%のブレーキノッチ位置 (67度)
	int Cars;				///< 車の数
};

/// 毎処理ごとの車両の状態
struct ATS_VEHICLESTATE
{
	double Location;		///< 列車の位置 (Z軸) (m)
	float Speed;			///< 列車の速度 (km/h)
	int Time;				///< 現在の時間 (ms)
	float BcPressure;		///< ブレーキシリンダの圧力 (Pa)
	float MrPressure;		///< 元空気溜まりの圧力 (Pa)
	float ErPressure;		///< 釣合空気溜まりの圧力 (Pa)
	float BpPressure;		///< ブレーキ管の圧力 (Pa)
	float SapPressure;		///< 直通管の圧力 (Pa)
	float Current;			///< 電流 (A)
};

/// 地上子の情報
struct ATS_BEACONDATA
{
	int Type;				///< 地上子の種類
	int Signal;				///< 接続されている閉塞の信号現示
	float Distance;			///< 接続されている閉塞への距離 (m)
	int Optional;			///< オプションデータの値
};

/// 列車の操縦命令
struct ATS_HANDLES
{
	int Brake;				///< ブレーキノッチ位置
	int Power;				///< 力行ノッチ位置
	int Reverser;			///< レバーサー位置
	int ConstantSpeed;		///< 定速度制御の状態
};

#endif	// ATS_DEFINE_HPP_INCLUDED
