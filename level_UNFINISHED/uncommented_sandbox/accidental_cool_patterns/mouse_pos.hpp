#ifndef MOUSE_POS_H_INCLUDE_GUARD
#define MOUSE_POS_H_INCLUDE_GUARD

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class MousePos {
public:
  // the absolute position in the screen frame of reference (in pixels)
  sf::Vector2i abs_pos;
  // the relative position in the window frame of reference (in pixels)
  sf::Vector2i rel_pos;
  // the absolute coordinates in the screen frame of reference (coordinates, floats)
  sf::Vector2f abs_coo;
  // the relative coordinates in the screen frame of reference (coordinates, floats)
  // this is what can be used easily to interface with user clicks
  sf::Vector2f rel_coo;
  bool left_pressed = false;
  bool right_pressed = false;
  MousePos(sf::Mouse &mouse, sf::RenderWindow &window);
  void set_left_pressed(bool pressed);
  void set_right_pressed(bool pressed);
  void update(sf::Mouse &mouse, sf::RenderWindow &window);
  bool left_is_pressed();
  bool right_is_pressed();
};

#endif
