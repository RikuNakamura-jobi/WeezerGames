//===================================
//
// ���U���g�w�b�_�[[result_winlose.h]
// Author ��������
//
//===================================
#ifndef _RESULT_WINLOSE_H_
#define _RESULT_WINLOSE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CWinLose)
//-----------------------------------
class CWinLose : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CWinLose();				// �R���X�g���N�^
	~CWinLose();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CWinLose* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif