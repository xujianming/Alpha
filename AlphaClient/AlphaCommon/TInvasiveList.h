/************************************************************************/
/* À´∂À«÷»Î Ω¡¥±Ì                                                                     */
/************************************************************************/

#pragma once

template<class T>
class TInvasiveList;

template<class T>
class TInvasiveNode 
{
public:
	friend class TInvasiveList<T>;

	TInvasiveNode():m_pPre(nullptr),m_pNext(nullptr){};
	virtual ~TInvasiveNode(){}

	T* Next(){	return (m_pNext && m_pNext->Next()) ? static_cast<T*>(m_pNext) : nullptr; }

	T* Pre(){	return (m_pNext && m_pNext->Pre()) ? static_cast<T*>(m_pPre) : nullptr; }

	bool IsInlist(){ return m_pPre || m_pNext;}

	void Remove()
	{
		if (!IsInlist())
			return;
		m_pPre->m_pNext = m_pNext;
		m_pNext->m_pPre = m_pPre;
	}

private:
	TInvasiveNode* m_pNext;
	TInvasiveNode* m_pPre;
};


template<class T>
class TInvasiveList
{
	TInvasiveList(const TInvasiveList&);
	const TInvasiveList& operator = (const TInvasiveList&);
public:
	TInvasiveList()
	{
		m_Head.m_pPre = nullptr;
		m_Tail.m_pNext = nullptr;
		m_Head.m_pNext = &m_Tail;
		m_Tail.m_pPre = &m_Head;
	}

	virtual ~TInvasiveList() {}

	void InsertAfter(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node)
	{
		Node.m_pPre = &NodePos;
		Node.m_pNext = NodePos.m_pNext;
		NodePos.m_pNext->m_pPre = &Node;
		NodePos->m_pNext = &Node;
	}

	void InsertBefore(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node)
	{
		Node.m_pPre = NodePos.m_pPre;
		Node.m_pNext = &NodePos;
		NodePos.m_pPre->m_pNext = &Node;
		Node.m_pPre = &Node;
	}

	void PushBack(TInvasiveNode<T>& Node)
	{
		InsertBefore(m_Tail, Node);
	}

	void PushFront(TInvasiveNode<T>& Node)
	{
		InsertAfter(m_Head, Node);
	}

	T* GetFirst()
	{
		if (IsEmpty())
			return nullptr;
		return static_cast<T*>(m_Head.m_pNext);
	}
	T* GetLast()
	{
		if (IsEmpty())
			return nullptr;
		return static_cast<T*>(m_Tail.m_pPre);
	}

	bool IsEmpty(){ return m_Head.m_pNext == &m_Tail; }

private:
	TInvasiveNode<T> m_Head;
	TInvasiveNode<T> m_Tail;
};
