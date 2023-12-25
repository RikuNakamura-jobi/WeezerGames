//============================================
//
// �u���b�N�̃��C������[block.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "block.h"
#include "useful.h"

#include "block_manager.h"

//=========================================
// �R���X�g���N�^
//=========================================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_TREE;		// ���

	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CBlockManager::Get()->Regist(this);
	}
}

//=========================================
// �f�X�g���N�^
//=========================================
CBlock::~CBlock()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}


//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = TYPE_TREE;		// ���

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CBlock::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CBlockManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//===========================================
// �X�V����
//===========================================
void CBlock::Update(void)
{

}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CBlock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CBlock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// �S�Ă̒l��ݒ肷��
	m_type = type;

	// ���̐ݒ菈��
	SetPos(pos);		// �ʒu
	SetPosOld(GetPos());											// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));				// ����
	SetScale(NONE_SCALE);											// �g�嗦
	SetFileData(CXFile::TYPE_FRAC_GEAR);
}

//===========================================
// ��������
//===========================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���m�̃|�C���^��錾
	CBlock* pSoldier = nullptr;

	if (pSoldier == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pSoldier = new CBlock;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return pSoldier;
	}

	if (pSoldier != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSoldier->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSoldier->SetData(pos, rot, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pSoldier;
}