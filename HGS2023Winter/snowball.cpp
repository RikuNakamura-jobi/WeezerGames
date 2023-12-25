//===========================================
//
// 雪玉のメイン処理[snowball.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "snowball.h"
#include "soldier.h"
#include "renderer.h"
#include "useful.h"
#include "collision.h"

#include "snowball_manager.h"
#include "soldier_manager.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CSnowBall::CSnowBall() : CModel(CObject::TYPE_SNOWBALL, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量

	m_pPrev = nullptr;		// 前のへのポインタ
	m_pNext = nullptr;		// 次のへのポインタ

	if (CSnowBallManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CSnowBallManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CSnowBall::~CSnowBall()
{

}

//============================
// 前のポインタの設定処理
//============================
void CSnowBall::SetPrev(CSnowBall* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CSnowBall::SetNext(CSnowBall* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CSnowBall* CSnowBall::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CSnowBall* CSnowBall::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 破片の初期化処理
//==============================
HRESULT CSnowBall::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;			// 移動量

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CSnowBall::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CSnowBallManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CSnowBallManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// 破片の更新処理
//=====================================
void CSnowBall::Update(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 位置を移動する
	pos += m_move;

	// 位置を設定する
	SetPos(pos);
}

//=====================================
// 破片の描画処理
//=====================================
void CSnowBall::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CSnowBall::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CXFile::TYPE_FRAC_WOOD);	// モデル情報

	// 全ての値を設定する
	m_move = move;			// 移動量
}

//=======================================
// 生成処理
//=======================================
CSnowBall* CSnowBall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ローカルオブジェクトを生成
	CSnowBall* pFrac = nullptr;	// インスタンスを生成

	if (pFrac == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFrac = new CSnowBall;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFrac != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFrac->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFrac->SetData(pos, move);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 破片のポインタを返す
	return pFrac;
}

//=======================================
// 当たり判定処理
//=======================================
bool CSnowBall::Colision()
{
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

				if (collision::SquareTrigger(pObjCheck->GetPos(), GetPos(), pObjCheck->GetRot(), D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(-100.0f, -100.0f, -100.0f)))
				{
					pObjCheck->Hit();

					Uninit();

					return true;
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}

	return false;
}