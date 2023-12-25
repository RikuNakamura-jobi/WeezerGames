//============================================
//
// �u���b�N�w�b�_�[[block.h]
// Author�F��������
//
//============================================
#ifndef _BLOCK_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "model.h"

//--------------------------------------------
// �N���X(�u���b�N�N���X)
//--------------------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_TREE = 0,		// ��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CBlock();				// �R���X�g���N�^
	~CBlock();				// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CBlock* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBlock* pNext);	// ��̃|�C���^�̐ݒ菈��
	CBlock* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CBlock* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���

	// ���X�g�\���֌W
	CBlock* m_pPrev;	// �O�ւ̃|�C���^
	CBlock* m_pNext;	// ���ւ̃|�C���^
};

#endif