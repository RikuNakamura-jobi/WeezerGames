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
#include "useful.h"

#include "snowball_manager.h"
#include "soldier_manager.h"

//==============================
// �R���X�g���N�^
//==============================
CFlag::CFlag() : CModel(CObject::TYPE_FLAG, CObject::PRIORITY_ENTITY)
{

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

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CFlag::Uninit(void)
{
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
// ���̓����蔻�菈��
//=====================================
void CFlag::collision(void)
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

			}
			else if (nNumOffe > nNumDefe)
			{

			}
			else
			{

			}
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CFlag::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_FRAC_SCREW);	// ���f������ݒ肷��
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