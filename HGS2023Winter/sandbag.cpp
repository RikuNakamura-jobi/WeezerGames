//============================================
//
// �y�X�̃��C������[sandbag.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "sandbag.h"
#include "useful.h"

#include "sandbag_manager.h"

//=========================================
// �R���X�g���N�^
//=========================================
CSandbag::CSandbag() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^

	if (CSandbagManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CSandbagManager::Get()->Regist(this);
	}
}

//=========================================
// �f�X�g���N�^
//=========================================
CSandbag::~CSandbag()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CSandbag::SetPrev(CSandbag* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CSandbag::SetNext(CSandbag* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CSandbag* CSandbag::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CSandbag* CSandbag::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}


//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CSandbag::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CSandbag::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CSandbagManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CSandbagManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//===========================================
// �X�V����
//===========================================
void CSandbag::Update(void)
{

}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CSandbag::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CSandbag::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
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
CSandbag* CSandbag::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���m�̃|�C���^��錾
	CSandbag* pSoldier = nullptr;

	if (pSoldier == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pSoldier = new CSandbag;
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
		pSoldier->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pSoldier;
}