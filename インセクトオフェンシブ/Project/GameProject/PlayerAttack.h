#pragma once

#include "CharaBase.h"

class PlayerAttack :public CharaBase
{
public:
	PlayerAttack(const CVector3D& pos);
	~PlayerAttack();

	void HitCheckCatp();
	void HitCheckBee();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

};