#include "stdafx.h"
#include "TInvasiveList.h"

template<class T>
TInvasiveNode<T>::~TInvasiveNode()
{

}

template<class T>
TInvasiveNode<T>::TInvasiveNode():
	m_pPre(nullptr),
	m_pNext(nullptr)
{

}

template<class T>
void TInvasiveNode<T>::Remove()
{
	if (!IsInlist())
		return;
	m_pPre->m_pNext = m_pNext;
	m_pNext->m_pPre = m_pPre;
}

template<class T>
bool TInvasiveNode<T>::IsInlist()
{
	return m_pPre || m_pNext;
}

template<class T>
T* TInvasiveNode<T>::Next()
{
	return static_cast<T*>(m_pNext);
}

template<class T>
T* TInvasiveNode<T>::Pre()
{
	return static_cast<T*>(m_pPre);
}


template<class T>
TInvasiveList<T>::~TInvasiveList()
{

}

template<class T>
TInvasiveList<T>::TInvasiveList()
{
	m_Head.m_pPre = nullptr;
	m_Tail..m_pNext = nullptr;
	m_Head.m_pNext = &m_pTail;
	m_Tail.m_pPre = &m_pHead;
}

template<class T>
void TInvasiveList<T>::InsertAfter(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node)
{
	Node.m_pPre = &NodePos;
	Node.m_pNext = NodePos.m_pNext;
	NodePos.m_pNext->m_pPre = &Node;
	NodePos->m_pNext = &Node;
}

template<class T>
void TInvasiveList<T>::InsertBefore(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node)
{
	Node.m_pPre = NodePos.m_pPre;
	Node.m_pNext = &NodePos;
	NodePos.m_pPre->m_pNext = &Node;
	Node.m_pPre = &Node;
}

template<class T>
void TInvasiveList<T>::PushBack( TInvasiveNode<T>& Node)
{
	InsertBefore(m_pTail, Node);
}

template<class T>
void PushFront(TInvasiveNode<T>& Node)
{
	InsertAfter(m_Head, Node);
}

template<class T>
T* TInvasiveList<T>::GetFirst()
{
	if (m_Head.m_pNext == &m_pTail)
		return nullptr;
	return static_cast<T*>(m_Head.m_pNext);
}

template<class T>
T* TInvasiveList<T>::GetLast()
{
	if (m_Head.m_pNext == &m_pTail)
		return nullptr;
	return static_cast<T*>(m_Tail.m_pPre);
}