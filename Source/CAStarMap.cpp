#include "DXUT.h"
#include "CAStarMap.h"
#include "CAStar.h"
CAStarMap::CAStarMap(float _fWidth, float _fHeight)
	: m_fHeight(_fHeight) ,m_fWidth(_fWidth)
{
	m_vEnemyPos = Vector2(0.f, 0.f);
	m_vTargetPos = m_vEnemyPos;
	m_Nodes = vector<vector<CNode*>>(_fHeight);
	for (int i = 0; i < _fHeight; i++)
	{
		m_Nodes[i] = vector<CNode*>(_fWidth, nullptr);
		for (int j = 0; j < _fWidth; j++)
		{
			m_Nodes[i][j] =  new CNode(NodeType::Floor);
			m_Nodes[i][j]->m_vPos = Vector2(j, i);
			m_Nodes[i][j]->m_vDir = Vector2(0.f, 0.f);
		//	m_Nodes[i][j]->m_listLinkedNode.pu
		}
	}
	m_pAstar = new CAStar(m_Nodes);
	CAMERA.SetRect(Vector2(0, 0), Vector2(_fWidth * 100+ 280, _fHeight * 100));
	//m_Nodes[5][5]->m_Type = NodeType::Wall;
}

CAStarMap::~CAStarMap()
{
	for (auto iter : m_Nodes)
	{
		for (auto iter2 : iter)
		{
			delete iter2;
		}
	}
	SAFE_DELETE( m_pAstar);
}

