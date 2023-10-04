#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>

// This program creates an empty window. If you click inside this
// window, it will color the column you clicked on!

void draw_color_frame(sf::RenderWindow &window,
                      int window_size,
                      int *frame) {

  // the shape we will draw
  sf::Vector2f size_line(1., (float) window_size);
  sf::RectangleShape line(size_line);
  line.setFillColor(sf::Color::White);
  line.setOutlineColor(sf::Color::White);

  for (int i = 0; i < window_size; i++) {
    if (frame[i] == 1) {
      line.setPosition(i * size_line.x,
                       0.);
      window.draw(line);
    }
  }
}

int main()
{
    const int window_size = 200;
    // create the window
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    // this variable represents the mouse!
    sf::Mouse mouse;
    
    int color_frame[window_size] = {0};

    // things to do while the window is opened
    while (window.isOpen())
    {
        // SFML records any interaction with the computer as an event,
        // so we create a variable that will store any events. An
        // event can be: 
        // - a mouse click
        // - a key pressed on your keyboard
        // - the movement of your mouse...
        // - and many more things
        sf::Event event;
        // the "pollEvent" method listen to any event and saves it in
        // our "event" variable.
        while (window.pollEvent(event))
        {

            // now that we have an event, we can do stuff depending on
            // the event type!

            // here, if the "Closed" event is registered, we close the
            // window. It can be clicking on the "X" button to close
            // the window for instance
            if (event.type == sf::Event::Closed)
              { window.close(); }

            // if the left button of the mouse is clicked, we register
            // the position of the mouse inside the window and print
            // it on the terminal!
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

              // we get the absolute position of the mouse at the
              // moment of the click.
              sf::Vector2i absolute_mouse_position = mouse.getPosition();
              // But this is the position on your SCREEN! not inside
              // your window! To get the position of the mouse inside
              // the sfml window, we need to compute the relative
              // position of your mouse inside the sfml window.

              // this is the absolute position of the top left corner
              // of your window, which will help us compute the
              // relative position of your mouse inside your window
              sf::Vector2i window_0_position = window.getPosition();

              // we create the variable containing the relative mouse
              // position
              sf::Vector2i rel_mouse_position;

              // we compute the relative position of the mouse INSIDE
              // the window
              rel_mouse_position.x = absolute_mouse_position.x - window_0_position.x;
              rel_mouse_position.y = absolute_mouse_position.y - window_0_position.y;

              if (rel_mouse_position.x < window_size
                  and
                  rel_mouse_position.x >= 0
                  and
                  rel_mouse_position.y < window_size
                  and
                  rel_mouse_position.y >= 0) {
                color_frame[rel_mouse_position.x] = !color_frame[rel_mouse_position.x];
              }
            }
        } // end of event handling loop

        window.clear();
        draw_color_frame(window,
                         window_size,
                         color_frame);
        window.display();
    } // end of window display loop

    return 0;
}
