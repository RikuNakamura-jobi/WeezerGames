//============================================
//
// ���U���g�̃��C������[result.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "texture.h"
#include "Objectmesh.h"

#include "file.h"
#include "camera.h"
#include "screen.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------

//=========================================
// �R���X�g���N�^
//=========================================
CResult::CResult() : CScene(TYPE_NONE, PRIORITY_BG)
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CResult::~CResult()
{

}

//=========================================
//����������
//=========================================
HRESULT CResult::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// 2D��ʂ𐶐�����
	CScreen::Create();

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CResult::Uninit(void)
{
	// �j������
	Release();
}

//======================================
//�X�V����
//======================================
void CResult::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// �^�C�g���ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CResult::Draw(void)
{

}