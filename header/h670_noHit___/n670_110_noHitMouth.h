#pragma once


#include "../h670_noHit___/n670_000_noHit.h"


// _____
// __x__
// _x1x_
// _____
// _____
//
// ��} x ���@���@�Ɍ����ĂāA
// 1 �����̒��Ɍ����āA
//
// ����̐΂̌��̒��ɑł��Ȃ��d�g�݁B
class NoHitMouth : NoHit {
public:
	int adjOppo;	// �㉺���E�ɗא�(adjacent)���鑊��(opponent)�̐΂̐��B

public:
	NoHitMouth();

	// ����̌��ɐ΂�ł����ޏ󋵂łȂ��������B
	void Research(
		int		color	,
		int		node	,
		Board*	pBoard
	);

	// �]���l���o���܂��B
	int Evaluate(
		int flgCapture		// suicide.flgCapture
	);
};