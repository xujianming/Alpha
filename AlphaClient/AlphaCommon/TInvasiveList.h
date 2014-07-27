#pragma once

template<class T>
class TInvasiveNode 
{
public:
	friend class TInvasiveList<T>;

	TInvasiveNode();
	virtual ~TInvasiveNode();

	TInvasiveNode<T>* NextNode();
	void Remove();

protected:
	TInvasiveNode<T>* m_pNext;
	TInvasiveNode<T>* m_pPre;
};


template<class T>
class TInvasiveList
{
public:
	TInvasiveList();
	virtual ~TInvasiveList();

	void InsertAfter(T* pCurNode, T* pNode);
	void Push(T* pNode);
	T* GetFirst();
protected:
	T* m_pHead;
	T* m_pTail;
};
