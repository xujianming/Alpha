#pragma once

template<class T>
class TInvasiveNode 
{
public:
	TInvasiveNode();
	virtual ~TInvasiveNode();

	TInvasiveNode<T>* Next();
	Remove();

protected:
	TInvasiveNode<T>* m_pNext;

};

template<class T>
class TInvasiveList
{
public:
	TInvasiveList();
	virtual ~TInvasiveList();

	void InsertAfter(TInvasiveNode<T>* pNode);
	void Push(TInvasiveNode<T>* pNode);
	TInvasiveNode<T>* GetFirst();
protected:
	TInvasiveNode<T>* m_pFirst;
};