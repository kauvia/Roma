#include "main.h"

using namespace std;

int main()
{

    printf("Hello everyone \n");

    Engine engine;

    engine.Initialize("Roma");

    if (!engine.runLoop())
    {
        engine.closeEngine();
        return 0;
    }

    return 0;
}