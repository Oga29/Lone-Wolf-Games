#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/stage_1_map.png");
	App->audio->PlayMusic("Assets/Music/01_Rise_from_Your_Grave_Round__1.ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 0, 170, 3930, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1500, 0, 10, 240 }, Collider::Type::SCREEN_RIGHT);
	App->collisions->AddCollider({ 0, 0, 10, 240 }, Collider::Type::SCREEN_LEFT);

	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 300, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 400, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 500, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 600, 100);

	/*App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 1000, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 1100, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 1200, 100);
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 1300, 100);*/

	App->enemies->AddEnemy(Enemy_Type::BROWNWOLF, 700, 120);
	App->enemies->AddEnemy(Enemy_Type::BROWNWOLF, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::BROWNWOLF, 800, 120);
	App->enemies->AddEnemy(Enemy_Type::BROWNWOLF, 850, 120);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 1;
	//bgleft->SetPos(App->render->camera.x * 0.334, 0);
	//bgright->SetPos(App->render->camera.x * 0.334 + 310, 0);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}