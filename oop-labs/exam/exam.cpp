#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// *Односвязный* список строк
class CStringList
{
	struct Item
	{
		Item(const string& value, unique_ptr<Item>&& next)
			: value(value), next(std::move(next))
		{
		}

		string value;
		unique_ptr<Item> next;
	};

public:
	CStringList() = default;

	CStringList(const CStringList& list)
	{
		Copy(list);
	}

	~CStringList()
	{
		while (m_begin != nullptr)
		{
			m_begin = std::move(m_begin->next);
		}
	}

	CStringList& operator=(const CStringList& list)
	{
		Copy(list);
		return *this;
	}

	// Добавляет строку в начало списка. Время выполнения: O(1)
	void AddToBegin(const string& value)
	{
		m_begin = make_unique<Item>(value, std::move(m_begin));
		++m_size;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	// Возвращает первый элемент списка. Бросает logic_error, если список пуст
	// Время выполнения: O(1)
	const string& GetFront() const
	{
		if (m_size == 0)
		{
			throw logic_error("list is empty");
		}
		return m_begin->value;
	}

	// Выводит элементы списка в out (по одному в каждой строке)
	void PrintList(ostream& out) const
	{
		const Item* item = m_begin.get();
		while (item != nullptr)
		{
			out << item->value << endl;
			item = item->next.get();
		}
	}

	// Очищает список
	void Clear()
	{
		Item* item = m_begin.get();
		while (item != nullptr)
		{
			item->value.clear();
		}
	}

private:
	size_t m_size = 0;
	unique_ptr<Item> m_begin;

	void Copy(const CStringList& list)
	{
		Item* item = list.m_begin.get();
		unique_ptr<Item> newList;
		Item* lastItem = nullptr;
		size_t newSize = 0;
		while (item != nullptr)
		{
			if (newList == nullptr)
			{
				newList = make_unique<Item>(item->value, nullptr);
				++newSize;
				lastItem = newList.get();
				item = item->next.get();
				continue;
			}
			if (lastItem)
			{
				lastItem->next = make_unique<Item>(item->value, nullptr);
				++newSize;
				lastItem = lastItem->next.get();
			}
			else
			{
				throw runtime_error("error in copy process");
			}
			item = item->next.get();
		}
		unique_ptr<Item> oldList = std::move(m_begin);
		while (oldList != nullptr)
		{
			oldList = std::move(oldList->next);
		}

		m_begin = move(newList);
		m_size = newSize;
	}

};

int main()
{
	CStringList lst;
	lst.AddToBegin("one");
	lst.AddToBegin("two");
	lst.AddToBegin("three");
	assert(lst.GetSize() == 3);
	assert(lst.GetFront() == "three");
	CStringList lst1(lst);
	lst1.PrintList(cout); // Должно быть выведено: three two one (по одному слову в каждой строке)
	cout << endl;
	lst1.AddToBegin("four");
	lst.PrintList(cout); // Должно быть выведено: three two one (по одному слову в каждой строке)
	cout << endl;
	CStringList lst2;
	lst2 = lst1;
	lst2.PrintList(cout); // Должно быть выведено: four three two one (по одному слову в каждой строке)
	cout << endl;

	CStringList stress;
	for (int i = 0; i < 1000000; ++i)
	{
		stress.AddToBegin(std::to_string(i));
	}
	return 0;
}
