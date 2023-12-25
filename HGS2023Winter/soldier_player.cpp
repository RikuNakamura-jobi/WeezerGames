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

namespace
{
	const float GRAVITY = 0.5f;				// �d��
	const float CAMERA_DISTANCE = -100.0f;	// �J�����̋���
	const float CAMERA_CYCLE = 0.04f;		// �J�����̉񂷑��x
}

//=========================================
// �R���X�g���N�^
//=========================================
CSoldierPlayer::CSoldierPlayer() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_CameraRot = NONE_D3DXVECTOR3;		// �J�����̌���
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

	// �S�Ă̒l������������
	m_CameraRot = NONE_D3DXVECTOR3;		// �J�����̌���

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

	// ���@�ǂ̓����蔻�菈��
	MagicWall();

	// ��ԃ}�l�[�W���[
	StateManager();
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

	// �S�Ă̒l��ݒ肷��
	m_CameraRot = NONE_D3DXVECTOR3;		// �J�����̌���
}

//=======================================
// ���쏈��
//=======================================
void CSoldierPlayer::Control(void)
{
	if (GetState() != STATE_THROW)
	{ // ������ԈȊO�̏ꍇ

		// �ړ��R���g���[��
		MoveControl();

		// �W�����v�R���g���[��
		JumpControl();

		// �����̃R���g���[��
		ThrowControl();
	}

	// �J�����̃R���g���[��
	CameraControl();
}

//=======================================
// �ړ��R���g���[��
//=======================================
void CSoldierPlayer::MoveControl(void)
{
	// �ړI�̌������擾����
	D3DXVECTOR3 rotDest = GetRotDest();
	bool bMove;		// �ړ���

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) > 0)
	{ // W�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = -D3DX_PI * 0.25f + m_CameraRot.y;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI * 0.25f + m_CameraRot.y;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			rotDest.y = 0.0f + m_CameraRot.y;
		}

		// �ړ��󋵂� true �ɂ���
		bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) < 0)
	{ // S�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = -D3DX_PI * 0.75f + m_CameraRot.y;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI * 0.75f + m_CameraRot.y;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			rotDest.y = D3DX_PI + m_CameraRot.y;
		}

		// �ړ��󋵂� true �ɂ���
		bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) < 0)
	{ // A�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		rotDest.y = -D3DX_PI * 0.5f + m_CameraRot.y;

		// �ړ��󋵂� true �ɂ���
		bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) > 0)
	{ // D�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI * 0.5f + m_CameraRot.y;

		// �ړ��󋵂� true �ɂ���
		bMove = true;
	}
	else
	{ // ��L�ȊO

		// �ړ��󋵂� false �ɂ���
		bMove = false;
	}

	if (bMove == true &&
		GetMotion()->GetType() == MOTIONTYPE_NEUTRAL)
	{ // �ړ����[�V��������Ȃ��ꍇ

		// �ړ����[�V������ݒ肷��
		GetMotion()->Set(MOTIONTYPE_MOVE);
	}
	else if(bMove == false &&
		GetMotion()->GetType() == MOTIONTYPE_MOVE)
	{ // �ҋ@���[�V��������Ȃ��ꍇ

		// �ړ����[�V������ݒ肷��
		GetMotion()->Set(MOTIONTYPE_NEUTRAL);
	}

	// �ړ��󋵂�ݒ肷��
	SetEnableMove(bMove);

	// �����̐��K��
	useful::RotNormalize(&rotDest.y);

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

		if (GetMotion()->GetType() != MOTIONTYPE_JUMP)
		{ // �W�����v���[�V��������Ȃ��ꍇ

			// �W�����v���[�V������ݒ肷��
			GetMotion()->Set(MOTIONTYPE_JUMP);
		}
	}
}

//=======================================
// �����̃R���g���[��
//=======================================
void CSoldierPlayer::ThrowControl(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// ������Ԃɂ���
		SetState(STATE_THROW);

		if (GetMotion()->GetType() != MOTIONTYPE_THROW)
		{ // �W�����v���[�V��������Ȃ��ꍇ

			// �W�����v���[�V������ݒ肷��
			GetMotion()->Set(MOTIONTYPE_THROW);
		}
	}
}

//=======================================
// �J�����̃R���g���[��
//=======================================
void CSoldierPlayer::CameraControl(void)
{
	// �����_�Ǝ��_���擾����
	D3DXVECTOR3 posR = CManager::Get()->GetCamera()->GetPosR();
	D3DXVECTOR3 posV = CManager::Get()->GetCamera()->GetPosV();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) < 0)
	{ // ���ɃX�e�B�b�N��|�����ꍇ

		// ���������Z����
		m_CameraRot.y -= CAMERA_CYCLE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0) > 0)
	{ // �E�ɃX�e�B�b�N��|�����ꍇ

		// ���������Z����
		m_CameraRot.y += CAMERA_CYCLE;
	}

	// ���_��ݒ肷��
	posV.x = posR.x + sinf(m_CameraRot.y) * CAMERA_DISTANCE;
	posV.z = posR.z + cosf(m_CameraRot.y) * CAMERA_DISTANCE;

	// ���_��ݒ肷��
	CManager::Get()->GetCamera()->SetPosV(posV);
}