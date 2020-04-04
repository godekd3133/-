#include "DXUT.h"
#include "CAStar.h"

CAStar::CAStar(vector<vector<CNode*>>& _Map)
	: m_Map(_Map)
{
}

CAStar::~CAStar()
{
}

list<CNode*> CAStar::GetAdjacencyNodes(CNode * _pSelectNode)
{
	list<CNode*> listAdjacencyNode;
	
	Vector2 Dir[8];
	Dir[AStarDir::Bottom] = Vector2(0, 1);
	Dir[AStarDir::Top] = Vector2(0, -1);
	Dir[AStarDir::Right] = Vector2(1, 0);
	Dir[AStarDir::Left] = Vector2(-1, 0);
	//Dir[AStarDir::LeftBottom] = Vector2(-1, 1);
	//Dir[AStarDir::LeftTop] = Vector2(-1, -1);
	//Dir[AStarDir::RightBottom] = Vector2(1, 1);
	//Dir[AStarDir::RightTop] = Vector2(1, -1);

	int Width = GetWidth();
	int Height = GetHeight();

	for (int i = 0; i < 8; i++)
	{
		Vector2 vDirPos = _pSelectNode->GetPos() + Dir[i];
		//���� ������ ����� �ʾҴٸ�
		if (vDirPos.x >= 0.f && vDirPos.x < Width &&
			vDirPos.y >= 0.f && vDirPos.y < Height)
		{
			CNode * pNode = GetNode(vDirPos);
			NodeType Type = pNode->GetNodeType();
			if (Type != NodeType::Wall)
			{
				listAdjacencyNode.push_back(GetNode(vDirPos));
			}
		}
	}

	return listAdjacencyNode;
}

void CAStar::SetParentNode(CNode * _pSelectNode, CNode * _pParentNode, CNode * _pStartNode, CNode * _pEndNode)
{
	_pSelectNode->SetDirection(_pParentNode);
	_pSelectNode->G = GetG(_pSelectNode, _pStartNode);
	_pSelectNode->H = GetH(_pSelectNode, _pEndNode);
	_pSelectNode->F = _pSelectNode->G + _pSelectNode->H;
}

vector<CNode*> CAStar::GetAstarRoute(CNode * _pStartNode, CNode * _pEndNode)
{
	list<CNode*> listOpenNode; // ������� 
	list<CNode*> listCloseNode; // �������
	vector<CNode*> vecRoute; // ���
	CNode * pSelectNode = _pStartNode;
	listCloseNode.push_back(pSelectNode);

	//���ۻ簢������ �˻��� �����簢������ ������Ͽ� �ִ´�.
	listOpenNode = GetAdjacencyNodes(_pStartNode);
	for(auto iter : listOpenNode)
	iter->m_Type = NodeType::OpenNode;

	//�����簢���߿� ��ǥ��尡 �ִٸ� Ž���� �����Ѵ�.
	if (std::find(listOpenNode.begin(), listOpenNode.end(), _pEndNode) != listOpenNode.end())
	{
		vecRoute.push_back(_pEndNode);
		return vecRoute;
	}

	//�˻��� �����簢������ �θ� ���� ���� �������ش�.
	for (auto iter : listOpenNode)
	{
		SetParentNode(iter, pSelectNode, _pStartNode, _pEndNode);
	}

	while (1)
	{
		//������Ͽ��� ���� ���� F����� ã�� ���� �簢������ �����Ѵ�.
		pSelectNode = listOpenNode.front();
		for (auto iter : listOpenNode)
		{
			if (pSelectNode->F > iter->F)
			{
				pSelectNode = iter;
			}
		}

		//���� �簢������ ������ ��带 ������Ͽ��� ���� ����������� �ִ´�.
		listOpenNode.remove(pSelectNode);
		listCloseNode.push_back(pSelectNode);

		//������ �簢���� ������ �簢���� ���� Ž���Ѵ�.
		for (auto iter : GetAdjacencyNodes(pSelectNode))
		{
			//������Ͽ� �ִٸ� ����
			if (std::find(listCloseNode.begin(), listCloseNode.end(), iter) != listCloseNode.end())
			{
				continue;
			}

			//������Ͽ� ���ٸ� ������Ͽ� �߰��ϰ� �θ��带 ���� �簢������ ������ FGH ��� ���
			if (std::find(listOpenNode.begin(), listOpenNode.end(), iter) == listOpenNode.end())
			{
				listOpenNode.push_back(iter);
				SetParentNode(iter, pSelectNode, _pStartNode, _pEndNode);
				iter->m_Type = NodeType::OpenNode;
				//��ǥ�簢���� ������忡 �߰�������� Ž���� �����Ѵ�.
				if (iter == _pEndNode)
				{
					CNode * pDirNode = _pEndNode;
					while (pDirNode != _pStartNode)
					{
						vecRoute.push_back(pDirNode);
						pDirNode = pDirNode->GetDirectionNode();
					}
					return vecRoute;
				}
			}
			//������Ͽ� �̹� �ִٸ�, G����� ���� �θ�簢������ �����ϰ� FGH ��� ���
			else
			{
				float OldF = iter->F;

				CNode * OldParentNode = iter->GetDirectionNode();
				
				SetParentNode(iter, pSelectNode, _pStartNode, _pEndNode);
				if (OldF < iter->F)
				{
					SetParentNode(iter, OldParentNode, _pStartNode, _pEndNode);
				}

			}
		}

	}
}



