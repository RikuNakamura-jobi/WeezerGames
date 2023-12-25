//===========================================
//
// ���擾UI�w�b�_�[[acquire_UI.h]
// Author ��������
//
//===========================================
#ifndef _ACQUIRE_UI_H_
#define _ACQUIRE_UI_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CBillboard;		// �r���{�[�h

//-------------------------------------------
// �N���X��`(���擾UI)
//-------------------------------------------
class CAcquireUI : public CObject
{
public:		// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�|���S���̎��)
	enum TYPE
	{
		TYPE_GAGE = 0,		// �Q�[�W
		TYPE_METER,			// ���[�^�[
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CAcquireUI();					// �R���X�g���N�^
	~CAcquireUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetData(const D3DXVECTOR3 pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	CBillboard* GetPolygon(const TYPE type);			// �|���S���̏��̎擾����

	// �ÓI�����o�֐�
	static CAcquireUI* Create(const D3DXVECTOR3 pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�

	// �����o�ϐ�
	CBillboard* m_apUI[TYPE_MAX];		// �r���{�[�h�̏��
};

#endif