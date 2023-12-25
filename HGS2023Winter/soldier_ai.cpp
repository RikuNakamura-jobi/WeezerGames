//============================================
//
// 兵士AIのメイン処理[soldier_AI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "soldier_ai.h"
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
CSoldierAI::CSoldierAI() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{

}

//=========================================
// デストラクタ
//=========================================
CSoldierAI::~CSoldierAI()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CSoldierAI::Init(void)
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
void CSoldierAI::Uninit(void)
{
	// 終了処理
	CSoldier::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CSoldierAI::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

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
void CSoldierAI::Draw(void)
{
	// 描画処理
	CSoldier::Draw();
}

//=======================================
// 情報の設定処理
//=======================================
void CSoldierAI::SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// 情報の設定処理
	CSoldier::SetData(pos, type, battle);
}