#include"GenerateXSudoku.h"
/***********************************************
*�������ƣ�isSafe
* �������ܣ�����ڸ������С��к����ֵ�����£������Ƿ���԰�ȫ�ط��������������ϡ�
* ע�ͣ�������������ʱ����������Ƿ���Է��������������ϡ�
* ����ֵ��������ֿ��԰�ȫ�ط��������������ϣ��򷵻�true�����򷵻�false��
************************************************/
bool isSafe(const vector<int>& board, int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        // �����
        if (board[row * SIZE + x] == num)
            return false;
        // �����
        if (board[x * SIZE + col] == num)
            return false;
    }

    // ���Ź���
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[(startRow + i) * SIZE + (startCol + j)] == num)
                return false;
        }
    }

    // ������Խ���
    if (row == col) {
        for (int i = 0; i < SIZE; i++) {
            if (board[i * SIZE + i] == num)
                return false;
        }
    }

    // ��鸱�Խ���
    if (row + col == SIZE - 1) {
        for (int i = 0; i < SIZE; i++) {
            if (board[i * SIZE + (SIZE - 1 - i)] == num)
                return false;
        }
    }

    return true;
}

/***********************************************
*�������ƣ�solveSudoku
* �������ܣ����������������
* ע�ͣ����õݹ���ݵ�˼�룬�����������̡�
* ����ֵ��bool���ͣ�����ɹ������������̣��򷵻�true�����򷵻�false��
************************************************/
bool solveSudoku(vector<int>& board) 
{
    for (int row = 1; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row * SIZE + col] == 0) { //�����ǰλ��Ϊ��
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row * SIZE + col] = num; // ��������

                        if (solveSudoku(board))
                            return true; // �ݹ�

                        // Backtrack
                        board[row * SIZE + col] = 0; //����
                    }
                }
                return false; // �ݹ�ʧ��
            }
        }
    }
	return true; // ���ɳɹ�
}
/***********************************************
*�������ƣ�GenerateFirstLine
* �������ܣ���������������̵ĵ�һ��
* ע�ͣ�solveSudoku�����ĸ������������������������̵ĵ�һ�У�������˺����������̵����ɡ�
* ����ֵ��void
************************************************/
void GenerateFirstLine(vector<int>& a) {

    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % SIZE + 1;
        int j = 0;
        while (j < i) {
			if (a[i] == a[j]) {//������ɵ������ظ�
                a[i] = rand() % SIZE + 1;//��������
				j = 0;//���¼��
            }
            else {
                j++;
            }
        }
    }
}

/***********************************************
*�������ƣ�generateDiagonalSudoku
* �������ܣ�������ɶԽ�����������
* ע�ͣ�����board���飬���ɶԽ����������̡�
* ����ֵ��void
************************************************/
void generateDiagonalSudoku(vector<int>& board) {
    for (int i = 0; i < 81; i++)
    {
        board[i] = 0;
    }
    GenerateFirstLine(board);
    solveSudoku(board);
   
}
