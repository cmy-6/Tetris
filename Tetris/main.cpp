#include <iostream>
#include "Tetris.h"
using namespace std;

int main()
{
    Tetris game(20, 10, 263, 133, 36);  // 根据游戏背景计算
    game.play();    // 启动游戏
    return 0;
}
