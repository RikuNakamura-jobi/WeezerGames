//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "useful.h"

//===============================
// �}�N����`
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)

//===============================
// �ۉe�̓����蔻�菈��
//===============================
void collision::ShadowCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// �e�̃|�C���^
	D3DXVECTOR3 posPlayer = pos;				// �v���C���[�̈ʒu
	D3DXVECTOR3 posCand = NONE_D3DXVECTOR3;		// �e�̈ʒu�̌��

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL ����Ȃ������ꍇ

		// �e�̈ʒu���擾����
		posCand = D3DXVECTOR3(posPlayer.x, pShadow->GetPos().y, posPlayer.z);

		// �ۉe�̋N���n�ʂ̓����蔻��
		ShadowElevCollision(posCand);

		// �ʒu��ݒ肷��
		pShadow->SetPos(posCand);
	}
}

//===============================
// �ۉe�ƋN���n�ʂ̓����蔻��
//===============================
void collision::ShadowElevCollision(D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// ���b�V���̃|�C���^���擾����

	while (pMesh != nullptr)
	{ // �I�u�W�F�N�g�̂� NULL ����Ȃ������

		// �e�̈ʒu��ݒ肷��
		pos.y = pMesh->ElevationCollision(pos);

		// ���̃I�u�W�F�N�g��������
		pMesh = pMesh->GetNext();
	}
}

//===============================
// �N���n�ʂ͈̔͊O�̓����蔻��
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �擪�̋N���n�ʂ��擾����
	bool bCollision = false;									// �����蔻���

	while (pElev != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
			pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
			pElev->GetPos().y > pPos->y)
		{ // �N���n�ʂ�艺�ɂ���ꍇ

			if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
				pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
			{ // ���̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
			else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
				pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
			{ // �E�̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pElev = pElev->GetNext();
	}

	// �����蔻��󋵂�Ԃ�
	return bCollision;
}

//============================================================
// ���̓����蔻��
//============================================================
bool collision::Square
( // ����
	D3DXVECTOR3 posSquare,			//���̈ʒu
	D3DXVECTOR3 *posTarget,			//�Փ˂������̈ʒu
	D3DXVECTOR3 posTargetOld,		//�Փ˂������̉ߋ��ʒu
	D3DXVECTOR3 rotSquare,			//���̊p�x
	D3DXVECTOR3 offsetMax,			//���̍ő�ʒu�I�t�Z�b�g
	D3DXVECTOR3 offsetMin			//���̍ŏ��ʒu�I�t�Z�b�g
)
{
	D3DXVECTOR3 posCorner[8] = {};									//���̊p
	D3DXVECTOR3 posPlaneCenter[6] = {};								//���̊e�ʂ̒��S
	D3DXVECTOR3 vecIntersect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���Ƃ̏Փ˓_
	D3DXVECTOR3 vecNorPlaneCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���ʂ̖@���x�N�g��
	D3DXPLANE plane = D3DXPLANE(0.0f, 0.0f, 0.0f, 0.0f);			//�e�ʂ̕���
	float lengthX, lengthY, lengthZ;								//�e�������̑傫��

																	//�e�������ő傫����}��
	lengthX = fabsf(offsetMax.x - offsetMin.x) * 0.5f;
	lengthY = fabsf(offsetMax.y - offsetMin.y) * 0.5f;
	lengthZ = fabsf(offsetMax.z - offsetMin.z) * 0.5f;

	//���̊e�ʂ̒��S�����߂�
	posPlaneCenter[0] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(lengthX, 0.0f, 0.0f));
	posPlaneCenter[1] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(-lengthX, 0.0f, 0.0f));
	posPlaneCenter[2] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, lengthY, 0.0f));
	posPlaneCenter[3] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, -lengthY, 0.0f));
	posPlaneCenter[4] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, 0.0f, lengthZ));
	posPlaneCenter[5] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, 0.0f, -lengthZ));

	//pos�����̒��ɓ����Ă���
	if (SquareTrigger(posSquare, *posTarget, rotSquare, offsetMax, offsetMin) == true)
	{
		//6�ʑS�ĂŊm���߂�
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			//�e�ʂ̖@���x�N�g�����v�Z����
			vecNorPlaneCenter = posSquare - posPlaneCenter[nCnt];
			D3DXVec3Normalize(&vecNorPlaneCenter, &vecNorPlaneCenter);

			//�@���x�N�g�����畽�ʂ̎����v�Z����
			D3DXPlaneFromPointNormal(&plane, &posPlaneCenter[nCnt], &vecNorPlaneCenter);

			//���ʂ̎��Ɠ_����
			if (D3DXPlaneDotCoord(&plane, posTarget) > 0.0f && D3DXPlaneDotCoord(&plane, &posTargetOld) <= 0.0f)
			{
				//���ʂƈʒu�ߋ��ʒu����Փ˓_���Z�o
				D3DXPlaneIntersectLine(&vecIntersect, &plane, posTarget, &posTargetOld);

				//�Փ˓_���C��
				if (posPlaneCenter[nCnt].x == 0.0f)
				{
					vecIntersect.x = 0.0f;
				}

				if (posPlaneCenter[nCnt].y == 0.0f)
				{
					vecIntersect.y = 0.0f;
				}

				if (posPlaneCenter[nCnt].z == 0.0f)
				{
					vecIntersect.z = 0.0f;
				}

				//�ʒu�C��
				*posTarget = vecIntersect - (vecNorPlaneCenter * 7.0f);

				return true;
			}
		}
	}

	return false;
}

