//============================================
//
// 旗ヘッダー[flag.h]
// Author：小原立暉
//
//============================================
#ifndef _FLAG_H_					// このマクロ定義がされていなかったら
#define _FLAG_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "model.h"

//--------------------------------------------
// クラス(旗クラス)
//--------------------------------------------
class CFlag : public CModel
{
public:			// 誰でもアクセスできる

	CFlag();				// コンストラクタ
	~CFlag();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);			// 情報の設定処理

	// 静的メンバ関数
	static CFlag* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void collision(void);

};

#endif