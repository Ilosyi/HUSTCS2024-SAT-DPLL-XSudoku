#pragma once
#include"definition.h"
#include"vector.hpp"

/***********************************************
*�������ƣ�sudokuToCnf
* �������ܣ�������������ת��Ϊ CNF ��ʽ��������д���ļ���
* ע�ͣ�- ��Դ�ļ� "SudokuBase.cnf" ���ƻ���Լ�����ݡ�
        - ��������������������ֵ�Լ����
        - д�����Խ��ߺ͸��Խ��߲����ظ��Ĺ���
        - д�� CNF �ļ�ͷ��
* ����ֵ��bool���ͣ�����ɹ����� CNF �ļ����򷵻� true�����򷵻� false��
************************************************/
bool SudokuToCnf(const vector<int>& board,int empty)
{
    string sourceFilename = "SudokuBase.cnf";
    string destinationFilename = "NormalSudoku.cnf";

    // ��Դ�ļ����ж�ȡ
    ifstream sourceFile(sourceFilename, ios::binary);
    if (!sourceFile) {
        cerr << "�޷���Դ�ļ� " << sourceFilename << endl;
        return 0;
    }

    // ��Ŀ���ļ�����д�룬����ļ����������½�
    ofstream destinationFile(destinationFilename, std::ios::out | std::ios::trunc);
    if (!destinationFile) {
        cerr << "�޷���Ŀ���ļ� " << destinationFilename << endl;
        return 0;
    }
    destinationFile << "p" << " " << "cnf" << " " << 729 << " " << 8829 + 81 - empty << endl;
    // ��Դ�ļ���ȡ���ݲ�д�뵽Ŀ���ļ�
   
    for (int i = 1; i <=9; ++i) {
        for (int j = 1; j <=9; ++j) {
            if (board[(i- 1) * 9 + j - 1]) {
				destinationFile << i << j << board[(i - 1) * 9 + j - 1] << " 0" << endl;
            }
        }
    }
    char buffer[1024];
    while (sourceFile.read(buffer, sizeof(buffer))) {
        destinationFile.write(buffer, sourceFile.gcount());
    }

    // д��ʣ������ݣ�����еĻ���
    if (sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
    }

    // �ر��ļ�
    sourceFile.close();
    destinationFile.close();

    //cout << "�ļ����ݸ�����ɡ�" << endl;

}

/***********************************************
*�������ƣ�XsudokuToCnf
* �������ܣ�������������(X����)ת��Ϊ CNF ��ʽ��������д���ļ���
* ע�ͣ�- ��Դ�ļ� "SudokuBase.cnf" ���ƻ���Լ�����ݡ�
        - ��������������������ֵ�Լ����
        - д�����Խ��ߺ͸��Խ��߲����ظ��Ĺ���
        - д�� CNF �ļ�ͷ��
* ����ֵ��bool���ͣ�����ɹ����� CNF �ļ����򷵻� true�����򷵻� false��
************************************************/
bool XSudokuToCnf(const vector<int>& board, int empty)
{
    string sourceFilename = "SudokuBase.cnf";
    string destinationFilename = "XSudoku.cnf";

    // ��Դ�ļ����ж�ȡ
    ifstream sourceFile(sourceFilename, ios::binary);
    if (!sourceFile) {
        cerr << "�޷���Դ�ļ� " << sourceFilename << endl;
        return 0;
    }

    // ��Ŀ���ļ�����д�룬����ļ����������½�
    ofstream destinationFile(destinationFilename, std::ios::out | std::ios::trunc);
    if (!destinationFile) {
        cerr << "�޷���Ŀ���ļ� " << destinationFilename << endl;
        return 0;
    }

	// д���ļ�ͷ
    destinationFile << "p" << " " << "cnf" << " " << 729 << " " << 8829 +648+81 - empty << endl;

    // ���Խ��߲����ظ��Ĺ���
    int mainDiagonal[9] = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (mainDiagonal[i] * 10 + z) << " " << 0 - (mainDiagonal[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }

    // ���Խ��߲����ظ��Ĺ���
    int antiDiagonal[9] = { 19, 28, 37, 46, 55, 64, 73, 82, 91 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (antiDiagonal[i] * 10 + z) << " " << 0 - (antiDiagonal[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }
//�������������ֲ�����Լ��----------------------------------------
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            if (board[(i - 1) * 9 + j - 1]) {
                destinationFile << i << j << board[(i - 1) * 9 + j - 1] << " 0" << endl;
            }
        }
    }
//�������������ֲ�����Լ��---------------------------------------
//���ƻ���Լ������-----------------------------------------------
    char buffer[1024];
    while (sourceFile.read(buffer, sizeof(buffer))) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
    // д��ʣ������ݣ�����еĻ���
    if (sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
//���ƻ���Լ������-----------------------------------------------

    // �ر��ļ�
    sourceFile.close();
    destinationFile.close();
}
