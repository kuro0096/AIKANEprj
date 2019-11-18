#include<dxlib.h>
#include<math.h>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。


// クランプ...つまり、値を特定の範囲内に収める
float Clamp(float val, float minval = 0.0f, float maxval = 1.0f) {
	return max(min(maxval, val), minval);
}

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
		// ①まず射影長から√(半径^2-垂線長^2を引く)
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

// 反射ベクトルを返す
// param inVec 入射ベクトル
// param nvec 法線ベクトル(正規化済み)
// retval 反射ベクトル
Vector3
RefrectVector(const Vector3& inVec, const Vector3& nVec) {
	// R = I-2N(I・N)を返す
	return inVec -nVec * 2 * Dot(inVec, nVec);
}

///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)
void RayTracing(const Position3& eye,const Sphere& sphere) {
	Vector3 lightVec(1, -1, -1);
	lightVec.Normalize();
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 P(x - screen_width /2,screen_height /2 - y,0);
			Vector3 ray(P - eye);
			float distance = 0.0f;
			//②正規化しとく
			ray.Normalize();
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。
			if (IsHitRayAndObject(eye,ray,sphere,distance))
			{
				int b = 255;
				// まずdiatanceとrayと球体へのベクトルを
				// もとに法線ベクトルを作る
				auto N = ray * distance - (sphere.pos - eye);
				N.Normalize();
				// そしてその法線ベクトルと「逆」ライトベクトルとの
				// 内積を取りそれを明るさとする。ただしcosθ
				// 拡散反射光(ディフューズ)
				auto light = Dot(N, -lightVec);
				// 鏡面反射光(スペキュラ)
				auto refLightVec = RefrectVector(lightVec,N);
				// 偶数だとcosのマイナス部がなくなるので奇数を乗算する
				auto sp = pow(Clamp(Dot(-ray, refLightVec)), 10);
				// なので範囲が-1～1までになるため、bをかけてDxLibの
				// 値のルールに合わせよう。
				// 環境光(アンビエント)
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
	SetMainWindowText(_T("1816223_千々波光祐"));
	DxLib_Init();

	// ｽｸﾘｰﾝはZ=0の位置にあるとします
	// 第一引数が視点座標(0, 0, 300)
	// 第二引数球体の情報(半径100の中心(0, 0, -100))
	/*DrawBox(0, 0, 640, 480, GetColor(0,0,128),true);*/
	auto sp = Sphere(100, Position3(0, 0, -100));
	RayTracing(Vector3(0, 0, 300), sp);

	WaitKey();
	DxLib_End();
}