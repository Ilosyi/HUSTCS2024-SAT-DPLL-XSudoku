#include "Literal.h"
//������
//Ĭ�Ϲ��캯��
Literal::Literal()
{
	this->var = 0;
}
//�вι��캯��
Literal::Literal(int var)
{
	this->var = var;
}
//��������
Literal::~Literal()
{
}	
//�Ƿ��Ǹ�����
bool Literal::isNegative()
{
	return var < 0;
}
//���ؾ���ֵ
int Literal::getAbs()
{
	return abs(var);
}
//��ӡ����
void Literal::print()
{
	cout << var << " ";
}
//���Ⱥ�����
bool Literal::operator!=(const Literal& l)const
{
	return this->var != l.var;
}
//�Ⱥ�����
bool Literal::operator==(const Literal& l)const
{
	return this->var == l.var;
}

