#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <format>
#include <cstdio>
#include <cstdbool>
#include <string>

// personal headers
#include "mouse_pos.hpp"
#include "bird.hpp"
#include "flock.hpp"

using namespace std;

int main()
{

  int framestep = 0;
  float dt = 0.05;
  // const float dt = 0.;
  const int window_size = 700;

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    int fps_count = 60;
    window.setFramerateLimit(fps_count);
    sf::Mouse sfml_mouse;
    MousePos mouse = MousePos(sfml_mouse, window);

    sf::CircleShape mouse_spotter(10);
    mouse_spotter.setFillColor(sf::Color::Transparent);
    mouse_spotter.setOutlineColor(sf::Color::Transparent);
    mouse_spotter.setOutlineThickness(2);

    Flock birds_flock = Flock(window_size);
    birds_flock.grid_init(200, 200,
                          400, 400);
    birds_flock.flock_birds[0].set_position(sf::Vector2f(190, 200));

    while (window.isOpen())
      {
        framestep += 1;
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
              
              mouse_spotter.setOutlineColor(sf::Color::White);
              mouse.set_left_pressed(true);;
            }
            break;
          case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left){
              mouse_spotter.setOutlineColor(sf::Color::Transparent);
              mouse.set_left_pressed(false);
            }
          case sf::Event::KeyPressed:
            if (event.key.scancode == sf::Keyboard::Scan::Space)
              {birds_flock.reset_velocities();}
          default:
            break;
          } // end of switch
        } // end of pollEvent
        
        if (mouse.left_is_pressed()) {
          mouse.update(sfml_mouse, window);
          
          mouse_spotter.setPosition(mouse.rel_coo.x - mouse_spotter.getRadius(),
                                    mouse.rel_coo.y - mouse_spotter.getRadius());
          birds_flock.add_repulsion_from(mouse.rel_coo.x,
                                         mouse.rel_coo.y);
        }

        // birds_flock.add_pairs_repulsion_forces();
        birds_flock.compute_boid_velocities(dt);
        birds_flock.next_step(dt);
        
        window.clear();

        birds_flock.draw_all(window);
        
        window.draw(mouse_spotter);
        window.display();
        // if (framestep > 2) {
        //   puts("pepeg");
        //   return 1;
        // }
    } // end of window display loop

    return 0;
} // end of main
