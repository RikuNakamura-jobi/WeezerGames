//=======================================
//
// �`���[�g���A���̉�ʂ̃��C������[tutorial_screen.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "tutorial_screen.h"
#include "renderer.h"
#include "texture.h"

//---------------------------------------
// �}�N����`
//---------------------------------------

//=========================
// �R���X�g���N�^
//=========================
CTutorialScreen::CTutorialScreen() : CObject2D(CObject2D::TYPE_SCREEN, CObject::PRIORITY_PLAYER)
{

}

//=========================
// �f�X�g���N�^
//=========================
CTutorialScreen::~CTutorialScreen()
{

}

//=========================
// ����������
//=========================
HRESULT CTutorialScreen::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CTutorialScreen::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CTutorialScreen::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CTutorialScreen::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//=========================
// ���̐ݒ菈��
//=========================
void CTutorialScreen::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));			// �ʒu�ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// �����ݒ�
	SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));			// �T�C�Y�ݒ�
	SetLength();			// �����ݒ�
	SetAngle();				// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTexture();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\Tutorial.png"));
}

//=========================
// ��������
//=========================
CTutorialScreen* CTutorialScreen::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTutorialScreen* pLocus2D = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLocus2D == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLocus2D = new CTutorialScreen;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLocus2D != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLocus2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLocus2D->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pLocus2D;
}