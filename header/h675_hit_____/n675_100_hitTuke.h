#pragma once


#include "../h190_board___/n190_100_board.h"
#include "../h190_board___/n190_150_liberty.h"
#include "../h675_hit_____/n675_000_hit.h"


// _____
// _ooo_
// __o__
// __1__
// _____
//
// ��} o �𑊎�̐΂Ƃ��A
// 1 �Ɏ����̐΂�u�����Ƃ��A
// �� �̐��������A�� �̌ċz�_�����Ȃ����̂ق�
// 1 �̕]���������Ȃ�d�g�݁B
//
// �c�P�悤�Ƃ��܂��B
class HitTuke : Hit {
public:
	HitTuke();

	// �]���l���o���܂��B
	int Evaluate(
		int		invColor,
		int		node,
		Liberty liberties[4],
		Board*	pBoard
		);

};