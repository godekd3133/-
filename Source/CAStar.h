#pragma once
class CAStar
{
public:
	CAStar(vector<vector<CNode*>>& _Map);
	~CAStar();

private:
	vector < vector<CNode*>>& m_Map;
public:
	list<CNode *> GetAdjacencyNodes(CNode * _pSelectNode);
	void SetParentNode(CNode * _pSelectNode, CNode * _pParentNode, CNode * _pStartNode, CNode * _pEndNode);

	vector<CNode*> GetAstarRoute(CNode * _pStartNode, CNode * _pEndNode);
	float GetG(CNode * _pSelectNode, CNode * _pStartNode);
	float GetH(CNode * _pSelectNode, CNode * _vEndPos);
	vector<CNode*> UpdateOpenNodes(CNode * _pSelNode,CNode * _pStartNode,CNode * _pEndNode,vector<CNode*>&  _vecOpenNodes, vector<CNode*>&  _vecCloseNodes);
	CNode * GetNode(int _iX, int _iY);
	CNode * GetNode(Vector2 _vPos);
	int GetWidth() { return m_Map[0].size();}
	int GetHeight() { return m_Map.size(); }

	NodeType GetNodeType(int _iX, int _iY);
	NodeType GetNodeType(Vector2 _vPos);
};						

