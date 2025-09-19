#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>

// 享元接口
class ChessPiece {
public:
    virtual ~ChessPiece() = default;
    virtual void Display(int x, int y) = 0; // 外部状态：棋子位置
};

// 具体享元：棋子的类型（例如，皇后）
class Queen : public ChessPiece {
public:
    void Display(int x, int y) override
    {
        std::cout << "Queen at position (" << x << ", " << y << ")\n";
    }
};

// 具体享元：骑士
class Knight : public ChessPiece {
public:
    void Display(int x, int y) override
    {
        std::cout << "Knight at position (" << x << ", " << y << ")\n";
    }
};

// 享元工厂：管理享元对象
class ChessPieceFactory {
public:
    std::shared_ptr<ChessPiece> GetChessPiece(const std::string &type)
    {
        if (pieces.find(type) == pieces.end()) {
            // 如果不存在，创建并保存到享元池
            if (type == "Queen") {
                pieces[type] = std::make_shared<Queen>();
            } else if (type == "Knight") {
                pieces[type] = std::make_shared<Knight>();
            }
        }
        return pieces[type]; // 返回共享对象
    }

private:
    std::unordered_map<std::string, std::shared_ptr<ChessPiece>> pieces;
};

// 客户端：管理棋盘上的棋子
class ChessBoard {
public:
    void PlacePiece(const std::string &pieceType, int x, int y)
    {
        std::shared_ptr<ChessPiece> piece = factory_.GetChessPiece(pieceType);
        piece->Display(x, y);
    }

private:
    ChessPieceFactory factory_;
};

void FlyweightTest()
{
    ChessBoard board;

    // 通过享元模式复用棋子对象
    board.PlacePiece("Queen", 1, 1);
    board.PlacePiece("Knight", 2, 2);
    board.PlacePiece("Queen", 3, 3); // 共享同一个Queen实例
}
