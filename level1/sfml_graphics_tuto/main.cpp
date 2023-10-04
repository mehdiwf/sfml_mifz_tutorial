#include <SFML/Graphics.hpp>
#include <cstdio>

// This tutorial is just a program that displays a green circle on the
// bottom right corner of your screen, and a text saying "my own
// text!" on the top left, and a thin rectangle in the middle.

int main() {
    // there is no default font ("police" in french) in sfml, we have
    // to load our own font!
    sf::Font font;

    // the method "loadFromFile" tries to load the file given, and it
    // returns 1 or 0. 
    // --> 1 means that it loaded the font without errors,
    // --> 0 means that there was a problem. 

    // We take the opposite (with '!'), so if the font was NOT loaded
    // properly, print the problem and return 1 (which crashes the
    // program)
    if (!font.loadFromFile("JetBrainsMono-Regular.ttf"))
      {
        puts("ERROR: couldn't load font file");
        return 1;
      }

    // we can create a text with a certain font, and change its
    // characteristics with methods
    sf::Text my_text("my own text!", font);
    // set the character size (in PIXELS!)
    my_text.setCharacterSize(50);
    // set the color
    my_text.setFillColor(sf::Color::White);
    
    // set the text style (if you want)
    // my_text.setStyle(sf::Text::Regular | sf::Text::Underlined);

    int window_size = 800;
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), 
                            "SFML window default name");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(600., 600.);

    // horizontal length first, then vertical length
    sf::Vector2f my_rect_size(100., 10.);
    sf::RectangleShape my_rectangle(my_rect_size);
    my_rectangle.setPosition(400, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(my_rectangle);
        window.draw(my_text);
        window.display();
    }

    return 0;
}
