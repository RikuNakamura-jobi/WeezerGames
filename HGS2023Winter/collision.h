//===================================
//
// �����蔻��w�b�_�[[collision.h]
// Author ��������
//
//===================================
#ifndef _COLLISION_H_			//���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �ۉe�̓����蔻��
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// �ۉe�̓����蔻��
	void ShadowElevCollision(D3DXVECTOR3& pos);										// �ۉe�ƋN���n�ʂ̓����蔻��

	// �N���n�ʂ̓����蔻��
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// �N���n�ʂ͈̔͊O�̓����蔻��

	// ���̓����蔻��
	bool Square
	( // ����
		D3DXVECTOR3 posSquare,		//���̈ʒu
		D3DXVECTOR3 *posTarget,		//�Փ˂������̈ʒu
		D3DXVECTOR3 posTargetOld,	//�Փ˂������̉ߋ��ʒu
		D3DXVECTOR3 rotSquare,		//���̊p�x
		D3DXVECTOR3 offsetMax,		//���̍ő�ʒu�I�t�Z�b�g
		D3DXVECTOR3 offsetMin		//���̍ŏ��ʒu�I�t�Z�b�g
	);
	bool SquareTrigger		//���̓����蔻��(���O����̂�)
	(// ����
		D3DXVECTOR3 posSquare,		//���̈ʒu
		D3DXVECTOR3 posTarget,		//�Փ˂������̈ʒu
		D3DXVECTOR3 rotSquare,		//���̊p�x
		D3DXVECTOR3 offsetMax,		//���̍ő�ʒu�I�t�Z�b�g
		D3DXVECTOR3 offsetMin		//���̍ŏ��ʒu�I�t�Z�b�g
	);
	D3DXVECTOR3 PosRelativeMtx	//3������Ԃł̍s��ɂ���]���W�ϊ��֐�
	(
		D3DXVECTOR3 posO,			//��]���S�_
		D3DXVECTOR3 rot,			//�p�x
		D3DXVECTOR3 offset			//�I�t�Z�b�g�ʒu
	);
}

#endif