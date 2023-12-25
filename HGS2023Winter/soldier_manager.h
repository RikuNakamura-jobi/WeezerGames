//============================================
//
// ���m�}�l�[�W���[�w�b�_�[[soldier_manager.h]
// Author�F��������
//
//============================================
#ifndef _SOLDIER_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _SOLDIER_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CSoldier;		// ���

//--------------------------------------------
// �N���X(�T���v���}�l�[�W���[�N���X)
//--------------------------------------------
class CSoldierManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CSoldierManager();			// �R���X�g���N�^
	~CSoldierManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CSoldier* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CSoldier* GetTop(void);				// �擪�̎擾����
	void Pull(CSoldier* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CSoldierManager* Create(void);	// ��������
	static CSoldierManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CSoldier* m_pTop;	// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CSoldierManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif