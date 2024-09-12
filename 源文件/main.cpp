#include"DPLL-Solver.h"
#include"Literal.h"
#include"Clause.h"
#include"CNF.h"
#include"CNFParser.h"
#include"vector.hpp"
#include"definition.h"
#include"GenerateXSudoku.h"
#include"CheckSudokuBoard.hpp"
bool SudokuToCnf(const vector<int>& board, int empty);//������ת��ΪCNF
bool XSudokuToCnf(const vector<int>& board, int empty);//���Խ�������ת��ΪCNF

int Count = 0;//�ݹ����
int numVars = 0, numClauses = 0;//��Ԫ�����Ӿ���

int main() {
	int choice = 1, choice2 = 1, choice3 = 1, choice4 = 1, way = 1;//ѡ��
	int isRead = 0;//�Ƿ��ȡCNF�ļ�
	std::string filename;//�ļ���
	CNF Cnf;	//CNF
	clock_t start, end;//��ʱ
	double time1 = 0, time2 = 0;//ʱ��Ƚ�
	int* assignments = nullptr;//������Ԫ�ĸ�ֵ״̬

    Sodoku* sodoku = new Sodoku();
    vector<int> NormalBoard(81, 0);//������������
    vector<int> GameBoard(81, 0);//�ڶ����ɵ�������Ϸ����
	vector<int> GamePlayBoard(81, 0);//�����д��������Ϸ����
	int empty = 0;//�ڶ���Ŀ
	int x = 0, y = 0, num = 0;//�����������������

	srand(static_cast<unsigned int>(time(nullptr)));//���������

    while (true) {
        cout << endl << endl;
		cout << "\t  ��  ��" << endl;
        cout << "**********************************" << endl;
        cout << endl;
		cout << "1.SAT�����\t  2.������Ϸ"<< endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "**********************************" << endl;
        cout << "����������ѡ��";
        cin >> choice;
		system("cls");
        switch (choice) {
        case 1:
            choice2 = 1;
            while (choice2)
            {
                way = 1;
                cout << endl;
                cout << "*****************SAT���********************" << endl << endl;
				cout << "\t1.��ȡCNF�ļ�     2.��ӡCNF�ļ�" << endl<<endl;
				cout << "\t3.���CNF�ļ�     0.����" << endl;
                cout << "********************************************" << endl<<endl;
                cout << "����������ѡ��";
				cin >> choice2;
                switch (choice2)
                {
                case 1:
                    cout << "������CNF�ļ�·����";
                    cin >> filename;
                    if (CNFParser::parse(Cnf, filename, numVars, numClauses))
                    {
                        isRead = 1;
                        if (assignments != nullptr) delete[] assignments;
						assignments = new int[numVars + 1];
			            
                        cout << "��ȡ�ɹ�" << endl;
                    }
                    //�����������
                    system("pause");
                    system("cls");
                    break;
                case 2:
					if (Cnf.isEmpty()) cout << "CNFΪ��" << endl;
                    else Cnf.print();
					//�����������
					system("pause");
                    system("cls");
                    break;
                case 3:
                    while (isRead&&way) {
                        Count = 0;
                        cout << endl;
						cout << "----------��Ԫѡ�����------------" << endl;
                        cout << "---1.���ѡ���Ԫ" << endl;
                        cout << "---2.ѡ���һ����Ԫ" << endl;
                        cout << "---3.ѡ����ִ�����������" << endl;
                        cout << "---4.ѡ��Ȩ����������" << endl;
						cout << "---5.ѡ��Ȩ���������֣�����������" << endl;
                        cout << "---0.����" << endl;
                        cout << endl;
                        cout << "�������Ԫѡ�����:";
                        cin >> way;
                        if (way == 0) { system("cls"); break; }
                        //����ִ��ʱ��

                        start = clock();
                        bool result = DPLL(Cnf, way, assignments);
                        if (result)
                        {
                            cout << "������" << endl;
							printAssignments(assignments,1);
                        }
                        else cout << "��������" << endl;
                        end = clock();
                        
						if (way == 2) time1 = (double)(end - start);
                        time2 = (double)(end - start);
                        saveResultToFile(filename, result, assignments, time2);
                        cout << "ִ��ʱ�䣺" << time2 << "ms" << endl;
						if (time1 == 0 || time1 == time2 || time2 == 0) cout << "ʱ���Ż��ʣ�0%" << endl;
						else cout << "ʱ���Ż��ʣ�" << (time1 - time2) / time1 * 100 << "%" << endl;

                        system("pause");
                        system("cls");
                    }
                    if (isRead == 0)
                    {
						cout << "���ȶ�ȡCNF�ļ�" << endl;
                        system("pause");
                        system("cls");
                    }
                    break;
				case 0:
					system("cls");
                   
					break;
                default:
                    break;
                }

            }		         
            break;
        case 2:
            choice3 = 1;
            while (choice3)
            {
               
                cout << endl;
                cout << "*****************������Ϸ*******************" << endl << endl;
                cout << "\t1.��ͨ����     2.�Խ�������" << endl << endl;;
                cout << "\t0.����" << endl;
                cout << "********************************************" << endl << endl;;
                cout << "����������ѡ��";
                cin >> choice3;
                switch (choice3)
                {
                case 1:
					system("cls");
                    StartSodokuGenerate(sodoku, NormalBoard);                 
					empty=generateGameBoard(NormalBoard, GameBoard);
					GamePlayBoard = GameBoard;					
                    choice4 = 1;
                    while (choice4)
                    {
						system("cls");
						cout << endl;
						cout << "-----------------������Ϸ-----------------" << endl << endl;
						cout << "\t1.��д����     2.�鿴��" << endl << endl;
                        cout << "\t3.���¿�ʼ     4.����" << endl << endl;
                        cout << "\t5.DPLL���     0.����" << endl;
						cout << "-------------------------------------------" << endl << endl;
                        PrintBoard(GamePlayBoard);
						cout << "����������ѡ��";
						cin >> choice4;
						switch (choice4)
						{
						case 1:
							cout << "���������꣨x,y�������֣�";
							cin >> x >> y >> num;
							if (x < 1 || x>9 || y < 1 || y>9 || num < 0 || num>9)
							{
								cout << "�����������������" << endl;
								system("pause");
								break;
							}
							
							if (GameBoard[(x - 1) * 9 + y - 1] != 0)
							{
								cout << "��λ�ò�����д������������" << endl;
								system("pause");
								break;
							}
							//��⵱ǰ�����Ƿ�Ϸ�
							if (CheckBoard(GamePlayBoard, x, y, num) == false)
							{
								cout << "��д��������������" << endl;
								system("pause");
								break;
							}
							GamePlayBoard[(x - 1) * 9 + y - 1] = num;
                            cout << endl;
							PrintBoard(GamePlayBoard);
							break;
						case 2:
                            cout << endl;
							PrintBoard(NormalBoard);
							system("pause");
							break;
						case 3:
							GamePlayBoard = GameBoard;
							system("cls");
							PrintBoard(GamePlayBoard);
							break;
						case 4:
							system("cls");
							break;
                        case 5:
							SudokuToCnf(GamePlayBoard,empty);
							if (CNFParser::parse(Cnf, "NormalSudoku.cnf", numVars, numClauses))
							{
								isRead = 1;
                                numVars = 999;
								if (assignments != nullptr) delete[] assignments;
								assignments = new int[numVars + 1];
								cout << "��ȡ�ɹ�" << endl;
							}
							if (DPLL(Cnf, 2, assignments))
							{
								cout << "�����ɽ�" << endl;
								printAssignments(assignments,0);
							}
							else cout << "�������ɽ�" << endl;
							system("pause");
							break;
						case 0:
							system("cls");
							break;
						default:
							break;
						}
                    }
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    generateDiagonalSudoku(NormalBoard);
					empty = generateGameBoard(NormalBoard, GameBoard);
					GamePlayBoard = GameBoard;
                    
					choice4 = 1;
					while (choice4)
					{
						system("cls");
						cout << endl;
						cout << "-----------------������Ϸ-----------------" << endl << endl;
						cout << "\t1.��д����     2.�鿴��" << endl << endl;
						cout << "\t3.���¿�ʼ     4.����" << endl << endl;
						cout << "\t5.DPLL���     0.����" << endl;
						cout << "-------------------------------------------" << endl << endl;
						PrintBoard(GamePlayBoard);
						cout << "����������ѡ��";
						cin >> choice4;
						switch (choice4)
						{
						case 1:
							cout << "���������꣨x,y�������֣�";
							cin >> x >> y >> num;
							if (x < 1 || x>9 || y < 1 || y>9 || num < 0 || num>9)
							{
								cout << "�����������������" << endl;
								system("pause");
								break;
							}
							
							if (GameBoard[(x - 1) * 9 + y - 1] != 0)
							{
								cout << "��λ�ò�����д������������" << endl;
								system("pause");
								break;
							}
							//��⵱ǰ�����Ƿ�Ϸ�
							if (CheckBoard(GamePlayBoard, x, y, num) == false)
							{
								cout << "��д��������������" << endl;
								system("pause");
								break;
							}

							GamePlayBoard[(x - 1) * 9 + y - 1] = num;
							cout << endl;
							PrintBoard(GamePlayBoard);
							break;
						case 2:
							cout << endl;
							PrintBoard(NormalBoard);
							system("pause");
							break;
						case 3:
							GamePlayBoard = GameBoard;
							system("cls");
							PrintBoard(GamePlayBoard);
							break;
						case 4:
							system("cls");
							break;
						case 5:
							XSudokuToCnf(GamePlayBoard, empty);
							if (CNFParser::parse(Cnf, "XSudoku.cnf", numVars, numClauses))
							{
								isRead = 1;
								numVars = 999;
								if (assignments != nullptr) delete[] assignments;
								assignments = new int[numVars + 1];
								cout << "��ȡ�ɹ�" << endl;
							}
							if (DPLL(Cnf, 2, assignments))
							{
								cout << "�����ɽ�" << endl;
								printAssignments(assignments,0);
							}
							else cout << "�������ɽ�" << endl;
							system("pause");
							break;
						case 0:
							system("cls");
							break;
						default:
							break;
						}
					}
					system("pause");
					break;
                case 0:
                    system("cls");
                    break;
                default:
                    break;

                }
       

            }
            break;
        case 0:
			cout << "�˳�����" << endl;
            return 0;
        default:
            cout << "��Ч��ѡ�������³���\n";
        }
    }

    return 0;
}