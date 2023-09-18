#include <stdio.h>

#include "src/atom/atoms_manager/atoms_manager.h"

const char* red_button = "src/img/red_button.png";
const char* blue_button = "src/img/blue_button.png";

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(Default_window_width, Default_window_height), "Gas model");

    
    AtomsManager atom_manager(Dot(20.0, 20.0), Dot(900.0, 700.0), 1.0, 50.0);
    
    ButtonsManager buttons_manager;
    buttons_manager.AddButton(new Button(red_button, red_button, red_button, Dot(20.0, 710.0), new NewCircleAtom(&atom_manager)));
    buttons_manager.AddButton(new Button(blue_button, blue_button, blue_button, Dot(20.0, 800.0), new NewSquareAtom(&atom_manager)));


    sf::Event event;
    while (window.isOpen())
    {   
        window.clear();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        atom_manager.Show(window);
        atom_manager.AtomsMovment();

        buttons_manager.ShowButtons(window);
        buttons_manager.DetectPresse();
    
        window.display();
    }

    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}