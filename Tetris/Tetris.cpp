#include "Tetris.h"
#include <time.h>
#include <stdlib.h>

// ��Ϸ�ٶȻ���
const int SPEED_NORMAL = 500;   // ms
const int SPEED_QUICK = 50;

Tetris::Tetris()
{

}


/**
 * @brief Tetris ���캯��
 * @param rows  ��Ϸ�����Ƕ�����
 * @param cols  ������
 * @param left  ��Ϸ������뱳���ģ���߽�
 * @param top   ���ϱ߽�
 * @param blockSize ÿ��С����Ĵ�С
 */
Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
    // ����ʱ�����ݽ��г�ʼ��
    this->rows = rows;
    this->cols = cols;
    this->leftMargin = left;
    this->topMargin = top;
    this->blockSize = blockSize;

    // ��ͼ��ʼ��Ϊ�հ� -> 0
    for (int i = 0; i < rows; ++i) {
        vector<int> mapRow;
        for (int j = 0; j < cols; ++j) {
            // �е����
            mapRow.push_back(0);
        }
        map.push_back(mapRow);
    }


}
/**
 * @brief init ģ���ʼ��
 */
void Tetris::init()
{
    delay = SPEED_NORMAL; // 0.��ʼ���ӳ�ʱ�� | ÿ��500ms�½�

    // 1. �����������
    srand(time(NULL));

    // 2. ������Ϸ���� 938 * 896 | ���� bg2
    initgraph(938, 896);    // easyx

    // ������ʾӦ�÷�����Ϸ������ʾ�ĳ����� updateWindow()����Ⱦ��

    // 3. ���ر���ͼƬ 
    loadimage(&imgBg, "res/bg2.png");

    // ��Ϸ������ ��Ҫ���³�ʼ����ͼ���ݵȵ� | 4. ��ʼ����Ϸ���е�����
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = 0;
        }
    }



}
/**
 * @brief play ��ʼ��Ϸ
 */
void Tetris::play()
{
    // 1. ��ʼ��ϷǰҪ���г�ʼ��
    init();

    /**
    * ��ʼ���� ������
    */
    // �� ����Ԥ�淽��
    nextBlock = new Block;
    // �� ���µ�ǰ����
    curBlock = nextBlock;
    // �� ������һ��Ԥ�淽��
    nextBlock = new Block;



    /*
     *  30s ��Ⱦһ�λ��漴��
     *  �����жϾ�����һ��ѭ������˶���ʱ��
     */
    int timer = 0;

    // 2. �κ���Ϸ����һ����ѭ���� ���ϼ���
    while (1)
    {
        // 2.1 �����û������룬 ����ʵʱ�� | �û������ Ҳ��Ҫ����
        keyEvent();
        timer += getDelay();    // ����ʱ���Ƿ񳬹��ӳ�
        if (timer > delay)
        {
            timer = 0;  // ������0

            // 2.3 ʱ�䵽�ˣ� ������Զ�����һ��
            drop();

            // 2.2 ��Ⱦ��Ϸ����
            update = true;  // ����Ϊ TRUE �漴��Ⱦ����
        }
        if (update)
        {
            update = false; // ��Ⱦһ�κ���ΪFALSE
            updateWindow(); // 2.2 ������Ϸ�ġ����桷

            // 2.4 ������Ϸ�����ݣ� ����Ҫ����
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
    // 1. �� x = 0, y = 0 λ�û��Ʊ���ͼƬ
    putimage(0, 0, &imgBg);

    // 2. ��ȡimgs | 7�ַ������Ͷ�Ӧ��СͼƬ
    IMAGE** imgs = Block::getImages();

    /* Ϊ�˱�֤���治��˸�� Ӧ��һ���Ի��ƻ���֮�� ����Ⱦ   BeginBatchDraw */
    BeginBatchDraw();

    // 3. �жϵ�ͼ��map������λ���ϵ�ֵΪ0�� ���ǿհ׵ط�
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == 0) {
                continue ;
            }
            // 4. ��map[i][j] ��ֵ���������, ��������
            int x = leftMargin + j * blockSize;
            int y = topMargin + i * blockSize;
            // 5. �ڸ����괦���Ʒ��� | �������� map[i][j] ��1��ʼ | ����imgs��0�±꿪ʼ
            putimage(x, y, imgs[map[i][j] - 1]);
        }
    }

    // ���Է���
    // Block block;
    // block.draw(leftMargin, topMargin);
    curBlock->draw(leftMargin, topMargin);
    nextBlock->draw(689, 150);  // Ԥ�淽��������Ͻ�

    EndBatchDraw();

}
/**
* getDelay����һ�ε��÷���0�� ���ؾ�����һ�ε��ã� ����˶���ms
* GetTickCount: ���أ�retrieve���Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
* ��̬�ֲ������ڳ���ִ�е��ö�������ʱ���ᱻ�״γ�ʼ����
* ������е��ö��������ʱ�������ٴγ�ʼ����ֻ�ᱻ��ʼ��һ�Σ���
*/
int Tetris::getDelay()
{
    static unsigned long long lastTime = 0; // lastTime����һ�ε�ʱ��(��һ��)
    /**
     * ��ǰ��ʱ�� currentTime
     */
    unsigned long long currentTime = GetTickCount();

    // ��һ�ε���
    if (lastTime == 0) 
    {
        lastTime = currentTime;
        return 0;
    }
    else
    {
        int ret = currentTime - lastTime;   // ���㵱ǰ���λ�ȡ��ʱ������һ�����µ�ʱ��֮���delay �ӳ٣�
        lastTime = currentTime; // ������һ��ʱ��lastTime��
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
