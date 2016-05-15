#pragma once


#include "../h190_board___/n190_100_board.h"


//--------------------------------------------------------------------------------
// enum �܂Ƃ�
//--------------------------------------------------------------------------------

// �������ŃZ�b�g����l
// ���̈ʒu�̐΂��u���v���u���v���B�s���ȏꍇ�́u���v�ŁB
// ���̈ʒu�̓_���u���n�v�u���n�v�u�_���v���B
enum GtpStatusType {
	GTP_ALIVE,				// ��
	GTP_DEAD,				// ��
	GTP_ALIVE_IN_SEKI,		// �Z�L�Ŋ��i���g�p�A�u���v�ő�p���ĉ������j
	GTP_WHITE_TERRITORY,	// ���n
	GTP_BLACK_TERRITORY,	// ���n
	GTP_DAME				// �_��
};


class Endgame {
public:

	// �I�Ǐ����i�T���v���ł͊ȒP�Ȕ��f�Ŏ��΂ƒn�̔�������Ă��܂��j
	static int EndgameStatus(
		int arr_endgameBoard[],	// �I�ǐ}�̔Տ�̐΂̐F
		Board* pBoard
		);

	// �}�`��`��
	static int EndgameDrawFigure(
		int arr_endgameBoard[],
		Board* pBoard
		);

	// ���l������(0�͕\������Ȃ�)
	static int EndgameDrawNumber(
		int arr_endgameBoard[],
		Board* pBoard
		);
};
