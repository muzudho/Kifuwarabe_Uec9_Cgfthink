#pragma once


#include "../h190_board___/n190_050_abstractBoard.h"
#include "../h190_board___/n190_100_board.h"



// �����̈ʒu���܂ސ΁A�܂��͘A�̑��ċz�_�̐����A�e��_�Ɋi�[�����e�[�u���ł��B
class MarkingBoard : public AbstractBoard {
public:
	void Initialize(Board* pBoard);
};