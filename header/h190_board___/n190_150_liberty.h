#pragma once


#include "../h190_board___/n190_100_board.h"




class Liberty {
public:
	// ���ɂ��̐΂����������ꍇ��1
	int checkedBoard[BOARD_MAX];

	// �A�̃��o�e�B�i�΂̌ċz�_�j�̐�(�ċA�֐��Ŏg��)
	int liberty;

	// �אڂ���i�P���邢�͘A�́j�΂̐�(�ċA�֐��Ŏg��)
	int renIshi;

public:
	Liberty();


	// �ʒu node �ɂ����郊�o�e�B�i�΂̌ċz�_�j�̐��Ɛ΂̐����v�Z�B���ʂ� liberty �ϐ��Ɋi�[�B
	void	Count(
		int		node,
		int		color,
		Board*	pBoard
	);

	// ���o�e�B�i�΂̌ċz�_�j�Ɛ΂̐�����ċA�֐�
	// 4�����𒲂ׂāA�󔒂�������+1�A�����̐΂Ȃ�ċA�ŁB����̐΁A�ǂȂ炻�̂܂܁B
	void	CountElement(
		int		tNode,
		int		color,
		Board*	pBoard
	);
};