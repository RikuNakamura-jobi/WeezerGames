//============================================
//
// �`���[�g���A����ʂ̃��C������[tutorial.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "renderer.h"

#include "tutorial_screen.h"

// �}�N����`
#define TRANS_COUNT				(50)									// �J�ڂ܂ł̃J�E���g��

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̏����N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g
	m_bEnd = false;				// �I����
}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �`���[�g���A���𐶐�����
	CTutorialScreen::Create();

	// �S�Ă̒l���N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g
	m_bEnd = false;				// �I����

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ������������ꍇ

		// true �ɂ���
		m_bEnd = true;
	}

	if (m_bEnd == true)
	{ // �I���󋵂� true �̏ꍇ

		// �I���J�E���g�����Z����
		m_nEndCount++;

		if (m_nEndCount >= TRANS_COUNT)
		{ // �X�L�b�v���܂��́A�I�����̏ꍇ

			// �Q�[�����[�h�ɂ���
			CManager::Get()->GetFade()->SetFade(MODE_GAME);
		}

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �X�V����
			CManager::Get()->GetRenderer()->Update();
		}
	}
}

//======================================
//�`�揈��
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CTutorial::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	// �S�Ă̒l��ݒ肷��
	m_nEndCount = 0;			// �I���܂ł̃J�E���g
	m_bEnd = false;				// �I����
}