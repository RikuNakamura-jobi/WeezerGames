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

	// ���X�g�\���֌W
	void SetPrev(CSnowBall* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CSnowBall* pNext);	// ��̃|�C���^�̐ݒ菈��
	CSnowBall* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CSnowBall* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSnowBall* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	bool Colision();			//�����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���

	// ���X�g�\���֌W
	CSnowBall* m_pPrev;	// �O�ւ̃|�C���^
	CSnowBall* m_pNext;	// ���ւ̃|�C���^
};

#endif