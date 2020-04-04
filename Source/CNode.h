#pragma once
enum NodeType
{
	Wall = 0, 
	Floor, 
	OpenNode
};
enum AStarDir
{
	Bottom,
	Top,
	Right,
	Left,
	RightTop,
	LeftTop,
	RightBottom,
	LeftBottom
};
class CNode
{
	friend class CAStarMap;
public:
	CNode(NodeType _Type);
	~CNode();

	NodeType m_Type;
private:
	CNode* m_pDirectionNode = nullptr;
	Vector2 m_vDir;
	Vector2 m_vPos;

public:
	float F, G, H;
	Vector2 GetDir() { return m_vDir;	}
	Vector2 GetPos() { return m_vPos; }
	CNode* GetDirectionNode() { return m_pDirectionNode; }
	NodeType GetNodeType() { return m_Type; }
	void SetDirection(CNode * _pNode)
	{
		Vector2 Dir = _pNode->GetPos() - GetPos();
		D3DXVec2Normalize(&Dir, &Dir);
		m_vDir = Dir;
		m_pDirectionNode = _pNode;
	}
	list<CNode*> m_listLinkedNode;
};

