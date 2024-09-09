#pragma once
#include"CNF.h"
#include"clause.h"
/*
��CNF��Conjunctive Normal Form����ȡ��ʽ��������У�assignment ��һ���ؼ������ݽṹ��
���ڼ�¼�����ĸ�ֵ״̬��������˵��assignment ��һ���������͵�������std::vector<bool>����
����ÿ��Ԫ�ض�Ӧһ�������ĸ�ֵ״̬��
*/
/*
�ṹ�ͺ���
������assignment �е�ÿ��������Ӧһ�����������磬assignment[1] ��ʾ���� 1 �ĸ�ֵ״̬��
ֵ��assignment �е�ÿ��ֵ��true �� false����ʾ�����ĸ�ֵ״̬��ͨ����true ��ʾ��������ֵ
Ϊ true��false ��ʾ����δ����ֵ�򱻸�ֵΪ false��
*/
class SATSolver
{
public:
    bool solve(CNF& cnf, vector<bool>& assignment) {
        // ���CNFΪ�գ�����True
        if (cnf.clauses.empty()) return true;

        // ����п��Ӿ䣬����False
        for (int i = 0; i < cnf.clauses.size(); ++i) {
            const Clause& clause = cnf.clauses[i];
            if (clause.literals.empty()) return false;
        }

        // ѡ��һ��δ��ֵ������
        int literal = selectLiteral(cnf, assignment);
        if (literal == 0) return false; // ���û���ҵ�δ��ֵ�����֣�����false

        // �ݹ����true
        CNF cnfTrue = propagate(cnf, literal, true, assignment); // ������ֵ
        vector<bool> assignmentTrue = assignment; // ����assignment
        assignmentTrue[abs(literal)] = (literal > 0); // ��¼�����ֵĸ�ֵ״̬

        if (solve(cnfTrue, assignmentTrue)) { // �ݹ����
            assignment = assignmentTrue;
            return true;
        }

        // �ݹ����false
        CNF cnfFalse = propagate(cnf, literal, false, assignment);
        vector<bool> assignmentFalse = assignment;
        assignmentFalse[abs(literal)] = (literal < 0); // ��¼�����ֵĸ�ֵ״̬

        if (solve(cnfFalse, assignmentFalse)) { // �ݹ����
            assignment = assignmentFalse;
            return true; // ����н⣬����true
        }

        // ���û�н⣬����false
        return false;
    }

private:
    // ѡ�����1��ѡȡ��һ��δ��ֵ������
    int selectLiteral(const CNF& cnf, const vector<bool>& assignment) {
        for (int i = 0; i < cnf.clauses.size(); ++i) {
            const Clause& clause = cnf.clauses[i];
            for (int j = 0; j < clause.literals.size(); ++j) {
                const Literal& literal = clause.literals[j];
                int varIndex = abs(literal.var);
                if (varIndex >= assignment.size() || !assignment[varIndex]) {
                    return literal.var;
                }
            }
        }
        return 0;
    }

    // ���ݷ��ѽ��
    CNF propagate(const CNF& cnf, int literal, bool value, const vector<bool>& assignment) {
        CNF newCNF;

        for (int i = 0; i < cnf.clauses.size(); ++i) {
            const Clause& clause = cnf.clauses[i];
            Clause newClause;
            bool satisfied = false; // �Ƿ�����

            for (int j = 0; j < clause.literals.size(); ++j) {
                const Literal& lit = clause.literals[j];
                if ((lit.var == literal && value) || (lit.var == -literal && !value)) {
                    // ��������Ѿ����㣬���ݵ��Ӿ���������Ӿ�����
                    satisfied = true;
                    break;
                }
                int varIndex = abs(lit.var);
                if (varIndex >= assignment.size() || !assignment[varIndex]) {
                    // �����ֲ������δ��ֵ
                    newClause.addLiteral(lit);
                }
            }

            if (!satisfied) { // ����Ӿ�û�����㣬��ӵ���CNF��
                newCNF.addClause(newClause);
            }
        }

        return newCNF;
    }
};