float CAStar::GetG(CNode * _pSelectNode, CNode * _pStartNode)
{
	Vector2 CurPos = _pSelectNode->GetPos();
	float G = 0.f;
	while (GetNode(CurPos) != _pStartNode)
	{
		
		G += D3DXVec2Length(&(GetNode(CurPos)->GetPos() - GetNode(CurPos)->GetDirectionNode()->GetPos()));
		CurPos = GetNode(CurPos)->GetDirectionNode()->GetPos();
	}
	return G;
}

float CAStar::GetH(CNode * _pSelectNode, CNode * _vEndPos)
{
	float H = 0.f;
	H += D3DXVec2Length(&(_vEndPos->GetPos() - _pSelectNode->GetPos()));
	return H;
}

vector<CNode*> CAStar::UpdateOpenNodes(CNode * _pSelNode, CNode * _pStartNode, CNode * _pEndNode, vector<CNode*>& _vecOpenNodes, vector<CNode*>& _vecCloseNodes)
{
	vector<CNode*> vecOpenNodes; 
	Vector2 Dir[9];
		bool DirChk[9];
	Dir[AStarDir::Bottom] = Vector2(0, 1);
	Dir[AStarDir::Top] = Vector2(0, -1);
	Dir[AStarDir::Right] = Vector2(1, 0);
	Dir[AStarDir::Left] = Vector2(-1, 0);
	Dir[AStarDir::LeftBottom] = Vector2(-1, 1);
	Dir[AStarDir::LeftTop] = Vector2(-1, -1);
	Dir[AStarDir::RightBottom] = Vector2(1, 1);
	Dir[AStarDir::RightTop] = Vector2(1, -1);

	for (int i = 0; i < 8; i++)
	{
		if ((_pSelNode->GetPos() + Dir[i]).x >= 0 && 
			(_pSelNode->GetPos() + Dir[i]).y >= 0 &&
			(_pSelNode->GetPos() + Dir[i]).x < 10 && 
			(_pSelNode->GetPos() + Dir[i]).y < 10 )
		{
			CNode * pNode = GetNode(_pSelNode->GetPos() + Dir[i]);
			bool isClose = false;
			for (auto iter : _vecCloseNodes)
			{
				if (pNode == iter) isClose = true;
			}
			bool SideChk = true;
			/*if (i == AStarDir::LeftBottom)
			{
				if (DirChk[AStarDir::Bottom] == false ||
					DirChk[AStarDir::Left] == false)
				{
					DirChk[i] = false;
					SideChk = false;
				}
			}
			else if (i == AStarDir::RightBottom)
			{
				if (DirChk[AStarDir::Right] == false ||
					DirChk[AStarDir::Bottom] == false)
				{
					DirChk[i] = false;
					SideChk = false;
				}
			}
			else if (i == AStarDir::RightTop)
			{
				if (DirChk[AStarDir::Right] == false ||
					DirChk[AStarDir::Top] == false)
				{
					DirChk[i] = false;
					SideChk = false;
				}
			}
			else if (i == AStarDir::LeftTop)
			{
				if (DirChk[AStarDir::Left] == false ||
					DirChk[AStarDir::Top] == false)
				{
					DirChk[i] = false;
					SideChk = false;
				}
			}*/
			if (isClose == false && pNode->m_Type != NodeType::Wall)
			{

				pNode->m_Type = NodeType::OpenNode;
				vecOpenNodes.push_back(pNode);
				_vecOpenNodes.push_back(pNode);

				DirChk[i] = true;
				bool isOpen = false;
				for (auto iter : _vecOpenNodes)
				{
					if (iter == pNode) // �̹� ���� ��Ͽ� �ִ� �����
					{
						isOpen = true;
					}
				}
				if (isOpen == true)
				{
					CNode * pLastDirNode = pNode->GetDirectionNode();
					float LastG = GetG(pNode, _pStartNode);
					pNode->SetDirection(_pSelNode);
					float CurG = GetG(pNode, _pStartNode);
					if (LastG < CurG)
					{
						pNode->SetDirection(pLastDirNode);
						pNode->G = LastG;
						pNode->H = GetH(pNode, _pEndNode);
						pNode->F = pNode->G + pNode->H;
					}
					else
					{
						pNode->G = CurG;
						pNode->H = GetH(pNode, _pEndNode);
						pNode->F = pNode->G + pNode->H;
					}
				}
				else
				{
					pNode->SetDirection(_pSelNode);
					pNode->G = GetG(pNode, _pStartNode);
					pNode->H = GetH(pNode, _pEndNode);
					pNode->F = pNode->G + pNode->H;
				}
			}
			//else DirChk[i] = false;
		}
	}
	return vecOpenNodes;
}

CNode * CAStar::GetNode(int _iX, int _iY)
{
	return m_Map[_iY][_iX];
}

CNode * CAStar::GetNode(Vector2 _vPos)
{
	return m_Map[int(floor(_vPos.y))][int(floor(_vPos.x))];
}

NodeType CAStar::GetNodeType(int _iX, int _iY)
{
	if (_iY >= m_Map.size() ||
		_iY < 0 ||
		_iX >= m_Map[_iY].size() ||
		_iX < 0)
	{
		return NodeType::Wall;
	}
	return GetNode(_iX, _iY)->m_Type;
}
NodeType CAStar::GetNodeType(Vector2 _vPos)
{
	if (_vPos.y >= m_Map.size() || 
		_vPos.y < 0 ||
		_vPos.x >= m_Map[(int)_vPos.y].size() ||
		_vPos.x < 0)
	{
		return NodeType::Wall;
	}
	return GetNode(_vPos)->m_Type;

}
