# 基于SAT的对角线数独游戏求解程序
参考资料

[个人笔记](https://www.cnblogs.com/losyi/p/18397445)

[HUST-SAT_solver_embedded_in_hanidoku](https://github.com/jiajingyyyyyy/HUST-SAT_solver_embedded_in_hanidoku)

[Propositional SAT Solving：DPLL算法求解CNF SAT 与 数独求解程序(C++ 实现)](https://blog.csdn.net/M1170780140/article/details/128053901)

[DPLL 算法之分裂策略](https://blog.csdn.net/wniuniu_/article/details/132550401)

[DPLL-SAT-Solver](https://github.com/hjnodm/DPLL-SAT-Solver/blob/master)

	
[1]杨晗. 求解SAT问题中分支策略与删除策略的研究[D].西南交通大学,2020.DOI:10.27414/d.cnki.gxnju.2019.001679.

[2]陈稳. 基于DPLL的SAT算法的研究及应用[D].电子科技大学,2011.

	
[3]肖凡. SAT及其相关问题的精确算法研究[D].华中科技大学,2020.DOI:10.27157/d.cnki.ghzku.2019.000280.


注:
本项目用vector存储cnf，进行传播时需要重新建立一个vector，在处理长子句时效率极低

虽然本项目功能上涵盖了课设要求，但是跑的很慢（~~能跑就行~~）

用链表的同学可参考[DPLL求解K-SAT问题 C++实现](https://www.cnblogs.com/chesium/p/15982285.html)
