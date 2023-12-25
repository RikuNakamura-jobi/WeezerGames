//============================================
//
// ���m�̃��C������[soldier.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "soldier.h"
#include "game.h"
#include "castle.h"
#include "off_respawn.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "useful.h"

#include "motion.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "snowball.h"

#include "soldier_manager.h"
#include "soldier_player.h"
#include "soldier_ai.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
namespace
{
	const int MAX_LIFE = 5;					// �̗͂̍ő吔
	const int NUM_MODEL = 15;				// ���f���̑���
	const int THROWSTATE_COUNT = 40;		// �ᓊ����Ԃ̃J�E���g
	const int THROW_COUNT = 20;				// �ᓊ���J�E���g
	const float ADD_GRAVITY = -50.0f;		// ���n���̒ǉ��̏d��
	const float SPEED = 4.0f;				// �ړ���
	const float GRAVITY = 0.4f;				// �d��
	const float JUMP = 4.0f;				// �W�����v�̍���
	const float SNOWBALL_SPEED = 16.0f;		// ��ʂ̑��x
	const float SNOWBALL_HEIGHT = 20.0f;	// ��ʂ̍���
	const float ROT_CORRECT = 0.1f;			// �����̕␳�W��
	const float STAGE_RIGHTMAX = 800.0f;	// �X�e�[�W�̉E���̍ő�l
	const float STAGE_LEFTMAX = -800.0f;	// �X�e�[�W�̍����̍ő�l
	const float STAGE_FARMAX = 2000.0f;		// �X�e�[�W�̉����̍ő�l
	const float STAGE_NEARMAX = -2000.0f;	// �X�e�[�W�̎�O���̍ő�l
}

