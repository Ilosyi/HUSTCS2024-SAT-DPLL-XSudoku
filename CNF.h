#pragma once
#include"clause.h"
class CNF
{
public:
	//�Ӿ伯��
	vector<Clause> clauses;
	//���캯��
	CNF();
	//����Ӿ�
	void addClause(Clause c);
	//�Ƴ����а������Ӿ�L���Ӿ�
	void removeClause(const Clause& clause);
	//�Ƴ�ʣ�������Ӿ��е�~L
	void removeLiteral(const Literal& L);
	bool isEmpty() const {
		return clauses.empty();
	}
	bool hasNext() const {
		// ����б���������һ���Ӿ䣬�Ҳ��ǿ��Ӿ䣬�򷵻�true
		return !clauses.empty() && !clauses[0].literals.empty();
	}
	void print();
};

