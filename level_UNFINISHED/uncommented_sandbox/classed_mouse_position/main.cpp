#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <format>
#include <cstdio>
#include <cstdbool>
#include <string>

using namespace std;

// you can click on the button and it toggles the button color

// CLASS DEF---------------------------------

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
  MousePos(sf::Mouse &mouse, sf::RenderWindow &window);
  void update(sf::Mouse &mouse, sf::RenderWindow &window);
};

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

MousePos::MousePos(sf::Mouse &mouse, sf::RenderWindow &window) {
  update(mouse, window);
}

class MousePosIndicator {
  string label = "mouse click position";
  string abs_pos_txt = format("abs:\nx pos: {}\ny pos: {}",
                              0., 0.);
  string rel_pos_txt = format("rel:\nx pos: {}\ny pos: {}",
                              0., 0.);
  string abs_coord_pos_txt = format("abs coord:\nx pos: {}\ny pos: {}",
                                    0., 0.);
  string rel_coord_pos_txt = format("rel coord:\nx pos: {}\ny pos: {}",
                                    0., 0.);
  string whole_text = label + "\n" + abs_pos_txt + "\n" + rel_pos_txt + "\n" + abs_coord_pos_txt + "\n" + rel_coord_pos_txt;

  sf::Font font;
  
  sf::Text sfml_txt;
  
public:
  MousePosIndicator();
  string get_string();
  void set_string();
  void update_string(sf::Vector2i abs_pos, sf::Vector2i rel_pos,
                     sf::Vector2f abs_coo, sf::Vector2f rel_coo);
  sf::Text get_shape();
  void set_pos(float x, float y);
};

MousePosIndicator::MousePosIndicator() {
  if (!font.loadFromFile("JetBrainsMono-Regular.ttf"))
    {
      puts("ERROR: couldn't load font file");
    }
  sfml_txt.setFont(font);
  sfml_txt.setCharacterSize(20);
  sfml_txt.setPosition(10., 300.);
  sfml_txt.setString(whole_text);
  sfml_txt.setFillColor(sf::Color::White);
};

void MousePosIndicator::set_pos(float x, float y) {
  sfml_txt.setPosition(x, y);
}

string MousePosIndicator::get_string() {
  return sfml_txt.getString();
}
void MousePosIndicator::update_string(sf::Vector2i abs_pos, sf::Vector2i rel_pos,
                                      sf::Vector2f abs_coo, sf::Vector2f rel_coo) {
    string label = "mouse click position";
    string abs_pos_txt = format("abs:\nx pos: {}\ny pos: {}",
                              abs_pos.x,
                              abs_pos.y);
  string rel_pos_txt = format("rel:\nx pos: {}\ny pos: {}",
                              rel_pos.x,
                              rel_pos.y);
  string abs_coord_pos_txt = format("abs coord:\nx pos: {}\ny pos: {}",
                                    abs_coo.x,
                                    abs_coo.y);
  string rel_coord_pos_txt = format("rel coord:\nx pos: {}\ny pos: {}",
                                    rel_coo.x,
                                    rel_coo.y);
  string t = label + "\n" + abs_pos_txt + "\n" + rel_pos_txt + "\n" + abs_coord_pos_txt + "\n" + rel_coord_pos_txt;
  sfml_txt.setString(t);
}
sf::Text MousePosIndicator::get_shape() {
  return sfml_txt;
}

// CLASS DEF---------------------------------

int main()
{
    const int window_size = 700;

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    window.setFramerateLimit(60);
    sf::Mouse sfml_mouse;
    MousePos mouse = MousePos(sfml_mouse, window);

    // doing
    sf::CircleShape circle(25);
    circle.setFillColor(sf::Color::White);
    
    MousePosIndicator mouse_pos = MousePosIndicator();
    mouse_pos.set_pos(300., 300.);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
              { window.close(); }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

              sf::Vector2i absolute_mouse_position = sfml_mouse.getPosition();
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
        }
        break;
      case sf::Event::MouseButtonPressed:
        {
          if ( event.mouseButton.button == sf::Mouse::Left ) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

              mouse.update(sfml_mouse, window);
              mouse_pos.update_string(mouse.abs_pos, mouse.rel_pos,
                                          mouse.abs_coo, mouse.rel_coo);
              circle.setPosition(mouse.rel_coo.x,
                                 mouse.rel_coo.y);
              
            }
          }
        }
        break;
              }
        } // end of event handling loop

        window.clear();
        window.draw(mouse_pos.get_shape());
        window.draw(circle);
        window.display();
    } // end of window display loop

    return 0;
} // end of main
