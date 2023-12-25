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
#include "soldier.h"
#include "renderer.h"
#include "acquire_UI.h"
#include "objectbillboard.h"
#include "useful.h"

#include "snowball_manager.h"
#include "soldier_manager.h"
#include "game.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const float OFF_WIN = 60.0f;		// �U�����������ɂȂ�l
}

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
	// �����蔻��
	if (collision() == true)
	{ // ���̃Q�[�W�����܂����ꍇ

		// �U�����̏����ɂ���
		CGame::SetState(CGame::STATE_OFFWIN);
	}
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
// ���̓����蔻�菈��
//=====================================
bool CFlag::collision(void)
{
	CSoldierManager *soldierManager = CSoldierManager::Get();
	int nNumOffe = 0, nNumDefe = 0;

	if (soldierManager != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �|�C���^��錾
		CSoldier *pObjectTop = soldierManager->GetTop();	// �擪�I�u�W�F�N�g

		if (pObjectTop != nullptr)
		{
			// �|�C���^��錾
			CSoldier *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				CSoldier *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (D3DXVec3Length(&(pObjCheck->GetPos() - GetPos())) < 500.0f)
				{
					nNumOffe++;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}

			if (nNumOffe == nNumDefe)
			{
				// OBARA::�����̓Q�[�W�𓮂����Ȃ�
			}
			else if (nNumOffe > nNumDefe)
			{
				// OBARA::�����̓Q�[�W�𑝂₷
				if (m_acquire != nullptr)
				{ // ���擾UI�� NULL ����Ȃ��ꍇ

					// �r���{�[�h�̏����擾
					D3DXVECTOR3 size = m_acquire->GetPolygon(CAcquireUI::TYPE_METER)->GetSize();

					// �T�C�Y�����Z����
					size.x += 0.1f;

					// �T�C�Y��K�p����
					m_acquire->GetPolygon(CAcquireUI::TYPE_METER)->SetSize(size);

					if (size.x >= OFF_WIN)
					{ // �T�C�Y����萔�𒴂����ꍇ

						// �T�C�Y��␳����
						size.x = OFF_WIN;

						// �T�C�Y��K�p����
						m_acquire->GetPolygon(CAcquireUI::TYPE_METER)->SetSize(size);

						// true ��Ԃ�
						return true;
					}
				}
			}
			else
			{
				// OBARA::�����̓Q�[�W�����炷
				if (m_acquire != nullptr)
				{ // ���擾UI�� NULL ����Ȃ��ꍇ

					// �r���{�[�h�̏����擾
					D3DXVECTOR3 size = m_acquire->GetPolygon(CAcquireUI::TYPE_METER)->GetSize();

					// �T�C�Y�����Z����
					size.x -= 0.1f;

					// �T�C�Y��K�p����
					m_acquire->GetPolygon(CAcquireUI::TYPE_METER)->SetSize(size);
				}
			}
		}
	}

	// false ��Ԃ�
	return false;
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