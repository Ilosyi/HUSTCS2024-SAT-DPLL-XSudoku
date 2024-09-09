#pragma once
#include"vector.hpp"
#define SIZE 9
//��������
typedef struct
{
    int base_col; // ��ǰ�е���ʼ������
    int curr_col; // ʵ�ʴ洢��
    unsigned int col_mask;//��¼ǰ���е����ݣ��������ǰ��ʵ�ʿ��е�λ��
} Col_Index;//ĳһ�е����ݽṹ������ǰ�������е����ݣ��������ǰ��ʵ�ʿ��е�λ�ã�����Ե�ǰ�е�����

typedef struct {
    int long_row; // ��ǰ�������ڼ��У��ĸ����ֵ���һ�У���81Ϊ�������
    Col_Index col_index[81]; //ÿһ�е�ʵ������״̬
} Sodoku;//��������

void InitSodoku(Sodoku* sodoku);//��ʼ������
bool isSodokuInProgress(const Sodoku* sodoku);//�ж������Ƿ����
void moveNextRow(Sodoku* sodoku);//������һ��
void rollback_row(Sodoku* sodoku);//�ع�����һ��
int calcRandCol(void);//���������
int calNextCol(int col);//������һ��
 void calculateColumnMaskForRow(Sodoku* sodoku, int long_row);//����������
bool moveNextCol(Sodoku* sodoku);//������һ��
void SaveSodokutoBoard(Sodoku* sodoku, vector<int>& Board);//��������������
void PrintBoard(const vector<int>& Board);//��ӡ����
void StartSodokuGenerate(Sodoku* sodoku, vector<int>& Board);//��ʼ��������
void shuffleArray(vector<int>& array);//��������
int generateGameBoard(const vector<int>& normalBoard, vector<int>& gameBoard);//�ڶ�


