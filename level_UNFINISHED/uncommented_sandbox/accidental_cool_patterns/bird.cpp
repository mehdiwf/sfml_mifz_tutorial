#include <SFML/System/Vector2.hpp>
#include <math.h>

// personal libs
#include "bird.hpp"
#include "mifz_math.hpp"


Bird::Bird(int window_size) {
  shape.setFillColor(sf::Color::Yellow);
  box_size = window_size;
}

float Bird::normalize_distance(float distance) {
  return periodic_normalization(distance, box_size);
}

float Bird::distance_to(Bird bird2) {
  float scale = box_size/5.f;
  float dx = fabsf(bird2.position.x - position.x)/scale;
  float dy = fabsf(bird2.position.y - position.y)/scale;
  dx = normalize_distance(dx);
  dy = normalize_distance(dy);
  return sqrtf(dx*dx + dy*dy);
}

sf::Vector2f Bird::pointing_to(Bird bird2) {
  // returns the unitary vector pointing to bird2, from bird
  float dx = bird2.position.x - position.x;
  float dy = bird2.position.y - position.y;
  float distance = distance_to(bird2);
  if (distance == 0.)
    return sf::Vector2f(0, 0);
  else
    return sf::Vector2f(dx, dy)/distance;
}

void Bird::add_repulsive_force_from(Bird bird2) {
  float distance = distance_to(bird2);
  int attractive = 1;
  float amplitude = 0.002/distance;
  sf::Vector2f force = attractive * amplitude * pointing_to(bird2);
  add_force(force);
}

void Bird::normalize_position() {
  position.x = position.x - floorf(position.x / box_size)*box_size;
  position.y = position.y - floorf(position.y / box_size)*box_size;
  if (position.x < 0)
    position.x += box_size;
  if (position.y < 0)
    position.y += box_size;
}

void Bird::update_position(float dt) {
  sf::Vector2f dv = (forces * dt) / mass;
  velocity += dv;
  position += velocity * dt;
  normalize_position();
  shape.setPosition(position);
  reset_forces();
}

void Bird::add_velocity(sf::Vector2f vel) {
  velocity += vel;
}

void Bird::add_force(sf::Vector2f force) {
  forces += force;
}

void Bird::reset_forces() {
  forces = sf::Vector2f(0, 0);
}

sf::CircleShape Bird::get_shape() {
  return shape;
}
