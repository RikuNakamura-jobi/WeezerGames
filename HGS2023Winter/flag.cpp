//===========================================
//
// ���̃��C������[flag.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "flag.h"
#include "renderer.h"
#include "acquire_UI.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CFlag::CFlag() : CModel(CObject::TYPE_FLAG, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_acquire = nullptr;		// ���擾UI�̏��
}

//==============================
// �f�X�g���N�^
//==============================
CFlag::~CFlag()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CFlag::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_acquire = nullptr;		// ���擾UI�̏��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CFlag::Uninit(void)
{
	if (m_acquire != nullptr)
	{ // ���擾UI�� NULL ����Ȃ��ꍇ

		// ���擾UI�̏I������
		m_acquire->Uninit();
		m_acquire = nullptr;
	}

	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CFlag::Update(void)
{
	
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CFlag::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CFlag::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);			// ����
	SetScale(NONE_SCALE);				// �g�嗦
	SetFileData(CXFile::TYPE_FLAG);		// ���f������ݒ肷��

	if (m_acquire == nullptr)
	{ // ���擾UI�� NULL �̏ꍇ

		// ���擾UI�𐶐�����
		m_acquire = CAcquireUI::Create(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z));
	}
}

//=======================================
// ��������
//=======================================
CFlag* CFlag::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFlag* pFlag = nullptr;			// �C���X�^���X�𐶐�

	if (pFlag == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pFlag = new CFlag;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFlag != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFlag->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFlag->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��̃|�C���^��Ԃ�
	return pFlag;
}