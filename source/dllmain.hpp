/**
 * \file dllmain.hpp
 * \brief BVEがATSプラグインを呼び出す時際に使うコールバック関数群。
 * \author mackoy, Takuya Itoh
 */

#ifndef DLL_MAIN_HPP_INCLUDED
#define DLL_MAIN_HPP_INCLUDED

#include <windows.h>

#include "ats_define.hpp"

/// このプラグインがBVEによって読み込まれた時に呼び出される。
 void WINAPI atsLoad();

/// このプラグインがBVEから解放された時に呼び出される。
 void WINAPI atsDispose();

/// BVEがこのATSプラグインのバージョン値を取得しようとした時に呼び出される。
/// \return ATSプラグインのバージョン値
 int WINAPI atsGetPluginVersion();

/// BVEに列車が読み込まれた時に呼び出される。
/// \param[in] vspec 車両の諸元
 void WINAPI atsSetVehicleSpec(ATS_VEHICLESPEC);

/// BVEのシナリオが開始された時に呼び出される。
/// \param[in] param ブレーキハンドルの位置
 void WINAPI atsInitialize(int);

/// BVEがシナリオ実行中に毎フレームごとに呼び出される。
/// \param[in] vs 毎処理ごとの車両の状態
/// \param[out] p_panel 運転台へ送る値の配列 (配列の範囲: 0-255)
/// \param[out] p_sound サウンド命令の値の配列 (配列の範囲: 0-255)
/// \return 列車の操縦命令
 ATS_HANDLES WINAPI atsElapse(ATS_VEHICLESTATE vs, int *p_panel, int *p_sound);

/// プレイヤーによって力行ノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後の力行ノッチ位置
 void WINAPI atsSetPower(int notch);

/// プレイヤーによってブレーキノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後のブレーキノッチ位置
 void WINAPI atsSetBrake(int notch);

/// プレイヤーによってレバーサーの位置が変更された時に呼び出される。
/// \param[in] pos 変更後のレバーサーの位置
 void WINAPI atsSetReverser(int pos);

/// プレイヤーによってATSプラグインで使用するキーが押された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
 void WINAPI atsKeyDown(int ats_key_code);

/// プレイヤーによってATSプラグインで使用するキーが押されていて、それが離された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
 void WINAPI atsKeyUp(int ats_key_code);

/// プレイヤーによって警笛が取り扱われた時に呼び出される。
/// \param[in] ats_horn 警笛の種類
 void WINAPI atsHornBlow(int ats_horn);

/// BVEによって列車のドアが開かれた時に呼び出される。
 void WINAPI atsDoorOpen();

/// BVEによって列車のドアが閉じられた時に呼び出される。
 void WINAPI atsDoorClose();

/// BVEによって現在の信号現示が変更された時に呼び出される。
/// \param[in] signal 信号現示のインデックス
 void WINAPI atsSetSignal(int signal);

/// BVEによって地上子を通過した際に呼び出される。
/// \param[in] beacon_data 地上子の情報
 void WINAPI atsSetBeaconData(ATS_BEACONDATA beacon_data);

#endif	// DLL_MAIN_HPP_INCLUDED