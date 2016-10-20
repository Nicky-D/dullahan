/*
    @brief Dullahan - a headless browser rendering engine
           based around the Chromium Embedded Framework

           Example: capture a web page to image file with a console app

    @author Callum Prentice - September 2016

    LICENSE FILE TO GO HERE
*/

#include <iostream>
#include <functional>
#include <string>
#include <fstream>

#include "dullahan.h"

dullahan* headless_browser;

unsigned char* gPixels = 0;
int gWidth = 0;
int gHeight = 0;

void writeBMPImage(const std::string& filename,
                   unsigned char* pixels,
                   int image_width, int image_height)
{
    std::cout << "Writing output image (BMP) (" << image_width << " x " << image_height << ") to " << filename << std::endl;

    std::ofstream img_stream(filename.c_str(), std::ios::binary | std::ios::out);
    if (img_stream)
    {
        unsigned char file[14] =
        {
            'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 40 + 14, 0, 0, 0
        };
        unsigned char info[40] =
        {
            40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x13, 0x0B, 0, 0, 0x13, 0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };
        int size_data = image_width * image_height * 3;
        int size_all = size_data + sizeof(file) + sizeof(info);

        file[2] = (unsigned char)(size_all);
        file[3] = (unsigned char)(size_all >> 8);
        file[4] = (unsigned char)(size_all >> 16);
        file[5] = (unsigned char)(size_all >> 24);

        info[4] = (unsigned char)(image_width);
        info[5] = (unsigned char)(image_width >> 8);
        info[6] = (unsigned char)(image_width >> 16);
        info[7] = (unsigned char)(image_width >> 24);

        info[8] = (unsigned char)(-image_height);
        info[9] = (unsigned char)(-image_height >> 8);
        info[10] = (unsigned char)(-image_height >> 16);
        info[11] = (unsigned char)(-image_height >> 24);

        info[20] = (unsigned char)(size_data);
        info[21] = (unsigned char)(size_data >> 8);
        info[22] = (unsigned char)(size_data >> 16);
        info[23] = (unsigned char)(size_data >> 24);

        img_stream.write((char*)file, sizeof(file));
        img_stream.write((char*)info, sizeof(info));

        const int image_depth = 4;
        for (int i = 0; i < image_width * image_height * image_depth; i += image_depth)
        {
            const unsigned char red = *(pixels + i + 2);
            const unsigned char green = *(pixels + i + 1);
            const unsigned char blue = *(pixels + i + 0);

            img_stream << blue;
            img_stream << green;
            img_stream << red;
        }

        img_stream.close();
    }
}

void onPageChanged(const unsigned char* pixels, int x, int y, int width,
                   int height, bool is_popup)
{
    std::cout << "Page changed" << std::endl;

    gPixels = (unsigned char*)pixels;
    gWidth = width;
    gHeight = height;
}

void onLoadStart()
{
    std::cout << "Page load started" << std::endl;
}

void onLoadEnd(int code)
{
    std::cout << "Page load ended with code " << code << std::endl;

    if (code == 200)
    {
        writeBMPImage("output.bmp", gPixels, gWidth, gHeight);
    }

    headless_browser->requestExit();
}

void onRequestExit()
{
    std::cout << "Exit requested - shutting down and exiting" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string url = "https://news.google.com";
    if (argc == 2)
    {
        url = std::string(argv[1]);
    }

    headless_browser = new dullahan();

    std::cout << "Dullahan console test" << std::endl << std::endl;
    std::cout << "Capturing: " << url << std::endl << std::endl;
    std::cout << "Dullahan version: " << headless_browser->dullahan_version() << std::endl << std::endl;

    headless_browser->setOnPageChangedCallback(std::bind(onPageChanged,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
            std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    headless_browser->setOnLoadStartCallback(std::bind(onLoadStart));
    headless_browser->setOnLoadEndCallback(std::bind(onLoadEnd,
                                           std::placeholders::_1));
    headless_browser->setOnRequestExitCallback(std::bind(onRequestExit));

    dullahan::dullahan_settings settings;
    settings.initial_width = 1024;
    settings.initial_height = 3072;
    settings.javascript_enabled = true;
    settings.cookies_enabled = true;
    settings.user_agent_substring = "Console Test";
    settings.accept_language_list = "en-us";

    headless_browser->init(settings);

    headless_browser->navigate(url);

    headless_browser->run();

    headless_browser->shutdown();
}
