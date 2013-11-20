#include "LaserEntity.h"


LaserEntity::LaserEntity(int x, int y){
	systemFlags.push_back("render");
	systemFlags.push_back("move");

	componentMap["texture"] = new TextureComponent("media/redlaser.png");
	componentMap["dimension"] = new DimensionComponent(x, y, 64, 32);
	componentMap["velocity"] = new VelocityComponent(1, 0);
	componentMap["projectile"] = new ProjectileComponent();
	
}

LaserEntity::LaserEntity(int x, int y, BaseEntity* parent){
	systemFlags.push_back("render");
	systemFlags.push_back("move");

	componentMap["texture"] = new TextureComponent("media/redlaser.png");
	componentMap["dimension"] = new DimensionComponent(x, y, 64, 32);
	componentMap["velocity"] = new VelocityComponent(1, 0);
	componentMap["projectile"] = new ProjectileComponent();
	
}




