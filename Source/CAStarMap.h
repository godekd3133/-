#pragma once
#include "CAStar.h"
class CAStarMap
{
public:
	CAStarMap(float _fWidth,float _fHeight);
	~CAStarMap();

public:
	vector<vector<CNode *>> m_Nodes;
	float m_fHeight;
	float m_fWidth;
	vector<CNode*> Route;
	int index =-1;
	Vector2 m_vEnemyPos;
	Vector2 m_vTargetPos;
	Vector2 m_vStartPos;
	void Render();
	CAStar * m_pAstar;
	CNode * GetNode(int _iX, int _iY);
	CNode * GetNode(Vector2 _vPos);
};

