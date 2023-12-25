//===================================
//
// 2D��ʃw�b�_�[[screen.h]
// Author ��������
//
//===================================
#ifndef _SCREEN_H_
#define _SCREEN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CScreen)
//-----------------------------------
class CScreen : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CScreen();				// �R���X�g���N�^
	~CScreen();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CScreen* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif