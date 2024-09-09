#include"GenerateSudoku.h"
#include "definition.h"
#include"vector.hpp"

// col mask
// +-------+-------+-------+
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// +-------+-------+-------+
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// +-------+-------+-------+
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// | 1 2 3 | 4 5 6 | 7 8 9 |
// +-------+-------+-------+

enum {
    COL_MASK_NONE = 0,
    COL_MASK_1 = 1 << 0,  // 0x001
    COL_MASK_2 = 1 << 1,  // 0x002
    COL_MASK_3 = 1 << 2,  // 0x004
    COL_MASK_4 = 1 << 3,  // 0x008
    COL_MASK_5 = 1 << 4,  // 0x010
    COL_MASK_6 = 1 << 5,  // 0x020
    COL_MASK_7 = 1 << 6,  // 0x040
    COL_MASK_8 = 1 << 7,  // 0x080
    COL_MASK_9 = 1 << 8,  // 0x100
    COL_MASK_123 = (1 << 0) | (1 << 1) | (1 << 2),  // 0x007
    COL_MASK_456 = (1 << 3) | (1 << 4) | (1 << 5),  // 0x038
    COL_MASK_789 = (1 << 6) | (1 << 7) | (1 << 8),  // 0x1C0
    COL_MASK_ALL = (1 << 9) - 1  // 0x1FF
};
//����BITλ����ÿһ�У��Ƿ���������֣�����Բ�ͬ�н���λ��������������Ƿ��Ѿ���䡣
//��ʼ��
void InitSodoku(Sodoku* sodoku)
{
    if (sodoku == nullptr) {
        return;
    }

    std::memset(sodoku, 0, sizeof(Sodoku));
	sodoku->long_row = -1; //��ʼ��Ϊ-1����ʾ��δ��ʼ����
}
//�ж������Ƿ����
bool isSodokuInProgress(const Sodoku* sodoku) {
    if (sodoku == nullptr) {
        return false;
    }

    return sodoku->long_row <= 80;
}
//������һ��
void moveNextRow(Sodoku* sodoku)
{
	if (sodoku == nullptr) //�������Ϊ��
    {
        return;
    }

	sodoku->long_row++; //������1
	if (sodoku->long_row > 80)//��ʾ�����Ѿ����
	{
		return;
	}
 
	sodoku->col_index[sodoku->long_row].base_col = calcRandCol();//������ʼ������Ϊ�����
	sodoku->col_index[sodoku->long_row].curr_col = -1; //��ʼ����ǰ��Ϊ-1��ʾ��δ��ʼ����

	//���㲢���µ�ǰ�е�������
    calculateColumnMaskForRow(sodoku, sodoku->long_row);
}
//�ع�����һ��
void rollback_row(Sodoku* sodoku)
{
    if (sodoku == nullptr)
        return;

    sodoku->long_row--;
  
    // ���¼���
    calculateColumnMaskForRow(sodoku, sodoku->long_row);
}
//���������
inline int calcRandCol(void)
{ 
	int col = rand() % 9; // 0-8
    return col;
}
//������һ��
 int calNextCol(int col)
{
	 return (col + 1) % 9; // 0-8 -> 1-9
}
 //����������
 void calculateColumnMaskForRow(Sodoku* sodoku, int long_row)
{
  
     
    int row;
    unsigned int mask = 0;
	//1��ʾ�ѱ����ã�0��ʾδ������
	// ����ǰ�������ڸ����Ѿ������У�����������
    for (row = long_row % 9; row < long_row; row += 9)
    {
        mask |= sodoku->col_index[row].col_mask;
    }

	//������ǰ����������У�����������
    for (row = long_row - long_row % 9; row < long_row; row++)
    {
        mask |= sodoku->col_index[row].col_mask;
    }

	//�Ź����ڵ�������
	for (row = long_row - long_row % 3; row < long_row; row++)//����ʼ�б�������ǰ��
	{
		if (sodoku->col_index[row].col_mask & COL_MASK_123)
            mask |= COL_MASK_123;
        else if (sodoku->col_index[row].col_mask & COL_MASK_456)
            mask |= COL_MASK_456;
        else //789
            mask |= COL_MASK_789;
    }
	////���Խ��ߵ�������
 //  for (row = long_row - long_row % 9; row < long_row; row++)
 //   {
 //      
 //       if (sodoku->col_index[row].col_mask & (1 << (row % 9)))
 //       {
	//		mask |= (1 << (long_row % 9));
 //           break;
 //       }
 //   }
 //  //���Խ��ߵ�������
 //  for (row = long_row - long_row % 9; row < long_row; row++)
 //  {

 //      if (sodoku->col_index[row].col_mask & (1 << (8-row % 9)))
 //      {
 //          mask |= (1 << (8-long_row % 9));
 //          break;
 //      }
 //  }

    sodoku->col_index[long_row].col_mask = ~mask; // ȡ����
}
 //������һ��

 bool moveNextCol(Sodoku* sodoku)
 {
     bool success = false; // ָʾ�����Ƿ�ɹ�
     int base_col; // ��ǰ�еĻ�׼������
     int curr_col; // ��ǰ�еĵ�ǰ������
     int next_col; // Ҫ�ҵ�����һ������
     bool found = false; // ָʾ�Ƿ��ҵ���Ч����һ��

     if (sodoku == nullptr)
         return success; // �������Ϊ�գ�����false

     base_col = sodoku->col_index[sodoku->long_row].base_col;
     curr_col = sodoku->col_index[sodoku->long_row].curr_col;

     if (curr_col == -1)
     {
         // �����ǰ����-1����base_col��ʼ�ҵ���һ����Ч��
         next_col = base_col;

         // ���base_col�Ƿ���Ч
         if (sodoku->col_index[sodoku->long_row].col_mask & (1 << base_col))
         {
             found = true;
         }
         else
         {
             // ���base_col��Ч���ҵ���һ����Ч��
             next_col = calNextCol(base_col);
         }
     }
     else
     {
         // �ӵ�ǰ���ҵ���һ����Ч��
         next_col = calNextCol(curr_col);
     }

     if (!found)
     {
         // ��������ֱ���ҵ���Ч�л�ѭ���ص�base_col
         while (next_col != base_col)
         {
             // ���next_col�Ƿ���Ч
             if (sodoku->col_index[sodoku->long_row].col_mask & (1 << next_col))
             {
                 found = true;
                 break;
             }

             // �ҵ���һ��
             next_col = calNextCol(next_col);
         }
     }

     if (!found)
         return success; // ���û���ҵ���Ч�У�����false

     // ���õ�ǰ��Ϊ�ҵ�����һ��
     sodoku->col_index[sodoku->long_row].curr_col = next_col;
     // ������������ָʾѡ�е���
	 sodoku->col_index[sodoku->long_row].col_mask = (1 << next_col);//����������

     success = true;
     return success; // ����trueָʾ�ɹ�
 }

 //��������������
