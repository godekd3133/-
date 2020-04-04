#include "DXUT.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	m_vPos = Vector2(WINSIZEX / 2.f, WINSIZEY / 2.f);

}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Update()
{
	m_matView = Matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		- m_vPos.x, -m_vPos.y, 0, 1
	);
	D3DXMatrixOrthoLH(&m_matProj, WINSIZEX, -WINSIZEY, 0.f, 1.f);
	Vector2 LastPos = m_vPos;
	if (INPUT.KeyPress(VK_LEFT))
	{
		m_vPos.x -= m_fSpeed * DeltaTime;
	}
	if (INPUT.KeyPress(VK_RIGHT))
	{
		m_vPos.x += m_fSpeed * DeltaTime;
	}
	if (INPUT.KeyPress(VK_DOWN))
	{
		m_vPos.y += m_fSpeed * DeltaTime;
	}
	if (INPUT.KeyPress(VK_UP))
	{
		m_vPos.y -= m_fSpeed * DeltaTime;
	}
	if ((m_vMinPos +Vector2(WINSIZEX / 2.F, WINSIZEY / 2.f)).x > m_vPos.x ||
		(m_vMinPos + Vector2(WINSIZEX / 2.F, WINSIZEY / 2.f)).y > m_vPos.y )
	{
		m_vPos = LastPos;
	}
	if ((m_vMaxPos - Vector2(WINSIZEX / 2.F, WINSIZEY / 2.f)).x < m_vPos.x ||
		(m_vMaxPos - Vector2(WINSIZEX / 2.F, WINSIZEY / 2.f)).y < m_vPos.y)
	{
		m_vPos = LastPos;
	}
}

void CCameraManager::SetTransform()
{
	g_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	g_Device->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCameraManager::SetRect(Vector2 _vMinPos, Vector2 _vMaxPos)
{
	m_vMinPos = _vMinPos;
	m_vMaxPos = _vMaxPos;
}
