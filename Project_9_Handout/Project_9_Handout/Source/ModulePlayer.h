#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	//HP And lives
	int hp = 3;
	int lives = 3;
	bool iFrames = false;
	int iTimer = 30;

	bool GodMode = false;
	bool start = false;
	float knockImpulse = 2;

	// Jumping
	int speedY = 1;
	int gravity = -1;

	// Player Form
	int phase = 0;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation jumpAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation crouchAnim;
	Animation crouchpunchAnim;
	Animation crouchkickAnim;
	Animation attackAnim;
	Animation kickAnim;
	Animation deathAnim;
	Animation powerAnim;

	//States of Player

	enum class state
	{
		IDLE,
		MOVEMENT,
		JUMP,
		CROUCH,
		PUNCH,
		CROUCH_PUNCH,
		KICK,
		CROUCH_KICK
	};

	state playerState = state::IDLE;

	int frame = 0;

	// The player's collider
	Collider* collider = nullptr;
	Collider* punch = nullptr;
	Collider* crouchkick = nullptr;
	Collider* kick = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint playerDeathFx;
	uint attackFx;
	uint damageHpFx;
	uint powerUpFx;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	int secondscounter = 0;

};

#endif //!__MODULE_PLAYER_H__