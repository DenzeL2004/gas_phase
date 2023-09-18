#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../graphic.h"

class Button
{

    public:
        Button  (const char *stat_texture_file, const char *point_texture_file, const char *press_texture_file, 
                 const Dot &pos);

        ~Button()
        {
            stat_texture_.~Texture();
            point_texture_.~Texture();
            press_texture_.~Texture();
        }

        virtual void Draw(sf::RenderWindow &window, sf::Texture texture) const;

        virtual void Action() = 0;

        bool CheckCursorOnButton();

        bool CheckButtonPress();

    protected:
        sf::Texture stat_texture_, point_texture_, press_texture_;
        Dot left_up_;

        bool flag_pressed_;
};


enum Buttons_err
{
    LOAD_TEXTURE_TO_STAT,
    LOAD_TEXTURE_TO_POINT,
    LOAD_TEXTURE_TO_PRESS,  
};

class Button
{

    public:
        Button  (const char *stat_texture_file, const char *point_texture_file, const char *press_texture_file, 
                 const Dot &pos);

        ~Button()
        {
            stat_texture_.~Texture();
            point_texture_.~Texture();
            press_texture_.~Texture();
        }

        virtual void Draw(sf::RenderWindow &window, sf::Texture texture) const;

        virtual void Action() = 0;

        bool CheckCursorOnButton();

        bool CheckButtonPress();

    protected:
        sf::Texture stat_texture_, point_texture_, press_texture_;
        Dot left_up_;

        bool flag_pressed_;
};



#endif
