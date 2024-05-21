#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
// uncomment that there seem to be a version problem
// #include <format>
#include <cstdio>
#include <cstdbool>
#include <string>

// personal headers
#include "mouse_pos.hpp"
#include "bird.hpp"

using namespace std;

int main()
{

  const float dt = 1.;
  const int window_size = 700;

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    int fps_count = 60;
    window.setFramerateLimit(fps_count);
    sf::Mouse sfml_mouse;
    MousePos mouse = MousePos(sfml_mouse, window);

    // doing
    sf::CircleShape mouse_spotter(10);
    mouse_spotter.setFillColor(sf::Color::Transparent);
    mouse_spotter.setOutlineColor(sf::Color::Transparent);
    mouse_spotter.setOutlineThickness(2);

    Bird richard(window_size);
    richard.position = sf::Vector2f(0, 100);
    richard.add_velocity(sf::Vector2f(3, 0));
    Bird patrick(window_size);
    patrick.position = sf::Vector2f(0,
                                    500);
    patrick.add_velocity(sf::Vector2f(-3, 0));

    Bird john(window_size);
    john.position = sf::Vector2f(20,
                                    350);
    john.add_velocity(sf::Vector2f(-3, 0));
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch ( event.type ) {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::MouseMoved:
            break;
          case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left){
              // if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
              
              // doing
              mouse_spotter.setOutlineColor(sf::Color::White);
              mouse.set_left_pressed(true);;
            }
            break;
          case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left){
              mouse_spotter.setOutlineColor(sf::Color::Transparent);
              mouse.set_left_pressed(false);
            }
            
          default:
            break;
          } // end of switch
        } // end of pollEvent
        
        if (mouse.left_is_pressed()) {
          mouse.update(sfml_mouse, window);
          
          mouse_spotter.setPosition(mouse.rel_coo.x - mouse_spotter.getRadius(),
                             mouse.rel_coo.y - mouse_spotter.getRadius());
        }

        richard.add_repulsive_force_from(patrick);
        richard.add_repulsive_force_from(john);
        
        patrick.add_repulsive_force_from(richard);
        patrick.add_repulsive_force_from(john);

        john.add_repulsive_force_from(richard);
        john.add_repulsive_force_from(patrick);
        
        john.update_position(dt);
        richard.update_position(dt);
        patrick.update_position(dt);
        
        window.clear();
        window.draw(mouse_spotter);
        window.draw(richard.get_shape());
        window.draw(patrick.get_shape());
        window.draw(john.get_shape());
        window.display();
    } // end of window display loop

    return 0;
} // end of main
