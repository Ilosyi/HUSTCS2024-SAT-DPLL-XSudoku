#pragma once
#include"GenerateSudoku.h"

//����ڸ������С��к����ֵ�����£������Ƿ���԰�ȫ�ط���������������
bool isSafe(const vector<int>& board, int row, int col, int num);
//���������������
bool solveSudoku(vector<int>& board);
//������ɵ�һ��
void GenerateFirstLine(vector<int>& a);
//���ɶԽ�������
void generateDiagonalSudoku(vector<int>& board);