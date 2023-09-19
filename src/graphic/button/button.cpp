#include "button.h"


Button::Button (const char *stat_texture_file, const char *point_texture_file, const char *press_texture_file,
                const Dot &pos, const Action *action):
                action_(nullptr), stat_texture_(), point_texture_(), press_texture_(), left_up_(), flag_pressed_(false)
{
    assert(action != nullptr && "action is nullptr");

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

    action_ = action;

    return;

}

//================================================================================

void Button::Draw(sf::RenderWindow &window) const
{
    const sf::Texture *texture = nullptr;

    if (this->CheckCursorOnButton())
    {
        texture = &point_texture_;
    }
    else if (flag_pressed_)
        texture = &press_texture_;
    else
        texture = &stat_texture_;
    

    sf::Sprite button_sprite;
    button_sprite.setTexture(*texture);
    button_sprite.setPosition((float)left_up_.GetX(), (float)left_up_.GetY());

    window.draw(button_sprite);

    return;
}

//================================================================================

bool Button::CheckCursorOnButton() const
{
    const sf::Texture *texture;

    if (flag_pressed_)  texture = &stat_texture_;
    else                texture = &press_texture_;

    double width  = (double)texture->getSize().x;
    double hieght = (double)texture->getSize().y;

    double mouse_x = (double)sf::Mouse::getPosition().x;
    double mouse_y = (double)sf::Mouse::getPosition().y - 65.0;

    bool res = (left_up_.GetX() < mouse_x  && mouse_x < left_up_.GetX() + width &&
                left_up_.GetY() < mouse_y  && mouse_y < left_up_.GetY() + hieght);

    return res;
}

//================================================================================

bool Button::CheckClick() const 
{
    
    const size_t Delay = 100;
    
    bool now = this->CheckCursorOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    bool after = true;
    for (size_t it = 0; it < Delay; it++)
        after = after && this->CheckCursorOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    return (now == true && after == false);
}

//================================================================================

void ButtonsManager::ShowButtons(sf::RenderWindow &window) const
{
    for (size_t it = 0 ; it < buttons_.size(); it++)
    {
        buttons_[it]->Draw(window);
    }    

    return;
}

//================================================================================

void ButtonsManager::DetectPresse() const
{
    for (size_t it = 0 ; it < buttons_.size(); it++)
    {
        if(buttons_[it]->CheckClick()) 
        {
            buttons_[it]->SetFlag((*buttons_[it]->action_)());
            
        }
    }    

    return;
}

//================================================================================