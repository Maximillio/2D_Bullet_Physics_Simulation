#include "Controllers/MainController.hpp"

int main()
{
    try
    {
        MainController controller;
        controller.start();
    }
    catch (const std::exception& exception)
    {
        // Not used in this case.
        (void)exception;
        exit(1);
    }
    return 0;
}

