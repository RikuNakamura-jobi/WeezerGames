//============================================
//
// ���m�w�b�_�[[soldier.h]
// Author�F��������
//
//============================================
#ifndef _SOLDIER_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SOLDIER_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����

//--------------------------------------------
// �N���X(���m�N���X)
//--------------------------------------------
class CSoldier : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	CSoldier();				// �R���X�g���N�^
	~CSoldier();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����

	void SetRotDest(const D3DXVECTOR3& rot);	// �ڕW�̌����̐ݒ菈��
	D3DXVECTOR3 GetRotDest(void) const;			// �ڕW�̌����̎擾����

	void SetLife(const int nLife);				// �̗͂̐ݒ菈��
	int GetLife(void) const;					// �̗͂̎擾����

	void SetSpeed(float fSpeed);				// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����

	void SetEnableMove(bool bMove);				// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����

	void SetEnableJump(bool bJump);				// �W�����v�󋵂̐ݒ菈��
	bool IsJump(void) const;					// �W�����v�󋵂̎擾����

	CMotion* GetMotion(void) const;				// ���[�V�����̏��̎擾����

	// �ÓI�����o�֐�
	static CSoldier* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void ElevationCollision(void);	// �N���n�ʂ̓����蔻�菈��

	// �����o�ϐ�
	CMotion* m_pMotion;				// ���[�V�����̏��

	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	int m_nLife;					// �̗�
	float m_fSpeed;					// ���x
	bool m_bMove;					// �ړ���
	bool m_bJump;					// �W�����v��
};

#endif