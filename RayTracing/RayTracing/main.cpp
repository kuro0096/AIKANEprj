#include<dxlib.h>
#include<math.h>
#include"Geometry.h"

const int screen_width = 640;
const int screen_height = 480;

// ���C(����)�Ƌ��̂̓����蔻��(���_����X�N���[���s�N�Z���ւ̃x�N�g��,��,��_�܂ł̋���)
// ray�͐��K��
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp, float& distance) {
	//���C�����K���ς݂ł���O��Łc
	//
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂�
	auto vec = sp.pos - eye; // �x�N�g��(����)
	float pLen = (Dot(vec, ray)); // �ˉe��
	Vector3 Pos = ray * pLen; // �����x�N�g���ƃx�N�g����������
	auto Perpendicular = vec - Pos; // ���S����̐����������_
	auto vLen = Perpendicular.Magnitude(); // ������

	if (vLen <= sp.radius)
	{
		// �����ɗ������_�œ������Ă���
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

// ���˃x�N�g����Ԃ�(���˃x�N�g��,�@���x�N�g��(���K���ς�))
Vector3
RefrectVector(const Vector3& inVec, const Vector3& nVec) {
	// R = I-2N(I�EN)��Ԃ�
	return inVec -nVec * 2 * Dot(inVec, nVec);
}

// ���𐶐�(�s���͗l)
Color GetCheckerColorFromPos(Vector3 &clossVec)
{
	if ((clossVec.x < 0 && ((int)clossVec.x / 20 + (int)clossVec.z / 20) % 2 == 0)
		|| (clossVec.x >= 0 && abs((int)clossVec.x / 20 + (int)clossVec.z / 20) % 2 == 1))
	{
		return Color(128,128,128);
	}
	else
	{
		return Color(255, 255, 255);
	}
}

// ���C�g���[�V���O(���_���W,���I�u�W�F�N�g(���̂��������ɂ���))
void RayTracing(const Position3& eye,const Sphere& sphere) {
	Vector3 lightVec(1, -1, -1);
	lightVec.Normalize();
	Plane plane = Plane(Vector3(0, 1, 0), -30);

	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			//�@���_�ƃX�N���[�����W���王���x�N�g�������
			Vector3 P(x - screen_width /2,screen_height /2 - y,0);
			Vector3 ray(P - eye);
			float distance = 0.0f;
			//�A���K������
			ray.Normalize();
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			if (IsHitRayAndObject(eye,ray,sphere,distance))
			{
				int b = 255;
				// �܂�diatance��ray�Ƌ��̂ւ̃x�N�g����
				// ���Ƃɖ@���x�N�g�������
				// ��U���̋��̂͊��S���˂Ƃ��čl����
				// �@���˃x�N�g�������߂�(�@���Ɠ��˃x�N�g��(����)����)
				// �A���˃x�N�g���ƌ�_���玟�̃��C���΂�
				// �B���̃��C�����Ƃ̌�_�����Ȃ�΂��̍��W�����߂�
				// �C�B�œ�����_�̍��W����F�������Ă��̐F�����݂̐F�Ƃ���DrawPixel����
				Vector3 hitPos = eye + ray * distance;	// ��_
				auto N = hitPos - sphere.pos;
				N.Normalize();
				auto refVec = RefrectVector(N, ray);

				auto hitRay = Dot(-refVec, plane.normal);

				auto ooo = Dot(plane.normal, hitPos) - plane.offset;
				auto t = (ooo) / hitRay;

				auto c = hitPos + refVec * t;


				//auto mag = plane.offset - hitPos.y / refVec.y;

				//auto clossPos = refVec * mag + hitPos;

//--------------------------------------------------------------------------
				// �����Ă��̖@���x�N�g���Ɓu�t�v���C�g�x�N�g���Ƃ�
				// ���ς���肻��𖾂邳�Ƃ���B������cos��
				// �g�U���ˌ�(�f�B�t���[�Y)
				auto diff = Dot(N, -lightVec);
				// ���ʔ��ˌ�(�X�y�L����)
				auto refLightVec = RefrectVector(lightVec,N);
				// ��������cos�̃}�C�i�X�����Ȃ��Ȃ�̂Ŋ����Z����
				auto sp = pow(Clamp(Dot(-ray, refLightVec)), 10);
				// �Ȃ̂Ŕ͈͂�-1�`1�܂łɂȂ邽�߁Ab��������DxLib��
				// �l�̃��[���ɍ��킹�悤�B
				// ����(�A���r�G���g)
				auto ambient = 0.15f;

				// �F�̏����l��ݒ�
				Color difCol(255, 0, 0);
				Color specCol(255, 255, 255);
				Color ambCol(32, 32, 32);

				difCol *= Clamp(diff);
				specCol *= Clamp(sp);

				Color col = difCol + specCol;
				col.r = max(col.r, ambCol.r);
				col.g = max(col.g, ambCol.g);
				col.b = max(col.b, ambCol.b);

				b *= Clamp(max(diff + sp , ambient));
				if (hitRay > 0)
				{
					auto color1 = GetCheckerColorFromPos(c);
					DrawPixel(x, y, color1.GetColor());
				}
				else
				{
					DrawPixel(x, y,GetColor(col.r, col.g,col.b) );
				}
			}
			else {
				// ���ʂ��王�_�܂ł̋���
				auto pVec = Dot(eye, plane.normal) - plane.offset;
				// 1�񂠂���̈ړ�����
				auto dVec = Dot(-ray,plane.normal);
				// ���W�����߂邽�߂Ɏg��
				auto t = pVec / dVec;
				// t�����Ƃɍ��W�����߂�
				Vector3 clossVec = eye + ray * t;
				
				if (dVec >= 0)
				{
					auto color = GetCheckerColorFromPos(clossVec);
					DrawPixel(x,y,color.GetColor());
				}
			}
		}
	}
}

int main() {
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1816223_��X�g���S"));
	DxLib_Init();

	// �X�N���[����Z=0�̈ʒu
	// �����������_���W(0, 0, 300)
	// ���������̂̏��(���a100�̒��S(0, 0, -100))
	DrawBox(0, 0, 640, 480, GetColor(0,128,128),true);
	auto sp = Sphere(100, Position3(0, 0, -100));
	RayTracing(Vector3(0, 0, 300), sp);

	WaitKey();
	DxLib_End();
}