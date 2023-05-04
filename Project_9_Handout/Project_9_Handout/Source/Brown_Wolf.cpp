#include "Brown_Wolf.h"

#include "Application.h"
#include "ModuleCollisions.h"

Brown_Wolf::Brown_Wolf(int x, int y) : Enemy(x, y)
{
	walk.PushBack({319,87,66,30});
	walk.speed = 0.005f;
	currentAnim = &walk;
	
	path.PushBack({ -0.15f, 0.0f }, 150, &walk);
	
	collider = App->collisions->AddCollider({0, 0, 66, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Brown_Wolf::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
