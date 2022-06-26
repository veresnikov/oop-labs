#pragma once
#include <algorithm>
#include <new>
#include <stdexcept>

template <typename T> class MyArray
{
	template <bool IsConst> class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;

		IteratorBase(const IteratorBase<false>& other)
			: m_item(other.m_item)
		{
		}

		IteratorBase(T* item)
			: m_item(item)
		{
		}

		reference& operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}

		MyType operator+(difference_type offset) const
		{
			MyType self(m_item);
			return self += offset;
		}

		MyType& operator-=(difference_type offset)
		{
			m_item -= offset;
			return *this;
		}

		MyType operator-(difference_type offset) const
		{
			MyType self(m_item);
			return self -= offset;
		}

		MyType& operator++()
		{
			return *this += 1;
		}

		MyType operator++(int)
		{
			auto self = *this;
			++(*this);
			return self;
		}

		MyType& operator--()
		{
			return *this -= 1;
		}

		MyType operator--(int)
		{
			auto self = *this;
			--(*this);
			return self;
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}

	protected:
		T* m_item = nullptr;
	};

public:
	MyArray() = default;

	MyArray(const MyArray& arr)
	{
		const size_t size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	MyArray(MyArray&& other) noexcept
		: m_begin(other.m_begin)
		  , m_end(other.m_end)
		  , m_endOfCapacity(other.m_endOfCapacity)
	{
		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_endOfCapacity = nullptr;
	}

	~MyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	MyArray& operator=(const MyArray& other)
	{
		if (std::addressof(other) != this)
		{
			MyArray copy(other);
			std::swap(m_begin, copy.m_begin);
			std::swap(m_end, copy.m_end);
			std::swap(m_endOfCapacity, copy.m_endOfCapacity);
		}
		return *this;
	}

	MyArray& operator=(MyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			DeleteItems(m_begin, m_end);
			m_begin = other.m_begin;
			m_end = other.m_end;
			m_endOfCapacity = other.m_endOfCapacity;

			other.m_begin = nullptr;
			other.m_end = nullptr;
			other.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	const T& operator[](size_t index) const
	{
		checkIndex(index);
		return m_begin[index];
	}

	T& operator[](size_t index)
	{
		checkIndex(index);
		return m_begin[index];
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			Resize(std::max(static_cast<size_t>(1), GetCapacity() * 2));
			new (m_end) T(value);
			++m_end;
		}
		else // has free space
		{
			new(m_end) T(value);
			++m_end;
		}
	}

	void Resize(size_t size)
	{
		auto newBegin = RawAlloc(size);
		T* newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			auto empty = size - (newEnd - newBegin);
			if (empty != 0)
			{
				T* copyEnd = newEnd;
				for (size_t i = 0; i < empty; ++i)
				{
					new (copyEnd) T();
					++copyEnd;
				}
			}
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + size;
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_begin = nullptr;
		m_end = nullptr;
		m_endOfCapacity = nullptr;
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator begin()
	{
		return m_begin;
	}

	iterator end()
	{
		return m_end;
	}

	const_iterator begin() const
	{
		return m_begin;
	}

	const_iterator end() const
	{
		return m_end;
	}

	const_iterator cbegin() const
	{
		return m_begin;
	}

	const_iterator cend() const
	{
		return m_end;
	}

	using reverse_iterator = std::reverse_iterator<IteratorBase<false>>;
	using const_reverse_iterator = std::reverse_iterator<IteratorBase<true>>;

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator crend() const
	{
		return const_reverse_iterator(begin());
	}

private:
	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);

		RawDealloc(begin);
	}

	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new(dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}

	void checkIndex(const size_t index) const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("index out of range");
		}
	}

	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};
