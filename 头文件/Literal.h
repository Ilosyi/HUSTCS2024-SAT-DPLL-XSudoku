#pragma once
#include"definition.h"
class Literal
{
public:
	//��������
	int var;
	Literal();
	//���캯��
	Literal(int var);
	//��������
	~Literal();
	//�Ƿ��Ǹ�����
	bool isNegative();
	//���ؾ���ֵ
	int getAbs();
	//��ӡ����
	void print();
	//���Ⱥ�����
	bool operator!=(const Literal& l)const;
	//�Ⱥ�����
	bool operator==(const Literal& l)const;
};

