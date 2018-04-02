#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SortList
{
private:
	struct element
	{
	T data;
	element* prev;
	element* next;
	};

	element* head;
	element* tail;

	int curSize;
	const int fullSize = 1000;

public:

	class Iterator
	{
	private:
		element* It;
	public:
		Iterator()
		{
			It = 0;
		}
		Iterator(element* val)
		{
			It = val;
		}
		T& operator*() const
		{
			return It->data;
		}
		Iterator operator++()
		{
			Iterator temp(It);
			It = It->next;
			return temp;
		}
		Iterator operator++(int)
		{
			It = It->next;
			return It;
		}
		Iterator operator--()
		{
			Iterator temp(It);
			It = It->prev;
			return temp;
		}
		Iterator operator--(int)
		{
			It = It->prev;
			return It;
		}
		bool operator==(Iterator it)
		{
			return It == it.It;
		}
		bool operator!=(Iterator it)
		{
			return !(It == it.It);
		}
	};

	class rIterator
	{
	private:
		element* It;
	public:
		rIterator()
		{
			It = 0;
		}
		rIterator(element* val)
		{
			It = val;
		}
		T& operator*() const
		{
			return It->data;
		}
		rIterator operator++()
		{
			rIterator temp(It);
			It = It->prev;
			return temp;
		}
		rIterator operator++(int)
		{
			It = It->prev;
			return It;
		}
		rIterator operator--()
		{
			rIterator temp(It);
			It = It->next;
			return temp;
		}
		rIterator operator--(int)
		{
			It = It->next;
			return It;
		}
		bool operator==(rIterator it)
		{
			return It == it.It;
		}
		bool operator!=(rIterator it)
		{
			return !(It == it.It);
		}
	};

	class const_Iterator
	{
	private:
		element* It;
	public:
		const_Iterator()
		{
			It = 0;
		}
		const_Iterator(element* val)
		{
			It = val;
		}
		const T& operator*() const
		{
			return It->data;
		}
		const_Iterator operator++()
		{
			const_Iterator temp(It);
			It = It->next;
			return temp;
		}
		const_Iterator operator++(int)
		{
			It = It->next;
			return It;
		}
		const_Iterator operator--()
		{
			const_Iterator temp(It);
			It = It->prev;
			return temp;
		}
		const_Iterator operator--(int)
		{
			It = It->prev;
			return It;
		}
		bool operator==(const_Iterator it)
		{
			return It == it.It;
		}
		bool operator!=(const_Iterator it)
		{
			return !(It == it.It);
		}
	};

	class const_rIterator
	{
	private:
		element* It;
	public:
		const_rIterator()
		{
			It = 0;
		}
		const_rIterator(element* val)
		{
			It = val;
		}
		const T& operator*() const
		{
			return It->data;
		}
		const_rIterator operator++()
		{
			const_rIterator temp(It);
			It = It->prev;
			return temp;
		}
		const_rIterator operator++(int)
		{
			It = It->prev;
			return It;
		}
		const_rIterator operator--()
		{
			const_rIterator temp(It);
			It = It->next;
			return temp;
		}
		const_rIterator operator--(int)
		{
			It = It->next;
			return It;
		}
		bool operator==(const_rIterator it) const
		{
			return It == it.It;
		}
		bool operator!=(const_rIterator it) const
		{
			return !(It == it.It);
		}
	};

	SortList()
	{
		head = NULL;
		tail = NULL;
		curSize = 0;
		return;
	};
	SortList(T newdata)
	{
		insert(newdata);
		return;
	}
	~SortList()
	{
		while (head && head != tail)
		{
			head = head->next;
			delete(head->prev);
		}
		if (head)
		{
			delete(head);
		}
		head = NULL;
		tail = NULL;
		curSize = 0;
		return;
	}

	Iterator begin() const
	{
		return Iterator(head);
	}
	Iterator end() const
	{
		return Iterator(tail->next);
	}
	rIterator rbegin() const
	{
		return rIterator(tail);
	}
	rIterator rend() const
	{
		return rIterator(head->prev);
	}

	const_Iterator cbegin() const
	{
		return const_Iterator(head);
	}
	const_Iterator cend() const
	{
		return const_Iterator(tail->next);
	}
	const_rIterator crbegin() const
	{
		return const_rIterator(tail);
	}
	const_rIterator crend() const
	{
		return const_rIterator(head->prev);
	}
	
	int size() const
	{
		return curSize;
	}
	int maxSize() const
	{
		return fullSize;
	}
	bool empty() const
	{
		return size == 0;
	}

	void insert(T newdata)
	{
		if (curSize == fullSize)
		{
			return;
		}
		
		element* newEl = new element;

		newEl->data = newdata;
		newEl->prev = NULL;
		newEl->next = NULL;

		if (!head)
		{
			head = newEl;
			tail = newEl;
		}
		else
		{
			element* l = head;

			while (l && l->data <= newEl->data)
				l = l->next;

			if (!l)
			{
				tail->next = newEl;
				newEl->prev = tail;
				tail = newEl;
			}
			else if (l == head)
			{
				head = newEl;
				head->next = l;
				l->prev = head;
			}
			else
			{
				newEl->prev = l->prev;
				l->prev->next = newEl;
				newEl->next = l;
				l->prev = newEl;
			}
		}

		++curSize;

		return;
	};
	void erase(T data)
	{
		element* el = head;
		while (el && el->data != data)
		{
			el = el->next;
		}
		while (el && el->data == data)
		{
			element* tmp = el;
			if (el->prev)
			{
				el->prev->next = el->next;
			}
			if (el->next)
			{
				el->next->prev = el->prev;
			}
			if (tmp == head)
			{
				head = el->next;
			}
			if (tmp == tail)
			{
				tail = el->prev;
			}
			el = el->next;
			delete(tmp);
			--curSize;
		}
		return;
	}

	bool operator==(SortList<T> const& l) const
	{
		if (size() != l.size())
		{
			return 0;
		}
		Iterator i = begin();
		Iterator j = l.begin();
		while (i != end())
		{
			if (*i != *j)
			{
				return 0;
			}
			++i;
			++j;
		}
		return 1;
	};
	bool operator!=(SortList<T> const& l) const
	{
		return !(*this == l);
	};
	bool operator>(SortList<T> const& l) const
	{
		Iterator i = begin();
		Iterator j = l.begin();
		while (i != end() && j != l.end())
		{
			if (*i > *j)
			{
				return 1;
			}
			else if (*i < *j)
			{
				return 0;
			}
			++i;
			++j;
		}
		if (size() > l.size())
		{
			return 1;
		}
		return 0;
	};
	bool operator<(SortList<T> const& l) const
	{
		Iterator i = begin();
		Iterator j = l.begin();
		while (i != end() && j != l.end())
		{
			if (*i < *j)
			{
				return 1;
			}
			else if (*i > *j)
			{
				return 0;
			}
			++i;
			++j;
		}
		if (size() < l.size())
		{
			return 1;
		}
		return 0;
	};
	bool operator>=(SortList<T> const& l) const
	{
		return !(*this < l);
	};
	bool operator<=(SortList<T> const& l) const
	{
		return !(*this > l);
	};
};

