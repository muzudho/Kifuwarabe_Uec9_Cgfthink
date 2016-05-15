// muzudho: ���O�o�͂̂��߂ɁB
#include <iostream>
#include <fstream>
using namespace std;

#include <time.h>		// clock() ���g�p���邽�߂ɁB
#include <tchar.h>		// Unicode�Ή��� _T() �֐����g�p���邽�߂ɁB
#include "../../header/h090_core____/n090_100_core.h"
#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h190_board___/n190_200_libertyOfNodes.h"
#include "../../header/h300_move____/n300_100_move.h"
#include "../../header/h390_explain_/n390_100_explain.h"
#include "../../header/h490_endgame_/n490_100_endgame.h"
#include "../../header/h670_noHit___/n670_050_noHitSuicide.h"
#include "../../header/h670_noHit___/n670_100_noHitOwnEye.h"
#include "../../header/h700_think___/n700_100_evaluation.h"
#include "../../header/h700_think___/n700_200_think.h"


int Think::Bestmove(
	Core			core			,
	int				color			,
	Board*			pBoard			,
	LibertyOfNodes*	pLibertyOfNodes
)
{
#ifdef CHECK_LOG
	core.PRT( _T("Bestmove�J�n���I \n"));
#endif

#ifdef ENABLE_MOVE_RETRY
	int retry = 0;
	// �ُ������I�@���g���C���I
	gt_Retry:
		;
#endif


	int maxScore;	// ���܂œǂ񂾎�ň�ԍ��������]���l
	int bestmoveNode;

	// ���s���邽�тɈႤ�l��������悤�Ɍ��݂̎����ŗ�����������
	srand((unsigned)clock());

	//----------------------------------------
	// �΂�u���ʒu�P���A���̎�̕]���l���Z�o���܂��B
	//----------------------------------------
	maxScore = -1;
	bestmoveNode = 0; // 0 �Ȃ�p�X�B

	pBoard->ForeachAllNodesWithoutWaku([color,&maxScore,&bestmoveNode,&pBoard,&pLibertyOfNodes, &core](int node, bool& isBreak) {
		//{
			//int x, y;
			//AbstractBoard::ConvertToXy(x, y, node);
			//core.PRT(_T("#(%d,%d) "), x, y);
		//}

		// ���̋ǖʂŁA�΂�u�����Ƃ��̕]���l
		int flgAbort = 0;
		int score;		// �ǂ�ł����̕]���l
		score = Evaluation::EvaluateAtNode(core, flgAbort, color, node, pBoard, pLibertyOfNodes);
		if (flgAbort)
		{
			goto gt_Next;
		}

		// �x�X�g���[�u���X�V���܂��B
		// PRT("x,y=(%d,%d)=%d\n",x,y,score);
		if (maxScore < score) {
			maxScore = score;
			bestmoveNode = node;
		}
	gt_Next:
		;
	});

#ifdef ENABLE_MOVE_RETRY

	int x, y;
	AbstractBoard::ConvertToXy(x, y, bestmoveNode);

	// �ُ������I�@���g���C���I
	if (bestmoveNode==0)
	{
		// �p�X�͐���ł��B
		goto gt_EndMethod;
	}
	else if (400<retry)
	{
		// ���߂ăp�X�ɂ��܂��B
		bestmoveNode = 0;
		goto gt_EndMethod;
	}
	else if (pBoard->ValueOf(bestmoveNode) == BLACK || pBoard->ValueOf(bestmoveNode) == WHITE) {
		// �΂�����Ȃ�
		core.PRT(_T("(%d,%d)�@�΂�����B�@���g���C���I�@[%d]\n"), x,y, retry);
		retry++;
		goto gt_Retry;
	}
	else if (pBoard->ValueOf(bestmoveNode) == WAKU) {
		// �g�Ȃ�
		core.PRT(_T("(%d,%d)�@�g�������B�@���g���C���I�@[%d]\n"), x, y, retry);
		retry++;
		goto gt_Retry;
	}
	else if (bestmoveNode == pBoard->kouNode) {
		// �R�E�ɂȂ�ʒu�Ȃ�
		core.PRT(_T("(%d,%d)�@�R�E�ɂȂ�B�@���g���C���I�@[%d]\n"), x, y, retry);
		retry++;
		goto gt_Retry;
	}

	Liberty liberties[4];// ��� �� �E�� �� ���� �� ����
	pBoard->ForeachArroundDirAndNodes(bestmoveNode, [&pBoard, &liberties](int iDir, int adjNode, bool& isBreak) {
		int adjColor = pBoard->ValueOf(adjNode);			// �㉺���E��(adjacent)�̐΂̐F
		liberties[iDir].Count(adjNode, adjColor, pBoard);	// �ׂ̐΁i�܂��͘A�j�̌ċz�_�@�̐��𐔂��܂��B
	});

	// �����̊�ׂ��`�F�b�N
	{
		NoHitOwnEye	noHitOwnEye;		// �����̊�ɑł��Ȃ��d�g�݁B
		if (noHitOwnEye.IsThis(color, bestmoveNode, liberties, pBoard)) {// �����̊�ɑł����ޏ󋵂�����
			core.PRT(_T("(%d,%d)�@�����̊�ɑł����ށB�@���g���C���I�@[%d]\n"), x, y, retry);
			retry++;
			goto gt_Retry;
		}
	}

	// ���E��`�F�b�N
	{
		NoHitSuicide			noHitSuicide;		// ���E���ł��Ȃ��悤�ɂ���d�g�݁B

		if (noHitSuicide.IsThis(core, color, bestmoveNode, liberties, pBoard)) {// ���E��ɂȂ�󋵂łȂ��������B
			core.PRT(_T("(%d,%d)�@���E��ɂȂ�B�@���g���C���I�@[%d]\n"), x, y, retry);
			retry++;
			goto gt_Retry;
		}
	}
#endif

gt_EndMethod:
	return bestmoveNode;
}
