#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>

// This program creates an empty window with a circle in it. If you
// click inside this window, it move the circle where you clicked!

int main()
{
    const int window_size = 200;

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    // this variable represents the mouse!
    sf::Mouse mouse;
    
    float circle_radius = 20.0;
    sf::CircleShape moving_circle(circle_radius);
    sf::Vector2f circle_position(0.0, 
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

              if (rel_mouse_position.x < window_size
                  and
                  rel_mouse_position.x >= 0
                  and
                  rel_mouse_position.y < window_size
                  and
                  rel_mouse_position.y >= 0) {
                // this will position the top right corner of your
                // circle on the clicked position
                moving_circle.setPosition(rel_mouse_position.x,
                                          rel_mouse_position.y);

                // if you want to put the circle in the center of your
                // click, do this instead:
                /*
                moving_circle.setPosition(rel_mouse_position.x - circle_radius,
                                          rel_mouse_position.y - circle_radius);
                */
              }
            }
        } // end of event handling loop

        window.clear();
        window.draw(moving_circle);
        window.display();
    } // end of window display loop

    return 0;
}
