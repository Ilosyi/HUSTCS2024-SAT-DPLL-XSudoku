#pragma once
#include"Literal.h"
#include"vector.hpp"
class Clause
{
public:
	//���ּ���
	vector<Literal> literals;
	//���캯��
	Clause();
	//��������
	~Clause();
	//�������
	void addLiteral(Literal l);
	//ɾ�������ض�����
	void removeLiteral(const Literal& l);
	//��ӡ�Ӿ�
	void print();
	//�ж��Ƿ��ǵ��Ӿ�
	bool isUnit()const;

};

