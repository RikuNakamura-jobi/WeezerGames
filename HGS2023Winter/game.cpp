//============================================
//
// �Q�[���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "skybox.h"

#include "soldier.h"
#include "snowball.h"
#include "castle.h"
#include "flag.h"
#include "off_respawn.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define SUCCESS_TRANS_COUNT		(80)		// �������̑J�ڃJ�E���g
#define FAILED_TRANS_COUNT		(200)		// ���s���̑J�ڃJ�E���g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CFlag* CGame::m_pFlag = nullptr;							// ���̏��
COffRespawn* CGame::m_pRespawn = nullptr;					// �U�����̕����n�_�̏��
CCastle* CGame::m_pCastle = nullptr;						// ��̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{

}

//=========================================
//����������
//=========================================
HRESULT CGame::Init(void)
{
	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���b�V���̓ǂݍ��ݏ���
	CMesh::TxtSet();

	// ���b�V���̃e�L�X�g�ǂݍ���
	//CMesh::TxtSet();

	//if (m_pField == NULL)
	//{ // �t�B�[���h�ւ̃|�C���^�� NULL �̏ꍇ

	//	// �t�B�[���h�̐ݒ菈��
	//	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
	//}

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �V�[���̏�����
	CScene::Init();

	// ���m�𐶐�����
	CSoldier::Create(NONE_D3DXVECTOR3, CSoldier::TYPE::TYPE_PLAYER, CSoldier::BATTLE_OFF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_OFF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_OFF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_OFF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_OFF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_DEF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_DEF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_DEF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_DEF);
	CSoldier::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), CSoldier::TYPE::TYPE_AI, CSoldier::BATTLE_DEF);

	// ���𐶐�����
	m_pFlag = CFlag::Create(D3DXVECTOR3(0.0f, 0.0f, 400.0f));

	// ��𐶐�����
	m_pCastle = CCastle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f),NONE_D3DXVECTOR3);

	// �U�����̕����n�_�𐶐�����
	m_pRespawn = COffRespawn::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f));

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CGame::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	m_pFlag = nullptr;			// ��

	// ��������������
	m_GameState = STATE_START;	// �Q�[���̐i�s���

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CGame::Update(void)
{
	switch (m_GameState)
	{
	case CGame::STATE_START:

		break;

	case CGame::STATE_PLAY:

		break;

	case CGame::STATE_GOAL:

		// �J�ڏ���
		Transition();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �����_���[�̍X�V
		CManager::Get()->GetRenderer()->Update();
	}

	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CGame::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CGame::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	// �X�^�[�g��Ԃɂ���
	m_GameState = STATE_START;

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
}

//======================================
// �J�ڏ���
//======================================
void CGame::Transition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % SUCCESS_TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// �Q�[���̐i�s��Ԃ̐ݒ菈��
//======================================
void CGame::SetState(const STATE state)
{
	// �Q�[���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �Q�[���̐i�s��Ԃ̎擾����
//======================================
CGame::STATE CGame::GetState(void)
{
	// �Q�[���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// ���̎擾����
//======================================
CFlag *CGame::GetFlag(void)
{
	// ����Ԃ�
	return m_pFlag;
}

//======================================
// �����ʒu�̎擾����
//======================================
COffRespawn *CGame::GetRespawn(void)
{
	// �����ʒu��Ԃ�
	return m_pRespawn;
}

//======================================
// ��̎擾����
//======================================
CCastle *CGame::GetCastle(void)
{
	// ���Ԃ�
	return m_pCastle;
}