//=========================================
// �R���X�g���N�^
//=========================================
CSoldier::CSoldier() : CCharacter(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================================
CSoldier::CSoldier(CObject::TYPE type, PRIORITY priority) : CCharacter(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �f�X�g���N�^
//=========================================
CSoldier::~CSoldier()
{

}

//=========================================
// �R���X�g���N�^�̔�
//=========================================
void CSoldier::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V�����̏��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_type = TYPE_AI;				// ���
	m_battle = BATTLE_OFF;			// �U��
	m_state = STATE_NONE;			// ���
	m_nSnowCount = 0;				// �ᓊ���J�E���g
	m_fSpeed = SPEED;				// ���x
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��

	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^

	if (CSoldierManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CSoldierManager::Get()->Regist(this);
	}
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CSoldier::SetPrev(CSoldier* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CSoldier::SetNext(CSoldier* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CSoldier* CSoldier::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CSoldier* CSoldier::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}


//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CSoldier::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(NUM_MODEL);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		m_pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		m_pMotion->Load(CMotion::TYPE_PLAYER);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	// �ҋ@���[�V������ݒ�
	GetMotion()->Set(0);

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_type = TYPE_AI;				// ���
	m_battle = BATTLE_OFF;			// �U��
	m_state = STATE_NONE;			// ���
	m_nSnowCount = 0;				// �ᓊ���J�E���g
	m_fSpeed = SPEED;				// ���x
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CSoldier::Uninit(void)
{
	// ���[�V�����̃��������J������
	delete m_pMotion;
	m_pMotion = nullptr;

	// �I������
	CCharacter::Uninit();

	if (CSoldierManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CSoldierManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CSoldier::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//===========================================
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CSoldier::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//=======================================
// �����蔻�菈��
//=======================================
void CSoldier::Hit()
{
	D3DXVECTOR3 posRes;

	if (m_battle == BATTLE_OFF)
	{
		posRes = CGame::GetRespawn()->GetPos();
	}
	else
	{
		posRes = CGame::GetCastle()->GetPos();
	}

	posRes.x += (float)(rand() % 200 - 100);
	posRes.z += (float)(rand() % 200 - 100);

	SetPos(posRes);
}

//===========================================
// ��������
//===========================================
CSoldier* CSoldier::Create(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// ���m�̃|�C���^��錾
	CSoldier* pSoldier = nullptr;

	if (pSoldier == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case CSoldier::TYPE_AI:			// AI�̏ꍇ

			// ���������m�ۂ���
			pSoldier = new CSoldierAI;

			break;

		case CSoldier::TYPE_PLAYER:		// �v���C���[�̏ꍇ

			// ���������m�ۂ���
			pSoldier = new CSoldierPlayer;

			break;

		default:

			// ��~
			assert(false);

			break;
		}
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
		pSoldier->SetData(pos, type, battle);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pSoldier;
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CSoldier::SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_type = type;					// ���
	m_battle = battle;				// �U��
	m_state = STATE_NONE;			// ���
	m_nSnowCount = 0;				// �ᓊ���J�E���g
	m_fSpeed = SPEED;				// ���x
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��

	// �S�Ă̒l������������
	SetPos(D3DXVECTOR3(pos.x - 500.0f, pos.y + 400.0f, pos.z));		// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));				// ����
	SetScale(NONE_SCALE);			// �g�嗦

	m_rotDest = GetRot();	// �ړI�̌�����ݒ肷��

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(NONE_D3DXVECTOR3);							// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦

		if (nCntData == 2)
		{ // �������߂�Ƃ�

			switch (m_battle)
			{
			case CSoldier::BATTLE_OFF:

				GetHierarchy(nCntData)->SetFileData(CXFile::TYPE_PLAYER_HEAD);		// �f�[�^�̐ݒ菈��

				break;

			case CSoldier::BATTLE_DEF:

				GetHierarchy(nCntData)->SetFileData(CXFile::TYPE_PLAYER_DEFHEAD);	// �f�[�^�̐ݒ菈��

				break;

			default:

				// ��~
				assert(false);

				break;
			}
		}
		else if(nCntData >= 3)
		{ // ���ȍ~

			GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData + 1));	// �f�[�^�̐ݒ菈��
		}
		else
		{ // ��L�ȊO

			GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));		// �f�[�^�̐ݒ菈��
		}
	}
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CSoldier::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CSoldier::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �ڕW�̌����̐ݒ菈��
//=======================================
void CSoldier::SetRotDest(const D3DXVECTOR3& rot)
{
	// �ڕW�̌�����ݒ肷��
	m_rotDest = rot;
}

//=======================================
// �ڕW�̌����̎擾����
//=======================================
D3DXVECTOR3 CSoldier::GetRotDest(void) const
{
	// �ڕW�̌�����Ԃ�
	return m_rotDest;
}

//=======================================
// ��ނ̎擾����
//=======================================
CSoldier::TYPE CSoldier::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=======================================
// ��Ԃ̐ݒ菈��
//=======================================
void CSoldier::SetState(const STATE state)
{
	// ��Ԃ�ݒ肷��
	m_state = state;
}

//=======================================
// ��Ԃ̎擾����
//=======================================
CSoldier::STATE CSoldier::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//=======================================
// �̗͂̎擾����
//=======================================
int CSoldier::GetLife(void) const
{
	// �̗͂�Ԃ�
	return m_nLife;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CSoldier::SetSpeed(float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CSoldier::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
}

//=======================================
// �w�c�̎擾����
//=======================================
CSoldier::BATTLE CSoldier::GetBattle(void) const
{
	return m_battle;
}

//=======================================
// �ړ��󋵂̐ݒ菈��
//=======================================
void CSoldier::SetEnableMove(bool bMove)
{
	// �ړ��󋵂�ݒ肷��
	m_bMove = bMove;
}

//=======================================
// �ړ��󋵂̎擾����
//=======================================
bool CSoldier::IsMove(void) const
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
}

//=======================================
// �W�����v�󋵂̐ݒ菈��
//=======================================
void CSoldier::SetEnableJump(bool bJump)
{
	// �W�����v�󋵂�ݒ肷��
	m_bJump = bJump;
}

//=======================================
// �W�����v�󋵂̎擾����
//=======================================
bool CSoldier::IsJump(void) const
{
	// �W�����v�󋵂�Ԃ�
	return m_bJump;
}

//=======================================
// �ړ�����
//=======================================
void CSoldier::Move(void)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (m_bMove == true &&
		m_state == STATE_NONE)
	{ // �ړ��󋵂� true �̏ꍇ

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(m_rotDest.y) * m_fSpeed;
		m_move.z = cosf(m_rotDest.y) * m_fSpeed;
	}
	else
	{ // ��L�ȊO

		// �ړ��ʂ�����������
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}

	// �ʒu���ړ�����
	pos += m_move;

	// �d�͂𑫂�
	useful::Gravity(&m_move.y, pos, GRAVITY);

	// �����̐��K������
	useful::RotCorrect(m_rotDest.y, &rot.y, ROT_CORRECT);

	// �ʒu�ƌ�����ݒ肷��
	SetPos(pos);
	SetRot(rot);
}

