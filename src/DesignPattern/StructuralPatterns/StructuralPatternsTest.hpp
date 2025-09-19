#include "./Adapter/Adapter.hpp"
#include "./Bridge/Bridge.hpp"
#include "./Composite/Composite.hpp"
#include "./Decorator/Decorator.hpp"
#include "./Facade/Facade.hpp"
#include "./Flyweight/Flyweight.hpp"
#include "./Proxy/Proxy.hpp"

void StructuralPatternsTest()
{
    std::cout << "---------AdapterTest1----------------" << std::endl;
    AdapterTest1();
    std::cout << "---------AdapterTest2----------------" << std::endl;
    AdapterTest2();
    std::cout << "---------BridgeTest------------------" << std::endl;
    BridgeTest();
    std::cout << "---------CompositeTest---------------" << std::endl;
    CompositeTest();
    std::cout << "---------DecoratorTest---------------" << std::endl;
    DecoratorTest();
    std::cout << "---------FacadeTest------------------" << std::endl;
    FacadeTest();
    std::cout << "---------FlyweightTest---------------" << std::endl;
    FlyweightTest();
    std::cout << "---------ProxyTest-------------------" << std::endl;
    ProxyTest();
    std::cout << "---------StructuralPatternsTest End--" << std::endl;
}
