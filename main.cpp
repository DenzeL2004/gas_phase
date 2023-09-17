#include <stdio.h>

#include "src/molecules/molecules.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    sf::RenderWindow window(sf::VideoMode(Default_window_width, Default_window_height), "Gas model");

    
    CircleMolecule circle({30.0, 100.0, 0.0}, {1.0, 1.0, 1.0});
    SquareMolecule square({100.0, 100.0, 0.0}, {1.0, 1.0, 1.0});



    sf::Event event;
    while (window.isOpen())
    {   
        window.clear();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        circle.Draw(window);
        square.Draw(window);
    
        window.display();

    }

    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}