#include "closedFormTest.h"

#include <math.h>


int calculate_iterations (float seconds, float FPS)
{
  return (int)ceilf (seconds / (1.0f / FPS));
}


/// <summary>
/// simulate one frame of the game
/// using *Euler integration*
/// this is what your update code should look like :)
/// </summary>
void simulate (Data* data, float FPS)
{
  const float magnetMultiplier = sqrtf (data->magnets + 1.0f) * data->ownsMagnetsUpgrade ? 2.0f : 1.0f;
  const float minimum_speed = data->ownsHamster ? 0.001f : 0.0f; // previously called "baseSpeed"

  // distance = data->storedEnergy
  const float acceleration = data->ownsFlywheel ? -0.01f : -0.05f; // previously called "slowdown"
  const float delta = 1.0f / FPS;


  // s = s + u*dt
  data->storedEnergy += (magnetMultiplier * data->speed) * delta;
  data->storedEnergy = fminf (data->storedEnergy, data->maxEnergy);

  // v = u + a*dt
  data->speed = data->speed + acceleration * delta;
  data->speed = fmaxf (data->speed, minimum_speed);
}

/// <summary>
/// simulate n seconds worth of playing using SUVAT
/// use me :)
/// </summary>
void simulate_n_seconds (Data* data, float seconds)
{
  const float magnetMultiplier = sqrtf (data->magnets + 1.0f) * data->ownsMagnetsUpgrade ? 2.0f : 1.0f;
  const float minimum_speed = data->ownsHamster ? 0.001f : 0.0f; // previously called "baseSpeed"

  // distance = data->storedEnergy
  const float acceleration = data->ownsFlywheel ? -0.01f : -0.05f; // previously called "slowdown"


  // t = (v - u)/a
  float const time_to_reach_minimum_speed = (minimum_speed - data->speed) / acceleration;

  bool const will_reach_reach_minimum_speed = time_to_reach_minimum_speed < seconds;


  if (will_reach_reach_minimum_speed)
  {
    // s = u*t + 0.5*a*t^2
    // whilst decelerating
    data->storedEnergy += magnetMultiplier * (data->speed * time_to_reach_minimum_speed + 0.5f * acceleration * powf (time_to_reach_minimum_speed, 2.0f));
    // whilst a minimum speed, no acceleration
    data->storedEnergy += magnetMultiplier * (minimum_speed * (seconds - time_to_reach_minimum_speed));
  }
  else
  {
    data->storedEnergy += magnetMultiplier * (data->speed * seconds + 0.5f * acceleration * powf (seconds, 2.0f));
  }
  data->storedEnergy = fminf (fabsf (data->storedEnergy), data->maxEnergy);

  // v = u + a*t
  data->speed = data->speed + acceleration * seconds;
  data->speed = fmaxf (data->speed, minimum_speed);
}

/// <summary>
/// simulate n seconds worth of playing by executing game for seconds/FPS iterations
/// </summary>
void simulate_n_iterations (Data* data, float seconds, float FPS)
{
  int const iterations = calculate_iterations (seconds, FPS);

  for (int i = 0; i < iterations; ++i)
  {
    simulate (data, FPS);
  }
}


void ORIG_simulateSeconds (Data* data, float seconds)
{
  const float magnetMultiplier = sqrtf (data->magnets + 1.0f) * data->ownsMagnetsUpgrade ? 2.0f : 1.0f;
  const float slowdown = data->ownsFlywheel ? 0.99f : 0.95f;
  const float baseSpeed = data->ownsHamster ? 0.001f : 0.0f;

  data->speed = (data->speed + baseSpeed * seconds * 30.0f) * powf (slowdown, seconds * 30.0f);
  data->storedEnergy += seconds * magnetMultiplier * data->speed;
  data->storedEnergy = fminf (data->storedEnergy, data->maxEnergy);
}
void ORIG_simulateIterations (Data* data, float seconds)
{
  const float magnetMultiplier = sqrtf (data->magnets + 1.0f) * data->ownsMagnetsUpgrade ? 2.0f : 1.0f;
  const float slowdown = data->ownsFlywheel ? 0.99f : 0.95f;
  const float baseSpeed = data->ownsHamster ? 0.001f : 0.0f;

  int iterations = (int)ceilf (seconds / (1.0f / 30.0f));
  for (int i = 0; i < iterations; i++)
  {
    data->speed = (data->speed + baseSpeed) * slowdown;
    data->storedEnergy += magnetMultiplier * data->speed;
  }
  data->storedEnergy = fminf (data->storedEnergy, data->maxEnergy);
}
void ORIG_simulateOneThirtieth (Data* data)
{
  const float magnetMultiplier = sqrtf (data->magnets + 1.0f) * data->ownsMagnetsUpgrade ? 2.0f : 1.0f;
  const float slowdown = data->ownsFlywheel ? 0.99f : 0.95f;
  const float baseSpeed = data->ownsHamster ? 0.001f : 0.0f;

  data->speed = (data->speed + baseSpeed) * slowdown;
  data->storedEnergy += magnetMultiplier * data->speed;
  data->storedEnergy = fminf (data->storedEnergy, data->maxEnergy);
}
