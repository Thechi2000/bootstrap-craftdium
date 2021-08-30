#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Test");
    window.display();
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