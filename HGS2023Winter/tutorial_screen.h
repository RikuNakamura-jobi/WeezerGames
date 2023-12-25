//===================================
//
// �`���[�g���A���X�N���[���w�b�_�[[tutorial_screen.h]
// Author ��������
//
//===================================
#ifndef _TUTORIAL_SCREEN_H_
#define _TUTORIAL_SCREEN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CTutorialScreen)
//-----------------------------------
class CTutorialScreen : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CTutorialScreen();		// �R���X�g���N�^
	~CTutorialScreen();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTutorialScreen* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif