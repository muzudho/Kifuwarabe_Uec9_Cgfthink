#pragma once


#include "../h090_core____/n090_100_core.h"
#include "../h190_board___/n190_100_board.h"
#include "../h190_board___/n190_200_libertyOfNodes.h"
#include "../h675_hit_____/n675_000_hit.h"

// �A�e�悤�Ƃ��܂��B
//
// _____
// __1__
// _xox_
// __x__
// _____
//
// ��} o �𑊎�̐΁A x �������̐΂Ƃ��A
// 1 �Ɏ����̐΂�u���]���������Ȃ�d�g�݁B
//
// �������A1 �̒n�_���R�E�ɂȂ�ꍇ�͒u���܂���B
//
// _____
// __o__
// _o1o_
// _xox_
// __x__
// _____
class HitAte : Hit {
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