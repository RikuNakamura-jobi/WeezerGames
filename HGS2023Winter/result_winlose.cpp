//=======================================
//
// ���U���g���ʂ̃��C������[result_winlose.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "result_winlose.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"

//---------------------------------------
// �}�N����`
//---------------------------------------

//=========================
// �R���X�g���N�^
//=========================
CWinLose::CWinLose() : CObject2D(CObject::TYPE_TITLELOGO, CObject::PRIORITY_PLAYER)
{

}

//=========================
// �f�X�g���N�^
//=========================
CWinLose::~CWinLose()
{

}

//=========================
// ����������
//=========================
HRESULT CWinLose::Init(void)
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
void CWinLose::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CWinLose::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CWinLose::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//=========================
// ���̐ݒ菈��
//=========================
void CWinLose::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 250.0f, 0.0f));			// �ʒu�ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// �����ݒ�
	SetSize(D3DXVECTOR3(400.0f, 100.0f, 0.0f));			// �T�C�Y�ݒ�
	SetLength();			// �����ݒ�
	SetAngle();				// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTexture();

	if (CGame::GetState() == CGame::STATE_OFFWIN)
	{ // �����̏ꍇ

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\SUCCESS.png"));
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\FAILED.png"));
	}
}

//=========================
// ��������
//=========================
CWinLose* CWinLose::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CWinLose* pLocus2D = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLocus2D == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLocus2D = new CWinLose;
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