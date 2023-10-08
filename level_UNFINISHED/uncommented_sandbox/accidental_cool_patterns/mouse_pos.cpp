#include "mouse_pos.hpp"

MousePos::MousePos(sf::Mouse &mouse, sf::RenderWindow &window) {
  update(mouse, window);
}

void MousePos::update(sf::Mouse &mouse, sf::RenderWindow &window) {
  abs_pos = mouse.getPosition();
  sf::Vector2i window_0_position = window.getPosition();
  sf::Vector2i rel_mouse_position;  
  rel_mouse_position.x = abs_pos.x - window_0_position.x;
  rel_mouse_position.y = abs_pos.y - window_0_position.y;
  rel_pos = rel_mouse_position;

  abs_coo = window.mapPixelToCoords(abs_pos);
  rel_coo = window.mapPixelToCoords(rel_mouse_position);
}

void MousePos::set_left_pressed(bool pressed) {
  left_pressed = pressed;
}

void MousePos::set_right_pressed(bool pressed) {
  right_pressed = pressed;
}

bool MousePos::left_is_pressed() {
  return left_pressed;
}

bool MousePos::right_is_pressed() {
  return right_pressed;
}
