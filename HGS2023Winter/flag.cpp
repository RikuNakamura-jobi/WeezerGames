//===========================================
//
// 旗のメイン処理[flag.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "flag.h"
#include "soldier.h"
#include "renderer.h"
#include "useful.h"

#include "snowball_manager.h"
#include "soldier_manager.h"

//==============================
// コンストラクタ
//==============================
CFlag::CFlag() : CModel(CObject::TYPE_FLAG, CObject::PRIORITY_ENTITY)
{

}

//==============================
// デストラクタ
//==============================
CFlag::~CFlag()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CFlag::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CFlag::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CFlag::Update(void)
{
	
}

//=====================================
// 破片の描画処理
//=====================================
void CFlag::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 旗の当たり判定処理
//=====================================
void CFlag::collision(void)
{
	CSoldierManager *soldierManager = CSoldierManager::Get();
	int nNumOffe = 0, nNumDefe = 0;

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
					nNumOffe++;
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}

			if (nNumOffe == nNumDefe)
			{

			}
			else if (nNumOffe > nNumDefe)
			{

			}
			else
			{

			}
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CFlag::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_FRAC_SCREW);	// モデル情報を設定する
}

//=======================================
// 生成処理
//=======================================
CFlag* CFlag::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CFlag* pFlag = nullptr;			// インスタンスを生成

	if (pFlag == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFlag = new CFlag;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFlag != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFlag->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFlag->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 城のポインタを返す
	return pFlag;
}