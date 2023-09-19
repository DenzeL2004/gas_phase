#include "gas_model.h"


static const char* red_button  = "src/img/red_button.png";
static const char* blue_button = "src/img/blue_button.png";

static const char* arrow_up = "src/img/arrow_up.png";
static const char* arrow_down = "src/img/arrow_down.png";



GasModel::GasModel(const AtomsManager &atoms_manager):
        atoms_manager_(atoms_manager), buttons_manager_()
{

    Dot pos = atoms_manager_.GetLeftUp();
    
    buttons_manager_.AddButton(new Button(red_button, red_button, red_button,    Dot(20.0, 710.0), new NewAtom(ATOM_CIRCLE, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(blue_button, blue_button, blue_button, Dot(20.0, 800.0), new NewAtom(ATOM_SQUARE, &atoms_manager_)));

    buttons_manager_.AddButton(new Button(arrow_up, arrow_up, arrow_up,       Dot(220.0, 710.0), new MovePiston(-10.0, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(arrow_down, arrow_down, arrow_down, Dot(220.0, 810.0), new MovePiston(10.0, &atoms_manager_)));


    return;
}

//==============================================================================================================

void GasModel::Show(sf::RenderWindow &window)
{

    sf::Event event;
    while (window.isOpen())
    {   
        window.clear();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        atoms_manager_.AtomsMovment();

       
        buttons_manager_.DetectPresse();
    
        window.display();
    }

}

//==============================================================================================================

void GasModel::DrawEnvironment(sf::RenderWindow &window) const
{
    atoms_manager_.Show(window);

    Draw
    buttons_manager_.ShowButtons(window);
}

//==============================================================================================================