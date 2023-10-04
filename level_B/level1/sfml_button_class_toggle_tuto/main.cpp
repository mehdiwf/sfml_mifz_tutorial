#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <cstdbool>

// unfinished

// CLASS DEF---------------------------------

class ToggleButton {
  sf::Vector2f size = sf::Vector2f(20., // the size
                                   20.);
  sf::Vector2f pos = sf::Vector2f(0., // the position
                                  0.);
  sf::Color pressed_color = sf::Color::Green;
  sf::Color not_pressed_color = sf::Color::Red;
  bool pressed = 0;
  sf::RectangleShape shape; // the sfml shape

public:
  ToggleButton();
  bool is_pressed();
  void toggle_state();
  void update_color();
};

bool ToggleButton::is_pressed() {
  return pressed;
}

void ToggleButton::update_color() {
  if (is_pressed()) {
    shape.setFillColor(pressed_color);
  }
  else {
    shape.setFillColor(not_pressed_color);
  }
}

ToggleButton::ToggleButton() {
  shape.setPosition(pos);
  shape.setSize(size);
}



// CLASS DEF---------------------------------

int main()
{
    const int window_size = 200;

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    // this variable represents the mouse!
    sf::Mouse mouse;

    sf::Vector2f rect_size(100., 100.);
    sf::RectangleShape toggling_rect(rect_size);
    sf::Vector2f rect_position(0.0, 
                               0.0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
              { window.close(); }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

              sf::Vector2i absolute_mouse_position = mouse.getPosition();
              sf::Vector2i window_0_position = window.getPosition();
              sf::Vector2i rel_mouse_position;

              rel_mouse_position.x = absolute_mouse_position.x - window_0_position.x;
              rel_mouse_position.y = absolute_mouse_position.y - window_0_position.y;
            }

              switch ( event.type ) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseMoved:
        {
          // sf::Vector2i absolute_mouse_position = mouse.getPosition();
          
          // not sure what this is lol
          sf::Vector2f mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
          if (toggling_rect.getGlobalBounds().contains(mouse_coords)) {
            toggling_rect.setFillColor(sf::Color::Green);
          }
          else {
            toggling_rect.setFillColor(sf::Color::White);
          }
        }
        break;
      case sf::Event::MouseButtonPressed:
        {
        }
        break;
              }
        } // end of event handling loop

        window.clear();
        window.draw(toggling_rect);
        window.display();
    } // end of window display loop

    return 0;
}
