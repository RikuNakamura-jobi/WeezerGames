//============================================
//
// �v���C���[�̃��C������[player.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "soldier.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "useful.h"

#include "motion.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "input.h"

#include "soldier_manager.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
namespace
{
	const int MAX_LIFE = 5;				// �̗͂̍ő吔
	const int NUM_MODEL = 15;			// ���f���̑���
	const float ADD_GRAVITY = -50.0f;	// ���n���̒ǉ��̏d��
	const float SPEED = 10.0f;			// �ړ���
	const float GRAVITY = 0.5f;			// �d��
}

//=========================================
// �R���X�g���N�^
//=========================================
CSoldier::CSoldier() : CCharacter(CObject::TYPE_SOLDIER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V�����̏��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nLife = MAX_LIFE;				// �̗�
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

//=========================================
// �f�X�g���N�^
//=========================================
CSoldier::~CSoldier()
{

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
	m_nLife = MAX_LIFE;				// �̗�
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
// �X�V����
//===========================================
void CSoldier::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// ���쏈��
	Control();

	// �ړ���
	Move();

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();

	// �v���C���[�̏���\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�ړ��ʁF%f %f %f\n�̗́F%d\n�W�����v�󋵁F%d\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z, m_nLife, m_bJump);
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

//===========================================
// ��������
//===========================================
CSoldier* CSoldier::Create(const D3DXVECTOR3& pos)
{
	// ���m�̃|�C���^��錾
	CSoldier* pSoldier = nullptr;

	if (pSoldier == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pSoldier = new CSoldier;
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
		pSoldier->SetData(pos);
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
void CSoldier::SetData(const D3DXVECTOR3& pos)
{
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
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// �f�[�^�̐ݒ菈��
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
// �̗͂̐ݒ菈��
//=======================================
void CSoldier::SetLife(const int nLife)
{
	if (nLife > MAX_LIFE)
	{ // �̗͂����ȏ�̏ꍇ

		// �̗͂��ő�ɐݒ肷��
		m_nLife = MAX_LIFE;
	}
	else
	{ // ��L�ȊO

		// �̗͂�ݒ肷��
		m_nLife = nLife;
	}
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
// ���쏈��
//=======================================
void CSoldier::Control(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = -D3DX_PI * 0.25f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = D3DX_PI * 0.25f;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = 0.0f;
		}

		// �ړ��󋵂�ݒ肷��
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[�������Ă���ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // A�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = -D3DX_PI * 0.75f;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // D�L�[�������Ă���ꍇ

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = D3DX_PI * 0.75f;
		}
		else
		{ // ��L�ȊO

			// �ړI�̌�����ݒ肷��
			m_rotDest.y = D3DX_PI;
		}

		// �ړ��󋵂�ݒ肷��
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		m_rotDest.y = -D3DX_PI * 0.5f;

		// �ړ��󋵂�ݒ肷��
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[�������Ă���ꍇ

		// �ړI�̌�����ݒ肷��
		m_rotDest.y = D3DX_PI * 0.5f;

		// �ړ��󋵂�ݒ肷��
		m_bMove = true;
	}
	else
	{ // ��L�ȊO

		// �ړ��󋵂� false �ɂ���
		m_bMove = false;
	}
}

//=======================================
// �ړ�����
//=======================================
void CSoldier::Move(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	if (m_bMove == true)
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

	// �ړ��ʂ�ݒ肷��
	SetPos(pos);
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
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}