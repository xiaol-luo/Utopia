#include "TryUserType.h"
#include <assert.h>

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
	}

	Scene::~Scene()
	{
		this->Reset();
	}

	void Scene::Reset()
	{
		for (auto kv_pair : units)
		{
			delete kv_pair.second;
		}
		units.clear();
	}

	void Scene::Tick()
	{
		printf("-- C++ Scene Tick \n");
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

	void RegisterUserType(sol::state_view & lua)
	{
		sol::table ns = lua.create_named_table("TryUserType");
		ns.new_usertype<Scene>(
			"Scene", sol::constructors<Scene()>(),
			"Reset", &Scene::Reset,
			"Tick", &Scene::Tick	
			);

		ns.new_usertype<Unit>(
			"Unit", sol::constructors<Unit(UnitType, const std::string&, float)>(),
			"unit_type", sol::property(&Unit::GetUnitType),
			"name", sol::property(&Unit::GetName),
			"pos", sol::property(&Unit::GetPos, &Unit::SetPos),
			"is_dead", sol::property(&Unit::GetIsDead, &Unit::SetIsDead),
			"scene", sol::property(&Unit::GetScene, &Unit::SetScene)
			);
	}
}