//============================================================
//���̓����蔻��(���O����̂�)
//============================================================
bool collision::SquareTrigger
(// ����
	D3DXVECTOR3 posSquare,		//���̈ʒu
	D3DXVECTOR3 posTarget,		//�Փ˂������̈ʒu
	D3DXVECTOR3 rotSquare,		//���̊p�x
	D3DXVECTOR3 offsetMax,		//���̍ő�ʒu�I�t�Z�b�g
	D3DXVECTOR3 offsetMin		//���̍ŏ��ʒu�I�t�Z�b�g
)
{
	bool bSquare;							//����pbool
	bSquare = false;

	D3DXVECTOR3 posCorner[8];			//���̊p
	D3DXVECTOR3 posPlaneCenter[6];		//���̊e�ʂ̒��S
	D3DXVECTOR3 vecNorPlaneCenter[6];	//���ʂ̖@���x�N�g��
	D3DXPLANE plane[6];					//�e�ʂ̕���
	int nCheckCollision = 0;			//�ʂœ����������ǂ����m�F�p�ϐ�

										//���̊e�ʂ̒��S�����߂�
	posPlaneCenter[0] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(offsetMax.x, 0.0f, 0.0f));
	posPlaneCenter[1] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(offsetMin.x, 0.0f, 0.0f));
	posPlaneCenter[2] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, offsetMax.y, 0.0f));
	posPlaneCenter[3] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, offsetMin.y, 0.0f));
	posPlaneCenter[4] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, 0.0f, offsetMax.z));
	posPlaneCenter[5] = PosRelativeMtx(posSquare, rotSquare, D3DXVECTOR3(0.0f, 0.0f, offsetMin.z));

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		//�e�ʂ̖@���x�N�g�����v�Z����
		vecNorPlaneCenter[nCnt] = posSquare - posPlaneCenter[nCnt];
		D3DXVec3Normalize(&vecNorPlaneCenter[nCnt], &vecNorPlaneCenter[nCnt]);

		//�@���x�N�g�����畽�ʂ̎����v�Z����
		D3DXPlaneFromPointNormal(&plane[nCnt], &posPlaneCenter[nCnt], &vecNorPlaneCenter[nCnt]);

		//���ʂ̎��Ɠ_����
		if (D3DXPlaneDotCoord(&plane[nCnt], &posTarget) > 0.0f)
		{
			nCheckCollision++;
		}
	}

	//�S�Ă̖ʂœ�����������
	if (nCheckCollision == 6)
	{
		bSquare = true;
	}

	return bSquare;
}

//========================================
//3������Ԃł̍s��ɂ���]���W�ϊ��֐�
//(�C�ӂ̓_����̃I�t�Z�b�g�ʒu���p�x�Ƌ����ŕϊ�)
//========================================
D3DXVECTOR3 collision::PosRelativeMtx
(
	D3DXVECTOR3 posO,		//��]���S�_
	D3DXVECTOR3 rot,		//�p�x
	D3DXVECTOR3 offset		//�I�t�Z�b�g�ʒu
)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();			// �f�o�C�X�̃|�C���^
	D3DXVECTOR3 posAnswer;																//�ԓ��p�ϐ�
	D3DXMATRIX mtxO, mtxAnswer;															//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRotModel, mtxTransModel, mtxPalent;									//�v�Z�p�}�g���b�N�X

																						//�p�[�c�̃��[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxO);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		posO.x, posO.y, posO.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxTransModel);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxO);

	mtxPalent = mtxO;

	//�p�[�c�̃��[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxAnswer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		3.14f, 3.14f, 3.14f);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		offset.x, offset.y, offset.z);
	D3DXMatrixMultiply(&mtxAnswer, &mtxAnswer, &mtxTransModel);

	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&mtxAnswer,
		&mtxAnswer,
		&mtxPalent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxAnswer);

	//�ϐ��p�ϐ��ɑ��
	posAnswer.x = mtxAnswer._41;
	posAnswer.y = mtxAnswer._42;
	posAnswer.z = mtxAnswer._43;

	return posAnswer;
}