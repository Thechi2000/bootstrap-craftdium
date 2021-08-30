#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "Downloader.h"

using namespace std;
using namespace sf;

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    RenderWindow window(VideoMode(385, 110), "Craftdium Updater");
    window.setFramerateLimit(60);
    Event event;

    Downloader::instance.queue({ "https://launcher.mojang.com/download/Minecraft.exe", "Minecraft.exe" });
    Downloader::instance.start();

    while (window.isOpen())
    {
        window.clear(Color::White);
        window.display();

        window.pollEvent(event);
        
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }

    Downloader::instance.stop();
}