#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../graphic.h"



//================================================================================

class Action
{
    public:
        Action(){};
        
        virtual ~Action() = default;

        virtual bool operator() () const = 0;
    
};

//================================================================================

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
                 const Dot &pos, const Action *action);

        Button(const Button &other) = default;

        virtual Button& operator= (const Button &other)
        {
            stat_texture_  = other.stat_texture_;
            point_texture_ = other.point_texture_;
            press_texture_ = other.press_texture_;

            delete action_;
            action_ = other.action_;

            return *this;
        }

        virtual ~Button()
        {
            stat_texture_.~Texture();
            point_texture_.~Texture();
            press_texture_.~Texture();

            delete action_;
        }


        virtual void Draw(sf::RenderWindow &window) const;

        virtual bool CheckCursorOnButton () const;

        virtual bool CheckClick         () const;

        bool GetFlag() const {return flag_pressed_;}
        
        void SetFlag(const bool flag) 
        {
            flag_pressed_ = flag;
            return;
        }

        const Action *action_; 

    protected:
        sf::Texture stat_texture_, point_texture_, press_texture_;
        Dot left_up_;

        bool flag_pressed_;
};


class ButtonsManager
{

    public:
        ButtonsManager (): buttons_(){}

        ~ButtonsManager ()
        {
            for (size_t it = 0; it < buttons_.size(); it++)
            {
                if (buttons_[it] != nullptr)
                    delete buttons_[it];
            }
                return;
        }

        void AddButton (Button *button)
        {
            buttons_.push_back(button);
            return;
        }

        void ShowButtons (sf::RenderWindow &window) const;

        void DetectPresse() const;


    protected:
        std::vector<Button*> buttons_;
};



#endif
