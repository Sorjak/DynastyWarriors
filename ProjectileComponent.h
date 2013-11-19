#pragma once
#include "basecomponent.h"
#include "BaseEntity.h"

class ProjectileComponent :
	public BaseComponent
{
public:
	ProjectileComponent();
	ProjectileComponent(BaseEntity*);
	~ProjectileComponent(void);

	BaseEntity* mParent;
};

