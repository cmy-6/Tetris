#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h" 
using namespace std;
class Tetris
{
public:
    Tetris();   // ���캯��
    /**
     * @brief Tetris ���캯��
     * @param rows  ��Ϸ�����Ƕ�����
     * @param cols  ������
     * @param left  ��Ϸ������뱳������߽�
     * @param top   ��Ϸ������뱳�����ϱ߽�
     * @param blockSize ÿ��С����Ĵ�С
     */
    Tetris(int rows, int cols, int left, int top, int blockSize);
    /**
     * @brief init ģ���ʼ��
     */
    void init();
    /**
     * @brief play ��ʼ��Ϸ
     */
    void play();
private:

    /**
     * @brief keyEvent: �����û������ API�ӿ�
     */
    void keyEvent();    // �ڲ��Լ�ʹ��

    /**
     * @brief updateWindow: ��Ⱦ��Ϸ���棬 ���´���
     */
    void updateWindow(); // �ڲ��Լ�ʹ�� ���˽��

    /**
     * @brief getDelay : ���ؾ�����һ�ε��øú����� ����˶���ʱ�䣨ms�� | ��һ�ε��øú����� ����0
     * @return : int
     */
    int getDelay();

    /**
     * @brief drop: ���齵��
     */
    void drop();

    /**
     * @brief clearLine: ����
     */
    void clearLine();

    // ����������ƶ�
    void moveLeftRight(int offset);


// ˽�����ݳ�Ա
private:
    int delay;      // ˢ��ʱ����
    bool update;    // �Ƿ����

    // C++ ��STL ������չ
    /**
     * 0: �հף� û���κη���
     * 1 - 7 
     * 5: �ǵ�5�ֶ���˹����
     */
    vector<vector<int>> map;

    int rows;   // ����Ϸ������
    int cols;
    int leftMargin; // ��Ϸ������뱳�������߽�
    int topMargin;  // �����߽�
    int blockSize;  // �����С

    IMAGE imgBg;    // ��Ϸ�ı���ͼƬ


    Block* curBlock;    // ��ǰ����
    Block* nextBlock;   // ��һ��Ԥ�淽��

    // ������ָ�룬 �Ǿ�û�б���������
    Block bakBlock;     // ��ǰ���齵������У� ����������һ���Ϸ�λ�õģ������շ�����䵽���£�

    // ����Tip 1: �����齵�䵽������ֹͣ�����ˣ� ��������η�����
    // ����Tip 2: ����˹����������ƶ�
};

