#include "CNF.h"
//���캯��
CNF::CNF()
{
}
//����Ӿ�
 void CNF::addClause(Clause c)
{
	clauses.push_back(c);
	/*����//cout << "addClause" << endl;
	this->print();*/
}
 /***********************************************
 *�������ƣ�removeClause
 * �������ܣ��Ƴ����а������Ӿ�L���Ӿ�
 * ע�ͣ����뵥�Ӿ�c���½�һ�����飬��������c���Ӿ临�Ƶ��������У�Ȼ��ָ�������顣
 * ����ֵ��void
 ************************************************/
 void CNF::removeClause(const Clause& c)
{
	vector<Clause> temp;//�½�һ������
	for (int i = 0; i < clauses.size(); i++)//��������
	{
		int j;
		for ( j = 0; j < clauses[i].literals.size(); j++)
		{
			if (clauses[i].literals[j].var == c.literals[0].var)//�������
			{
				break;
			}
		}
		if (j == clauses[i].literals.size())//û�а���
		{
			temp.push_back(clauses[i]);//��ӵ�temp
		}
	}
	clauses = temp;//ָ��������
}

 /***********************************************
*�������ƣ�removeLiteral
* �������ܣ��Ƴ�ʣ�������Ӿ��е�~L����
* ע�ͣ���������L�����������Ӿ䣬ɾ���Ӿ��е�L���֡�
* ����ֵ��void
************************************************/
void CNF::removeLiteral(const Literal& L)
{
	for (int i = 0; i < clauses.size(); i++)
	{
		clauses[i].removeLiteral(L);
	}
}

/***********************************************
*�������ƣ�print
* �������ܣ���ӡCNF
* ע�ͣ����δ�ӡCNF�е��Ӿ䡣
* ����ֵ��void
************************************************/
void CNF::print()
{
	for (int i = 0; i < clauses.size(); i++)
	{
		clauses[i].print();
	}
}