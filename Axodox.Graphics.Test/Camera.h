#pragma once
#include "pch.h"
#include <winrt/Windows.UI.Core.h>

class Camera
{
private:
	bool m_slow;
	bool m_fast;

	int m_goForward = 0;
	int m_goRight = 0;
	int m_goUp = 0;

	float zoom;

	float m_angle = 90.0f;
	float m_aspect;
	float m_zNear = 0.01f;
	float m_zFar = 100.0f;

	DirectX::XMVECTOR m_eye;
	DirectX::XMVECTOR m_at;
	DirectX::XMVECTOR m_up;
	DirectX::XMVECTOR m_right;
	DirectX::XMVECTOR m_forward;
	DirectX::XMVECTOR m_worldUp;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_matProj;
	DirectX::XMMATRIX m_matViewProj;

	float m_distance;
	float m_u;
	float m_v;
	float m_speed = 10.0f;

	// view matrix needs recomputation
	bool m_viewDirty = true;
	// projection matrix needs recomputation
	bool m_projectionDirty = true;

	void SetView(DirectX::XMVECTOR _eye, DirectX::XMVECTOR _at, DirectX::XMVECTOR _worldUp);
public:
#pragma region Setters
	void SetAspect(float _aspect) { m_aspect = _aspect; }
#pragma endregion

#pragma region Getters
	inline DirectX::XMVECTOR GetEye() const { return m_eye; }
	inline DirectX::XMVECTOR GetAt() const { return m_at; }
	inline DirectX::XMVECTOR GetWorldUp() const { return m_worldUp; }

	inline DirectX::XMMATRIX GetViewMatrix() const { return m_viewMatrix; }
	inline DirectX::XMMATRIX GetProj() const { return m_matProj; }
	inline DirectX::XMMATRIX GetViewProj() const { return m_matViewProj; }
#pragma endregion

	DirectX::XMFLOAT4 frustum[6];

#pragma region Constructors
	Camera();
	Camera(DirectX::XMVECTOR _eye, DirectX::XMVECTOR _at, DirectX::XMVECTOR _worldUp);
	~Camera();
#pragma endregion

#pragma region Methods
	void Update(float _deltaTime);
	void UpdateUV(float du, float dv);
	void UpdateDistance(float dDistance);
	void UpdateParams();
#pragma endregion

#pragma region Events
	void KeyBoardDown(winrt::Windows::UI::Core::KeyEventArgs const& keys);
	void KeyboardUp(winrt::Windows::UI::Core::KeyEventArgs const& keys);
	void MouseMove(winrt::Windows::UI::Core::PointerEventArgs const& keys);
	void MouseWheel(winrt::Windows::UI::Core::PointerEventArgs const& keys);
#pragma endregion
};
