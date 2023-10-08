#ifndef FLOCK_H_INCLUDE_GUARD
#define FLOCK_H_INCLUDE_GUARD

#include "bird.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

const int nb_bird = 10;

class Flock {
public:
  Bird flock_birds[nb_bird];
  int n_birds = nb_bird;
  sf::Color default_color = sf::Color::White;
  sf::Vector2f gravity_center;

  Flock(int window_size);
  
  void grid_init(float x0, float y0,
                 float l_x, float l_y);
  void add_pairs_repulsion_forces();
  void next_step(float dt);
  void add_repulsion_from(sf::Vector2f pos);
  void add_repulsion_from(float x, float y);
  void draw_all(sf::RenderWindow &window);
  void reset_velocities();
  void compute_gravity_center();
  sf::Vector2f get_gravity_center();
};

#endif
