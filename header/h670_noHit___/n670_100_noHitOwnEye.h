#pragma once


#include "../h190_board___/n190_150_liberty.h"
#include "../h670_noHit___/n670_000_noHit.h"


// _____
// __o__
// _o1o_
// __o__
// _____
//
// ��} o �������̐΂Ƃ��A
// 1 ���@��@�Ɍ����ĂāA
//
// �����̊�ɑł��Ȃ��d�g�݁B
class NoHitOwnEye : NoHit {
public:
	// �S�����ɗאڂ���A�ċz�_��������@�Ȃ����閡���̐΂��@�������B0�`4�B
	int safe;

public:
	NoHitOwnEye();

	// �����̊�ɑł����ޏ󋵂�����
	bool IsThis(
		int		color		,
		int		node		,
		Liberty liberties[4],
		Board*	pBoard
	);
};