#pragma once
#include<DxLib.h>

//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2():x(0),y(0){}
	Vector2(float inx,float iny):x(inx),y(iny){}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;
	
	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
typedef Vector2 Position2;


//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0) ,z(0){}
	Vector3(float inx, float iny,float inz) :x(inx), y(iny) ,z(inz){}
	float x, y,z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator-() {
		return Vector3(-x, -y,-z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
float operator*(const Vector3& va, const Vector3& vb);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///����\���\����
struct Sphere {
	float radius;//���a
	Position3 pos; //���S���W
	Sphere() :radius(0), pos(0, 0,0) {}
	Sphere(float r, Position3& p) :radius(r), pos(p) {}
};

///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
};

// �N�����v(�l�����͈͓̔��Ɏ��߂�)
float Clamp(float val, float minval = 0.0f, float maxval = 1.0f);

// �F�̍\����
struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color() : r(0), g(0), b(0) {}
	Color(unsigned char inr, unsigned char ing, unsigned char inb)
		: r(inr), g(ing), b(inb) {}
	Color operator*(float scale) {
		Color ret(r, g, b);
		ret.r *= scale;
		ret.g *= scale;
		ret.b *= scale;
		return ret;
	}
	void operator*=(float scale) {
		r *= scale;
		g *= scale;
		b *= scale;
	}
	Color operator+(const Color& col) {
		Color ret(r, g, b);
		ret.r = Clamp(r + col.r, 0, 255);
		ret.g = Clamp(g + col.g, 0, 255);
		ret.b = Clamp(b + col.b, 0, 255);
		return ret;
	}
	void operator+=(const Color& col) {
		r = Clamp(r + col.r, 0, 255);
		g = Clamp(g + col.g, 0, 255);
		b = Clamp(b + col.b, 0, 255);
	}

	unsigned int GetColor()const {
		return DxLib::GetColor(r, g, b);
	}
};

// ���̍\����
struct Plane {
	Vector3 normal;	// �@��(a,b,c)���K�����K������Ă��邱��
	float offset;	// ���_����̵̾��(d)
	Plane(const Vector3& inNormal, float inOffset) :
		normal(inNormal), offset(inOffset) {
		normal.Normalize();
	}
};
