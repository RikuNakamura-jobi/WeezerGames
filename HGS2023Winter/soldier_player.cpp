//============================================
//
// 兵士プレイヤーのメイン処理[soldier_player.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "soldier_player.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "useful.h"

#include "input.h"
#include "motion.h"

//=========================================
// コンストラクタ
//=========================================
CSoldierPlayer::CSoldierPlayer() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{

}

//=========================================
// デストラクタ
//=========================================
CSoldierPlayer::~CSoldierPlayer()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CSoldierPlayer::Init(void)
{
	if (FAILED(CSoldier::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CSoldierPlayer::Uninit(void)
{
	// 終了処理
	CSoldier::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CSoldierPlayer::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// 操作処理
	Control();

	// 移動量
	Move();

	// モーションの更新処理
	GetMotion()->Update();

	// 起伏地面との当たり判定処理
	ElevationCollision();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CSoldierPlayer::Draw(void)
{
	// 描画処理
	CSoldier::Draw();
}

//=======================================
// 情報の設定処理
//=======================================
void CSoldierPlayer::SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// 情報の設定処理
	CSoldier::SetData(pos, type, battle);
}

//=======================================
// 操作処理
//=======================================
void CSoldierPlayer::Control(void)
{
	// 移動コントロール
	MoveControl();

	// ジャンプコントロール
	JumpControl();
}

//=======================================
// 移動コントロール
//=======================================
void CSoldierPlayer::MoveControl(void)
{
	// 目的の向きを取得する
	D3DXVECTOR3 rotDest = GetRotDest();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) > 0)
	{ // Wキーを押している場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // Aキーを押している場合

			// 目的の向きを設定する
			rotDest.y = -D3DX_PI * 0.25f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // Dキーを押している場合

			// 目的の向きを設定する
			rotDest.y = D3DX_PI * 0.25f;
		}
		else
		{ // 上記以外

			// 目的の向きを設定する
			rotDest.y = 0.0f;
		}

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) < 0)
	{ // Sキーを押している場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // Aキーを押している場合

			// 目的の向きを設定する
			rotDest.y = -D3DX_PI * 0.75f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // Dキーを押している場合

			// 目的の向きを設定する
			rotDest.y = D3DX_PI * 0.75f;
		}
		else
		{ // 上記以外

			// 目的の向きを設定する
			rotDest.y = D3DX_PI;
		}

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
	{ // Aキーを押している場合

		// 目的の向きを設定する
		rotDest.y = -D3DX_PI * 0.5f;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
	{ // Dキーを押している場合

		// 目的の向きを設定する
		rotDest.y = D3DX_PI * 0.5f;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else
	{ // 上記以外

		// 移動状況を false にする
		SetEnableMove(false);
	}

	// 目的の向きを設定する
	SetRotDest(rotDest);
}

//=======================================
// ジャンプコントロール
//=======================================
void CSoldierPlayer::JumpControl(void)
{
	if ((CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true) &&
		IsJump() == false)
	{ // SPACEキーを押した場合

		// ジャンプ処理
		Jump();
	}
}