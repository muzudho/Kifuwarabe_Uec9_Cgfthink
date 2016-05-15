#pragma once


#include <windows.h> // �R���\�[���ւ̏o�͓�
#include "../h090_core____/n090_100_core.h"
#include "../h190_board___/n190_150_liberty.h"
#include "../h670_noHit___/n670_000_noHit.h"


//--------------------------------------------------------------------------------
// �N���X
//--------------------------------------------------------------------------------

//
// ���E����w���Ȃ��d�g�݁B
//
class NoHitSuicide : NoHit
{
public:
	// �G�΂�������t���O
	int flgCapture;

public:
	NoHitSuicide();

	// ���E��ɂȂ�󋵂łȂ��������B
	bool IsThis(
		Core	core		,
		int		color		,
		int		node		,
		Liberty liberties[4],
		Board*	pBoard
	);
};
