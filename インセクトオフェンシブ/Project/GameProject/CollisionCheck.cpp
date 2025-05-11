#include "CollisionCheck.h"

bool IsHitBox3D(float _cx, float _cy, float _cz, float _dx, float _dy, float _dz, SRect3D _srcRect, SRect3D _destRect) {
    float al = _cx + _srcRect.TopX; //����[(��_)�̍��W��
    float at = _cy + _srcRect.TopY; //��[
    float af = _cz + _srcRect.TopZ; // Z�̊J�n�ʒu
    float ar = al + _srcRect.Width; //�E���[
    float ab = at + _srcRect.Height;//���[
    float aback = af + _srcRect.Depth; // Z�̏I���ʒu

    float bl = _dx + _destRect.TopX;
    float bt = _dy + _destRect.TopY;
    float bf = _dz + _destRect.TopZ; // Z�̊J�n�ʒu
    float br = bl + _destRect.Width;
    float bb = bt + _destRect.Height;
    float bback = bf + _destRect.Depth; // Z�̏I���ʒu

    if (al < br && bl < ar &&   // X���͈̔͂��d�Ȃ��Ă���
        at < bb && bt < ab &&       // Y���͈̔͂��d�Ȃ��Ă���
        af < bback && bf < aback) {  // Z���͈̔͂��d�Ȃ��Ă���
        return true;
    }
    else {
        return false;
    }
}
