#include <iostream>
#include "Application.h"

int main(int arg, char** arge)
{
	
	
    try
    {
        Application* app = Application::GetInstance();
        app->initApp();
        //app.getRoot()->startRendering();
        app->Run();
        app->closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }
	return 0;

}