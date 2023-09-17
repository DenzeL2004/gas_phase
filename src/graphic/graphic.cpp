#include "graphic.h"


//================================================================================

void DrawLine(sf::RenderWindow &window, 
              const Dot &dot_begin, const Dot &dot_end, const sf::Color color_line)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f((float)dot_begin.GetX(), (float)dot_begin.GetY()), color_line),
        sf::Vertex(sf::Vector2f((float)dot_end.GetX(), (float)dot_end.GetY()), color_line)
    };

    window.draw(line, 2, sf::Lines);

    return;
   
}

//================================================================================


void DrawCircle(sf::RenderWindow &window, const Dot &pos, 
                const float radius, const sf::Color color)
{

    sf::CircleShape circle(radius);
    circle.setFillColor(color);

    circle.setPosition((float)pos.GetX(), (float)pos.GetY());

    window.draw(circle);

    return;
   
}

//================================================================================


void DrawRectangle(sf::RenderWindow &window, 
                   const Dot &left_up, const Dot &right_down, const sf::Color color)
{

    float hieght = (float)(right_down.GetY() - left_up.GetY());
    float width  = (float)(right_down.GetX() - left_up.GetX());

    sf::RectangleShape rectangle;
    rectangle.setSize({ width, hieght});
    rectangle.setFillColor(color);

    rectangle.setPosition((float)left_up.GetX(), (float)left_up.GetY());

    window.draw(rectangle);

    return;
   
}

//================================================================================


void DrawPixel(sf::RenderWindow &window, const Dot &pos, const sf::Color color)
{

    sf::RectangleShape pixel;
    pixel.setSize({ 1.f, 1.f });
    pixel.setFillColor(color);


    pixel.setPosition((float)pos.GetX(), (float)pos.GetY());

    window.draw(pixel);
    
    return;
   
}

//================================================================================
