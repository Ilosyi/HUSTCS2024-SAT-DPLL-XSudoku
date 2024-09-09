#include "clause.h"

//���캯��
Clause::Clause()
{
}
//��������
Clause::~Clause()
{
}
//�������
 void Clause::addLiteral(Literal l)
{
	literals.push_back(l);
}
 /***********************************************
*�������ƣ�removeLiteral
* �������ܣ�ɾ���Ӿ��е��ض�����
* ע�ͣ��½�һ�����飬�������ض����ֵ����ָ��Ƶ��������У�Ȼ��ָ�������顣
* ����ֵ��void
************************************************/
 void Clause::removeLiteral(const Literal& l)
{
	vector<Literal> temp;//�½�һ������
	for (int i = 0; i < literals.size(); i++)//��������
	{
		if (literals[i].var != l.var)
		{
			temp.push_back(literals[i]);
		}
	}
	literals = temp;//ָ��������
	
}
 /***********************************************
 *�������ƣ�print
 * �������ܣ���ӡ�Ӿ�
 * ע�ͣ����δ�ӡ�Ӿ��е����֡�
 * ����ֵ��void
 ************************************************/
 void Clause::print()
{
	for (int i = 0; i < literals.size(); i++)
	{
		literals[i].print();
	}
	cout << endl;
}
 /***********************************************
 *�������ƣ�isUnit
 * �������ܣ��ж��Ƿ��ǵ��Ӿ�
 * ע�ͣ��ж��Ӿ������ֵĸ����Ƿ�Ϊ1��
 * ����ֵ��bool���ͣ�����ǵ��Ӿ䣬�򷵻�true�����򷵻�false��
 ************************************************/
 bool Clause::isUnit()const
{
	return literals.size() == 1;
}
