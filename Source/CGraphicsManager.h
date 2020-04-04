#pragma once
#include "CTexture.h"
class CGraphicsManager : public CSingleton< CGraphicsManager>
{
public:
	CGraphicsManager();
	~CGraphicsManager();

private:
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	map<string, CTexture * > m_mapTexture;

public:
	void LoadSprite(const string& _Key, const string& _Path);
	CTexture * FindSprite(const string& _Key);

	void RenderSprite(const string& _Key, Vector2 _vPos,Vector2 _vScale, float _fRotation, D3DCOLOR _Color);
	void RenderFont(const wstring& _Key, Vector2 _vPos, float _fSize, bool _bCenter ,D3DCOLOR _Color);

	void Begin(UINT _Flag);
	void End();

	void OnLostDevice();
	void OnResetDevice();
};

#define GRAPHICS (*CGraphicsManager::GetInstance())