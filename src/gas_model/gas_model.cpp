#include "gas_model.h"


static const char* Red_button_file  = "src/img/red_button.png";
static const char* Blue_button_file = "src/img/blue_button.png";

static const char* Arrow_up_file   = "src/img/arrow_up.png";
static const char* Arrow_down_file = "src/img/arrow_down.png";  

static const char* Degree_up_file  = "src/img/degree_up.png";
static const char* Degre_down_file = "src/img/degree_down.png";  

static const Dot Piston_title = Dot(220.0, 710.0);
static const Dot Walls_title = Dot(340.0, 710.0);

static const double Time_show = 10;


GasModel::GasModel(const AtomsManager &atoms_manager):
        atoms_manager_(atoms_manager), buttons_manager_()
{

    Dot pos = atoms_manager_.GetLeftUp();
    
    buttons_manager_.AddButton(new Button(Red_button_file, Red_button_file, Red_button_file,    Dot(20.0, 710.0), new NewAtom(ATOM_CIRCLE, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Blue_button_file, Blue_button_file, Blue_button_file, Dot(20.0, 800.0), new NewAtom(ATOM_SQUARE, &atoms_manager_)));

    buttons_manager_.AddButton (new Button(Arrow_up_file, Arrow_up_file, Arrow_up_file,      Dot(240.0, 750.0), new MovePiston(-20.0, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Arrow_down_file, Arrow_down_file, Arrow_down_file, Dot(240.0, 850.0), new MovePiston(20.0, &atoms_manager_)));

    buttons_manager_.AddButton (new Button(Degree_up_file, Degree_up_file, Degree_up_file,   Dot(350.0, 750.0), new ChangeDegree(2.0, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Degre_down_file, Degre_down_file, Degre_down_file, Dot(350.0, 820.0), new ChangeDegree(-2.0, &atoms_manager_)));


    return;
}

//==============================================================================================================

void GasModel::Show(sf::RenderWindow &window)
{

    while (window.isOpen())
    {   
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        this->DrawEnvironment(window);

        atoms_manager_.AtomsMovment();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            buttons_manager_.DetectPresse();
    
        window.display();
    }

}

//==============================================================================================================

void GasModel::DrawEnvironment(sf::RenderWindow &window) const
{
    static sf::Clock clock;

    double delta_time = clock.getElapsedTime().asMilliseconds();


    if (delta_time > Time_show)
    {
        atoms_manager_.Show(window);

        WriteText(window, Piston_title, "Piston", Oldtimer_font_path);

        buttons_manager_.ShowButtons(window);
    }

    return;
}

//==============================================================================================================