#include<dxlib.h>
#include<math.h>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B


// �N�����v...�܂�A�l�����͈͓̔��Ɏ��߂�
float Clamp(float val, float minval = 0.0f, float maxval = 1.0f) {
	return max(min(maxval, val), minval);
}

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
		// �@�܂��ˉe�������(���a^2-������^2������)
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

// ���˃x�N�g����Ԃ�
// param inVec ���˃x�N�g��
// param nvec �@���x�N�g��(���K���ς�)
// retval ���˃x�N�g��
Vector3
RefrectVector(const Vector3& inVec, const Vector3& nVec) {
	// R = I-2N(I�EN)��Ԃ�
	return inVec -nVec * 2 * Dot(inVec, nVec);
}

///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)
void RayTracing(const Position3& eye,const Sphere& sphere) {
	Vector3 lightVec(1, -1, -1);
	lightVec.Normalize();
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			//�@���_�ƃX�N���[�����W���王���x�N�g�������
			Vector3 P(x - screen_width /2,screen_height /2 - y,0);
			Vector3 ray(P - eye);
			float distance = 0.0f;
			//�A���K�����Ƃ�
			ray.Normalize();
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			if (IsHitRayAndObject(eye,ray,sphere,distance))
			{
				int b = 255;
				// �܂�diatance��ray�Ƌ��̂ւ̃x�N�g����
				// ���Ƃɖ@���x�N�g�������
				auto N = ray * distance - (sphere.pos - eye);
				N.Normalize();
				// �����Ă��̖@���x�N�g���Ɓu�t�v���C�g�x�N�g���Ƃ�
				// ���ς���肻��𖾂邳�Ƃ���B������cos��
				// �g�U���ˌ�(�f�B�t���[�Y)
				auto light = Dot(N, -lightVec);
				// ���ʔ��ˌ�(�X�y�L����)
				auto refLightVec = RefrectVector(lightVec,N);
				// ��������cos�̃}�C�i�X�����Ȃ��Ȃ�̂Ŋ����Z����
				auto sp = pow(Clamp(Dot(-ray, refLightVec)), 10);
				// �Ȃ̂Ŕ͈͂�-1�`1�܂łɂȂ邽�߁Ab��������DxLib��
				// �l�̃��[���ɍ��킹�悤�B
				// ����(�A���r�G���g)
				auto ambient = 0.15f;
				b *= Clamp(max(light + sp , ambient));
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
	/*DrawBox(0, 0, 640, 480, GetColor(0,0,128),true);*/
	auto sp = Sphere(100, Position3(0, 0, -100));
	RayTracing(Vector3(0, 0, 300), sp);

	WaitKey();
	DxLib_End();
}