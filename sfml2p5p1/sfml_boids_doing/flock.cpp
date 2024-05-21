#include "flock.hpp"
#include "bird.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstdio>

Flock::Flock(int window_size) {
  for (int i = 0; i < n_birds; i++) {
    flock_birds[i] = Bird(window_size);
    flock_birds[i].reset_forces();
  }
}

void Flock::grid_init(float x0, float y0,
                      float l_x, float l_y) {
  for (int i = 0; i < n_birds; i++) {
    sf::Vector2f pos_i(x0 + (i * l_x)/n_birds,
                       y0 + (i * l_y)/n_birds);
    flock_birds[i].set_position(pos_i);
  }
  compute_gravity_center();
}

void Flock::add_pairs_repulsion_forces() {
  for (int i = 0; i < n_birds - 1; i++) {
    for (int k_i = i + 1; k_i < n_birds; k_i++) {
      Bird &bird_i = flock_birds[i];
      Bird &bird_k_i = flock_birds[k_i];
      bird_i.add_repulsive_force_from(bird_k_i);
      bird_k_i.add_repulsive_force_from(bird_i);
    }
  }
}

void Flock::next_step(float dt) {
  for (int i = 0; i < n_birds; i++) {
    flock_birds[i].update_position(dt);
    compute_gravity_center();
  }
}

void Flock::add_repulsion_from(sf::Vector2f pos) {
  for (int i = 0; i < n_birds; i++) {
    flock_birds[i].add_repulsive_force_from(pos);
  }
}

void Flock::add_repulsion_from(float x, float y) {
  for (int i = 0; i < n_birds; i++) {
    flock_birds[i].add_repulsive_force_from(sf::Vector2f(x, y));
  }
}

void Flock::draw_all(sf::RenderWindow &window) {
  for (int i = 0; i < n_birds; i++) {
    window.draw(flock_birds[i].get_shape());
  }
}

void Flock::reset_velocities() {
  for (int i = 0; i < n_birds; i++) {
    flock_birds[i].reset_velocity();
  }
}

void Flock::compute_gravity_center() {
  sf::Vector2f grav_center(0., 0.);
  for (int i = 0; i < n_birds; i++) {
    grav_center += flock_birds[i].position;
  }
  grav_center /= (float) n_birds;
  gravity_center = grav_center;
}

sf::Vector2f Flock::get_gravity_center() {
  return gravity_center;
}

  
void Flock::compute_boid_velocities(float dt) {
  for (int i = 0; i < n_birds; i++) {
    Bird &bird_i = flock_birds[i];
    // adding gravity center speed
    float distance = bird_i.distance_to(gravity_center);
    sf::Vector2f direction = flock_birds[i].pointing_to(gravity_center);
    sf::Vector2f dv = 0.001f * distance * direction / dt;
    
    for (int k_i = 0; k_i < n_birds;  k_i++) {
      if (k_i != i) {
        distance = bird_i.distance_to(flock_birds[k_i].get_position());
        direction = bird_i.pointing_to(flock_birds[k_i].get_position());
        if (distance < min_distance) {
          // adding the min distance speed
          dv += - 0.5f * (min_distance - distance) * direction / dt;
        }
        
        if (distance < neighbor_copy_distance) {
          // adding the neighbor copy distance speed
          dv += 0.2f * (flock_birds[k_i].velocity - bird_i.velocity)/8.f;
        }
      }
    } // other birds -
    bird_i.add_velocity(dv);
  } // main loop
}
