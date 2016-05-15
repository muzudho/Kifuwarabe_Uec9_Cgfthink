#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h190_board___/n190_150_Liberty.h"
#include "../../header/h675_hit_____/n675_100_hitTuke.h"




HitTuke::HitTuke()
{
};




int HitTuke::Evaluate(
	int		invColor,
	int		node,
	Liberty liberties[4],
	Board*	pBoard
	)
{
	int score = 0;

#ifndef RANDOM_MOVE_ONLY
#ifdef ENABLE_MOVE_ATTACK
	// �]���l�̌v�Z�i�S�������J��Ԃ��j
	pBoard->ForeachArroundDirAndNodes(node, [&pBoard,&liberties,&score, invColor](int iDir,int adjNode, bool& isBreak) {
		int adjColor = pBoard->ValueOf(adjNode);		// ���̐F

		score +=
			(adjColor == invColor)		// �ׂ̐�
										//		����̐�: 1
										//		����ȊO: 0
										//   �~
			* liberties[iDir].renIshi	// �A�̐΂̐�
										//   �~
			* (10 / (liberties[iDir].liberty + 1));	// �A�̌ċz�_�̌�
													//		0��: 10�_
													//		1��:  5�_
													//		2��:  3.3333...�_
													//		3��:  2.5�_
													//		4��:  2�_
													//		...
	});
#endif
#endif

	return score;
}