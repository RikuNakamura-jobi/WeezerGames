//============================================
//
// プレイヤーのメイン処理[player.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "soldier.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"

#include "motion.h"
#include "elevation_manager.h"
#include "objectElevation.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
namespace
{
	const int MAX_LIFE = 5;				// 体力の最大数
	const int NUM_MODEL = 15;			// モデルの総数
	const float ADD_GRAVITY = -50.0f;	// 着地時の追加の重力
}

//=========================================
// コンストラクタ
//=========================================
CSoldier::CSoldier() : CCharacter(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;			// モーションの情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nLife = MAX_LIFE;				// 体力
	m_fSpeed = 0.0f;				// 速度
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況
}

//=========================================
// デストラクタ
//=========================================
CSoldier::~CSoldier()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CSoldier::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(NUM_MODEL);

	// データの設定処理
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		m_pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		m_pMotion->Load(CMotion::TYPE_PLAYER);
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nLife = MAX_LIFE;				// 体力
	m_fSpeed = 0.0f;				// 速度
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CSoldier::Uninit(void)
{
	// モーションのメモリを開放する
	delete m_pMotion;
	m_pMotion = nullptr;

	// 終了処理
	CCharacter::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CSoldier::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// モーションの更新処理
	m_pMotion->Update();

	// 起伏地面との当たり判定処理
	ElevationCollision();

	// プレイヤーの情報を表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n移動量：%f %f %f\n体力：%d\nジャンプ状況：%d\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z, m_nLife, m_bJump);
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CSoldier::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//===========================================
// モーションの情報の設定処理
//===========================================
CMotion* CSoldier::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// 生成処理
//===========================================
CSoldier* CSoldier::Create(const D3DXVECTOR3& pos)
{
	// 兵士のポインタを宣言
	CSoldier* pSoldier = nullptr;

	if (pSoldier == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pSoldier = new CSoldier;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pSoldier;
	}

	if (pSoldier != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pSoldier->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSoldier->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pSoldier;
}

//=======================================
// 情報の設定処理
//=======================================
void CSoldier::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を初期化する
	SetPos(D3DXVECTOR3(pos.x - 500.0f, pos.y + 400.0f, pos.z));		// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));				// 向き
	SetScale(NONE_SCALE);			// 拡大率

	m_rotDest = GetRot();	// 目的の向きを設定する

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(nCntData));	// データの設定処理
	}
}

//=======================================
// 移動量の設定処理
//=======================================
void CSoldier::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CSoldier::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 目標の向きの設定処理
//=======================================
void CSoldier::SetRotDest(const D3DXVECTOR3& rot)
{
	// 目標の向きを設定する
	m_rotDest = rot;
}

//=======================================
// 目標の向きの取得処理
//=======================================
D3DXVECTOR3 CSoldier::GetRotDest(void) const
{
	// 目標の向きを返す
	return m_rotDest;
}

//=======================================
// 体力の設定処理
//=======================================
void CSoldier::SetLife(const int nLife)
{
	if (nLife > MAX_LIFE)
	{ // 体力が一定以上の場合

		// 体力を最大に設定する
		m_nLife = MAX_LIFE;
	}
	else
	{ // 上記以外

		// 体力を設定する
		m_nLife = nLife;
	}
}

//=======================================
// 体力の取得処理
//=======================================
int CSoldier::GetLife(void) const
{
	// 体力を返す
	return m_nLife;
}

//=======================================
// 速度の設定処理
//=======================================
void CSoldier::SetSpeed(float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CSoldier::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
}

//=======================================
// 移動状況の設定処理
//=======================================
void CSoldier::SetEnableMove(bool bMove)
{
	// 移動状況を設定する
	m_bMove = bMove;
}

//=======================================
// 移動状況の取得処理
//=======================================
bool CSoldier::IsMove(void) const
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// ジャンプ状況の設定処理
//=======================================
void CSoldier::SetEnableJump(bool bJump)
{
	// ジャンプ状況を設定する
	m_bJump = bJump;
}

//=======================================
// ジャンプ状況の取得処理
//=======================================
bool CSoldier::IsJump(void) const
{
	// ジャンプ状況を返す
	return m_bJump;
}

//=======================================
// 起伏地面の当たり判定処理
//=======================================
void CSoldier::ElevationCollision(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	float fHeight = 0.0f;			// 高さ
	bool bJump = true;				// ジャンプ状況
	bool bRange = false;			// 範囲内状況

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos, bRange);
		
		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			// 重力を設定する
			m_move.y = ADD_GRAVITY;

			// ジャンプ状況を false にする
			bJump = false;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}