#pragma once

#include <functional>
#include <unordered_map>
#include <assert.h>

class EventDispacher
{
private:
	class SubcribeDataBase
	{
	public:
		const static uint32_t INVALID_ID = 0;

		SubcribeDataBase() {}
		virtual ~SubcribeDataBase() { this->Release(); }
		virtual void Release() {};
		virtual void Remove(uint32_t id) = 0;
		virtual size_t Count() = 0;
		uint32_t next_id = 0;

		std::unordered_map<uint32_t, void*> fs_ptr;
		template <typename... Params>
		void ForeachFs(Params... params)
		{
			for (auto &&kv_pair : fs_ptr)
			{
				auto fn = (std::function<void(Params...)> *)(kv_pair.second);
				(*fn)(params...);
			}
		}
	};

public:
	EventDispacher();
	~EventDispacher();


	void Cancel(int64_t subscribe_id)
	{
	}

private:
	std::unordered_map<int, SubcribeDataBase *> m_subscribes;
};
