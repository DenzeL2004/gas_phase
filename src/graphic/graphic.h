#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <unistd.h>

#include "../vector/vector.h"
        
#include "../graphic/graphic_config.h"

void    DrawLine        (sf::RenderWindow &window, 
                         const Dot &dot_begin, const Dot &dot_end, const sf::Color color_line);

void    DrawCircle      (sf::RenderWindow &window, const Dot &pos, 
                         const float radius, const sf::Color color);

void    DrawRectangle   (sf::RenderWindow &window, 
                         const Dot &left_up, const Dot &right_down, const sf::Color color);

void    DrawPixel       (sf::RenderWindow &window, const Dot &pos, const sf::Color color);

const sf::Color Brown  = sf::Color(128, 64, 48);

const sf::Color Orange = sf::Color(255, 165, 48);


#endif //#endif _GRAPHIC_H_