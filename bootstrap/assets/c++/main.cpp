#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    RenderWindow window(VideoMode(385, 110), "Craftdium Updater");
    Event event;

    while (window.isOpen())
    {
        window.clear(Color::White);
        window.display();

        window.waitEvent(event);
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
}