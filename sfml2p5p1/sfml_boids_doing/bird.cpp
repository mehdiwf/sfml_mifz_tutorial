#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <iostream>
#include <math.h>

// personal libs
#include "bird.hpp"
#include "mifz_math.hpp"


Bird::Bird() {
  shape.setFillColor(sf::Color::Yellow);
  box_size = 100;
}

Bird::Bird(int window_size) {
  shape.setFillColor(sf::Color::Yellow);
  box_size = window_size;
}

float Bird::normalize_distance(float distance) {
  return periodic_normalization(distance, box_size);
}

float Bird::distance_to(sf::Vector2f pos) {
  float dx = fabsf(pos.x - position.x);
  float dy = fabsf(pos.y - position.y);
  dx = normalize_distance(dx);
  dy = normalize_distance(dy);
  return sqrtf(dx*dx + dy*dy);
}

sf::Vector2f Bird::get_position() {
  return position;
}

sf::Vector2f Bird::pointing_to(sf::Vector2f pos) {
  // returns the unitary vector pointing to bird2, from bird

  // TODO: not consistent with periodic conditions, because pointing
  // to the position, and not the mirrored one if necessary
  float dx = pos.x - position.x;
  float dy = pos.y - position.y;
  float distance = distance_to(pos);
  if (distance == 0.)
    return sf::Vector2f(0, 0);
  else
    return sf::Vector2f(dx, dy)/distance;
}

void Bird::add_repulsive_force_from(Bird &bird2) {
  sf::Vector2f pos = bird2.get_position();
  float distance = distance_to(pos);
  int attractive = 1;
  float amplitude = 10.f/distance;
  sf::Vector2f force = attractive * amplitude * pointing_to(pos);
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

void Bird::set_position(sf::Vector2f new_pos) {
  position = new_pos;
}

void Bird::add_repulsive_force_from(sf::Vector2f source) {
  float distance = distance_to(source);
  int attractive = -1;
  float amplitude = 100000.f/(distance * distance);
  sf::Vector2f force = attractive * amplitude * pointing_to(source);
  add_force(force);
}

void Bird::reset_velocity() {
  velocity.x = velocity.y = 0.f;
}
