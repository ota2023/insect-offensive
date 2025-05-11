#pragma once


//��`�p�\����
struct SRect3D {
    int TopX;   // �����X���W
    int TopY;   // �����Y���W
    int TopZ;   // �O�ʂ�Z���W�i���s�����l���j
    int Width;  // ��`�̕��iX�����j
    int Height; // ��`�̍����iY�����j
    int Depth;  // ��`�̉��s���iZ�����j
};

//��`�̈�̓����蔻��
bool IsHitBox3D(float _cx, float _cy, float _cz,
    float _dx, float _dy, float _dz,
    SRect3D _srcRect, SRect3D _destRect);