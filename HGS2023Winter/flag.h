//============================================
//
// ���w�b�_�[[flag.h]
// Author�F��������
//
//============================================
#ifndef _FLAG_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _FLAG_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "model.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CAcquireUI;		// ���擾UI

//--------------------------------------------
// �N���X(���N���X)
//--------------------------------------------
class CFlag : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CFlag();				// �R���X�g���N�^
	~CFlag();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CFlag* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void collision(void);

	// �����o�ϐ�
	CAcquireUI* m_acquire;		// ���擾UI�̏��
};

#endif