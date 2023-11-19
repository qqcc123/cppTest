#pragma once

#include <iostream>

template <typename T>
class qc_unique_ptr {
public:
	qc_unique_ptr() : m_data(nullptr) {}
	qc_unique_ptr(T* data) : m_data(data) {}
	qc_unique_ptr(const qc_unique_ptr<T>& data) = delete;
	qc_unique_ptr(qc_unique_ptr<T>&& other) : m_data(other.release()) {}
	qc_unique_ptr& operator= (const qc_unique_ptr<T>&) = delete;

	void reset(T* p = nullptr) noexcept
	{
		if (m_data != p)
		{
			delete m_data;
			m_data = p;
		}
	}

	T* release() noexcept
	{
		auto temp = m_data;
		m_data = nullptr;

		return temp;
	}

	void swap(qc_unique_ptr& x) noexcept
	{
		auto temp = m_data;
		m_data = x.m_data;
		x.m_data = temp;
	}

	qc_unique_ptr& operator= (qc_unique_ptr<T>&& other)
	{	
		if (&other == this)
		{
			return *this;
		}

		reset(other.release());
		return *this;
	}

	T* operator->() const noexcept
	{
		return m_data;
	}

	T& operator* ()
	{
		return *m_data;
	}

	T get() const noexcept
	{
		return *m_data;
	}

	explicit operator bool() const noexcept
	{
		return m_data != nullptr;
	}

private:
	T* m_data;
};