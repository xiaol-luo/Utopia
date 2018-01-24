#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <sol.hpp>
#include "TryUserTypeUtil.h"

namespace TryUserType
{
	enum UnitType
	{
		UnitType_Unknown,
		UnitType_Animal,
		UnitType_Plant,
	};
	template <typename T>
	static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
	{
		assert(false);
	}

	template <>
	static void DoLuaBind<UnitType>(lua_State *L, const std::string &name_space, const std::string &name)
	{
		std::string enum_name = !name.empty() ? name : "UnitType";
		sol::state_view lua(L);
		sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
		{
			sol::optional<sol::object> opt_object = ns_table[enum_name];
			assert(!opt_object);
		}
		ns_table.new_enum(enum_name, 
			"UnitType_Unknown", UnitType::UnitType_Unknown,
			"UnitType_Animal", UnitType::UnitType_Animal,
			"UnitType_Plant", UnitType::UnitType_Plant
			);
	}

	struct DynamicObject
	{
		std::unordered_map<std::string, sol::object> entries;

		void DynamicSet(std::string key, sol::stack_object value)
		{
			auto it = entries.find(key);
			if (it == entries.cend()) {
				entries.insert(it, { std::move(key), std::move(value) });
			}
			else {
				std::pair<const std::string, sol::object>& kvp = *it;
				sol::object& entry = kvp.second;
				entry = sol::object(std::move(value));
			}
		}
		
		sol::object DynamicGet(std::string key)
		{
			auto it = entries.find(key);
			if (it == entries.end())
				return sol::nil;
			return it->second;
		}

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");
	};

	class Unit;
	class Scene
	{
	public:
		Scene();
		~Scene();

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");
	public:
		void Tick();
		void Start();
		bool IsDone();
		void SetIsDone(bool _is_done);

		/*
		bool AddUnit(std::string name, Unit *unit);
		void RemoveUnit(std::string name);
		Unit * FindUnit(std::string name);
		*/
	protected:
		bool is_done = true;

	protected:
		sol::function lua_fn_tick;
		sol::function lua_fn_start;
		DynamicObject params;
	};

	class Unit
	{
	public:
		Unit(UnitType _unit_type, const std::string &_name, float _pos) : unit_type(_unit_type), name(_name), pos(_pos) {}
		virtual ~Unit() {}

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");

	public:
		UnitType GetUnitType();
		const std::string & GetName();
		float GetPos();
		void SetPos(float _pos);
		bool GetIsDead();
		void SetIsDead(bool _is_dead);
		Scene * GetScene();
		void SetScene(Scene *_scene);

	protected:
		UnitType unit_type = UnitType::UnitType_Unknown;
		std::string name;
		float pos = 0;
		bool is_dead = false;
		Scene *scene = nullptr;
	};

	class Plant : public Unit
	{
	public:
		Plant(std::string _name, float _pos, int _recover_hp, int _recover_energy);
		virtual ~Plant();

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");

	public:
		int GetRecoverHp();
		void SetRecoverHp(int _recover_hp);
		int GetRecoverEnergy();
		void SetRecoverEnergy(int _recover_energy);

	protected:
		int recover_hp = 0;
		int recover_energy = 0;
	};

	class Animal;
	class Foot
	{
	public: 
		Foot(Animal *_animal, float _move_speed);
		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");

		void Run();

	protected:
		Animal *animal = nullptr;
		float move_speed = 0;
	};

	class Animal : public Unit
	{
	public:
		Animal(std::string name, float _pos, int _hp, int _energy, float _move_speed);
		virtual ~Animal();
		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");

	public: 
		virtual void TryAction();

	protected:
		void Run();
		void Rest();

	public:
		int GetHP();
		void SetHp(int _hp);
		int GetEnergy();
		void SetEnergy(int _energy);
		Foot * GetFoot();

	protected:
		Foot *foot;
		int hp = 0;
		int energy = 0;
	};

	class Wolf : public Animal
	{
	public:
		Wolf(std::string _name, float _pos, int _hp, int _energy, float _move_speed, float _attack, float _attack_range);
		virtual ~Wolf();

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");
		virtual void TryAction() override;
		bool TryBite(Animal *animal);

	public:
		int GetAttack();
		void SetAttack(int _attack);
		float GetAttackRange();
		void SetAttackRange(float _attack_range);

	protected:
		int attack = 0;
		float attack_range = 0;
	};

	class Sheep : public Animal
	{
	public:
		Sheep(std::string _name, float _pos, int _hp, int _energy, float _move_speed, float _eat_plant_range);
		virtual ~Sheep();

	public:
		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name = "");
		virtual void TryAction() override;
		bool TryEatPlant(Plant *plant);

	public:
		float GetEatPlantRange();
		void SetEatPlantRange(float _eat_plant_range);

	protected:
		float eat_plant_range = 0;
	};

	void RegisterUserType();
}
