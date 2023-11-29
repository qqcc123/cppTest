#pragma once

template<typename T>
class qc_share_ptr {
public:
	qc_share_ptr() : m_data(nullptr), m_useCount(nullptr) {};
	qc_share_ptr(T* data) : m_data(data)
	{
		if (m_data != nullptr)
		{
			m_useCount = new int;
			(*m_useCount)++;
		}
	}

	//调用拷贝构造函数之前必然会先调用普通构造函数
	qc_share_ptr(const qc_share_ptr<T>& data) : m_data(data.m_data), m_useCount(data.m_useCount)
	{
		if (m_data != nullptr) 
		{
			(*m_useCount)++;
		}
	}

	//移动构造，原对象会销毁，所以目的对象只需要拷贝原始对象的数据即可，引用计数不变
	qc_share_ptr(qc_share_ptr<T>&& data) : m_data(data.m_data), m_useCount(data.m_useCount)
	{
		data.m_data = nullptr;
		data.m_useCount = nullptr;
	}

	T* get()
	{
		return m_data;
	}

	void reset(T* data)
	{
		if (data == m_data)
		{
			return;
		}

		if (m_data != nullptr)
		{
			(*m_useCount)--;
			if (m_useCount <= 0)
			{
				delete m_data;
				delete m_useCount;
			}
		}

		if (data == nullptr)
		{
			m_data = nullptr;
			m_useCount = nullptr;
		}
		else
		{
			m_data = data->m_data;
			m_useCount = new int(1);
		}


		//if (data == nullptr)
		//{
		//	if (m_data != nullptr)
		//	{
		//		(*m_useCount)--;
		//		if (m_useCount <= 0)
		//		{
		//			delete m_data;
		//			delete m_useCount;
		//		}
		//		
		//		m_data = nullptr;
		//		m_useCount = nullptr;
		//	}
		//}
		//else
		//{
		//	if (m_data != nullptr)
		//	{
		//		(*m_useCount)--;
		//		if (m_useCount <= 0)
		//		{
		//			delete m_data;
		//			delete m_useCount;
		//		}

		//		m_data = data->m_data;
		//		m_useCount = new int(1);
		//	}
		//}

		
	}

	int use_count()
	{
		if (m_data == nullptr)
		{
			return 0;
		}

		return *m_useCount;
	}

	bool unique()
	{
		if (m_data == nullptr)
		{
			return false;
		}

		return *m_useCount == 1;
	}

	void swap(qc_share_ptr<T>& data)
	{
		auto tempData = data.m_data;
		auto tempCount = data.m_useCount;
		data.m_data = m_data;
		data.m_useCount = m_useCount;
		m_data = tempData;
		m_useCount = tempCount;
	}

	explicit operator bool() const noexcept
	{
		return m_data != nullptr;
	}

	T* operator->() const
	{
		return m_data;
	}

	T& operator* ()
	{
		return *m_data;
	}

	qc_share_ptr& operator= (const qc_share_ptr<T>& other)
	{
		if (&other == this)
		{
			return *this;
		}

		if (other && other.m_data)
		{
			m_data = other.m_data;
			m_useCount = other.m_useCount;
			(*m_useCount)++;
		}

		return *this;
	}

	//qc_share_ptr& operator= (qc_share_ptr<T>&& other)
	//{
	//	if (&other == this)
	//	{
	//		other.m_data = nullptr;
	//		other.m_useCount = nullptr;
	//	}


	//}


	~qc_share_ptr()
	{
		if (m_data)
		{
			(*m_useCount)--
			if ((*m_useCount) <= 0)
			{
				delete m_data;
				m_data = nullptr;
				delete m_useCount;
				m_useCount = nullptr;
			}
		}
	}



private:
	T* m_data = nullptr;

	int* m_useCount = nullptr;

};