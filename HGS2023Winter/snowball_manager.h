//============================================
//
// ��ʃ}�l�[�W���[�w�b�_�[[snowball_manager.h]
// Author�F��������
//
//============================================
#ifndef _SNOWBALL_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _SNOWBALL_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CSnowBall;		// ���

//--------------------------------------------
// �N���X(�T���v���}�l�[�W���[�N���X)
//--------------------------------------------
class CSnowBallManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CSnowBallManager();			// �R���X�g���N�^
	~CSnowBallManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CSnowBall* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CSnowBall* GetTop(void);				// �擪�̎擾����
	void Pull(CSnowBall* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CSnowBallManager* Create(void);	// ��������
	static CSnowBallManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CSnowBall* m_pTop;	// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CSnowBallManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif