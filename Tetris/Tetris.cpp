#include "Tetris.h"
#include <time.h>
#include <stdlib.h>

// 游戏速度划分
const int SPEED_NORMAL = 500;   // ms
const int SPEED_QUICK = 50;

Tetris::Tetris()
{

}


/**
 * @brief Tetris 构造函数
 * @param rows  游戏界面是多少行
 * @param cols  多少列
 * @param left  游戏区域距离背景的）左边界
 * @param top   与上边界
 * @param blockSize 每个小方块的大小
 */
Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
    // 构造时对数据进行初始化
    this->rows = rows;
    this->cols = cols;
    this->leftMargin = left;
    this->topMargin = top;
    this->blockSize = blockSize;

    // 地图初始化为空白 -> 0
    for (int i = 0; i < rows; ++i) {
        vector<int> mapRow;
        for (int j = 0; j < cols; ++j) {
            // 列的填充
            mapRow.push_back(0);
        }
        map.push_back(mapRow);
    }


}
/**
 * @brief init 模块初始化
 */
void Tetris::init()
{
    delay = SPEED_NORMAL; // 0.初始化延迟时间 | 每隔500ms下降

    // 1. 配置随机种子
    srand(time(NULL));

    // 2. 创建游戏窗口 938 * 896 | 根据 bg2
    initgraph(938, 896);    // easyx

    // 背景显示应该放在游戏真正显示的场景中 updateWindow()【渲染】

    // 3. 加载背景图片 
    loadimage(&imgBg, "res/bg2.png");

    // 游戏结束后， 需要重新初始化地图数据等等 | 4. 初始化游戏区中的数据
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = 0;
        }
    }



}
/**
 * @brief play 开始游戏
 */
void Tetris::play()
{
    // 1. 开始游戏前要进行初始化
    init();

    /**
    * 初始方块 三步骤
    */
    // ① 生成预告方块
    nextBlock = new Block;
    // ② 更新当前方块
    curBlock = nextBlock;
    // ③ 生成下一个预告方块
    nextBlock = new Block;



    /*
     *  30s 渲染一次画面即可
     *  可以判断距离上一次循环间隔了多少时间
     */
    int timer = 0;

    // 2. 任何游戏都是一个死循环， 不断监听
    while (1)
    {
        // 2.1 接受用户的输入， 保持实时性 | 用户输入后， 也需要更新
        keyEvent();
        timer += getDelay();    // 计算时间是否超过延迟
        if (timer > delay)
        {
            timer = 0;  // 进行清0

            // 2.3 时间到了， 方块就自动降落一格
            drop();

            // 2.2 渲染游戏画面
            update = true;  // 设置为 TRUE 真即渲染画面
        }
        if (update)
        {
            update = false; // 渲染一次后置为FALSE
            updateWindow(); // 2.2 更新游戏的《画面》

            // 2.4 更新游戏的数据， 比如要清行
            clearLine();
        }

    }
}

void Tetris::keyEvent()
{
    // to do.
}

void Tetris::updateWindow()
{
    // 1. 在 x = 0, y = 0 位置绘制背景图片
    putimage(0, 0, &imgBg);

    // 2. 获取imgs | 7种方块类型对应的小图片
    IMAGE** imgs = Block::getImages();

    /* 为了保证画面不闪烁， 应该一次性绘制画好之后， 再渲染   BeginBatchDraw */
    BeginBatchDraw();

    // 3. 判断地图（map）若该位置上的值为0， 则是空白地方
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == 0) {
                continue ;
            }
            // 4. 若map[i][j] 有值则计算坐标, 后续绘制
            int x = leftMargin + j * blockSize;
            int y = topMargin + i * blockSize;
            // 5. 在该坐标处绘制方块 | 方块种类 map[i][j] 从1开始 | 但是imgs从0下标开始
            putimage(x, y, imgs[map[i][j] - 1]);
        }
    }

    // 测试方块
    // Block block;
    // block.draw(leftMargin, topMargin);
    curBlock->draw(leftMargin, topMargin);
    nextBlock->draw(689, 150);  // 预告方块放在右上角

    EndBatchDraw();

}
/**
* getDelay：第一次调用返回0； 返回距离上一次调用， 间隔了多少ms
* GetTickCount: 返回（retrieve）从操作系统启动所经过（elapsed）的毫秒数，它的返回值是DWORD。
* 静态局部变量在程序执行到该对象声明时，会被首次初始化。
* 其后运行到该对象的声明时，不会再次初始化（只会被初始化一次）；
*/
int Tetris::getDelay()
{
    static unsigned long long lastTime = 0; // lastTime最新一次的时间(上一次)
    /**
     * 当前的时间 currentTime
     */
    unsigned long long currentTime = GetTickCount();

    // 第一次调用
    if (lastTime == 0) 
    {
        lastTime = currentTime;
        return 0;
    }
    else
    {
        int ret = currentTime - lastTime;   // 计算当前本次获取的时间与上一次最新的时间之差（即delay 延迟）
        lastTime = currentTime; // 更新上一次时间lastTime；
        return ret;
    }
}

void Tetris::drop()
{

}

void Tetris::clearLine()
{
    // To do.
}
