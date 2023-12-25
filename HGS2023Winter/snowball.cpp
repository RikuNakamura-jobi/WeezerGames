//===========================================
//
// ��ʂ̃��C������[snowball.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "snowball.h"
#include "renderer.h"
#include "useful.h"

#include "snowball_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CSnowBall::CSnowBall() : CModel(CObject::TYPE_SNOWBALL, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���

	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^

	if (CSnowBallManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CSnowBallManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CSnowBall::~CSnowBall()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CSnowBall::SetPrev(CSnowBall* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CSnowBall::SetNext(CSnowBall* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CSnowBall* CSnowBall::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CSnowBall* CSnowBall::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CSnowBall::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;			// �ړ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CSnowBall::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CSnowBallManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CSnowBallManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CSnowBall::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CSnowBall::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSnowBall::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CXFile::TYPE_FRAC_WOOD);	// ���f�����
}

//=======================================
// ��������
//=======================================
CSnowBall* CSnowBall::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSnowBall* pFrac = nullptr;	// �C���X�^���X�𐶐�

	if (pFrac == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pFrac = new CSnowBall;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFrac != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFrac->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFrac->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �j�Ђ̃|�C���^��Ԃ�
	return pFrac;
}