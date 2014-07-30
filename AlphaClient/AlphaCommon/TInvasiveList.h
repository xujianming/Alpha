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

	TInvasiveNode();
	virtual ~TInvasiveNode();

	T* Next();
	T* Pre();

	void Remove();
	bool IsInlist();

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
	TInvasiveList();
	virtual ~TInvasiveList();

	void InsertAfter(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node);
	void InsertBefore(TInvasiveNode<T>& NodePos, TInvasiveNode<T>& Node);
	void PushBack(TInvasiveNode<T>& Node);
	void PushFront(TInvasiveNode<T>& Node);
	T* GetFirst();
	T* GetLast();
private:
	TInvasiveNode<T> m_Head;
	TInvasiveNode<T> m_Tail;
};
