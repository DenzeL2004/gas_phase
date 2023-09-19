#include <stdio.h>

#include "src/atom/atoms_manager/atoms_manager.h"
#include "src/gas_model/gas_model.h"

int main()
{
     #ifdef USE_LOG
        if (OpenLogsFile()) 
            return OPEN_FILE_LOG_ERR;
    #endif

    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(Default_window_width, Default_window_height), "Gas model");

    
    GasModel gas_model(AtomsManager(Dot(20.0, 20.0), Dot(900.0, 700.0), 1.0, 50.0));
    gas_model.Show(window);
    
    #ifdef USE_LOG
        if (CloseLogsFile ())
            return OPEN_FILE_LOG_ERR;
    #endif

    return EXIT_SUCCESS;
}