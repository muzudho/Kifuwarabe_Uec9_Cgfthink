#pragma once

#include <tchar.h> // Unicode�Ή��� _T() �֐����g�p���邽�߂ɁB
#include "../h190_board___/n190_100_board.h"
#include "../h190_board___/n190_200_libertyOfNodes.h"


//--------------------------------------------------------------------------------
// enum
//--------------------------------------------------------------------------------

// ���݋ǖʂŉ������邩�A���w��
enum GameType {
	GAME_MOVE,				// �ʏ�̎�
	GAME_END_STATUS,		// �I�Ǐ���
	GAME_DRAW_FIGURE,		// �}�`��`��
	GAME_DRAW_NUMBER 		// ���l������
};


class Think {
public:
	// �����ɋ߂��]���֐��B�����΂����ɍs���悤�ɁB
	static int	Bestmove(
		Core			core			,
		int				coler			,		// �΂̐F
		Board*			pBoard			,
		LibertyOfNodes*	pLibertyOfNodes
		);
};
