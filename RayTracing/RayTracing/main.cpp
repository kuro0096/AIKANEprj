#include<dxlib.h>
#include<math.h>
#include"Geometry.h"

const int screen_width = 640;
const int screen_height = 480;

// レイ(光線)と球体の当たり判定(視点からスクリーンピクセルへのベクトル,球,交点までの距離)
// rayは正規化
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp, float& distance) {
	//レイが正規化済みである前提で…
	//
	//視点から球体中心へのベクトル(視線)を作る
	//中心から視線への内積をとります＝＞ベクトル長
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求める
	auto vec = sp.pos - eye; // ベクトル(視線)
	float pLen = (Dot(vec, ray)); // 射影長
	Vector3 Pos = ray * pLen; // 視線ベクトルとベクトル長をかけ
	auto Perpendicular = vec - Pos; // 中心からの垂線下した点
	auto vLen = Perpendicular.Magnitude(); // 垂線長

	if (vLen <= sp.radius)
	{
		// ここに来た時点で当たっている
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

// 反射ベクトルを返す(入射ベクトル,法線ベクトル(正規化済み))
Vector3
RefrectVector(const Vector3& inVec, const Vector3& nVec) {
	// R = I-2N(I・N)を返す
	return inVec -nVec * 2 * Dot(inVec, nVec);
}

// 床を生成(市松模様)
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

// レイトレーシング(視点座標,球オブジェクト(そのうち複数にする))
void RayTracing(const Position3& eye,const Sphere& sphere) {
	Vector3 lightVec(1, -1, -1);
	lightVec.Normalize();
	Plane plane = Plane(Vector3(0, 1, 0), -30);

	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 P(x - screen_width /2,screen_height /2 - y,0);
			Vector3 ray(P - eye);
			float distance = 0.0f;
			//②正規化する
			ray.Normalize();
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。
			if (IsHitRayAndObject(eye,ray,sphere,distance))
			{
				int b = 255;
				// まずdiatanceとrayと球体へのベクトルを
				// もとに法線ベクトルを作る
				// 一旦この球体は完全反射として考える
				// ①反射ベクトルを求める(法線と入射ベクトル(視線)から)
				// ②反射ベクトルと交点から次のレイを飛ばす
				// ③このレイが床との交点を持つならばその座標を求める
				// ④③で得た交点の座標から色分けしてその色を現在の色としてDrawPixelする
				Vector3 hitPos = eye + ray * distance;	// 交点
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
				// そしてその法線ベクトルと「逆」ライトベクトルとの
				// 内積を取りそれを明るさとする。ただしcosθ
				// 拡散反射光(ディフューズ)
				auto diff = Dot(N, -lightVec);
				// 鏡面反射光(スペキュラ)
				auto refLightVec = RefrectVector(lightVec,N);
				// 偶数だとcosのマイナス部がなくなるので奇数を乗算する
				auto sp = pow(Clamp(Dot(-ray, refLightVec)), 10);
				// なので範囲が-1～1までになるため、bをかけてDxLibの
				// 値のルールに合わせよう。
				// 環境光(アンビエント)
				auto ambient = 0.15f;

				// 色の初期値を設定
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
				// 平面から視点までの距離
				auto pVec = Dot(eye, plane.normal) - plane.offset;
				// 1回あたりの移動距離
				auto dVec = Dot(-ray,plane.normal);
				// 座標を求めるために使う
				auto t = pVec / dVec;
				// tをもとに座標を求める
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
	SetMainWindowText(_T("1816223_千々波光祐"));
	DxLib_Init();

	// スクリーンはZ=0の位置
	// 第一引数が視点座標(0, 0, 300)
	// 第二引数球体の情報(半径100の中心(0, 0, -100))
	DrawBox(0, 0, 640, 480, GetColor(0,128,128),true);
	auto sp = Sphere(100, Position3(0, 0, -100));
	RayTracing(Vector3(0, 0, 300), sp);

	WaitKey();
	DxLib_End();
}