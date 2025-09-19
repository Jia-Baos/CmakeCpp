#include "./BehavioralPatterns/BehavioralPatternsTest.hpp"
#include "./CreationalPatterns/CreationalPatternsTest.hpp"
#include "./StructuralPatterns/StructuralPatternsTest.hpp"

int main(int argc, char *argv[])
{
    CreationalPatternsTest();
    StructuralPatternsTest();
    BehavioralPatternsTest();

    return 0;
}