void CAStarMap::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(DXUTGetHWND(), &ptMouse);
	if (INPUT.KeyDown(VK_LBUTTON))
	{
		for (auto iter : m_Nodes)
		{
			for (auto iter2 : iter)
			{
				iter2->F = 0;
				iter2->G = 0;
				iter2->H = 0;
				iter2->m_vDir = Vector2(0.f, 0.f);
				iter2->m_pDirectionNode = nullptr;
				if(iter2->m_Type != NodeType::Wall)
				iter2->m_Type = NodeType::Floor;
			}
		}
		m_vStartPos = m_vEnemyPos;
		m_vTargetPos = Vector2((int)((ptMouse.x + CAMERA.GetPos().x- WINSIZEX/2.f) / 100), (int)((ptMouse.y + CAMERA.GetPos().y- WINSIZEY/2.f )/ 100));
		if (ptMouse.x > 0 && ptMouse.x < 990 &&
			ptMouse.y > 0 && ptMouse.y < WINSIZEY-15)
		{
			Route = m_pAstar->GetAstarRoute(GetNode(m_vEnemyPos), GetNode(m_vTargetPos));
			index = Route.size() - 1;
		}

	}
	if (INPUT.KeyDown(VK_RBUTTON))
	{
		m_vTargetPos = Vector2((int)((ptMouse.x + CAMERA.GetPos().x - WINSIZEX / 2.f) / 100), (int)((ptMouse.y + CAMERA.GetPos().y - WINSIZEY / 2.f) / 100));
		GetNode(m_vTargetPos)->m_Type = NodeType::Wall;
	}
	if (index != -1)
	{
		Vector2 Dir = Route[index]->GetPos() - m_vEnemyPos;
		D3DXVec2Normalize(&Dir, &Dir);
		m_vEnemyPos +=  Dir * DeltaTime * 10;
		if (D3DXVec2Length(&(Route[index]->GetPos() - m_vEnemyPos)) < 0.5f)
		{
			m_vEnemyPos = Route[index]->GetPos();
		//	Route.pop_back();
			index--;
		}

	}
	GRAPHICS.Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	for (int y = 0; y < m_fHeight; y++)
	{
		for (int x = 0; x < m_fWidth; x++)
		{
			switch (m_Nodes[y][x]->m_Type)
			{
			case NodeType::Floor:
				GRAPHICS.RenderSprite("FLOOR", Vector2(x * 100, y * 100), Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case NodeType::Wall:
				GRAPHICS.RenderSprite("WALL", Vector2(x * 100, y * 100), Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case NodeType::OpenNode:
				GRAPHICS.RenderSprite("FLOOR", Vector2(x * 100, y * 100), Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(100, 100, 100, 255));

					Vector2 Dir = m_Nodes[y][x]->GetDirectionNode()->GetPos() - m_Nodes[y][x]->GetPos();
					D3DXVec2Normalize(&Dir, &Dir);

					float Rot = atan2f(Dir.y, Dir.x);

					GRAPHICS.RenderSprite("DIR", Vector2(x * 100 + 50, y * 100 + 50), Vector2(1.f, 1.f), D3DXToDegree(Rot) +90, D3DCOLOR_ARGB(255, 255, 255, 255));
					GRAPHICS.RenderFont(to_wstring((int)(m_Nodes[y][x]->F*10)), Vector2(x * 100 + 10, y * 100 ), 10, false , D3DCOLOR_ARGB(255, 255, 255, 255));
					GRAPHICS.RenderFont(to_wstring((int)(m_Nodes[y][x]->G * 10)), Vector2(x * 100 + 10, y * 100 + 60), 10, false, D3DCOLOR_ARGB(255, 255, 255, 255));
					GRAPHICS.RenderFont(to_wstring((int)(m_Nodes[y][x]->H * 10)), Vector2(x * 100 + 70, y * 100 + 60), 10, false, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
			}

		}
	}

	GRAPHICS.RenderSprite("START", Vector2(m_vStartPos.x * 100 + 50, m_vStartPos.y * 100 + 50), Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
	GRAPHICS.RenderSprite("TARGET", Vector2(m_vTargetPos.x * 100 + 50, m_vTargetPos.y * 100 + 50), Vector2(1.f, 1.f),0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
	for (auto iter : Route)
	{
		Vector2 Dir = iter->GetDirectionNode()->GetPos() - iter->GetPos();
		D3DXVec2Normalize(&Dir, &Dir);

		float Rot = atan2f(Dir.y, Dir.x) ;
		GRAPHICS.RenderSprite("ROUTE", Vector2(iter->GetPos().x * 100 + 50, iter->GetPos().y * 100 + 50), Vector2(1.f, 1.f), D3DXToDegree(Rot) + 180, D3DCOLOR_ARGB(255, 255, 255, 255));

	}


	GRAPHICS.RenderSprite("ENEMY",m_vEnemyPos * 100, Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
	GRAPHICS.End();
	GRAPHICS.Begin(D3DXSPRITE_ALPHABLEND );
	GRAPHICS.RenderSprite("UI_BG",Vector2(1000,0), Vector2(1.f, 1.f), 0.f, D3DCOLOR_ARGB(255, 255, 255, 255));
	GRAPHICS.RenderFont(L"맵의 크기 : " + to_wstring(m_Nodes[0].size()) + L" x " + to_wstring(m_Nodes.size()),Vector2(1020,100),8,false,D3DCOLOR_ARGB(255,0,0,0));
	GRAPHICS.RenderFont(L"플레이어의 위치 : " + to_wstring((int)(m_vEnemyPos.x) + 1) + L" , " + to_wstring((int)(m_vEnemyPos.y) + 1), Vector2(1020, 200), 8, false, D3DCOLOR_ARGB(255, 0, 0, 0));
	GRAPHICS.RenderFont(L"FPS : " + to_wstring(DXUTGetFPS()) , Vector2(1020, 300), 8, false, D3DCOLOR_ARGB(255, 0, 0, 0));
	GRAPHICS.End();

}





CNode * CAStarMap::GetNode(int _iX, int _iY)
{
	return m_Nodes[_iY][_iX];
}

CNode * CAStarMap::GetNode(Vector2 _vPos)
{
	return m_Nodes[_vPos.y][_vPos.x];
}
