//============================================
//
// ���mAI�w�b�_�[[soldier_ai.h]
// Author�F��������
//
//============================================
#ifndef _SOLDIER_AI_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SOLDIER_AI_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "soldier.h"

//--------------------------------------------
// �N���X(���m�v���C���[�N���X)
//--------------------------------------------
class CSoldierAI : public CSoldier
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�퓬AI)
	enum BATTLEAI
	{
		BATTLEAI_ATTACK = 0,	// �U���I
		BATTLEAI_GUARD,			// ����I
		BATTLEAI_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�퓬AI)
	enum SITUATION
	{
		SITUATION_ASSAULT = 0,	// �ˌ�
		SITUATION_SHOOT,		// �U��
		SITUATION_GUARD,		// ���
		SITUATION_ESCAPE,		// ����
		SITUATION_WAIT,			// �ҋ@
		SITUATION_MAX			// ���̗񋓌^�̑���
	};

	CSoldierAI();			// �R���X�g���N�^
	~CSoldierAI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle);		// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void AI(void);	//AI�̂܂Ƃ�

	// �ړ��Ȃ�
	void AIMove(void);
	void AIShoot(void);

	// �s���I��
	void AIOffense(void);
	void AIOffenseAttack(void);
	void AIOffenseGuard(void);
	void AIDefense(void);
	void AIDefenseAttack(void);
	void AIDefenseGuard(void);

	// �����o�ϐ�
	BATTLEAI m_BattleAI;
	SITUATION m_Situation;
	D3DXVECTOR3 m_AimPos;
	int m_nCountJudge;
	int m_nNumNearPlayer;
	int m_nNumNearEnemy;
	float m_fTargetRot;
};

#endif