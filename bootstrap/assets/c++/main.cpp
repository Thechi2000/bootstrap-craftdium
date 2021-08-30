#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <curl/curl.h>
#pragma warning(disable : 4996)


void downloadFile(const char* url, const char* fname)
{
    CURL* curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();
    
    fp = fopen(fname, "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
    res = curl_easy_perform(curl);
    fclose(fp);
}


using namespace std;
using namespace sf;

int main(int argc, char* argv[])
{

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    RenderWindow window(VideoMode(385, 110), "Craftdium Updater");
    Event event;
    downloadFile("https://launcher.mojang.com/download/Minecraft.exe", "Minecraft.exe");

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