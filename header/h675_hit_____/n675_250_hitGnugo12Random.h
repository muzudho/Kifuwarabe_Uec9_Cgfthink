#pragma once


#include "../h190_board___/n190_100_board.h"
#include "../h675_hit_____/n675_000_hit.h"




// Gnugo1.2 ���Q�l�ɂ��������_���ȕ]����Ԃ��܂��B
class HitGnugo12Random : Hit {
public:
	// �]���l���o���܂��B
	int Evaluate(
		int		color,
		int		node,
		Board*	pBoard
		);
};