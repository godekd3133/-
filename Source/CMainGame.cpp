#include "DXUT.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
	m_pAstarMap = new CAStarMap(CAMERA.Width,CAMERA.Height);
}

CMainGame::~CMainGame()
{
	
}

void CMainGame::Init()
{
	GRAPHICS.LoadSprite("WALL", "./resource/Wall.png");
	GRAPHICS.LoadSprite("FLOOR", "./resource/Floor.png");
	GRAPHICS.LoadSprite("ENEMY", "./resource/Enemy.png");
	GRAPHICS.LoadSprite("DIR", "./resource/Dir.png");
	GRAPHICS.LoadSprite("TARGET", "./resource/Target.png");
	GRAPHICS.LoadSprite("START", "./resource/Start.png");
	GRAPHICS.LoadSprite("ROUTE", "./resource/Route.png");
	GRAPHICS.LoadSprite("UI_BG", "./resource/UI_BG.png");

	GRAPHICS.FindSprite("WALL")->m_vAnchor = Vector2(0.f, 0.f);
	GRAPHICS.FindSprite("FLOOR")->m_vAnchor = Vector2(0.f, 0.f);
	GRAPHICS.FindSprite("ENEMY")->m_vAnchor = Vector2(0.f, 0.f);
	GRAPHICS.FindSprite("UI_BG")->m_vAnchor = Vector2(0.f, 0.f);
}

void CMainGame::Update()
{
	CAMERA.Update();
	INPUT.Update();
}

void CMainGame::Render()
{
	CAMERA.SetTransform();
	m_pAstarMap->Render();

}

void CMainGame::Release()
{
	SAFE_DELETE(m_pAstarMap);
	GRAPHICS.ReleaseInstance();
	CAMERA.ReleaseInstance();
	INPUT.ReleaseInstance();
}

void CMainGame::OnResetDevice()
{
	GRAPHICS.OnResetDevice();
}

void CMainGame::OnLostDevice()
{
	GRAPHICS.OnLostDevice();
}
