#include <iostream>
#include "Application.h"

int main(int argc, char** argv)
{
    try
    {
        Application* a = Application::GetInstance();
        a->initApp();
        a->Run();
        a->closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;

}