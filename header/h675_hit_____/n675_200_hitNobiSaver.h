#pragma once


#include "../h090_core____/n090_100_core.h"
#include "../h190_board___/n190_100_board.h"
#include "../h190_board___/n190_200_libertyOfNodes.h"
#include "../h675_hit_____/n675_000_hit.h"

// ������ꂻ���Ȑ΂��@�m�r�@�����悤�Ƃ��܂��B
//
// _____
// __o__
// __1__
// _xox_
// __x__
// _____
//
// ��} o �𑊎�̐΁A x �������̐΂Ƃ��A
// �n�_ 1 �� o ��u�����ƂŁA
// �ċz�_ 1�`4 �̎����̐΂́@�ċz�_�@�𑝂₷���Ƃŏ�������悤�A
// �]���������Ȃ�d�g�݁B
//
// �ċz�_ 2�ȏ�̐΂́@���܂�~�o���悤�Ƃ��Ȃ��B
class HitNobiSaver : Hit {
public:

	// �]���l���o���܂��B
	int Evaluate(
		Core			core,
		int				color,
		int				node,
		Board*			pBoard,
		LibertyOfNodes*	pLibertyOfNodes
	);
};