//=======================================
// �W�����v����
//=======================================
void CSoldier::Jump(void)
{
	// �c�̈ړ��ʂ�ݒ肷��
	m_move.y = JUMP;

	// �W�����v�󋵂� true �ɂ���
	m_bJump = true;
}

//=======================================
// �����鏈��
//=======================================
void CSoldier::Throw(void)
{
	// �ړ��ʂ�錾
	D3DXVECTOR3 move = NONE_D3DXVECTOR3;

	// �ړ��ʂ�ݒ肷��
	move.x = sinf(GetRot().y) * SNOWBALL_SPEED;
	move.z = cosf(GetRot().y) * SNOWBALL_SPEED;

	// ��ʂ𐶐�����
	CSnowBall::Create(D3DXVECTOR3(GetPos().x, GetPos().y + SNOWBALL_HEIGHT, GetPos().z), move, m_battle);
}

//=======================================
// �N���n�ʂ̓����蔻�菈��
//=======================================
void CSoldier::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	float fHeight = 0.0f;			// ����
	bool bJump = true;				// �W�����v��
	bool bRange = false;			// �͈͓���

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos, bRange);
		
		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			// �d�͂�ݒ肷��
			m_move.y = ADD_GRAVITY;

			// �W�����v�󋵂� false �ɂ���
			bJump = false;

			if (GetMotion()->GetType() == MOTIONTYPE_JUMP)
			{ // �W�����v���[�V�����̏ꍇ

				// �ҋ@���[�V�����ɐݒ肷��
				GetMotion()->Set(MOTIONTYPE_NEUTRAL);
			}
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �W�����v�󋵂�ݒ肷��
	m_bJump = bJump;

	// �ʒu���X�V����
	SetPos(pos);
}

//=======================================
// ���@�ǂ̓����蔻�菈��
//=======================================
void CSoldier::MagicWall(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	if (pos.x >= STAGE_RIGHTMAX)
	{ // �E�̌��E�n�𒴂����ꍇ

		// �ʒu��ݒ肷��
		pos.x = STAGE_RIGHTMAX;
	}

	if (pos.x <= STAGE_LEFTMAX)
	{ // ���̌��E�n�𒴂����ꍇ

		// �ʒu��ݒ肷��
		pos.x = STAGE_LEFTMAX;
	}

	if (pos.z >= STAGE_FARMAX)
	{ // ���̌��E�n�𒴂����ꍇ

		// �ʒu��ݒ肷��
		pos.z = STAGE_FARMAX;
	}

	if (pos.z <= STAGE_NEARMAX)
	{ // ��O�̌��E�n�𒴂����ꍇ

		// �ʒu��ݒ肷��
		pos.z = STAGE_NEARMAX;
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// ��ԃ}�l�[�W���[
//=======================================
void CSoldier::StateManager(void)
{
	switch (m_state)
	{
	case CSoldier::STATE_NONE:



		break;

	case CSoldier::STATE_THROW:

		// �ᓊ���J�E���g�����Z����
		m_nSnowCount++;

		if (m_nSnowCount == THROW_COUNT)
		{ // ���J�E���g�̏ꍇ

			// ��������
			Throw();
		}

		if (m_nSnowCount >= THROWSTATE_COUNT)
		{ // �J�E���g�����ȏ�ɂȂ����ꍇ

			// �ᓊ���J�E���g�� 0 �ɂ���
			m_nSnowCount = 0;

			// �ʏ��Ԃɂ���
			m_state = STATE_NONE;

			// �ҋ@���[�V�����ɂ���
			GetMotion()->Set(MOTIONTYPE_NEUTRAL);
		}

		break;

	default:
		
		// ��~
		assert(false);

		break;
	}
}