#include <SFML/Graphics.hpp>
#include <iostream>
#include "Downloader.h"
#include "ProgressBar.h"

using namespace std;
using namespace sf;

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    RenderWindow window(VideoMode(385, 110), "Craftdium Updater");
    window.setFramerateLimit(60);
    Event event;

    auto& down = Downloader::instance;

    down.queue("https://launcher.mojang.com/download/Minecraft.exe", "Minecraft.exe");
    down.setBackgroundColor(Color::Blue);
    down.setForegroundColor(Color::Red);
    down.setPosition(50, 35);
    down.setScale(2, 1.5);
    Downloader::instance.start();

    while (window.isOpen())
    {
        window.clear(Color::White);
        window.draw(Downloader::instance);
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