#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>  // ����̨IO���
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
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

    // ��ʼ����ǰ�ķ���Ϊ0
    score = 0;


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
    bool rotateFlag = false;    // ��ת���
    unsigned char ch;    // ���ռ������� 0..255
    int dx = 0; // �����ƶ���ƫ��
    // TODO.
    // ʹ��getchar() ����Ҫ���س��Ż�ȷ���� �������߼�
    // kbhit�����������Ƿ��а���,���򷵻�-1,û���򷵻�0;
    if (_kbhit())
    {
        // �����֪��������ʲô��,Ӧ����_getch()����ȡ(��ֵ�Ѿ����뻺����,_getch�ӻ�������ȡ�ö����ٴӼ�������)
        ch = _getch();
        // ���ڷ������ ���Զ����������ַ�
        // �� ���Ϸ������ ���Ⱥ󷵻أ�224 72
        // �� ���·������ ���Ⱥ󷵻أ�224 80
        // �� ��������� ���Ⱥ󷵻أ�224 75
        // �� ���ҷ������ ���Ⱥ󷵻أ�224 77
        if (ch == 224) {
            ch = _getch();
            switch (ch)
            {
            case 72:
                rotateFlag = true;  // ���Ϊ��ת
                break;
            case 80:
                delay = SPEED_QUICK;    // ��������
                break;
            case 75:
                dx = -1;    // ���ƶ�
                break;
            case 77:
                dx = 1;     // ���ƶ�
                break;
            default:
                break;   
            }
        }
    }

    if (rotateFlag)
    {
        // TODO. ��ʵ�֣� ����ת���� | ����ʵ���ɷ����������
        rotateFlag = false; // �ָ���ֵ
        rotate();
        update = true;

    }

    if (dx != 0)
    {
        // TODO. ʵ�������ƶ�
        moveLeftRight(dx);  // ע�ⰴ�������ƶ��� ������Ҫ���ϸ���
        update = true;  // �������
    }

    
}

void Tetris::updateWindow()
{
    // 1. �� x = 0, y = 0 λ�û��Ʊ���ͼƬ
    putimage(0, 0, &imgBg);

    // 2. ��ȡimgs | 7�ַ������Ͷ�Ӧ��СͼƬ
    IMAGE** imgs = Block::getImages();

    /* Ϊ�˱�֤���治��˸�� Ӧ��һ���Ի��ƻ���֮�� ����Ⱦ  BeginBatchDraw ---- EndBatchDraw */
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

    drawScore();    // ���Ʒ���

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

// ����ʱ�� ע�����޳����߽� | ����
void Tetris::drop()
{
    // ����ĸ�ֵҪע����
    // ��ֵ���캯�� operator=
    // 1. ���÷��鱣�� | ��һ��λ�õĺϷ�λ | �������ٽ���
    bakBlock = *curBlock;



    // ���齵��Ӧ���ɷ�������ʵ�� | ����˹���鱾�������
    curBlock->drop();

    // �½������У� Ҫ�жϷ����Ƿ񵽵ײ� | ��װ˼�� | ��Block���ṩAPI 
    // 2. �����齵���ײ��ˣ���������顰�̻���
    if (!curBlock->blockInMap(map))
    {
        bakBlock.solidify(map); // ����̻�

        // 3. �̻�֮�� �Ͱѵ�ǰ�������ΪԤ��ķ��飬 ����Ԥ�淽�������·���
        delete curBlock;    // ��
        curBlock = nextBlock;   // ��
        nextBlock = new Block;  // ��

    }

    // �½�֮�� �ͻ�ԭ���������ٶ�
    delay = SPEED_NORMAL;


}

void Tetris::clearLine()
{
    int lines = 0;  // �ж���ȥ������
    // To do.
    // ˫ָ��
    int k = rows - 1;   // �洢���ݵ�����
    for (int i = rows - 1; i >= 0; --i)
    {
        // �������Ƿ�����
        int count = 0;
        for (int j = 0; j < cols; ++j)
        {
            // ��λ���з���
            if (map[i][j])
            {
                count++;
            }
            // һ��ɨ��һ�ߴ洢 -> ������������Ҫ�����ģ�
            map[k][j] = map[i][j];  
        }
        if (count < cols)
        {
            // ��������
            k--;
        } // �������У�k���䣬 �´�ѭ���Ϳ������������渲��
        else
        {
            // count == cols   ����
            lines++;
        }
    }

    if (lines > 0)
    {
        // ����÷�  | ����һ��10�֣� ͬʱ����2��30�֣� 3 - 60�� 4��80��
        int addScore[4] = { 10, 30, 60, 80 };
        score += addScore[lines - 1];
        // ������Ч
        mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
        update = true;  // ������Ҫ����

    }
}

// ���ƶ���ʱ��Ҫע�����޳����߽� | ����
void Tetris::moveLeftRight(int offset)
{
    bakBlock = *curBlock;   // ���ݺϷ�����
    curBlock->moveLeftRight(offset);  // �������������ƶ�

    if (!curBlock->blockInMap(map)) {
        *curBlock = bakBlock;
    }
}

void Tetris::rotate()
{
    // �����η���û����ת����
    if (curBlock->getBlockType() == 7) return;

    bakBlock = *curBlock;   // ���ݺϷ�����
    curBlock->rotate();

    // ���Ϸ�λ�ü���ԭ
    if (!curBlock->blockInMap(map)) {
        *curBlock = bakBlock;
    }
}

void Tetris::drawScore()
{
    char scoreText[32];

    sprintf_s(scoreText, sizeof(scoreText), "%d", score);

    // ����������ɫ
    setcolor(RGB(180, 180, 180));

    LOGFONT f;
    // ��ȡ��ǰ������
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfWidth = 30;
    f.lfQuality = ANTIALIASED_QUALITY;  // ��������Ϊ ������ݡ�Ч��
    strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
    settextstyle(&f);

    setbkmode(TRANSPARENT); // ����ı�������Ϊ͸��Ч��

    outtextxy(670, 727, scoreText);
}
