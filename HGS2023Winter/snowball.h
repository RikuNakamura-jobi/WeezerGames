//===================================
//
// ��ʃw�b�_�[[snowball.h]
// Author ��������
//
//===================================
#ifndef _SNOWBALL_H_
#define _SNOWBALL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(���)
//-----------------------------------
class CSnowBall : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CSnowBall();			// �R���X�g���N�^
	~CSnowBall();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSnowBall* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
};

#endif