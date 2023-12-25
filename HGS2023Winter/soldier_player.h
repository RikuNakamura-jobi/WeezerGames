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

	void SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle);		// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Control(void);				// ���쏈��
	void MoveControl(void);			// �ړ��R���g���[��
	void JumpControl(void);			// �W�����v�R���g���[��
	void ThrowControl(void);		// �����̃R���g���[��
	void CameraControl(void);		// �J�����̃R���g���[��

	// �����o�ϐ�
	D3DXVECTOR3 m_CameraRot;		// �J�����̌���
};

#endif