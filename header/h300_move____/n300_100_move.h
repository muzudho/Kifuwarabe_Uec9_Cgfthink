#pragma once


#include <windows.h> // �R���\�[���ւ̏o�͓�
#include "../h090_core____/n090_100_core.h"


//--------------------------------------------------------------------------------
// enum
//--------------------------------------------------------------------------------

// move()�֐��Ŏ��i�߂����̌���
enum MoveResult {
	// ������󂯓����P��ށB
	MOVE_SUCCESS,			// ����

							// �����e���S��ށB
	MOVE_SUICIDE,			// ���E��
	MOVE_KOU,				// �R�E
	MOVE_EXIST,				// ���ɐ΂�����
	MOVE_FATAL				// �G���[�ȂǁB
};


class Move {
public:
	Move();
	~Move();

	// 1��i�߂�B
	int	MoveOne(
		Core core,
		int node,	// ���W
		int color,		// �΂̐F
		Board* pBoard
		);

	// 1��߂��B�i�߂���̂͂P�񂾂��ł��j
	void UndoOnce(Core core, Board* pBoard);
};

