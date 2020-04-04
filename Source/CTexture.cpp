#include "DXUT.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_vAnchor = Vector2(0.5f, 0.5f);
	m_pTexture = nullptr;
}

CTexture::~CTexture()
{
}
