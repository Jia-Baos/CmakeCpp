#include "./ChainofResponsibility/ChainofResponsibility.hpp"
#include "./Command/Command.hpp"
#include "./Interpreter/Interpreter.hpp"
#include "./Iterator/Iterator.hpp"
#include "./Mediator/Mediator.hpp"
#include "./Memento/Memento.hpp"
#include "./Observer/Observer.hpp"
#include "./State/State.hpp"
#include "./Strategy/Strategy.hpp"
#include "./TemplateMethod/TemplateMethod.hpp"
#include "./Visitor/Visitor.hpp"

void BehavioralPatternsTest()
{
    std::cout << "-----------ChainofResponsibilityTest-----------" << std::endl;
    ChainofResponsibilityTest();
    std::cout << "-----------CommandTest-------------------------" << std::endl;
    CommandTest();
    std::cout << "-----------InterpreterTest---------------------" << std::endl;
    InterpreterTest();
    std::cout << "-----------IteratorTest------------------------" << std::endl;
    IteratorTest();
    std::cout << "-----------MediatorTest------------------------" << std::endl;
    MediatorTest();
    std::cout << "-----------MementoTest-------------------------" << std::endl;
    MementoTest();
    std::cout << "-----------ObserverTest------------------------" << std::endl;
    ObserverTest();
    std::cout << "-----------StateTest---------------------------" << std::endl;
    StateTest();
    std::cout << "-----------StrategyTest------------------------" << std::endl;
    StrategyTest();
    std::cout << "-----------TemplateMethodTest------------------" << std::endl;
    TemplateMethodTest();
    std::cout << "-----------VisitorTest-------------------------" << std::endl;
    VisitorTest();
    std::cout << "-----------BehavioralPatterns End--------------" << std::endl;
}