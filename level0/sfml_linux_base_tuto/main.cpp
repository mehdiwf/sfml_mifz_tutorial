#include <SFML/Graphics.hpp>

// This tutorial is just a program that displays a green circle in a
// black background! It shows the very simple components you need to
// run a sfml window.

// Usually, for graphic libraries, there is a lot of loops: a loop to
// display an image every time the program is ready, a loop to
// register the user clicks or keyboard input... It's not easy to
// understand everything at first glance, but you don't have to! You
// can do very interesting stuff even if you just copy a basic
// template and add things on top of it. But don't hesitate to search
// on the internet for help, or ask your tutor!
int main()
{
    int window_size = 200;
    // create the window
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML works!");
    float circle_radius = 100.0;
    sf::CircleShape my_circle(circle_radius);
    // to choose colors, we use sf::Color::... you have all basic
    // colors like red, black, white, blue, cyan, magenta, yellow,
    // ect...
    my_circle.setFillColor(sf::Color::Green);
    
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
            // here, if the "Closed" event is registered, we close the
            // window. It can be clicking on the "X" button to close
            // the window for instance
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // each step, we clear the entire window
        window.clear();
        // then we tell sfml that we want to draw our shape
        window.draw(my_circle);
        // then we tell sfml to display everything we wanted to draw!
        window.display();
    }

    return 0;
}
