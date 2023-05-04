#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 30, 1, 32, 65 });

	/*// Jump
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;*/

	// Jump
	
	jumpAnim.PushBack({ 0, 71, 36, 52 });
	jumpAnim.loop = false;
	jumpAnim.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 68, 1, 40, 65 });
	rightAnim.PushBack({ 108, 1, 14, 65 });
	rightAnim.PushBack({ 129, 1, 40, 65 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 916, 1, 40, 65 });
	leftAnim.PushBack({ 895, 1, 14, 65 });
	leftAnim.PushBack({ 850, 1, 40, 65 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//Attack
	attackAnim.PushBack({ 171, 1, 50, 65 });
	attackAnim.PushBack({ 228, 1, 36, 65 });
	attackAnim.PushBack({ 270, 1, 60, 65 });
	attackAnim.loop = true;
	attackAnim.speed = 0.1f;

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters/Player character.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	playerDeathFx = App->audio->LoadFx("Assets/Fx/player_death.wav");

	position.x = 150;
	position.y = 100;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 65 }, Collider::Type::PLAYER, this);
	//punch = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	//kick = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	//crouchkick = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	/*char lookupTable[] = {"!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz"};
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);*/

	lives = 3;
	hp = 4;
	//idle = true;
	//dir = Direction::RIGHT;
	start = false;
	//attack = 1;
	//tranSt = Transform::DEFAULT;

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz 1234567890.,'=(?!)+-*/      " };
	scoreFont = App->fonts->Load("Assets/Fonts/altered_beast_font.png", lookupTable, 2);
	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= 2;
		playerState = state::JUMP;
		if (currentAnimation != &jumpAnim)
		{
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
	}

	/*if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		
	}*/
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 0;
	}
	/*if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 1;
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 2;
	}*/

	switch (playerState) {

	case state::JUMP:
		currentAnimation = &jumpAnim;
		jumpAnim.Update();
		frame++;
		if (frame <= 32) {
			position.y -= -1;
			speedY += -1;
		}
		else {
			frame = 0;
			speedY = 1;
			playerState = state::IDLE;
		}
		break;
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score at the bottom of the screen
	App->fonts->BlitText(0, 20, scoreFont, scoreText);
	App->fonts->BlitText(100, 20, scoreFont, scoreText);
    secondscounter++;
    if (secondscounter %100 ==0){

	secondscounter=0;
}
    else if (secondscounter >50){
	App->fonts->BlitText(200, 20, scoreFont, "insert coin");
}

	if (score >= 200) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
	}

	return Update_Status::UPDATE_CONTINUE;
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && c2->type == collider->WALL)
	{
		position.y -= 2;

		
		//App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = false;
	}

	else if (c2->type == collider->SCREEN_LEFT)
	{
		position.x += 2;
	}
	else if (c2->type == collider->SCREEN_RIGHT)
	{
		position.x -= 2;
	}

	if (c1->type == Collider::Type::PLAYER_ATTACK && c2->type == Collider::Type::ENEMY)
	{
		//score += 23;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT && destroyed == false) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM) {
		App->audio->PlayFx(powerUpFx);
		if (phase < 3) {
			phase++;
		}

		
	}
}