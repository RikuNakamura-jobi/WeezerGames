//===================================
//
// �^�C�g�����S�w�b�_�[[title_logo.h]
// Author ��������
//
//===================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CTitleLogo)
//-----------------------------------
class CTitleLogo : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CTitleLogo();			// �R���X�g���N�^
	~CTitleLogo();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitleLogo* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif