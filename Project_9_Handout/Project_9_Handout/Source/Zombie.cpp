#include "Zombie.h"

#include "Application.h"
#include "ModuleCollisions.h"

Zombie::Zombie(int x, int y) : Enemy(x, y)
{
	walkAnim.PushBack({481,0,27,60});
    
	currentAnim = &walkAnim;
	path.PushBack({ -0.15f, 0.0f }, 150, &walkAnim);
	collider = App->collisions->AddCollider({0, 0, 27, 60}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Zombie::Update()
{
	

	position.y = 100;
	position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
