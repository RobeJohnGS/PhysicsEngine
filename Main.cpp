#include "ParticleTest.h"
#include "ForceTest.h"



int main(int argc, char* argv[])
{
    Test* test = new ForceTest();
    //ParticleTest* Ptest = new ParticleTest();
    //Ptest->Initialize();
    test->Initialize();

    while (!test->IsQuit()) { test->Run(); }
    delete test;

    return 0;
}