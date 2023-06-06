#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>  // 控制台IO输出

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
    bool rotateFlag = false;    // 旋转标记
    unsigned char ch;    // 接收键盘输入 0..255
    int dx = 0; // 左右移动的偏移
    // TODO.
    // 使用getchar() 则需要按回车才会确定， 不符合逻辑
    // kbhit用来检测键盘是否有按键,有则返回-1,没有则返回0;
    if (_kbhit())
    {
        // 如果想知道按下了什么键,应该用_getch()来获取(键值已经输入缓冲区,_getch从缓冲区中取得而非再从键盘输入)
        ch = _getch();
        // 对于方向键， 会自动返回两个字符
        // 按 向上方向键， 会先后返回：224 72
        // 按 向下方向键， 会先后返回：224 80
        // 按 向左方向键， 会先后返回：224 75
        // 按 向右方向键， 会先后返回：224 77
        if (ch == 224) {
            ch = _getch();
            switch (ch)
            {
            case 72:
                rotateFlag = true;  // 标记为旋转
                break;
            case 80:
                delay = SPEED_QUICK;    // 加速下落
                break;
            case 75:
                dx = -1;    // 左移动
                break;
            case 77:
                dx = 1;     // 右移动
                break;
            default:
                break;   
            }
        }
    }

    if (rotateFlag)
    {
        // TODO. 待实现， 做旋转处理 | 真正实现由方块类来完成
        rotateFlag = false; // 恢复初值
        rotate();
        update = true;

    }

    if (dx != 0)
    {
        // TODO. 实现左右移动
        moveLeftRight(dx);  // 注意按键左右移动后， 画面需要马上更新
        update = true;  // 画面更新
    }

    
}

void Tetris::updateWindow()
{
    // 1. 在 x = 0, y = 0 位置绘制背景图片
    putimage(0, 0, &imgBg);

    // 2. 获取imgs | 7种方块类型对应的小图片
    IMAGE** imgs = Block::getImages();

    /* 为了保证画面不闪烁， 应该一次性绘制画好之后， 再渲染  BeginBatchDraw ---- EndBatchDraw */
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

// 降落时， 注意有无超出边界 | 备份
void Tetris::drop()
{
    // 对象的赋值要注意了
    // 赋值构造函数 operator=
    // 1. 备用方块保存 | 上一个位置的合法位 | 保存完再降落
    bakBlock = *curBlock;



    // 方块降落应该由方块类来实现 | 俄罗斯方块本身的特性
    curBlock->drop();

    // 下降过程中， 要判断方块是否到底部 | 封装思想 | 由Block类提供API 
    // 2. 若方块降到底部了：把这个方块“固化”
    if (!curBlock->blockInMap(map))
    {
        bakBlock.solidify(map); // 方块固化

        // 3. 固化之后， 就把当前方块更新为预告的方块， 再让预告方块生成新方块
        delete curBlock;    // ①
        curBlock = nextBlock;   // ②
        nextBlock = new Block;  // ③

    }

    // 下降之后， 就还原成正常的速度
    delay = SPEED_NORMAL;


}

void Tetris::clearLine()
{
    // To do.
}

// 在移动的时候要注意有无超出边界 | 备份
void Tetris::moveLeftRight(int offset)
{
    bakBlock = *curBlock;   // 备份合法方块
    curBlock->moveLeftRight(offset);  // 方块自身左右移动

    if (!curBlock->blockInMap(map)) {
        *curBlock = bakBlock;
    }
}

void Tetris::rotate()
{
    // 田字形方块没有旋转意义
    if (curBlock->getBlockType() == 7) return;

    bakBlock = *curBlock;   // 备份合法方块
    curBlock->rotate();

    // 不合法位置即还原
    if (!curBlock->blockInMap(map)) {
        *curBlock = bakBlock;
    }
}
