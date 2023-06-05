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
        int value = blocks[blockType - 1][i]; // 1 3 5 7
        // Point smallBlocks[4];   // 此结构体数组存储一个俄罗斯方块的4个小方块的row与col | 一个俄罗斯方块的位置 | 第几行第几列
        smallBlocks[i].row = value / 2;         // 0 1 2 3
        smallBlocks[i].col = value % 2;         // 1 1 1 1
    }

    // 4. 本身图片指向哪一个 | 确定好方块类型， 各个小方块的位置
    img = imgs[blockType - 1];




}
/**
 * @brief drop 俄罗斯方块下降
 * smallBlocks
 */
void Block::drop()
{
    // 在俄罗斯方块中有四个小方块Point 修改4个小方块的下标
    //for (int i = 0; i < 4; ++i) {
    //    smallBlocks[i].row++;
    //}

    // C++ 11 写法 | 每一次取出的 smallBlocks[i] 0 1 2 3 即block引用（即会修改原数组的值）
    for (auto& block : smallBlocks) {
        block.row++;
    }
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

IMAGE** Block::getImages()
{

    return imgs;
}
// & other ： 这个&是引用 | 另一个对象other
Block& Block::operator=(const Block& other)
{
    // TODO: 在此处插入 return 语句
    // 自己赋值自己是错误的 | 若另一个对象的地址等于这个指针本身, 则返回this对象的引用
    if (this == &other) return *this;
    // 其他情况
    this->blockType = other.blockType;
    for (int i = 0; i < 4; ++i) {
        this->smallBlocks[i] = other.smallBlocks[i];
    }

    return *this;



}
// 方块自身方法：判断数据的有效性
bool Block::blockInMap(const vector<vector<int>>& map)
{
    int rows = map.size();
    int cols = map[0].size();
    // 判断一个俄罗斯方块的四个方块坐标有没有越界且地图上该位置上有没有方块
    for (int i = 0; i < 4; ++i)
    {
        if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
            smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
            map[smallBlocks[i].row][smallBlocks[i].col])
        {
            return false;
        }
    }
    return true;
}
// 固化：bakBlock.solidify(map); 
// bakBlock是上一个在合法有效位置的俄罗斯方块（Tetris ---> drop之前）
void Block::solidify(vector<vector<int>>& map)
{
    // 空白位置处理 -> blockType 
    // 设置标记， “固化”对应的位置
    for (int i = 0; i < 4; ++i)
    {
        map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
    }
}

//Point* Block::getSmallBlocks()
//{
//
//    return nullptr;
//}
