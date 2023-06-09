#pragma once
#include <graphics.h>   // 需要先安装easyx图形库
#include <vector>
using namespace std;
// ! 一个俄罗斯方块到底在屏幕的第几行第几列， 可以定义一个结构体(而一个俄罗斯方块有四个小方块)
struct Point {
    int row;
    int col;
};


/**
 * @brief The Block class
 * - C++ 开发注意面向对象
 */
class Block
{
public:

    /**
     * @brief Block 方块构造函数
     */
    Block();

    /**
     * @brief drop 下降
     */
    void drop();

    /**
     * @brief moveLeftRight : 根据offset 来让方块左移动或者右移动
     * @param offset
     */
    void moveLeftRight(int offset);

    /**
     * @brief rotate:方块旋转
     */
    void rotate();

    /**
     * @brief draw: 画方块取决于方块游戏其左侧边界和顶部边界有多大
     * @param leftMargin
     * @param topMargin
     */
    void draw(int leftMargin, int topMargin);

    /*
    * @brief : 为了获取私有 static IMAGE* imgs[7]  数据 | 7种类型的方块 img存储在 imgs指针数组中
    * @return : IMAGE**
    */
    static IMAGE** getImages(); 

    /** 
    * @brief : 运算符重载 | 赋值构造函数
    * @return : Block
    */
    Block& operator=(const Block& other);

    /**
    * @brief : 获取私有SmallBlocks数组->得到这个数据后到Tetris类中进行判断
    * @return : Point*
    */
    //Point* getSmallBlocks();

    /**
    * @brief : 判断方块是否在地图中
    * @return : bool
    */
    bool blockInMap(const vector<vector<int>>& map);
    
    /**
    * @brief : 方块的固化功能， 改变map中的数据
    */
    void solidify(vector<vector<int>>& map);

    // 获取方块类型
    int getBlockType();

private:
    int blockType;  // 方块的类型， 应当属于这个Block类的属性成员
    /**
     * @brief smallBlocks: 表示某一个俄罗斯方块类型中， 四个小方块的所在位置（对于整个游戏界面？）
     */
    Point smallBlocks[4];   // 此结构体数组存储一个俄罗斯方块的4个小方块的row与col | 一个俄罗斯方块的位置
    // 定义一个图片指针变量， 表示这个方块对应的图片
    /**
     * 此游戏中要创建很多的方块，且很多小方块其展示的图片是完全一样的，这样就没有必要对每一个小方块都创建一个独立的图片；
     * 这里用指针， 指向那个图片即可 | 同一块内存可以反复渲染；
     */
    IMAGE *img;     // 每个图片指向imgs中（7种类型的方块）

    /**
     * static 静态变量
       这个类的静态成员：每个Block 对象都可以使用这个成员， 但是其不属于每一个对象， 而是属于所有的Block
     */
    static IMAGE* imgs[7];  // 7种图案
    // int data[7]   ->   int* getData() | 获取int 型的Data数组
    // int* data[7]  ->   int** getData()


    static int size;        // 图片大小



};

