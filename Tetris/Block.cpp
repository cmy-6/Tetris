#include "Block.h"
#include <stdlib.h>

// 初始化为空
IMAGE* Block::imgs[7] = { NULL };
// 4个小方块， 其颜色从tiles中取 | 不同类型的方块可以用不同的颜色
int Block::size = 36;

Block::Block()
{
    // 最开始为空， 要将7种方块配置 | 初始化一次
    if (imgs[0] == NULL) {
        /**
        * 放在一张图片（tiles.png）中是为了节省空间， 使用代码进行切割高效
        */
        IMAGE imgTmp;

        // 1. 加载图片到内存中
        loadimage(&imgTmp, "res/tiles.png");

        // 2. 设置切割对象
        SetWorkingImage(&imgTmp);
        for (int i = 0; i < 7; ++i) {
            imgs[i] = new IMAGE;    // 给指针指向分配内存空间
            getimage(imgs[i], i * size, 0, size, size); // 切割图片， x, y, width， height
        }
        // 3. 切割完图片后要恢复工作区
        SetWorkingImage();  

    }


    // 1. 定义俄罗斯方块的初始形态
    /*
     * 在具体显示的时候， 包含了4个小方块
     */
    int blocks[7][4] =
    {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z 1型
        3, 5, 4, 6, // Z 2型
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // 田
    };

    // 2. 随机生成一种俄罗斯方块
    blockType = 1 + rand() % 7; // 1 + 0..6 => 1..7 类型1-7

    // 3. 初始化 smallBlocks
    /*
     * 创建俄罗斯方块时， 其类型 blockType 已知，这种类型里具体的四个小方块的推算如下：第几行， 第几列
     */
    for (int i = 0; i < 4; ++i) {
        int value = blocks[blockType - 1][i];
        // Point smallBlocks[4];   // 此结构体数组存储一个俄罗斯方块的4个小方块的row与col | 一个俄罗斯方块的位置 | 第几行第几列
        smallBlocks[i].row = value / 2;
        smallBlocks[i].col = value % 2;
    }

    // 4. 本身图片指向哪一个 | 确定好方块类型， 各个小方块的位置
    img = imgs[blockType - 1];




}
/**
 * @brief drop 下降
 */
void Block::drop()
{

}
/**
 * @brief moveLeftRight : 根据offset 来让方块左移动或者右移动
 * @param offset
 */
void Block::moveLeftRight(int offset)
{

}
/**
 * @brief rotate:方块旋转
 */
void Block::rotate()
{

}
/**
 * @brief draw: 画方块取决于方块游戏其左侧边界和顶部边界有多大
 * @param leftMargin
 * @param topMargin
 */
void Block::draw(int leftMargin, int topMargin)
{
    // 方块绘制->分4个小方块 | 确定第几行第几列结合左部边界与顶部边界， 行高， 列宽
    for (int i = 0; i < 4; ++i) {
        int x = leftMargin + smallBlocks[i].col * size;
        int y = topMargin + smallBlocks[i].row * size;

        putimage(x, y, img);    // 画图像（方块）
    }


}
