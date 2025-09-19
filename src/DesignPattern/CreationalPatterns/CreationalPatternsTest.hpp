#include "./AbstractFactory/AbstractFactory.hpp"
#include "./Builder/Builder.hpp"
#include "./FactoryMethod/FactoryMethod.hpp"
#include "./Prototype/Prototype.hpp"
#include "./Singleton/Singleton.hpp"

void CreationalPatternsTest()
{
    std::cout << "-----------AbstractFactoryTest-----------" << std::endl;
    AbstractFactoryTest();
    std::cout << "-----------BuilderTest-------------------" << std::endl;
    BuilderTest();
    std::cout << "-----------FactoryMethodTest-------------" << std::endl;
    FactoryMethodTest();
    std::cout << "-----------PrototypeTest-----------------" << std::endl;
    PrototypeTest();
    std::cout << "-----------SingletonTest-----------------" << std::endl;
    SingletonTest();
    std::cout << "-----------CreationalPatternsTest End----" << std::endl;
}