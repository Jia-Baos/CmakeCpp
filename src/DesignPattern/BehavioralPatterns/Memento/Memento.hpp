#pragma once
#include <vector>
#include <iostream>
#include <memory>

// 备忘录类，用于保存发起人状态
class Memento {
public:
    Memento(const std::string &state)
        : state_(state) {}

    const std::string &GetState() const
    {
        return state_;
    }

private:
    std::string state_;
};

// 发起人类，保存和恢复状态
class TextEditor {
public:
    void SetText(const std::string &text)
    {
        text_ = text;
    }

    const std::string &GetText() const
    {
        return text_;
    }

    // 创建备忘录对象，保存当前状态
    std::shared_ptr<Memento> CreateMemento() const
    {
        return std::make_shared<Memento>(text_);
    }

    // 恢复备忘录中的状态
    void RestoreMemento(const std::shared_ptr<Memento> &memento)
    {
        text_ = memento->GetState();
    }

private:
    std::string text_;
};

// 看护者类，负责保存和恢复备忘录
class Caretaker {
public:
    void SaveMemento(const std::shared_ptr<Memento> &memento)
    {
        mementos_.push_back(memento);
    }

    std::shared_ptr<Memento> GetMemento(int index) const
    {
        if (index < mementos_.size()) {
            return mementos_[index];
        }
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Memento>> mementos_;
};

void MementoTest()
{
    // 创建发起人对象（文本编辑器）
    std::shared_ptr<TextEditor> editor = std::make_shared<TextEditor>();
    std::shared_ptr<Caretaker> caretaker = std::make_shared<Caretaker>();

    // 设置一些文本
    editor->SetText("Hello, World!");
    std::cout << "Text: " << editor->GetText() << std::endl;

    // 保存当前状态
    caretaker->SaveMemento(editor->CreateMemento());

    // 修改文本
    editor->SetText("Hello, C++!");
    std::cout << "Text: " << editor->GetText() << std::endl;

    // 保存修改后的状态
    caretaker->SaveMemento(editor->CreateMemento());

    // 修改文本
    editor->SetText("Goodbye, C++!");
    std::cout << "Text: " << editor->GetText() << std::endl;

    // 恢复到之前的状态
    editor->RestoreMemento(caretaker->GetMemento(1));
    std::cout << "Text after restore: " << editor->GetText() << std::endl;

    // 恢复到最初的状态
    editor->RestoreMemento(caretaker->GetMemento(0));
    std::cout << "Text after restore: " << editor->GetText() << std::endl;
}
