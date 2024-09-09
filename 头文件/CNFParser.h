#pragma once
#include"CNF.h"
class CNFParser
{
public:
	static bool parse(CNF& cnf,const string& filename, int& NumVars, int& NumClauses)
       //���óɾ�̬������������ã�����Ҫʵ��������
    {

        ifstream file(filename);
        std::string line;

		if (!file.is_open())//���ļ�ʧ��
        {
			cerr << "���ļ�: " << filename <<"ʧ��"<< endl;//���������Ϣ
            return false;
        }
   //����     else
   //     {
			//printf("File opened successfully\n");//���ļ��ɹ�
   //     }
        if (!cnf.isEmpty())//���CNF��Ϊ��
        {
			cnf.clauses.clear();//���CNF
        }
		while (std::getline(file, line)) // ���ж�ȡ�ļ�
        {
			//cout << line << endl;
            istringstream iss(line);
			
            if (line[0] == 'c' || line.empty()) {
                continue; // ����ע�ͺͿ���
            }

            if (line[0] == 'p') {
				string format;//��ȡ��p cnf
				iss >> format >> format >> NumVars >> NumClauses;//��ȡ���������Ӿ�
                //���� cout << numVars << " " << numClauses << endl; 
            }
			
            else {
				Clause clause;//�½��Ӿ�
				
				int var;//���ֵ�ֵ
                while (iss >> var && var != 0) {
                    Literal l(var);
					clause.addLiteral(l);//�������				
                }	
				
				cnf.addClause(clause);//����Ӿ�
              
				
            }
        }

		file.close();//�ر��ļ�
        return true;
    }
};