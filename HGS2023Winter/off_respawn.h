//===========================================
//
// �U���������n�_�w�b�_�[[off_respawn.h]
// Author ��������
//
//===========================================
#ifndef _OFF_RESPAWN_H_
#define _OFF_RESPAWN_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"

//-------------------------------------------
// �N���X��`(�U���������n�_)
//-------------------------------------------
class COffRespawn : public CObject
{
public:		// �N�ł��A�N�Z�X�ł���

	COffRespawn();					// �R���X�g���N�^
	~COffRespawn();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetData(const D3DXVECTOR3 pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);		// �ʒu�̐ݒ菈��
	D3DXVECTOR3 GetPos(void) const;				// �ʒu�̎擾����

	// �ÓI�����o�֐�
	static COffRespawn* Create(const D3DXVECTOR3 pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
};

#endif