#include<dxlib.h>
#include<math.h>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。

///レイ(光線)と球体の当たり判定
///@param ray (視点からスクリーンピクセルへのベクトル)
///@param sphere 球
///@param distance 交点までの距離
///@hint レイは正規化しといたほうが使いやすいだろう
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp, float& distance) {
	//レイが正規化済みである前提で…
	//
	//視点から球体中心へのベクトル(視線)を作ります
	//中心から視線への内積をとります＝＞ベクトル長
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	auto vec = sp.pos - eye; // ベクトル(視線)
	float pLen = (Dot(vec, ray)); // 射影長
	Vector3 Pos = ray * pLen; // 視線ベクトルとベクトル長をかけ
	auto Perpendicular = vec - Pos; // 中心からの垂線下した点
	auto vLen = Perpendicular.Magnitude(); // 垂線長

	if (vLen <= sp.radius)
	{
		// ここに来た時点で当たっている
		// なので
		// ①まず射影長から√(半径^2-垂線長を引く)
		auto newdistance = pLen - sqrt(pow(sp.radius,2.0) - pow(vLen, 2.0));
		// それをdistanceに代入
		distance = newdistance;
		return true;
	}
	else
	{
		return false;
	}
}

///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)
void RayTracing(const Position3& eye,const Sphere& sphere) {
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 P(x - screen_width /2,y - screen_height /2,0);
			Vector3 ray(P - eye);
			float distance = 0;
			//②正規化しとく
			ray.Normalize();
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。
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
	SetMainWindowText(_T("1816223_千々波光祐"));
	DxLib_Init();
	// ｽｸﾘｰﾝはZ=0の位置にあるとします
	// 第一引数が視点座標(0, 0, 300)
	// 第二引数球体の情報(半径100の中心(0, 0, -100))
	RayTracing(Vector3(0, 0, 300), Sphere(100, Position3(0, 0, -100)));

	WaitKey();
	DxLib_End();
}