//=======================================
//
// �U���������n�_�̃��C������[off_respawn.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "off_respawn.h"

//==========================================
// �R���X�g���N�^
//==========================================
COffRespawn::COffRespawn() : CObject(TYPE_ACQUIREUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
}

//==========================================
// �f�X�g���N�^
//==========================================
COffRespawn::~COffRespawn()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT COffRespawn::Init(void)
{
	// �S�Ă̒l������������
	m_pos = NONE_D3DXVECTOR3;		// �ʒu

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void COffRespawn::Uninit(void)
{
	// �j������
	Release();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void COffRespawn::Update(void)
{
	
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void COffRespawn::Draw(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void COffRespawn::SetData(const D3DXVECTOR3 pos)
{
	// �S�Ă̒l��ݒ肷��
	m_pos = pos;		// �ʒu
}

//=====================================
// �ʒu�̐ݒ菈��
//=====================================
void COffRespawn::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//=====================================
// �ʒu�̎擾����
//=====================================
D3DXVECTOR3 COffRespawn::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//=====================================
// ��������
//=====================================
COffRespawn* COffRespawn::Create(const D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	COffRespawn* pRespawn = nullptr;			// �����n�_�̃C���X�^���X�𐶐�

	if (pRespawn == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pRespawn = new COffRespawn;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRespawn != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRespawn->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRespawn->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �����n�_�̃|�C���^��Ԃ�
	return pRespawn;
}