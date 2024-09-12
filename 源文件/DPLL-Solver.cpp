#include "DPLL-Solver.h"
#include <chrono>

extern int  numVars;//��Ԫ��������main.cpp�ж���
extern int Count;//�����ã����ݹ����

/***********************************************
*�������ƣ�propagate
* �������ܣ����ݸ��������֣�literal���� CNF ��ʽ���д��������� CNF ��ʽ�͸�ֵ���顣
* ע�ͣ�- ���� CNF ��ʽ�е������Ӿ䡣
        - ����Ӿ��Ƿ��ѱ��������֣�literal�����㡣
        - ����Ӿ��ѱ����㣬����Ը��Ӿ䡣
        - ����Ӿ�δ�����㣬ɾ���Ӿ�������������෴�����֡�
        - ���ɾ�����ֺ��Ӿ�Ϊ�գ��򷵻� False����ʾ��ͻ��
        - ����Ӿ�ǿգ�������ӵ��µ� CNF ��ʽ�С�
        - ���¸�ֵ�����Լ�¼���ֵĸ�ֵ��
* ����ֵ��bool ���ͣ���������ɹ����򷵻� True�������ֿ��Ӿ䣬�򷵻� False��
************************************************/
bool propagate(CNF& cnf, const Literal& literal,int *assignments) {
    CNF newCNF;
    bool hasChanged = false;

    for (int i = 0; i < cnf.clauses.size(); ++i) {
        const Clause& clause = cnf.clauses[i];//ȡ��һ���Ӿ�

        //����־��Ƿ��������
        bool satisfied = false;
        for (int j = 0; j < clause.literals.size(); ++j) {
            if (clause.literals[j] == literal) //�������
            {
                satisfied = true;
                break;
            }
        }

        if (satisfied) {
			//ɾ����������־䣬������ӵ���CNF
            continue;
        }

        //ɾ���Ӿ��е�~L����
        Clause newClause = clause;
        Literal negLiteral(-literal.var);
        newClause.removeLiteral(negLiteral);

        //���ɾ��~L���Ӿ䲻Ϊ�գ���ӵ���CNF
        if (!newClause.literals.empty()) {
            newCNF.addClause(newClause);
        }
        else {
            // ������ֿ��Ӿ䣬����false
            return false;
        }
        hasChanged = true;//����Ѿ��ı�
    }
	assignments[abs(literal.var)] = (literal.var > 0) ? 1 : -1; //��¼��ֵ���
	cnf = newCNF;//����CNF
    return true;
}

/***********************************************
*�������ƣ�selectLiteral
* �������ܣ�����ָ���Ĳ���ѡ��һ�����֡�
* ע�ͣ�- ����1��ѡ���һ���Ӿ�ĵ�һ�����֡�
        - ����2�����ѡ��һ���ǿ��Ӿ��е�һ�����֡�
        - ����3��ѡ����ִ����������֡�
        - ����4��ѡ��Ȩ���������֣���������������
        - ����5��ѡ��Ȩ���������֣�������������
* ����ֵ��Literal ���ͣ�����ѡ������֡�
************************************************/
 Literal selectLiteral(const CNF& cnf,int way) {
    // ����1��ѡ���һ���Ӿ�ĵ�һ������
	 
     Count++;
     if (way == 2) 
     {
         if (!cnf.clauses.empty() && !cnf.clauses[0].literals.empty()) //����Ӿ䲻Ϊ��
         {
             return cnf.clauses[0].literals[0];
         }
     }
	 // ����2�����ѡȡһ������
     else if (way == 1)
     {
            
         // �ҵ�һ���ǿ��Ӿ�
         int clauseIndex = rand() % cnf.clauses.size();
         while (cnf.clauses[clauseIndex].literals.empty()) {
             clauseIndex = rand() % cnf.clauses.size();
         }

         // ѡ���Ӿ��е�һ������
         int literalIndex = rand() % cnf.clauses[clauseIndex].literals.size();
         return cnf.clauses[clauseIndex].literals[literalIndex];
     }
	 // ����3��ѡ����ִ�����������
     else if (way == 3)
	 {
         // ��ʼ����������
         vector<int> cnt(numVars * 2 + 1, 0);

         // ����ÿ����Ԫ�ĳ��ִ���
         for (const Clause& clause : cnf.clauses) {
             for (const Literal& literal : clause.literals) {
                 if (literal.var > 0) {
                     cnt[literal.var]++;
                 }
                 else {
                     cnt[numVars - literal.var]++;
                 }
             }
         }

         // ѡ����ִ������ı�Ԫ�����棩
         int maxBool = 0;
         int maxTimes = 0;
         for (int i = 1; i <= numVars; ++i) {
             if (cnt[i] > maxTimes) {
                 maxTimes = cnt[i];
                 maxBool = i;
             }
         }

         // ��������Ԫ�ĳ��ִ������� 1����ѡ�����Ԫ
         if (maxTimes == 1) {
             for (int i = numVars + 1; i <= numVars * 2; ++i) {
                 if (cnt[i] > maxTimes) {
                     maxTimes = cnt[i];
                     maxBool = numVars - i;
                 }
             }
         }

         return Literal(maxBool);
	 }
	 //����4��ѡ��Ȩ���������֣�������������
     else if (way == 4)
     {

         // ʹ�� vector �����ָ��
         vector<double> weight(numVars + 1, 0.0);

         // ����ÿ����Ԫ��Ȩ��
         for (const Clause& clause : cnf.clauses) {
             double clauseWeight = pow(2.0, -static_cast<double>(clause.literals.size()));
             for (const Literal& literal : clause.literals) {
                 if (literal.var != 0) {
                     int varIndex = abs(literal.var);
                     if (varIndex <= numVars) {
                         weight[varIndex] += clauseWeight;
                     }
                 }
             }
         }

         // �ҵ����Ȩ�صı�Ԫ
         double maxWeight = 0.0;
         int maxBool = 0;
         for (int i = 1; i <= numVars; ++i) {
             if (weight[i] > maxWeight) {
                 maxWeight = weight[i];
                 maxBool = i;
             }
         }

         return Literal(maxBool);
     }
	 //����5��ѡ��Ȩ���������֣�����������
     else
     {
         // ʹ�� std::vector �����ָ��
         vector<double> weight(numVars * 2 + 1, 0.0);

         // ����ÿ����Ԫ��Ȩ��
         for (const Clause& clause : cnf.clauses) {
             double clauseWeight = pow(2.0, -static_cast<double>(clause.literals.size()));
             for (const Literal& literal : clause.literals) {
                 int varIndex = std::abs(literal.var);
                 if (literal.var > 0) {
                     weight[varIndex] += clauseWeight;
                 }
                 else {
                     weight[numVars - literal.var] += clauseWeight;
                 }
             }
         }

         // �ҵ����Ȩ�صı�Ԫ
         double maxWeight = 0.0;
         int maxBool = 0;
         for (int i = 1; i <= numVars; ++i) {
             double totalWeight = weight[i] + weight[i + numVars];
             if (totalWeight > maxWeight) {
                 maxWeight = totalWeight;
                 maxBool = i;
             }
         }

         // ȷ�����ձ�Ԫ�����滹�Ƿ���
         if (weight[maxBool] < weight[maxBool + numVars]) {
             maxBool = -maxBool;
         }

         return Literal(maxBool);
     }
         return Literal(); // ���ؿ�����
     
}

