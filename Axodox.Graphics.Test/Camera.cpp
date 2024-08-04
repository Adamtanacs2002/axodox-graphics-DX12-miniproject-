#include "pch.h"
#include "Camera.h"
#include "DirectXMath.h"

Camera::Camera()
{
  SetView(DirectX::XMVectorSet(3.0f, 7.0f, 7.0f,0.0f),
    DirectX::XMVectorSet(0.0f, 0.0f, 3.0f,0.0f), DirectX::XMVectorSet(0.f, 0.f, 1.0f,0.0f));
}

Camera::Camera(DirectX::XMVECTOR _eye, DirectX::XMVECTOR _at, DirectX::XMVECTOR _worldUp)
{
  SetView(_eye, _at, _worldUp);
}

Camera::~Camera()
{
}

void Camera::SetView(DirectX::XMVECTOR _eye, DirectX::XMVECTOR _at, DirectX::XMVECTOR _worldUp)
{
  m_eye = _eye;
  m_at = _at;
  m_worldUp = _worldUp;

  DirectX::XMVECTOR ToAim = DirectX::XMVectorSubtract(m_at, m_eye);

  m_distance = DirectX::XMVector3Length(ToAim).m128_f32[0];

  // m_u = atan2f(ToAim.z, ToAim.x);
  m_u = atan2f(DirectX::XMVectorGetZ(ToAim), DirectX::XMVectorGetX(ToAim));
  m_v = acosf(DirectX::XMVectorGetY(ToAim) / m_distance);

  UpdateParams();

  m_viewDirty = true;
}

void Camera::Update(float _deltaTime)
{
  using namespace DirectX;
  if (m_goForward != 0.0f || m_goRight != 0.0f || m_goUp != 0.0f)
  {
    // deltaPosition = (m_goForward * m_forward + m_goRight * m_right + m_goUp * m_up) * m_speed * _deltaTime;
    DirectX::XMVECTOR deltaPosition = 
      (m_forward * m_goForward + m_goRight * m_right + m_up * m_goUp) * m_speed * _deltaTime;
    m_eye = m_eye + deltaPosition;
    m_at = m_at + deltaPosition;
    m_viewDirty = true;
  }

  if (m_viewDirty)
  {
    m_viewMatrix = DirectX::XMMatrixLookAtLH(m_eye, m_at, m_worldUp);
  }

  if (m_projectionDirty)
  {
    m_matProj = DirectX::XMMatrixPerspectiveFovLH(m_angle, m_aspect, m_zNear, m_zFar);
  }

  if (m_viewDirty || m_projectionDirty)
  {
    m_matViewProj = m_matProj * m_viewMatrix;
    m_viewDirty = false;
    m_projectionDirty = false;
  }
}

void Camera::UpdateUV(float du, float dv)
{
  using namespace DirectX;
  m_u += du;
  XMVECTOR tmp_v = XMVECTOR{ m_v + dv };
  if (tmp_v.m128_f32[0] > XM_PI || tmp_v.m128_f32[0] < -XM_PI)
    tmp_v = -tmp_v;
  m_v = XMVector3ClampLength(tmp_v , 0.1f, XM_PI).m128_f32[0];
  UpdateParams();
}

void Camera::UpdateDistance(float dDistance)
{
  m_distance += dDistance;
  UpdateParams();
}

void Camera::UpdateParams()
{
  DirectX::XMVECTOR lookDirection{ cosf(m_u) * sinf(m_v), cosf(m_v), sinf(m_u) * sinf(m_v) };

  m_eye = DirectX::XMVectorSubtract(m_at,DirectX::XMVectorScale(lookDirection,m_distance));

  m_up = m_worldUp;
  m_right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(lookDirection, m_worldUp));

  m_forward = DirectX::XMVector3Cross(m_up, m_right);

  m_viewDirty = true;
}

void Camera::KeyBoardDown(winrt::Windows::UI::Core::KeyEventArgs const& key)
{
  using namespace winrt::Windows::System;

  switch (key.VirtualKey()) {
  case VirtualKey::Shift:
  case VirtualKey::LeftShift:
    if (!m_slow) {
      m_slow = true;
    }
    break;
  case VirtualKey::RightShift:
  case VirtualKey::Control:
  case VirtualKey::RightControl:
  case VirtualKey::LeftControl:
    if (!m_fast) {
      m_fast = true;
    }
    break;
  case VirtualKey::W:
    m_goForward = 1;
    break;
  case VirtualKey::S:
    m_goForward = -1;
    break;
  case VirtualKey::A:
    m_goRight = -1;
    break;
  case VirtualKey::D:
    m_goRight = 1;
    break;
  case VirtualKey::E:
    m_goUp = 1;
    break;
  case VirtualKey::Q:
    m_goUp = -1;
    break;
  }
}

void Camera::KeyboardUp(winrt::Windows::UI::Core::KeyEventArgs const& key)
{
  using namespace winrt::Windows::System;

  switch (key.VirtualKey()) {
  case VirtualKey::Shift:
  case VirtualKey::LeftShift:
  case VirtualKey::RightShift:
    if (m_slow) {
      m_slow = false;
    }
    break;
  case VirtualKey::Control:
  case VirtualKey::RightControl:
  case VirtualKey::LeftControl:
    if (m_fast) {
      m_fast = false;
    }
    break;

  case VirtualKey::W:
  case VirtualKey::S:
    m_goForward = 0;
    break;
  case VirtualKey::A:
  case VirtualKey::D:
    m_goRight = 0;
    break;
  case VirtualKey::E:
  case VirtualKey::Q:
    m_goUp = 0;
    break;
  }
}

void Camera::MouseMove(winrt::Windows::UI::Core::PointerEventArgs const& mouse)
{
  using CursorPos = decltype(mouse.CurrentPoint().Position());
  auto point = mouse.CurrentPoint().Position();
  static CursorPos prev = point;
  if (mouse.CurrentPoint().Properties().IsLeftButtonPressed()) {
    UpdateUV((point.Y - prev.Y) / 600.0f,(point.X - prev.X) / 600.0f);
  }
  prev = point;
}

void Camera::MouseWheel(winrt::Windows::UI::Core::PointerEventArgs const& wheel)
{
  UpdateDistance(
    static_cast<float>(wheel.CurrentPoint().Properties().MouseWheelDelta()) *
    1.0f / -300.0f);
}
