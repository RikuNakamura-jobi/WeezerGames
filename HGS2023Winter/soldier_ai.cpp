//============================================
//
// ���mAI�̃��C������[soldier_AI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "soldier_ai.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "useful.h"

#include "input.h"
#include "motion.h"

#include "soldier_manager.h"

//=========================================
// �R���X�g���N�^
//=========================================
CSoldierAI::CSoldierAI() : CSoldier(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	m_BattleAI = BATTLEAI_ATTACK;
	m_Situation = SITUATION_ASSAULT;
	m_nCountJudge = 0;
	m_nNumNearPlayer = 0;
	m_nNumNearEnemy = 0;
}

//=========================================
// �f�X�g���N�^
//=========================================
CSoldierAI::~CSoldierAI()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CSoldierAI::Init(void)
{
	if (FAILED(CSoldier::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	m_nCountJudge = 0;

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CSoldierAI::Uninit(void)
{
	// �I������
	CSoldier::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CSoldierAI::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// AI
	AI();

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
void CSoldierAI::Draw(void)
{
	// �`�揈��
	CSoldier::Draw();
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CSoldierAI::SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle)
{
	// ���̐ݒ菈��
	CSoldier::SetData(pos, type, battle);

	int nRand = rand() % 2;

	if (nRand)
	{
		m_BattleAI = BATTLEAI_ATTACK;
	}
	else
	{
		m_BattleAI = BATTLEAI_GUARD;
	}
}

//=======================================
// AI�̏���
//=======================================
void CSoldierAI::AI(void)
{
	m_nCountJudge++;

	CSoldierManager *soldierManager = CSoldierManager::Get();

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
					if (pObjCheck->GetBattle() == GetBattle())
					{
						m_nNumNearPlayer++;
					}
					else
					{
						m_nNumNearEnemy++;
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	if (GetBattle() == BATTLE_OFF)
	{
		AIOffense();
	}
	else
	{
		AIDefense();
	}
}

//=======================================
// �ړ�AI�̏���
//=======================================
void CSoldierAI::AIMove(void)
{
	// �ړI�̌������擾����
	D3DXVECTOR3 rotDest = GetRotDest();

	if (m_Situation == SITUATION_ASSAULT)
	{
		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_SHOOT)
	{
		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_GUARD)
	{
		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else if (m_Situation == SITUATION_ESCAPE)
	{
		// �ړI�̌�����ݒ肷��
		rotDest.y = D3DX_PI;

		// �ړ��󋵂�ݒ肷��
		SetEnableMove(true);
	}
	else
	{
		// �ړ��󋵂�ݒ肷��
		SetEnableMove(false);
	}

	// �ړI�̌�����ݒ肷��
	SetRotDest(rotDest);
}

//=======================================
// �U��AI�̏���
//=======================================
void CSoldierAI::AIOffense(void)
{
	if (m_BattleAI == BATTLEAI_ATTACK)
	{
		AIOffenseAttack();
	}
	else
	{
		AIOffenseGuard();
	}
}
void CSoldierAI::AIOffenseAttack(void)
{//�U���I

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 1)
		{
			if (nRand > 1)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 0)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_ASSAULT;
		}
	}
}
void CSoldierAI::AIOffenseGuard(void)
{//����I

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 2)
		{
			if (m_nNumNearPlayer == 0)
			{
				if (nRand > 0)
				{
					m_Situation = SITUATION_ESCAPE;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
			else
			{
				if (nRand > 2)
				{
					m_Situation = SITUATION_ASSAULT;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 2)
			{
				m_Situation = SITUATION_ASSAULT;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_ASSAULT;
		}
	}
}

//=======================================
// ���AI�̏���
//=======================================
void CSoldierAI::AIDefense(void)
{
	if (m_BattleAI == BATTLEAI_ATTACK)
	{
		AIDefenseAttack();
	}
	else
	{
		AIDefenseGuard();
	}
}
void CSoldierAI::AIDefenseAttack(void)
{// �U���I

	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 1)
		{
			if (nRand > 1)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 0)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_GUARD;
		}
	}
}
void CSoldierAI::AIDefenseGuard(void)
{// ����I
	
	int nRand = 0;

	if (m_nCountJudge % 60 == 0)
	{
		m_nCountJudge = 0;

		nRand = rand() % 4;

		if (m_nNumNearEnemy > 2)
		{
			if (m_nNumNearPlayer == 0)
			{
				m_Situation = SITUATION_SHOOT;
			}
			else
			{
				if (nRand > 2)
				{
					m_Situation = SITUATION_ESCAPE;
				}
				else
				{
					m_Situation = SITUATION_SHOOT;
				}
			}
		}
		else if (m_nNumNearEnemy > 0)
		{
			if (nRand > 2)
			{
				m_Situation = SITUATION_GUARD;
			}
			else
			{
				m_Situation = SITUATION_SHOOT;
			}
		}
		else
		{
			m_Situation = SITUATION_GUARD;
		}
	}
}