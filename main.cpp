#include <stdio.h>

#include "src/molecules/molecules_manager/molecules_manager.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(Default_window_width, Default_window_height), "Gas model");

    
    MoleculesManager mol_manager(Dot(20.0, 20.0), Dot(900.0, 700.0), 10.0, 10.0);

    
    mol_manager.AddMolecule(MOL_SQUARE);
    mol_manager.AddMolecule(MOL_CIRCLE);
    mol_manager.AddMolecule(MOL_CIRCLE);
    mol_manager.AddMolecule(MOL_SQUARE);
    mol_manager.AddMolecule(MOL_CIRCLE);

    sf::Event event;
    while (window.isOpen())
    {   
        window.clear();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        mol_manager.Show(window);
        mol_manager.MoleculesMovment();
    
        window.display();
        
        sleep(1);

    }

    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}