#pragma once
template <typename T>
class CSingleton
{
public:
	static T * m_pInstacne;
public:
	static T * GetInstance()
	{
		if (m_pInstacne == nullptr)
		{
			m_pInstacne = new T;
		}
		return m_pInstacne;
	}
	static void ReleaseInstance()
	{
		delete m_pInstacne;
		m_pInstacne = nullptr;
	}
};
template <typename T>
T* CSingleton<T>::m_pInstacne = nullptr;
