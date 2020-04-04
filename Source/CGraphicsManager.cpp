#include "DXUT.h"
#include "CGraphicsManager.h"

CGraphicsManager::CGraphicsManager()
{
	D3DXCreateSprite(g_Device, &m_pSprite);
	D3DXCreateFontW(DXUTGetD3D9Device(), 40, 0, 0, 1,
		FALSE, HANGUL_CHARSET, 0, 0, 0, L"¸¼Àº °íµñ", &m_pFont);
}

CGraphicsManager::~CGraphicsManager()
{
	for (auto iter : m_mapTexture)
	{
		SAFE_RELEASE(iter.second->m_pTexture);
		SAFE_DELETE(iter.second);
	}
	m_mapTexture.clear();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pFont);
}

void CGraphicsManager::LoadSprite(const string & _Key, const string & _Path)
{
	if (FindSprite(_Key) == nullptr)
	{
		CTexture * pTexture = new CTexture();

		if (S_OK == D3DXCreateTextureFromFileExA(
			g_Device,
			_Path.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			0,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&pTexture->m_Info,
			nullptr,
			&pTexture->m_pTexture
		))
		{
			m_mapTexture.insert(make_pair(_Key, pTexture));
			return;
		}
		else
		{
			SAFE_DELETE(pTexture);
			return;
		}
	}
}

CTexture *  CGraphicsManager::FindSprite(const string & _Key)
{
	auto Find = m_mapTexture.find(_Key);
	if (Find != m_mapTexture.end())
	{
		return Find->second;
	}
	return nullptr;
}

void CGraphicsManager::RenderSprite(const string & _Key, Vector2 _vPos, Vector2 _vScale, float _fRotation , D3DCOLOR _Color)
{
	CTexture* pTexture = FindSprite(_Key);
	if (pTexture != nullptr)
	{
		Matrix matWorld, matTrans, matScale, matRotation;

		D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, 0.f);
		D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(_fRotation));
		matWorld = matScale * matRotation * matTrans;

		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(
			pTexture->m_pTexture,
			nullptr,
			&Vector3(pTexture->m_Info.Width * pTexture->m_vAnchor.x,
				pTexture->m_Info.Height * pTexture->m_vAnchor.y,
				0.f),
			nullptr,
			_Color
		);
	}
}

void CGraphicsManager::RenderFont(const wstring & _Key, Vector2 _vPos, float _fSize, bool _bCenter, D3DCOLOR _Color)
{
	D3DXMATRIX matWorld, matTrans, matScale;

	if (!_bCenter)
		D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, 0);
	else
		D3DXMatrixTranslation(&matTrans, _vPos.x - _fSize * (_Key.size() * 0.25), _vPos.y - _fSize / 2.f, 0);

	D3DXMatrixScaling(&matScale, _fSize/10.f, _fSize/10.f,0.f);

	m_pSprite->SetTransform(&(matScale * matTrans ));
	m_pFont->DrawTextW(m_pSprite, _Key.c_str(), _Key.size(), NULL, DT_CENTER | DT_NOCLIP, _Color);

}

void CGraphicsManager::Begin(UINT _Flag)
{
	m_pSprite->Begin(_Flag);
}

void CGraphicsManager::End()
{
	m_pSprite->End();
}

void CGraphicsManager::OnLostDevice()
{
	m_pFont->OnLostDevice();
	m_pSprite->OnLostDevice();
}

void CGraphicsManager::OnResetDevice()
{
	m_pFont->OnResetDevice();
	m_pSprite->OnResetDevice();
}
