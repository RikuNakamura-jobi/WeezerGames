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
#include "renderer.h"
#include "useful.h"

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
}

//==============================
// デストラクタ
//==============================
CSnowBall::~CSnowBall()
{

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
}

//=====================================
// 破片の更新処理
//=====================================
void CSnowBall::Update(void)
{

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
void CSnowBall::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CXFile::TYPE_FRAC_WOOD);	// モデル情報
}

//=======================================
// 生成処理
//=======================================
CSnowBall* CSnowBall::Create(const D3DXVECTOR3& pos)
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
		pFrac->SetData(pos);
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