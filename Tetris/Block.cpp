#include "Block.h"
#include <stdlib.h>

// ��ʼ��Ϊ��
IMAGE* Block::imgs[7] = { NULL };
// 4��С���飬 ����ɫ��tiles��ȡ | ��ͬ���͵ķ�������ò�ͬ����ɫ
int Block::size = 36;

Block::Block()
{
    // �ʼΪ�գ� Ҫ��7�ַ������� | ��ʼ��һ��
    if (imgs[0] == NULL) {
        /**
        * ����һ��ͼƬ��tiles.png������Ϊ�˽�ʡ�ռ䣬 ʹ�ô�������и��Ч
        */
        IMAGE imgTmp;

        // 1. ����ͼƬ���ڴ���
        loadimage(&imgTmp, "res/tiles.png");

        // 2. �����и����
        SetWorkingImage(&imgTmp);
        for (int i = 0; i < 7; ++i) {
            imgs[i] = new IMAGE;    // ��ָ��ָ������ڴ�ռ�
            getimage(imgs[i], i * size, 0, size, size); // �и�ͼƬ�� x, y, width�� height
        }
        // 3. �и���ͼƬ��Ҫ�ָ�������
        SetWorkingImage();  

    }


    // 1. �������˹����ĳ�ʼ��̬
    /*
     * �ھ�����ʾ��ʱ�� ������4��С����
     */
    int blocks[7][4] =
    {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z 1��
        3, 5, 4, 6, // Z 2��
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // ��
    };

    // 2. �������һ�ֶ���˹����
    blockType = 1 + rand() % 7; // 1 + 0..6 => 1..7 ����1-7

    // 3. ��ʼ�� smallBlocks
    /*
     * ��������˹����ʱ�� ������ blockType ��֪�����������������ĸ�С������������£��ڼ��У� �ڼ���
     */
    for (int i = 0; i < 4; ++i) {
        int value = blocks[blockType - 1][i];
        // Point smallBlocks[4];   // �˽ṹ������洢һ������˹�����4��С�����row��col | һ������˹�����λ�� | �ڼ��еڼ���
        smallBlocks[i].row = value / 2;
        smallBlocks[i].col = value % 2;
    }

    // 4. ����ͼƬָ����һ�� | ȷ���÷������ͣ� ����С�����λ��
    img = imgs[blockType - 1];




}
/**
 * @brief drop �½�
 */
void Block::drop()
{

}
/**
 * @brief moveLeftRight : ����offset ���÷������ƶ��������ƶ�
 * @param offset
 */
void Block::moveLeftRight(int offset)
{

}
/**
 * @brief rotate:������ת
 */
void Block::rotate()
{

}
/**
 * @brief draw: ������ȡ���ڷ�����Ϸ�����߽�Ͷ����߽��ж��
 * @param leftMargin
 * @param topMargin
 */
void Block::draw(int leftMargin, int topMargin)
{
    // �������->��4��С���� | ȷ���ڼ��еڼ��н���󲿱߽��붥���߽磬 �иߣ� �п�
    for (int i = 0; i < 4; ++i) {
        int x = leftMargin + smallBlocks[i].col * size;
        int y = topMargin + smallBlocks[i].row * size;

        putimage(x, y, img);    // ��ͼ�񣨷��飩
    }


}
