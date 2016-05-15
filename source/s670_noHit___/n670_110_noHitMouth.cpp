#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h670_noHit___/n670_110_noHitMouth.h"




NoHitMouth::NoHitMouth() {
	this->adjOppo = 0;
};




void NoHitMouth::Research(
	int		color	,
	int		node	,
	Board*	pBoard
)
{
	int invColor = INVCLR(color);	//�������]

	pBoard->ForeachArroundNodes(node, [this,&pBoard, invColor](int adjNode, bool& isBreak) {
		int adjColor = pBoard->ValueOf(adjNode);		// �㉺���E��(adjacent)�̐΂̐F

		// 2016-03-12 16:45 Add
		// �ׂ�����̐΁A�܂��͘g�Ȃ�J�E���g�A�b�v�B
		if (adjColor == invColor || adjColor == WAKU) {
			this->adjOppo++;
		}
	});
}




int NoHitMouth::Evaluate(int flgCapture)
{
	int score = 0;

#ifndef RANDOM_MOVE_ONLY

	// 2016-03-12 16:45 Add
	if (this->adjOppo == 3 && ! flgCapture)
	{
		// 3����������̐΂̂Ƃ����
		// ������Ȃ��Ƃ���ɂ́A�ł����݂����Ȃ��B
	}
	else
	{
		// ����ȊO�̓_���A�啝�ɉ��_�B
		//score += 50;
		score += 100;
	}

#endif

	return score;
}

