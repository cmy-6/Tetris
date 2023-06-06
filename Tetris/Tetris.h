#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h" 
using namespace std;
class Tetris
{
public:
    Tetris();   // 构造函数
    /**
     * @brief Tetris 构造函数
     * @param rows  游戏界面是多少行
     * @param cols  多少列
     * @param left  游戏区域距离背景的左边界
     * @param top   游戏区域距离背景的上边界
     * @param blockSize 每个小方块的大小
     */
    Tetris(int rows, int cols, int left, int top, int blockSize);
    /**
     * @brief init 模块初始化
     */
    void init();
    /**
     * @brief play 开始游戏
     */
    void play();
private:

    /**
     * @brief keyEvent: 接收用户输入的 API接口
     */
    void keyEvent();    // 内部自己使用

    /**
     * @brief updateWindow: 渲染游戏界面， 更新窗口
     */
    void updateWindow(); // 内部自己使用 归成私有

    /**
     * @brief getDelay : 返回距离上一次调用该函数， 间隔了多少时间（ms） | 第一次调用该函数， 返回0
     * @return : int
     */
    int getDelay();

    /**
     * @brief drop: 方块降落
     */
    void drop();

    /**
     * @brief clearLine: 清行
     */
    void clearLine();

    // 方块的左右移动
    void moveLeftRight(int offset);


// 私有数据成员
private:
    int delay;      // 刷新时间间隔
    bool update;    // 是否更新

    // C++ 的STL 方便拓展
    /**
     * 0: 空白， 没有任何方块
     * 1 - 7 
     * 5: 是第5种俄罗斯方块
     */
    vector<vector<int>> map;

    int rows;   // 该游戏的行数
    int cols;
    int leftMargin; // 游戏区域距离背景的左侧边界
    int topMargin;  // 顶部边界
    int blockSize;  // 方块大小

    IMAGE imgBg;    // 游戏的背景图片


    Block* curBlock;    // 当前方块
    Block* nextBlock;   // 下一个预告方块

    // 这里用指针， 那就没有备份作用了
    Block bakBlock;     // 当前方块降落过程中， 用来备份上一个合法位置的！（最终方块会落到底下）

    // 问题Tip 1: 当方块降落到最下面停止不动了， 这个情况如何分析？
    // 问题Tip 2: 俄罗斯方块的左右移动
};