int main()
{
#if 0
	SortList<int> l;
	int i;
	int j = 0;
	
	while (true)
	{
		cin >> i;
		l.insert(i);
		SortList<int>::const_Iterator it;
		for (it = l.cbegin(); it != l.cend(); it++)
		{
			cout << *it << " ";
		}
		printf("\n");
		/*if (j == 3)
		{
			cout << "delete: ";
			cin >> i;
			l.erase(i);
			j = 0;
		}
		++j;*/
	}
	
	SortList<int> li1(1);
	SortList<int> li2(2);
	
	cout << (li1 == li2) << endl;
	cout << (li1 != li2) << endl;
	cout << (li1 > li2) << endl;
	cout << (li1 < li2) << endl;
	cout << (li1 >= li2) << endl;
	cout << (li1 <= li2) << endl << endl;

	SortList<string> l1("str1");
	SortList<string> l2("str2");
#endif
	//l1.insert("strstr");
	SortList<wstring> l3;
	
	l3.insert(L"def");
	l3.insert(L"abc");
	l3.insert(L"sdfer");
	l3.insert(L"abc");
	l3.insert(L"234h2j34j2");


	for (SortList<wstring>::const_rIterator itt = l3.crbegin(); itt != l3.crend(); ++itt)
	{
		wcout << *itt << endl;
	}

	//cout << (l1 == l2) << endl;
	//cout << (l1 != l2) << endl;
	//cout << (l1 > l2) << endl;
	//cout << (l1 < l2) << endl;
	//cout << (l1 >= l2) << endl;
	//cout << (l1 <= l2) << endl;

	return 0;
}