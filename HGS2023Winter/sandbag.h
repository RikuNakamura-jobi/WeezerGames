//============================================
//
// �y�X�w�b�_�[[sandbag.h]
// Author�F��������
//
//============================================
#ifndef _SANDBAG_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SANDBAG_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "model.h"

//--------------------------------------------
// �N���X(�y�X�N���X)
//--------------------------------------------
class CSandbag : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CSandbag();				// �R���X�g���N�^
	~CSandbag();				// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CSandbag* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CSandbag* pNext);	// ��̃|�C���^�̐ݒ菈��
	CSandbag* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CSandbag* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSandbag* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:		// ���������A�N�Z�X�ł���

	// ���X�g�\���֌W
	CSandbag* m_pPrev;	// �O�ւ̃|�C���^
	CSandbag* m_pNext;	// ���ւ̃|�C���^
};

#endif