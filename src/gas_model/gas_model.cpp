#include "gas_model.h"


static const char* Red_button_file  = "src/img/red_button.png";
static const char* Blue_button_file = "src/img/blue_button.png";

static const char* Arrow_up_file   = "src/img/arrow_up.png";
static const char* Arrow_down_file = "src/img/arrow_down.png";  

static const char* Degree_up_file  = "src/img/degree_up.png";
static const char* Degre_down_file = "src/img/degree_down.png";  

static const char* Cross_file  = "src/img/cross.png";
static const char* Tick_file = "src/img/tick.png";  

static const Dot Piston_title       = Dot(220.0, 710.0);
static const Dot Temperature_title  = Dot(1035, 45.0);
static const Dot Pressure_title     = Dot(1035, 525.0);

static const double Time_show = 10;


void GasModel::Example()
{
    
    buttons_manager_.AddButton(new Button(Red_button_file, Red_button_file,   Dot(20.0, 710.0), new NewAtom(ATOM_CIRCLE, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Blue_button_file, Blue_button_file, Dot(20.0, 800.0), new NewAtom(ATOM_SQUARE, &atoms_manager_)));

    buttons_manager_.AddButton(new Button(Arrow_up_file, Arrow_up_file,      Dot(240.0, 750.0), new MovePiston(-20.0, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Arrow_down_file, Arrow_down_file,  Dot(240.0, 850.0), new MovePiston(20.0, &atoms_manager_)));

    buttons_manager_.AddButton(new Button(Degree_up_file, Degree_up_file,   Dot(350.0, 750.0), new ChangeDegree(0.5, &atoms_manager_)));
    buttons_manager_.AddButton(new Button(Degre_down_file, Degre_down_file, Dot(350.0, 820.0), new ChangeDegree(-0.5, &atoms_manager_)));

    buttons_manager_.AddButton(new Button(Cross_file, Tick_file, Dot(950.0, 20.0),  new ButtonState));
    buttons_manager_.AddButton(new Button(Cross_file, Tick_file, Dot(950.0, 500.0), new ButtonState));

    return;
}

//==============================================================================================================

void GasModel::Show(sf::RenderWindow &window)
{
    this->Example();

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

        buttons_manager_.DetectPresse(event);
    
        window.display();
    }

}

//==============================================================================================================

void GasModel::DrawEnvironment(sf::RenderWindow &window) 
{
    static sf::Clock clock;

    double delta_time = clock.getElapsedTime().asMilliseconds();


    if (delta_time > Time_show)
    {
        atoms_manager_.Show(window);

        WriteText(window, Piston_title, "Piston", Oldtimer_font_path);

        WriteText(window, Temperature_title, "Temperature", Oldtimer_font_path);
        if (buttons_manager_.GetButtonState(6)) //show temperature 
            this->DrawTemperatureChart(window);

        WriteText(window, Pressure_title, "Perssure", Oldtimer_font_path);
        if (buttons_manager_.GetButtonState(7)) //show temperature 
            this->DrawPerssureGraphic(window);

        buttons_manager_.ShowButtons(window);
    }

    return;
}

//==============================================================================================================

void GasModel::DrawTemperatureChart(sf::RenderWindow &window) const
{
    
    double temperature = atoms_manager_.GetTemperature();

    DrawLine(window, Dot(1035.0, 480.0), Dot(1235.0, 480.0));
    DrawRectangle(window, Dot(1075.0, 480.0 - temperature), Dot(1195.0, 480.0));

    char buffer[BUFSIZ];
    sprintf(buffer, "%5.3lg", temperature);

    WriteText(window, Dot(1100.0, 480.0 - temperature - 40.0), buffer, Oldtimer_font_path);

    return;
}

//==============================================================================================================


void GasModel::DrawPerssureGraphic(sf::RenderWindow &window)
{
    const size_t size_limit = 10u;
    static std::vector<double> last_val;
    size_t size = last_val.size();

    static sf::Clock clock;
    double delta_time = clock.getElapsedTime().asSeconds();
    

    if (delta_time > 2.0)
    {
        double perssure = atoms_manager_.GetPreasure();

        if (size < size_limit)
        {
            last_val.push_back(perssure);
        }
        else
        {
            for (size_t it = 0; it < size - 1; it++)
                last_val[it] = last_val[it + 1];
            
            last_val[size - 1] = perssure;
        }

        clock.restart();
    }

    Dot Def_coord(1000.0, 900.0);
    const Vector vec_x(60.0, 0.0), vec_y(0, -3.0);

    for (size_t it = 1; it < size; it++)
    {
        DrawLine(window, Def_coord + vec_x * (double)(it - 1) + vec_y * last_val[it - 1], 
                         Def_coord + vec_x * (double)it       + vec_y * last_val[it]);
    }

    char buffer[BUFSIZ];

    for (size_t it = 0; it < size; it++)
    {
        Dot pos = Def_coord + vec_x * (double)it + vec_y * last_val[it];
        DrawCircle(window, pos, 5.0);

        sprintf(buffer, "%5.3lg", last_val[it]);
        WriteText(window, pos + Vector(0.0, -40.0), buffer, Oldtimer_font_path, 10, sf::Color::Red);
    }


    return;
}

//==============================================================================================================