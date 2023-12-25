//============================================
//
// ���m�v���C���[�̃��C������[soldier_player.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "soldier_player.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "useful.h"

#include "input.h"
#include "motion.h"

//=========================================
// �R���X�g���N�^
//=========================================
CSoldierPlayer::CSoldierPlayer() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CSoldierPlayer::~CSoldierPlayer()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CSoldierPlayer::Init(void)
{
	if (FAILED(CSoldier::Init()))
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
void CSoldierPlayer::Uninit(void)
{
	// �I������
	CSoldier::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CSoldierPlayer::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// ���쏈��
	Control();

	// �ړ���
	Move();

	// ���[�V�����̍X�V����
	GetMotion()->Update();

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CSoldierPlayer::Draw(void)
{
	// �`�揈��
	CSoldier::Draw();
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CSoldierPlayer::SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// ���̐ݒ菈��
	CSoldier::SetData(pos, type, battle);
}

//=======================================
// ���쏈��
//=======================================
void CSoldierPlayer::Control(void)
{
	// �ړ��R���g���[��
	MoveControl();

	// �W�����v�R���g���[��
	JumpControl();
}

//=======================================
// �ړ��R���g���[��
//=======================================
void CSoldierPlayer::MoveControl(void)
{
	// �ړI�̌������擾����
	D3DXVECTOR3 rotDest = GetRotDest();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) > 0)
	{ // W�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = -D3DX_PI * 0.25f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI * 0.25f;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			rotDest.y = 0.0f;
		}

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) < 0)
	{ // S�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = -D3DX_PI * 0.75f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI * 0.75f;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI;
		}

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
	{ // A�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		rotDest.y = -D3DX_PI * 0.5f;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
	{ // D�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI * 0.5f;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else
	{ // ��L�ȊO

		// �ړ��󋵂� false �ɂ���
		SetEnableMove(false);
	}

	// �ړI�̌�����ݒ肷��
	SetRotDest(rotDest);
}

//=======================================
// �W�����v�R���g���[��
//=======================================
void CSoldierPlayer::JumpControl(void)
{
	if ((CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true) &&
		IsJump() == false)
	{ // SPACE�L�[���������ꍇ

		// �W�����v����
		Jump();
	}
}