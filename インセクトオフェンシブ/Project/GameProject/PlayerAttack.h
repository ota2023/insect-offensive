#pragma once

#include "CharaBase.h"

class PlayerAttack :public CharaBase
{
public:
	PlayerAttack(const CVector3D& pos);
	~PlayerAttack();

	void HitCheckCatp();
	void HitCheckBee();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

};