#include "button.h"


Button::Button (const char *stat_texture_file, const char *point_texture_file, const char *press_texture_file,
                const Dot &pos)
{
    if (!stat_texture_.loadFromFile(stat_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_STAT, "failed load teture from %s\n", stat_texture_file);
        return;
    }


    if (!point_texture_.loadFromFile(point_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_POINT, "failed load teture from %s\n", point_texture_file);
        return;
    }


    if (!press_texture_.loadFromFile(press_texture_file))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_TO_PRESS, "failed load teture from %s\n", press_texture_file);
        return;
    }

    left_up_ = pos;
    flag_pressed_ = false;

    return;

}

void Button::Draw(sf::RenderWindow &window, sf::Texture texture) const
{
    sf::Sprite button_sprite;
    button_sprite.setTexture(texture);
    button_sprite.setPosition(left_up_.GetX(), left_up_.GetY());

    window.draw(button_sprite);

    return;
}

bool Button::CheckCursorOnButton()
{
    sf::Texture *texture;

    if (flag_pressed_)  texture = &stat_texture_;
    else                texture = &press_texture_;

    int width  = (int)texture->getSize().x;
    int hieght = (int)texture->getSize().y;

    int mouse_x = sf::Mouse::getPosition().x;
    int mouse_y = sf::Mouse::getPosition().y;

    bool res = (left_up_.GetX() < mouse_x  && mouse_x < left_up_.GetX() + width &&
                left_up_.GetY() < mouse_y  && mouse_y < left_up_.GetY() + hieght);

    return res;
}

bool Button::CheckButtonPress()
{
    return this->CheckCursorOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}