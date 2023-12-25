//============================================
//
// ���m�v���C���[�w�b�_�[[soldier_player.h]
// Author�F��������
//
//============================================
#ifndef _SOLDIER_PLAYER_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SOLDIER_PLAYER_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "soldier.h"

//--------------------------------------------
// �N���X(���m�v���C���[�N���X)
//--------------------------------------------
class CSoldierPlayer : public CSoldier
{
public:			// �N�ł��A�N�Z�X�ł���

	CSoldierPlayer();			// �R���X�g���N�^
	~CSoldierPlayer();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);		// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Control(void);				// ���쏈��
};

#endif