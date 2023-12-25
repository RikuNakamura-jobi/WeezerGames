//============================================
//
// �y�X�}�l�[�W���[�w�b�_�[[sandbag_manager.h]
// Author�F��������
//
//============================================
#ifndef _SANDBAG_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _SANDBAG_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CSandbag;		// �u���b�N

//--------------------------------------------
// �N���X(�T���v���}�l�[�W���[�N���X)
//--------------------------------------------
class CSandbagManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CSandbagManager();			// �R���X�g���N�^
	~CSandbagManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CSandbag* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CSandbag* GetTop(void);				// �擪�̎擾����
	void Pull(CSandbag* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CSandbagManager* Create(void);	// ��������
	static CSandbagManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CSandbag* m_pTop;			// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CSandbagManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif