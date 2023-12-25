//=======================================
//
// ���擾UI�̃��C������[acquire_UI.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "acquire_UI.h"

#include "objectbillboard.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const D3DXVECTOR3 UI_SIZE[CAcquireUI::TYPE_MAX] = 
	{
		D3DXVECTOR3(60.0f,22.0f,0.0f),
		D3DXVECTOR3(60.0f,20.0f,0.0f),
	};
}

//==========================================
// �R���X�g���N�^
//==========================================
CAcquireUI::CAcquireUI() : CObject(TYPE_ACQUIREUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apUI[nCnt] = nullptr;						// �|���S���̏��
	}
}

//==========================================
// �f�X�g���N�^
//==========================================
CAcquireUI::~CAcquireUI()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT CAcquireUI::Init(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apUI[nCnt] == nullptr)
		{ // �|���S���� NULL �̏ꍇ

			// �|���S���𐶐�����
			m_apUI[nCnt] = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CAcquireUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// �I������
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
	}

	// �j������
	Release();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CAcquireUI::Update(void)
{
	
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void CAcquireUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �`�揈��
		m_apUI[nCnt]->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAcquireUI::SetData(const D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// ���̐ݒ菈��
			m_apUI[nCnt]->SetPos(pos);					// �ʒu
			m_apUI[nCnt]->SetPosOld(pos);				// �O��̈ʒu
			m_apUI[nCnt]->SetSize(UI_SIZE[nCnt]);		// �T�C�Y

			// ���_���W�̐ݒ菈��
			m_apUI[nCnt]->SetVtxPosLeft();
		}
	}
}

//=====================================
// ��������
//=====================================
CAcquireUI* CAcquireUI::Create(const D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAcquireUI* pUI = nullptr;			// UI�̃C���X�^���X�𐶐�

	if (pUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pUI = new CAcquireUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pUI->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// UI�̃|�C���^��Ԃ�
	return pUI;
}