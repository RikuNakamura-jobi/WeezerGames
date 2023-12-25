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

#include "motion.h"
#include "elevation_manager.h"
#include "objectElevation.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
namespace
{
	const int MAX_LIFE = 5;				// �̗͂̍ő吔
	const int NUM_MODEL = 15;			// ���f���̑���
	const float ADD_GRAVITY = -50.0f;	// ���n���̒ǉ��̏d��
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
	m_fSpeed = 0.0f;				// ���x
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��
}

//=========================================
// �f�X�g���N�^
//=========================================
CSoldier::~CSoldier()
{

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

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nLife = MAX_LIFE;				// �̗�
	m_fSpeed = 0.0f;				// ���x
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
}

//===========================================
// �X�V����
//===========================================
void CSoldier::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

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
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(nCntData));	// �f�[�^�̐ݒ菈��
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