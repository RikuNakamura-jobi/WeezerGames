//=======================================
//
// �^�C�g�����S�̃��C������[title_logo.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "title_logo.h"
#include "renderer.h"
#include "texture.h"

//---------------------------------------
// �}�N����`
//---------------------------------------

//=========================
// �R���X�g���N�^
//=========================
CTitleLogo::CTitleLogo() : CObject2D(CObject::TYPE_TITLELOGO, CObject::PRIORITY_PLAYER)
{

}

//=========================
// �f�X�g���N�^
//=========================
CTitleLogo::~CTitleLogo()
{

}

//=========================
// ����������
//=========================
HRESULT CTitleLogo::Init(void)
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
void CTitleLogo::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CTitleLogo::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CTitleLogo::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//=========================
// ���̐ݒ菈��
//=========================
void CTitleLogo::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 250.0f, 0.0f));			// �ʒu�ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// �����ݒ�
	SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));			// �T�C�Y�ݒ�
	SetLength();			// �����ݒ�
	SetAngle();				// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTexture();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\Title_logo.png"));
}

//=========================
// ��������
//=========================
CTitleLogo* CTitleLogo::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTitleLogo* pLocus2D = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLocus2D == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLocus2D = new CTitleLogo;
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