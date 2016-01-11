#ifndef IWEAPON_H
#define IWEAPON_H
#include "IITem.h"

class IWeapon : public IItem
{
protected:
	float _range;
	float _damage;
	bool _equipped;

public:
	virtual ~IWeapon() {}
};

#endif