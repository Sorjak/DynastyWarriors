#include "LaserEntity.h"


LaserEntity::LaserEntity(long id, int x, int y){
	mID = id;

	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("expires");

	componentMap["texture"] = new TextureComponent("media/redlaser.png");
	componentMap["dimension"] = new DimensionComponent(x, y, 64, 32);
	componentMap["velocity"] = new VelocityComponent(1, 0);
	componentMap["projectile"] = new ProjectileComponent();
	componentMap["expiration"] = new ExpirationComponent(5000);
}

LaserEntity::LaserEntity(long id, int x, int y, BaseEntity* parent){
	mID = id;

	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("expires");

	componentMap["texture"] = new TextureComponent("media/redlaser.png");
	componentMap["dimension"] = new DimensionComponent(x, y, 64, 32);
	componentMap["velocity"] = new VelocityComponent(1, 0);
	componentMap["projectile"] = new ProjectileComponent();
	componentMap["expiration"] = new ExpirationComponent(5000);
	
}




