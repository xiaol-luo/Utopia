#include "TryUserType.h"
#include <assert.h>
#include "TryUserTypeUtil.h"
#include <string.h>

extern lua_State * MainLua();

namespace TryUserType
{
	Wolf::Wolf(std::string _name, float _pos, int _hp, int _energy, float _move_speed, float _attack, float _attack_range)
		: Animal(_name, _pos, _hp, _energy, _move_speed), attack(_attack), attack_range(_attack_range)
	{
		foot = new Foot(this, _move_speed);
	}

	Wolf::~Wolf()
	{
	}

	void Wolf::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Wolf";
		sol::usertype<Wolf> meta_table(
			sol::constructors<Wolf(std::string, float, int, int, float, float, float)>(),
			"attack_range", &Wolf::attack_range,
			"attack", &Wolf::attack,
			"TryBite", &Wolf::TryBite,
			sol::base_classes, sol::bases<Animal, Unit>()
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	void Wolf::TryAction()
	{

	}

	bool Wolf::TryBite(Animal * animal)
	{
		if (nullptr == animal || animal->GetIsDead())
			return false;
		if (energy <= 0 || pos + attack_range < animal->GetPos())
			return false;

		--energy;
		int hp = animal->GetHP() - attack;
		if (hp < 0)
		{
			hp = 0;
			animal->SetIsDead(true);
		}
		animal->SetHp(hp);
		return true;
	}

	int Wolf::GetAttack()
	{
		return attack;
	}

	void Wolf::SetAttack(int _attack)
	{
		attack = _attack;
	}

	float Wolf::GetAttackRange()
	{
		return attack_range;
	}

	void Wolf::SetAttackRange(float _attack_range)
	{
		attack_range = _attack_range;
	}

	Scene::Scene()
	{
		sol::state_view lua(MainLua());
		lua_fn_tick = lua["TryUserType"]["Scene"]["LuaTick"]; 
		lua_fn_start = lua["TryUserType"]["Scene"]["LuaStart"];

		assert(lua_fn_tick.valid());
		assert(lua_fn_start.valid());
	}

	Scene::~Scene()
	{
	}

	void Scene::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Scene";
		sol::usertype<Scene> meta_table(
			sol::constructors<Scene()>(),
			"Tick", &Scene::Tick,
			"is_done", sol::property(&Scene::IsDone, &Scene::SetIsDone),
			"Start", &Scene::Start,
			"params", &Scene::params
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	void Scene::Tick()
	{
		printf("-- C++ Scene Tick \n");
		// lua_fn_tick(this, 1024);
		lua_fn_tick.call(this);
	}

	void Scene::Start()
	{
		printf("-- C++ Scene Start \n");
		is_done = false;
		lua_fn_start(this);
	}

	bool Scene::IsDone()
	{
		return is_done;
	}

	void Scene::SetIsDone(bool _is_done)
	{
		is_done = _is_done;
	}

	void Unit::DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
	{
		std::string class_name = !name.empty() ? name : "Unit";
		sol::usertype<Unit> meta_table(
			sol::constructors<Unit(UnitType, const std::string&, float)>(),
			"unit_type", sol::property(&Unit::GetUnitType),
			"name", sol::property(&Unit::GetName),
			"pos", sol::property(&Unit::GetPos, &Unit::SetPos),
			"is_dead", sol::property(&Unit::GetIsDead, &Unit::SetIsDead),
			"scene", sol::property(&Unit::GetScene, &Unit::SetScene)
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	UnitType Unit::GetUnitType()
	{
		return UnitType();
	}

	const std::string & Unit::GetName()
	{
		return name;
	}

	float Unit::GetPos()
	{
		return pos;
	}	
	void Unit::SetPos(float _pos)
	{
		pos = _pos;
	}

	bool Unit::GetIsDead()
	{
		return is_dead;
	}

	void Unit::SetIsDead(bool _is_dead)
	{
		is_dead = _is_dead;
	}

	Scene * Unit::GetScene()
	{
		return scene;
	}

	void Unit::SetScene(Scene * _scene)
	{
		scene = _scene;
	}

	Plant::Plant(std::string _name, float _pos, int _recover_hp, int _recover_energy)
		: Unit(UnitType::UnitType_Plant, _name, _pos), recover_hp(_recover_hp), recover_energy(_recover_energy)
	{

	}

	Plant::~Plant()
	{
	}

	void Plant::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Plant";
		sol::usertype<Plant> meta_table(
			sol::constructors<Plant(std::string, float, int, int)>(),
			"recover_energy", &Plant::recover_energy,
			"recover_hp", &Plant::recover_hp,
			sol::base_classes, sol::bases<Unit>()
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	int Plant::GetRecoverHp()
	{
		return recover_hp;
	}

	void Plant::SetRecoverHp(int _recover_hp)
	{
		recover_hp = _recover_hp;
	}

	int Plant::GetRecoverEnergy()
	{
		return recover_hp;
	}

	void Plant::SetRecoverEnergy(int _recover_energy)
	{
		recover_hp = _recover_energy;
	}

	Foot::Foot(Animal * _animal, float _move_speed) : animal(_animal), move_speed(_move_speed)
	{
		assert(animal && move_speed > 0);
	}

	void Foot::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Foot";
		sol::usertype<Foot> meta_table(
			sol::constructors<Foot(Animal*, float)>(),
			"move_speed", &Foot::move_speed,
			"Run", &Foot::Run
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	void Foot::Run()
	{
		if (animal->GetIsDead())
			return;
		if (animal->GetEnergy() <= 0)
			return;

		int energy = animal->GetEnergy() - 1;
		animal->SetEnergy(energy);
		float pos = animal->GetPos() + move_speed;
		animal->SetPos(pos);
	}

	Animal::Animal(std::string name, float _pos, int _hp, int _energy, float _move_speed) : Unit(UnitType::UnitType_Animal, name, _pos),
		hp(_hp), energy(_energy)
	{
		foot = new Foot(this, _move_speed);
		assert(hp > 0 && energy > 0);
	}

	Animal::~Animal()
	{
		if (nullptr != foot)
			delete foot;
		foot = nullptr;
	}

	void Animal::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Animal";
		sol::usertype<Animal> meta_table(
			sol::constructors<Animal(std::string, float, int, int, float)>(),
			"energy", &Animal::energy,
			"hp", &Animal::hp,
			"foot", sol::property(&Animal::GetFoot),
			"Run", &Animal::Run,
			"Rest", &Animal::Rest,
			"TryAction", &Animal::TryAction,
			sol::base_classes, sol::bases<Unit>()
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	void Animal::TryAction()
	{
		printf("Animal TryAction \n");
	}

	void Animal::Run()
	{
		foot->Run();
	}

	void Animal::Rest()
	{
		energy += 1;
	}

	int Animal::GetHP()
	{
		return hp;
	}

	void Animal::SetHp(int _hp)
	{
		hp = _hp;
	}

	int Animal::GetEnergy()
	{
		return energy;
	}

	void Animal::SetEnergy(int _energy)
	{
		energy = _energy;
	}
	Foot * Animal::GetFoot()
	{
		return foot;
	}

	Sheep::Sheep(std::string _name, float _pos, int _hp, int _energy, float _move_speed, float _eat_plant_range)
		: Animal(_name, _pos, _hp, _energy, _move_speed), eat_plant_range(_eat_plant_range)
	{

	}

	Sheep::~Sheep()
	{
	}

	void Sheep::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "Sheep";
		sol::usertype<Sheep> meta_table(
			sol::constructors<Sheep(std::string, float, int, int, float, float)>(),
			"eat_plant_range", &Sheep::eat_plant_range,
			"TryEatPlant", &Sheep::TryEatPlant,
			sol::base_classes, sol::bases<Animal, Unit>()
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}

	void Sheep::TryAction()
	{

	}

	bool Sheep::TryEatPlant(Plant * plant)
	{
		if (nullptr == plant || plant->GetIsDead())
			return false;
		if (is_dead || energy <= 0 || std::abs(pos - plant->GetPos()) > eat_plant_range)
			return false;

		--energy;
		plant->SetIsDead(true);
		energy += plant->GetRecoverEnergy();
		hp += plant->GetRecoverHp();
		return true;
	}

	float Sheep::GetEatPlantRange()
	{
		return eat_plant_range;
	}

	void Sheep::SetEatPlantRange(float _eat_plant_range)
	{
		eat_plant_range = _eat_plant_range;
	}

	void RegisterUserType()
	{
		AddLuaBindUserTypeFn([](lua_State *L) {Scene::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Unit::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Plant::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Animal::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Wolf::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Sheep::DoLuaBind(L, "TryUserType"); });
		AddLuaBindUserTypeFn([](lua_State *L) {Foot::DoLuaBind(L, "TryUserType"); });
	}
	void DynamicObject::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
	{
		std::string class_name = !name.empty() ? name : "NativeDynamicObject";

		sol::usertype<DynamicObject> meta_table(
			sol::constructors<DynamicObject()>(),
			sol::meta_function::index, &DynamicObject::DynamicSet,
			sol::meta_function::new_index, &DynamicObject::DynamicGet,
			sol::meta_function::length, [](DynamicObject& d) {
			return d.entries.size(); }
		);
		BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
	}
}
