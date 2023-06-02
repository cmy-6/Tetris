#pragma once
#include <graphics.h>   // ��Ҫ�Ȱ�װeasyxͼ�ο�

// ! һ������˹���鵽������Ļ�ĵڼ��еڼ��У� ���Զ���һ���ṹ��(��һ������˹�������ĸ�С����)
struct Point {
    int row;
    int col;
};


/**
 * @brief The Block class
 * - C++ ����ע���������
 */
class Block
{
public:

    /**
     * @brief Block ���鹹�캯��
     */
    Block();

    /**
     * @brief drop �½�
     */
    void drop();

    /**
     * @brief moveLeftRight : ����offset ���÷������ƶ��������ƶ�
     * @param offset
     */
    void moveLeftRight(int offset);

    /**
     * @brief rotate:������ת
     */
    void rotate();

    /**
     * @brief draw: ������ȡ���ڷ�����Ϸ�����߽�Ͷ����߽��ж��
     * @param leftMargin
     * @param topMargin
     */
    void draw(int leftMargin, int topMargin);
private:
    int blockType;  // ��������ͣ� Ӧ���������Block������Գ�Ա
    /**
     * @brief smallBlocks: ��ʾĳһ������˹���������У� �ĸ�С���������λ�ã�����������Ϸ���棿��
     */
    Point smallBlocks[4];   // �˽ṹ������洢һ������˹�����4��С�����row��col | һ������˹�����λ��
    // ����һ��ͼƬָ������� ��ʾ��������Ӧ��ͼƬ
    /**
     * ����Ϸ��Ҫ�����ܶ�ķ��飬�Һܶ�С������չʾ��ͼƬ����ȫһ���ģ�������û�б�Ҫ��ÿһ��С���鶼����һ��������ͼƬ��
     * ������ָ�룬 ָ���Ǹ�ͼƬ���� | ͬһ���ڴ���Է�����Ⱦ��
     */
    IMAGE *img;     // ÿ��ͼƬָ��imgs�У�7�����͵ķ��飩

    /**
     * static ��̬����
       �����ľ�̬��Ա��ÿ��Block ���󶼿���ʹ�������Ա�� �����䲻����ÿһ������ �����������е�Block
     */
    static IMAGE* imgs[7];  // 7��ͼ��
    static int size;        // ͼƬ��С



};

