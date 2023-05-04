#ifndef __Zombie__
#define __Zombie__

#include "Enemy.h"
#include "Path.h"

class Zombie : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Zombie(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	Path path;
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation walkAnim;
};

#endif // __Zombie__