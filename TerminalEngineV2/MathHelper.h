#include<windows.h>
#include<DirectXMath.h>
#include<cstdint>

class MathHelper {
public:
	//retunrs random float in range [0, 1]
	static float RandF() {
		return (float)(rand()) / (float)RAND_MAX;
	}

	//returns random float in range [a, b]
	static float RandF(float a, float b) {
		return a + RandF() * (b - a);
	}

	static int Rand(int a, int b) {
		return a + rand() % ((b - a) + 1);
	}

	template<typename T>
	static T Min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	template<typename T>
	static T Lerp(const T& a, const T& b, float t) {
		return a + (b - a) * t;
	}

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high) {
		return x < low ? low : (x > high ? high : x);
	}

	//returns the polar angle of the point (x, y) in range [0, 2*PI]
	static float AngleFromXY(float x, float y);

	static DirectX::XMVECTOR SphericalToCartesian(float radius, float theta, float phi) {
		return DirectX::XMVectorSet(
			radius * sinf(phi) * cosf(theta),
			radius * cosf(phi),
			radius * sinf(phi) * sinf(theta),
			1.0f
		);
	}

	static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M) {
		//inverse-transpose is just applied to normals. So zero out
		//translation row so that it doesn't get into our inverse-transpose
		//calculatio--we don't want the interse-transpose of the translation
		DirectX::XMMATRIX A = M;
		A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A));
	}

	static DirectX::XMFLOAT4X4 Identity4X4() {
		static DirectX::XMFLOAT4X4 I(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		return I;
	}

	static DirectX::XMVECTOR RandUnitVec3();
	static DirectX::XMVECTOR RandHemisphereUnitVec3(DirectX::XMVECTOR n);

	static const float Infinity;
	static const float Pi;
};