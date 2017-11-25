#pragma once

#include <functional>
#include <unordered_map>
#include <assert.h>

class EventDispacher
{
public:
	static const uint64_t INVALID_ID = 0;
	union SubscribeId
	{
		struct 
		{
			int event_id;
			int f_key;
		};
		uint64_t id;
	};

public:
	EventDispacher();
	~EventDispacher();

	template <typename... Args>
	void Fire(int id, Args... args)
	{
		auto it = m_subscribes.find(id);
		if (m_subscribes.end() == it)
			return;

		SubscribeData<Args...> *subscribe = dynamic_cast<SubscribeData<Args...> *>(it->second);
		assert(subscribe); // 如果不能动态转换，那么肯定是Args...和之前设置的类型不匹配，要检查
		subscribe->ForeachFs(args...);
	}

	template <typename Ret, typename...Args>
	int64_t Subscribe(int id, std::function<Ret(Args...)> f)
	{
		auto it = m_subscribes.find(id);
		if (m_subscribes.end() == it)
		{
			bool ret = false;
			std::tie(it, ret) = m_subscribes.insert(std::make_pair(id, new SubscribeData<Args...>()));
			if (!ret) return INVALID_ID;
		}
		SubscribeData<Args...> *subscribe = dynamic_cast<SubscribeData<Args...> *>(it->second);
		assert(subscribe); // 如果不能动态转换，那么肯定是Args...和之前设置的类型不匹配，要检查
		uint32_t f_key = subscribe->Add(f);
		if (SubcribeDataBase::INVALID_ID == f_key)
			return INVALID_ID;

		SubscribeId sid;
		sid.event_id = id;
		sid.f_key = f_key;
		return sid.id;
	}
	
	template <typename...Args, typename F>
	int64_t Subscribe(int id, F f)
	{
		std::function<void(Args...)> stl_f = f;
		return this->Subscribe(id, stl_f);
	}
	

	void Cancel(int64_t subscribe_id)
	{
		SubscribeId sid;
		sid.id = subscribe_id;

		auto it = m_subscribes.find(sid.event_id);
		if (m_subscribes.end() != it)
		{
			SubcribeDataBase *sdb = it->second;
			sdb->Remove(sid.f_key);
		}
	}

private:
	class SubcribeDataBase 
	{
	public:
		const static uint32_t INVALID_ID = 0;
	public:
		SubcribeDataBase() {}
		virtual ~SubcribeDataBase() { this->Release(); }
		virtual void Release() {};
		virtual void Remove(uint32_t id) = 0;
		virtual size_t Count() = 0;
		uint32_t next_id = 0;
	};

	template <typename...Args>
	class SubscribeData : public SubcribeDataBase
	{
	public:
		using stl_function_type = std::function<void(Args...)>;
		std::unordered_map<uint32_t, stl_function_type> fs;
		void ForeachFs(Args... args)
		{
			for (auto &&kv_pair : fs)
				kv_pair.second(args...);
		}
		uint32_t Add(stl_function_type f)
		{
			++next_id;
			(INVALID_ID == next_id) ? next_id = 1 : 0;
			bool ret = false;
			std::tie(std::ignore, ret) = fs.insert(std::make_pair(next_id, f));
			return ret ? next_id : INVALID_ID;
		}
		virtual void Remove(uint32_t id) override
		{
			fs.erase(id);
		}
		virtual size_t Count() override
		{
			return fs.size();
		}
		virtual void Release() override
		{
			fs.clear();
		}
	};

	std::unordered_map<int, SubcribeDataBase *> m_subscribes;
};
