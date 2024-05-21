#ifndef BIRD_H_INCLUDE_GUARD
#define BIRD_H_INCLUDE_GUARD

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Bird {
public:
  float mass = 1.;
  int box_size;
  sf::Vector2f position = sf::Vector2f(0., 0.);
  sf::CircleShape shape = sf::CircleShape(7);
  sf::Vector2f velocity = sf::Vector2f(0., 0.);
  sf::Vector2f forces = sf::Vector2f(0., 0.);
  
  Bird();
  Bird(int window_size);
  void normalize_position();
  float normalize_distance(float distance);
  float distance_to(sf::Vector2f pos);
  sf::Vector2f pointing_to(sf::Vector2f pos);
  void add_repulsive_force_from(Bird &bird2);
  void update_position(float dt);
  void add_velocity(sf::Vector2f vel);
  void add_force(sf::Vector2f vel);
  void reset_forces();
  sf::CircleShape get_shape();
  void set_position(sf::Vector2f new_pos);
  sf::Vector2f get_position();
  void add_repulsive_force_from(sf::Vector2f source);
  void reset_velocity();
};

#endif

