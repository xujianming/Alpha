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

}

template<class T>
T* TInvasiveNode<T>::Next()
{
	return m_pNext;
}

template<class T>
TInvasiveList<T>::~TInvasiveList()
{

}

template<class T>
TInvasiveList<T>::TInvasiveList():
	m_pHead(nullptr),
	m_pTail(nullptr)
{

}

template<class T>
void TInvasiveList<T>::Push( T* pNode )
{
	InsertAfter(m_pTail, pNode);
}

template<class T>
void TInvasiveList<T>::InsertAfter(T* pCurNode,  T* pNode )
{
	if (pCurNode == nullptr)
	{
		m_pHead = m_pTail = pNode;
		return;
	}
	pNode->m_pPre = pCurNode;
	pNode->m_pNext = pCurNode->m_pNext;
	if (pCurNode->m_pNext)
		pCurNode->m_pNext->m_pPre = pNode;
	pCurNode->m_pNext = pNode;
	if (!pCurNode->m_pNext)
		m_pTail = pCurNode;
}

template<class T>
T* TInvasiveList<T>::GetFirst()
{
	return m_pHead;
}
