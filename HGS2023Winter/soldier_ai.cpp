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

#include "soldier_manager.h"

//=========================================
// コンストラクタ
//=========================================
CSoldierAI::CSoldierAI() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	m_BattleAI = BATTLEAI_ATTACK;
	m_Situation = SITUATION_ASSAULT;
	m_nCountJudge = 0;
	m_nNumNearPlayer = 0;
	m_nNumNearEnemy = 0;
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

	m_nCountJudge = 0;

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

	// AI
	AI();

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

	int nRand = rand() % 2;

	if (nRand)
	{
		m_BattleAI = BATTLEAI_ATTACK;
	}
	else
	{
		m_BattleAI = BATTLEAI_GUARD;
	}
}

//=======================================
// AIの処理
//=======================================
void CSoldierAI::AI(void)
{
	m_nCountJudge++;

	CSoldierManager *soldierManager = CSoldierManager::Get();

	if (soldierManager != nullptr)
	{ // マネージャーが存在していた場合

	  // ポインタを宣言
		CSoldier *pObjectTop = soldierManager->GetTop();	// 先頭オブジェクト

		if (pObjectTop != nullptr)
		{
			// ポインタを宣言
			CSoldier *pObjCheck = pObjectTop;	// オブジェクト確認用

			while (pObjCheck != NULL)
			{ // オブジェクトが使用されている場合繰り返す

				CSoldier *pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (D3DXVec3Length(&(pObjCheck->GetPos() - GetPos())) < 500.0f)
				{
					if (pObjCheck->GetBattle() == GetBattle())
					{
						m_nNumNearPlayer++;
					}
					else
					{
						m_nNumNearEnemy++;
					}
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}

	if (GetBattle() == BATTLE_OFF)
	{
		AIOffense();
	}
	else
	{
		AIDefense();
	}
}

//=======================================
// 移動AIの処理
//=======================================
void CSoldierAI::AIMove(void)
{
	// 目的の向きを取得する
	D3DXVECTOR3 rotDest = GetRotDest();

	if (m_Situation == SITUATION_ASSAULT)
	{
		// 目的の向きを設定する
		rotDest.y = D3DX_PI;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_SHOOT)
	{
		// 目的の向きを設定する
		rotDest.y = D3DX_PI;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_GUARD)
	{
		// 目的の向きを設定する
		rotDest.y = D3DX_PI;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_ESCAPE)
	{
		// 目的の向きを設定する
		rotDest.y = D3DX_PI;

		// 移動状況を設定する
		SetEnableMove(true);
	}
	else
	{
		// 移動状況を設定する
		SetEnableMove(false);
	}

	// 目的の向きを設定する
	SetRotDest(rotDest);
}

//=======================================
// 攻めAIの処理
//=======================================
void CSoldierAI::AIOffense(void)
{
	if (m_BattleAI == BATTLEAI_ATTACK)
	{
		AIOffenseAttack();
	}
	else
	{
		AIOffenseGuard();
	}
}
void CSoldierAI::AIOffenseAttack(void)
{//攻撃的

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 1)
		{
			if (nRand > 1)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 0)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_ASSAULT;
		}
	}
}
void CSoldierAI::AIOffenseGuard(void)
{//守備的

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 2)
		{
			if (m_nNumNearPlayer == 0)
			{
				if (nRand > 0)
				{
					m_Situation = SITUATION_ESCAPE;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
			else
			{
				if (nRand > 2)
				{
					m_Situation = SITUATION_ASSAULT;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 2)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_ASSAULT;
		}
	}
}

//=======================================
// 守りAIの処理
//=======================================
void CSoldierAI::AIDefense(void)
{
	if (m_BattleAI == BATTLEAI_ATTACK)
	{
		AIDefenseAttack();
	}
	else
	{
		AIDefenseGuard();
	}
}
void CSoldierAI::AIDefenseAttack(void)
{// 攻撃的

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 1)
		{
			if (nRand > 1)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 0)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_GUARD;
		}
	}
}
void CSoldierAI::AIDefenseGuard(void)
{// 守備的
	
	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 2)
		{
			if (m_nNumNearPlayer == 0)
			{
				m_Situation = SITUATION_SHOOT;
			}
			else
			{
				if (nRand > 2)
				{
					m_Situation = SITUATION_ESCAPE;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 2)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_GUARD;
		}
	}
}