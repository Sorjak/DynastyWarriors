#include "FPSTextEntity.h"


FPSTextEntity::FPSTextEntity(int x, int y){
	systemFlags.push_back("render");

	componentMap["dimension"] = new DimensionComponent(x, y, 64, 32);
}
