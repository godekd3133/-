#pragma once
class CTexture
{
public:
	CTexture();
	~CTexture();
	
public:
	Vector2 m_vAnchor;
	D3DXIMAGE_INFO m_Info;
	LPDIRECT3DTEXTURE9 m_pTexture;
};

