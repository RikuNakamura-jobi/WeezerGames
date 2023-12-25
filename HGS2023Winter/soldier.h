//============================================
//
// 兵士ヘッダー[soldier.h]
// Author：小原立暉
//
//============================================
#ifndef _SOLDIER_H_					// このマクロ定義がされていなかったら
#define _SOLDIER_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "character.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション

//--------------------------------------------
// クラス(兵士クラス)
//--------------------------------------------
class CSoldier : public CCharacter
{
public:			// 誰でもアクセスできる

	CSoldier();				// コンストラクタ
	~CSoldier();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// セット・ゲット関係
	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理

	void SetRotDest(const D3DXVECTOR3& rot);	// 目標の向きの設定処理
	D3DXVECTOR3 GetRotDest(void) const;			// 目標の向きの取得処理

	void SetLife(const int nLife);				// 体力の設定処理
	int GetLife(void) const;					// 体力の取得処理

	void SetSpeed(float fSpeed);				// 速度の設定処理
	float GetSpeed(void) const;					// 速度の取得処理

	void SetEnableMove(bool bMove);				// 移動状況の設定処理
	bool IsMove(void) const;					// 移動状況の取得処理

	void SetEnableJump(bool bJump);				// ジャンプ状況の設定処理
	bool IsJump(void) const;					// ジャンプ状況の取得処理

	CMotion* GetMotion(void) const;				// モーションの情報の取得処理

	// 静的メンバ関数
	static CSoldier* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void ElevationCollision(void);	// 起伏地面の当たり判定処理

	// メンバ変数
	CMotion* m_pMotion;				// モーションの情報

	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	int m_nLife;					// 体力
	float m_fSpeed;					// 速度
	bool m_bMove;					// 移動状況
	bool m_bJump;					// ジャンプ状況
};

#endif