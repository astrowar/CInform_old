#include "FEnviroment.h"


CKind::CKind(std::string named, CKind* prev):previous(prev), name(named)
{

}

CValueKind::CValueKind(std::string _name): name(_name)
{}

FEnviroment::FEnviroment()
{
}

FEnviroment* FEnviroment::copy() const
{
	auto  c =  new FEnviroment();
	
	c->kinds = std::list<HKind>(this->kinds.begin(), this->kinds.end());
	c->instances = std::list<HInstance>(this->instances.begin(), this->instances.end());


	return c;
}

FEnviroment::~FEnviroment()
{
}

void FEnviroment::addKind(HKind _k)
{
	this->kinds.push_back(_k);
}

void FEnviroment::addInstance(HInstance _k)
{
	this->instances.push_back(_k);
}

HKind make_kind(FEnviroment *env,  std::string name)
{
	auto c = std::make_shared<CKind>(name, nullptr);
	env->addKind(c);
	return c;
}

HKind make_derivade_kind(FEnviroment* env, std::string name , HKind base)
{
	auto c = std::make_shared<CKind>(name, base.get());
	env->addKind(c);
	return c;
}

HInstance make_instance(FEnviroment* env, std::string name, HKind k)
{
	auto c = std::make_shared<CInstance>(k.get(), name);
	env->addInstance(c);
	return c;
}
