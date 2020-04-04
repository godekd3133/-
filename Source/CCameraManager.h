#pragma once
class CCameraManager : public
	CSingleton< CCameraManager>
{
public:
	CCameraManager();
	~CCameraManager();

private:
	Vector2 m_vPos;
	Matrix m_matView;
	Matrix m_matProj;
	float m_fSpeed = 350.f;

	Vector2 m_vMinPos;
	Vector2 m_vMaxPos;
public:
	int Width;
	int Height;
	Vector2 GetPos() { return m_vPos; }
	void Update();
	void SetTransform();
	void SetRect(Vector2 _vMinPos, Vector2 _vMaxPos);
};
#define CAMERA (*CCameraManager::GetInstance())
