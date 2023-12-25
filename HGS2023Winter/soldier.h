//============================================
//
// ���m�w�b�_�[[soldier.h]
// Author�F��������
//
//============================================
#ifndef _SOLDIER_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SOLDIER_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����

//--------------------------------------------
// �N���X(���m�N���X)
//--------------------------------------------
class CSoldier : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_AI = 0,		// AI(CPU)
		TYPE_PLAYER,		// �v���C���[
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���[�V�����̎��)
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@���[�V����
		MOTIONTYPE_MOVE,			// �ړ����[�V����
		MOTIONTYPE_THROW,			// �������[�V����
		MOTIONTYPE_JUMP,			// �W�����v���[�V����
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�o�g��)
	enum BATTLE
	{
		BATTLE_OFF = 0,		// �U����
		BATTLE_DEF,			// �h�䑤
		BATTLE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_THROW,		// �������
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CSoldier();				// �R���X�g���N�^
	CSoldier(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CSoldier();	// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// ���X�g�\���֌W
	void SetPrev(CSoldier* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CSoldier* pNext);	// ��̃|�C���^�̐ݒ菈��
	CSoldier* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CSoldier* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle);	// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����

	void SetRotDest(const D3DXVECTOR3& rot);	// �ڕW�̌����̐ݒ菈��
	D3DXVECTOR3 GetRotDest(void) const;			// �ڕW�̌����̎擾����

	TYPE GetType(void) const;					// ��ނ̎擾����

	void SetState(const STATE state);			// ��Ԃ̐ݒ菈��
	STATE GetState(void) const;					// ��Ԃ̎擾����

	void SetSpeed(float fSpeed);				// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����

	BATTLE GetBattle(void) const;				// �w�c�̎擾����

	void SetEnableMove(bool bMove);				// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����

	void SetEnableJump(bool bJump);				// �W�����v�󋵂̐ݒ菈��
	bool IsJump(void) const;					// �W�����v�󋵂̎擾����

	CMotion* GetMotion(void) const;				// ���[�V�����̏��̎擾����

	void Hit();

	// �ÓI�����o�֐�
	static CSoldier* Create(const D3DXVECTOR3& pos, const TYPE type, const BATTLE battle);	// ��������

protected:		// �����Ɣh���N���X�����A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);				// �ړ�����
	void Jump(void);				// �W�����v����
	void Throw(void);				// �����鏈��
	void ElevationCollision(void);	// �N���n�ʂ̓����蔻�菈��
	void MagicWall(void);			// ���@�ǂ̓����蔻�菈��
	void StateManager(void);		// ��ԃ}�l�[�W���[

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CMotion* m_pMotion;				// ���[�V�����̏��

	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	TYPE m_type;					// ���
	BATTLE m_battle;				// �U��
	STATE m_state;					// ���
	int m_nSnowCount;				// �ᓊ���J�E���g
	float m_fSpeed;					// ���x
	bool m_bMove;					// �ړ���
	bool m_bJump;					// �W�����v��

	// ���X�g�\���֌W
	CSoldier* m_pPrev;	// �O�ւ̃|�C���^
	CSoldier* m_pNext;	// ���ւ̃|�C���^
};

#endif