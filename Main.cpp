#include "Tests/ForceTest.h"
#include "Tests/JointTest.h"
#include "Tests/ParticleTest.h"



int main(int argc, char* argv[])
{
    Test* test = new JointTest();
    test->Initialize();

    while (!test->IsQuit()) { test->Run(); }
    delete test;

    return 0;
}