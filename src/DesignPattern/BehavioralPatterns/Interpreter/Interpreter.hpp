#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <sstream>

// 上下文类，包含解释表达式时需要的全局信息
class Context {
public:
    void SetVariable(const std::string &name, const int value)
    {
        variables_[name] = value;
    }

    int GetVariable(const std::string &name)
    {
        return variables_[name];
    }

private:
    std::unordered_map<std::string, int> variables_;
};

// 抽象表达式类
class Expression {
public:
    virtual ~Expression() = default;
    virtual int Interpret(std::shared_ptr<Context> &context) const = 0;
};

// 终结符表达式类，表示一个数字
class Number : public Expression {
public:
    Number(int value)
        : value_(value) {}

    int Interpret(std::shared_ptr<Context> &context) const override
    {
        return value_;
    }

private:
    int value_;
};

// 非终结符表达式类，表示加法操作
class AddExpression : public Expression {
public:
    AddExpression(std::shared_ptr<Expression> &left, std::shared_ptr<Expression> &right)
        : left_(left), right_(right) {}

    int Interpret(std::shared_ptr<Context> &context) const override
    {
        return left_->Interpret(context) + right_->Interpret(context);
    }

private:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;
};

// 非终结符表达式类，表示减法操作
class SubtractExpression : public Expression {
public:
    SubtractExpression(std::shared_ptr<Expression> &left, std::shared_ptr<Expression> &right)
        : left_(left), right_(right) {}

    int Interpret(std::shared_ptr<Context> &context) const override
    {
        return left_->Interpret(context) - right_->Interpret(context);
    }

private:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;
};

// 解释器类，负责将输入的表达式解析为相应的表达式树
class ExpressionParser {
public:
    static std::shared_ptr<Expression> Parse(const std::string &expression)
    {
        std::istringstream stream(expression);
        return ParseExpression(stream);
    }

private:
    static std::shared_ptr<Expression> ParseExpression(std::istringstream &stream)
    {

        auto left = ParseTerm(stream);
        while (stream.peek() == '+' || stream.peek() == '-' || stream.peek() == ' ') {

            char op = stream.get(); // 取出一个字节后，stream 指针会后移
            if (op == ' ') {
                continue;
            }

            // only for display intermediate result
            // std::shared_ptr<Context> context1 = std::make_shared<Context>();
            // std::cout << "--------" << left->interpret(context1) << std::endl;

            auto right = ParseTerm(stream);
            if (op == '+') {
                left = std::make_shared<AddExpression>(left, right);
            } else if (op == '-') {
                left = std::make_shared<SubtractExpression>(left, right);
            }
        }
        return left;
    }

    static std::shared_ptr<Expression> ParseTerm(std::istringstream &stream)
    {
        int value;
        stream >> value; // 读取流中的第一个整数值
        return std::make_shared<Number>(value);
    }
};

void InterpreterTest()
{
    // 创建上下文
    std::shared_ptr<Context> context = std::make_shared<Context>();

    // 解析表达式 "1 + 2 - 3"
    std::string expression = "1 + 2 - 3";
    auto expr = ExpressionParser::Parse(expression);

    // 计算结果
    int result = expr->Interpret(context);
    std::cout << "Result: " << result << std::endl; // 输出: Result: 0
}