/***********************************************
*�������ƣ�DPLL
* �������ܣ�ʹ�� DPLL �㷨�Ը����� CNF ��ʽ������⡣
* ע�ͣ�- ���ϲ��ҵ��Ӿ䣬�����д�����
        - ����ҵ����Ӿ��Ҵ����ɹ������������
        - ��� CNF ��ʽΪ�գ�˵�������Ӿ䶼���㣬���� True��
        - ����ѡ��һ�����ֽ��з�֧������
        - ���Ը����ָ�ֵΪ���٣����ݹ�ص��� DPLL ������
        - �����һ��֧�ɹ����򷵻� True�����򣬷��� False��
* ����ֵ��bool ���ͣ���� CNF ��ʽ�����㣬�򷵻� True�����򷵻� False��
************************************************/
 bool DPLL(CNF& cnf,int way, int* assignments) {
    while (true) {
        bool unitClauseFound = false;
        for (int i = 0; i < cnf.clauses.size(); ++i) {
            const Clause& clause = cnf.clauses[i];
            if (clause.isUnit()) {
                //����ǵ��Ӿ䣬����
                Literal unitLiteral = clause.literals[0];//ȡ�����Ӿ������
                if (!propagate(cnf, unitLiteral, assignments)) {
                    return false;//�������ʧ�ܣ�����false
                }
              
                unitClauseFound = true;

                break;
            }
        }

		if (!unitClauseFound) {//û�е��Ӿ䣬����ѭ��
            break;
        }
    }

    if (cnf.isEmpty()) {
        return true; // �����Ӿ䶼����,����true
    }

    //���cnf�л����Ӿ䣬ѡ������
    if (cnf.hasNext())
    {
        // ѡ������������
        Literal literal = selectLiteral(cnf,way);
        if (literal.var == 0) {
            return false; //û�пɹ�ѡ�������
        }

        // �������ֵ����ָ�ֵ
        CNF cnfTrue = cnf;
        Literal posLiteral(literal.var);
        if (propagate(cnfTrue, posLiteral, assignments)) {
            if (DPLL(cnfTrue,way, assignments)) {

                return true;
            }
        }


        CNF cnfFalse = cnf;
        Literal negLiteral(-literal.var);
        if (propagate(cnfFalse, negLiteral, assignments)) {
            if (DPLL(cnfFalse,way, assignments)) {

                return true;
            }
        }
    }

    return false; // ���ַ�֧��ʧ��
}
 
 /***********************************************
*�������ƣ�printAssignments
* �������ܣ���ӡ������ֵ�����еı�����ֵ��
* ע�ͣ�-������ֵ���飬��ӡ��ֵΪ 1 �ı�����
        - ��� choice Ϊ True���Ҹ�ֵΪ -1����Ҳ��ӡ��������
* ����ֵ��void
************************************************/
 void printAssignments(const int* assignments,int choice) {
     for (int i = 1; i <= numVars; ++i) {
         if (assignments[i] == 1) {
             std::cout << i << " ";
         }
         else if (choice&&assignments[i] == -1) {
             std::cout << -i << " ";
         }
     }
     std::cout << std::endl;
 }
 // ��������浽�ļ���
 void saveResultToFile(const std::string& baseFilename, bool result, const int* assignments,double duration) {
     string filename = baseFilename;
     filename.erase(filename.end() - 4,filename.end());
     filename += ".res";
     ofstream outFile(filename);

     if (!outFile) {
         cerr << "���ļ�: " << filename << "ʧ��" << endl;
         return;
     }

     // д�������
     outFile << "s " << (result ? "1" : "0") << std::endl;

     // д�������ֵ
     outFile << "v ";
     if (result) {
     for (int i = 1; i <= numVars; ++i) {
         if (assignments[i] == 1) {
             outFile << i << " ";
         }
         else if (assignments[i] == -1) {
             outFile << -i << " ";
         }
     }
     outFile << std::endl;
 }
     // д��ִ��ʱ��
     outFile << "t " << duration << std::endl;

     outFile.close();
 }