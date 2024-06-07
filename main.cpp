#include <Novice.h>
#include<Vector3.h>
#include<Matrix4x4.h>
#include<cmath>

const char kWindowTitle[] = "GC2C_01_オガワ_リョウ";

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0];
	result.m[0][1] = m1.m[0][1] * m2.m[0][1];
	result.m[0][2] = m1.m[0][2] * m2.m[0][2];
	result.m[0][3] = m1.m[0][3] * m2.m[0][3];

	result.m[1][0] = m1.m[1][0] * m2.m[1][0];
	result.m[1][1] = m1.m[1][1] * m2.m[1][1];
	result.m[1][2] = m1.m[1][2] * m2.m[1][2];
	result.m[1][3] = m1.m[1][3] * m2.m[1][3];

	result.m[2][0] = m1.m[2][0] * m2.m[2][0];
	result.m[2][1] = m1.m[2][1] * m2.m[2][1];
	result.m[2][2] = m1.m[2][2] * m2.m[2][2];
	result.m[2][3] = m1.m[2][3] * m2.m[2][3];

	result.m[3][0] = m1.m[3][0] * m2.m[3][0];
	result.m[3][1] = m1.m[3][1] * m2.m[3][1];
	result.m[3][2] = m1.m[3][2] * m2.m[3][2];
	result.m[3][3] = m1.m[3][3] * m2.m[3][3];
	return result;





}

Matrix4x4 MakeRotateXMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { 1.0f, 0.0f,      0.0f,     0.0f, 0.0f, cosTheta, sinTheta, 0.0f,
			0.0f, -sinTheta, cosTheta, 0.0f, 0.0f, 0.0f,     0.0f,     1.0f };
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { cosTheta, 0.0f, -sinTheta, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			sinTheta, 0.0f, cosTheta,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4x4 MakeRotateZMatrix(float radian) {

	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { cosTheta, sinTheta, 0.0f, 0.0f, -sinTheta, cosTheta, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

			0.0f,           0.0f,           0.0f, 1.0f };

	Matrix4x4 MakeAffineMatrix(const Vector3 & scale, const Vector3 & rotate, const Vector3 & translate) {


		Matrix4x4 Multiply(const Matrix4x4 & m1, const Matrix4x4 & m2);
		Matrix4x4 result = Multiply(
			Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)),
			MakeRotateZMatrix(rotate.z));


		result.m[0][0] *= scale.x;
		result.m[0][1] *= scale.x;
		result.m[0][2] *= scale.x;

		result.m[1][0] *= scale.y;
		result.m[1][1] *= scale.y;
		result.m[1][2] *= scale.y;

		result.m[2][0] *= scale.z;
		result.m[2][1] *= scale.z;
		result.m[2][2] *= scale.z;

		result.m[3][0] = translate.x;
		result.m[3][1] = translate.y;
		result.m[3][2] = translate.z;

		return result;
	}

static const int kColumnWidth = 60;
static const int kRowHeight = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f",
				matrix.m[row][column]);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//拡大縮小成分ベクトル
		Vector3 scale{ 1.2f, 0.79f, -2.1f };
		//回転成分ベクトル
		Vector3 rotate{ 0.4f, 1.43f, -0.8f };
		//平行移動成分ベクトル
		Vector3 translate{ 2.7f, -4.15f, 1.57f };
		//↑の3つの成分からそれぞれの行列をつくり、さらにその行列を掛け算で1つにする
		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

