#include "main.h"

using namespace std;

int main()
{

    printf("Hello everyone \n");

    Engine engine;

    engine.Initialize("Roma");
    
    this_thread::sleep_for(chrono::seconds(3));

    engine.closeEngine();

    return 0;
}