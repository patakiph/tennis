#include "Entity.h"



Entity::Entity(String name, float x, float y, float dx = 0, float dy = 0,float w = 0, float h = 0) : name(name),x(x), y(y),dx(dx),dy(dy),w(w),h(h)
{
	state = stay;
}


Entity::~Entity()
{
}