void SaveSodokutoBoard(Sodoku* sodoku,vector<int>& Board)
{
    if (sodoku == nullptr) {
        return;
    }
//�洢������ÿ������

    for (int long_row = 0; long_row < sodoku->long_row; long_row++) {
        
        int digit = long_row / 9 + 1;//�ڼ�������
		int row = long_row % 9;//����digit����
		int col = sodoku->col_index[long_row].curr_col;//��ǰ�е�ʵ����
        
        Board[row * 9 + col] = digit;
    }
}
void PrintBoard(const vector<int>& Board)
{
    cout << "   �� �� �� ��" << endl;

    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            cout << "+-----+-----+-----+" << endl;//ÿ���д�ӡһ��
        }
        cout << "|";//ÿ�п�ʼ��ӡ
        for (int col = 0; col < 9; col++) {
            if (Board[row * 9 + col] != 0)
            {
				cout << Board[row * 9 + col];//��ӡ����
           }
            else
            {
				cout << "_";//��ӡ�ո�
            }
            if (col % 3 == 2) {
                cout << "|";//ÿ���д�ӡһ��
            }
            else {
                cout << " ";//ÿ��֮���ӡһ���ո�
            }
        }
        cout << endl;
    }
    cout << "+-----+-----+-----+" << endl;
}
//��ʼ��������
void StartSodokuGenerate(Sodoku* sodoku, vector<int>& Board)
{
    // ��ʼ������
    InitSodoku(sodoku);
    // ������һ��
    moveNextRow(sodoku);

    while (isSodokuInProgress(sodoku))//�ж������Ƿ����
    {
        if (moveNextCol(sodoku))
        {
            moveNextRow(sodoku);//������һ��
        }
        else
        {
            rollback_row(sodoku);//�ع�����һ��
        }
    }
	SaveSodokutoBoard(sodoku, Board);//��������������
}
void shuffleArray(vector<int>&array) {
    for (int i = 80; i > 0; --i) {
        int j = rand()%i;
        swap(array[i], array[j]);
    }
}
int generateGameBoard(const vector<int>& normalBoard, vector<int>& gameBoard) {
	
    // �����ȥ����������
    int numToRemove = 35 + rand() % 13;

    // ���� normalBoard �� gameBoard
    gameBoard = normalBoard;

    // ������������
    vector<int> indices(81,0);
    for (int i = 0; i <81; ++i) {
        indices[i] = i;
    }
   
    // ������������
    shuffleArray(indices);

    // ��ȥ����
    for (int i = 0; i < numToRemove; ++i) {
        gameBoard[indices[i]] = 0; // 0 ��ʾ�հ�
    }
    return numToRemove;
}