#include "../../header/h190_board___/n190_150_liberty.h"
#include "..\..\header\h675_hit_____\n675_200_hitNobiSaver.h"

int HitNobiSaver::Evaluate(
	Core			core			,
	int				color			,
	int				node			,
	Board*			pBoard			,
	LibertyOfNodes* pLibertyOfNodes
)
{
	int score = 0;

#ifndef RANDOM_MOVE_ONLY

	// �΂�u���O�́A��A�E�A���A���@�ɂ��鎩���̐΁i�܂��͘A�j�̌ċz�_�̐��̍��v�B
	int currentAdjLibertySum = 0;
	pLibertyOfNodes->ForeachArroundNodes(node, [&pBoard,&pLibertyOfNodes, &currentAdjLibertySum, color](int adjNode, bool& isBreak) {
		if (pBoard->ValueOf(adjNode)== color)//�����̐�
		{
			currentAdjLibertySum += pLibertyOfNodes->ValueOf(adjNode);
		}
	});

	//----------------------------------------
	// ��@�ł������̂ɐL�΂��Ă��܂��Ƃ������Ƃ��Ȃ��悤�A�ċz�_�� 1�`3 �̂Ƃ�����@�ƒ�`���܂��B
	//----------------------------------------
	if (!(0<currentAdjLibertySum && currentAdjLibertySum<4))
	{
		// ��@����Ȃ������B
		goto gt_EndMethod;
	}
	// �����0�ɂ�鏜�Z�������

	// �ċz�_�Ɏ����̐΂�u�����ƍl���āA�΂�u�����ǖʂ̂��̎����̐΁i�܂��͘A�j�̌ċz�_�𐔂��܂��B
	Liberty futureLiberty;
	futureLiberty.Count(node, color, pBoard);

	// �]���l�v�Z
	if (futureLiberty.liberty <= currentAdjLibertySum)
	{
		// �c�P�ā@�ċz�_�������Ă��Ȃ��悤�ł͘b���ɂȂ�܂���B
		//score += 0;
	}
	else
	{
		// �c�P�ā@�ċz�_�������Ă���̂ŁA�ǂꂾ�����������𐔂��܂��B
		int upLiberty = futureLiberty.liberty - currentAdjLibertySum;

		//score += 40  // 40����{�ɁB
		score += 1  // 1 ����{�ɁB
			+
			(upLiberty - 1) * 50    // �ċz�_���Q�ȏ㑝����Ȃ�A
									// �ċz�_���P�����邽�т� 50 �_�̃{�[�i�X�B
			/
			(currentAdjLibertySum * currentAdjLibertySum * currentAdjLibertySum)
									// �c�P��O�̌ċz�_�̐����傫���قǁA
									// �X�R�A������i�ً}�̊֐S�𔖂ꂳ����j�d�|���B
									// �ċz�_ 1 = 1�^1 �_
									// �ċz�_ 2 = 1�^8 �_
									// �ċz�_ 3 = 1�^27 �_
									// �ċz�_ 4 = 1�^64 �_
			;
	}
	
	//----------------------------------------
	// �����ڂɔ{�����|���܂��B
	//----------------------------------------
	score *= 80 / 10;

gt_EndMethod:

#endif

	return score;
}
