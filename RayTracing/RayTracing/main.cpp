#include<dxlib.h>
#include<math.h>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B

///���C(����)�Ƌ��̂̓����蔻��
///@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
///@param sphere ��
///@param distance ��_�܂ł̋���
///@hint ���C�͐��K�����Ƃ����ق����g���₷�����낤
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp, float& distance) {
	//���C�����K���ς݂ł���O��Łc
	//
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
	auto vec = sp.pos - eye; // �x�N�g��(����)
	float pLen = (Dot(vec, ray)); // �ˉe��
	Vector3 Pos = ray * pLen; // �����x�N�g���ƃx�N�g����������
	auto Perpendicular = vec - Pos; // ���S����̐����������_
	auto vLen = Perpendicular.Magnitude(); // ������

	if (vLen <= sp.radius)
	{
		// �����ɗ������_�œ������Ă���
		// �Ȃ̂�
		// �@�܂��ˉe�������(���a^2-������������)
		auto newdistance = pLen - sqrt(pow(sp.radius,2.0) - pow(vLen, 2.0));
		// �����distance�ɑ��
		distance = newdistance;
		return true;
	}
	else
	{
		return false;
	}
}

///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)
void RayTracing(const Position3& eye,const Sphere& sphere) {
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			//�@���_�ƃX�N���[�����W���王���x�N�g�������
			Vector3 P(x - screen_width /2,y - screen_height /2,0);
			Vector3 ray(P - eye);
			float distance = 0;
			//�A���K�����Ƃ�
			ray.Normalize();
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			if (IsHitRayAndObject(eye,ray, sphere,distance))
			{
				int b = 255;
				float rate = (400.f - (float)distance) / 100.0f;
				b *= rate;
				DrawPixel(x, y, GetColor(b, b, b));
			}
		}
	}
}

int main() {
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1816223_��X�g���S"));
	DxLib_Init();
	// ��ذ݂�Z=0�̈ʒu�ɂ���Ƃ��܂�
	// �����������_���W(0, 0, 300)
	// ���������̂̏��(���a100�̒��S(0, 0, -100))
	RayTracing(Vector3(0, 0, 300), Sphere(100, Position3(0, 0, -100)));

	WaitKey();
	DxLib_End();
}