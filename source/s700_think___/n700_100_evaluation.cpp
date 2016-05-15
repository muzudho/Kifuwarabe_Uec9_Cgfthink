#include "../../header/h090_core____/n090_100_core.h"
#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h190_board___/n190_200_libertyOfNodes.h"
#include "../../header/h300_move____/n300_100_move.h"
#include "../../header/h670_noHit___/n670_050_noHitSuicide.h"
#include "../../header/h670_noHit___/n670_100_noHitOwnEye.h"
#include "../../header/h670_noHit___/n670_110_noHitMouth.h"
#include "../../header/h670_noHit___/n670_120_noHitHasinohoBocchi.h"
#include "../../header/h675_hit_____/n675_050_hitRandom.h"
#include "../../header/h675_hit_____/n675_100_hitTuke.h"
#include "../../header/h675_hit_____/n675_150_hitAte.h"
#include "../../header/h675_hit_____/n675_200_hitNobiSaver.h"
#include "../../header/h675_hit_____/n675_250_hitGnugo12Random.h"
#include "../../header/h700_think___/n700_100_evaluation.h"


int Evaluation::EvaluateAtNode(
	Core			core			,
	int&			flgAbort		,
	int				color			,
	int				node			,
	Board*			pBoard			,
	LibertyOfNodes* pLibertyOfNodes
)
{
	int invColor = INVCLR(color);				//�������]
	NoHitSuicide			noHitSuicide;		// ���E���ł��Ȃ��悤�ɂ���d�g�݁B
	NoHitOwnEye				noHitOwnEye;		// �����̊�ɑł��Ȃ��d�g�݁B
	NoHitMouth				noHitMouth;			// ����̌��ɑł��Ȃ��d�g�݁B
	NoHitHasinohoBocchi		noHitHasinoho;		// �[�̕��ɂ́A�ڂ����΁@���A���܂�ł��Ȃ��悤�ɂ���d�g�݁B
	HitRandom				hitRandom;			// ����΂炯������d�g�݁B
	HitTuke					hitTuke;			// ����̐΂ɐϋɓI�Ƀc�P��悤�ɂ���d�g�݁B
	HitAte					hitAte;				// �A�^���ɐϋɓI�ɃA�e��悤�ɂ���d�g�݁B
	HitNobiSaver			hitNoviServer;		// ��������΂�ϋɓI�Ƀm�r��悤�ɂ���d�g�݁B
	HitGnugo12Random		hitGnugo12Random;	// Gnugo1.2���Q�l�ɂ��������_���B
	int score = 0;					// �ǂ�ł����̕]���l


	if (pBoard->ValueOf(node) == BLACK || pBoard->ValueOf(node) == WHITE) {
		// �΂�����Ȃ�
#ifdef CHECK_LOG
		core.PRT(_T("�΂�����B"));
		core.PRT(_T("\n"));
#endif
		flgAbort = 1;
		goto gt_EndMethod;
	} else if (pBoard->ValueOf(node) == WAKU) {
		// �g�Ȃ�
#ifdef CHECK_LOG
		core.PRT(_T("�g�B"));
		core.PRT(_T("\n"));
#endif
		flgAbort = 1;
		goto gt_EndMethod;
	} else if (node == pBoard->kouNode) {
		// �R�E�ɂȂ�ʒu�Ȃ�
#ifdef CHECK_LOG
		core.PRT(_T("�R�E�B "));
		core.PRT(_T("\n"));
#endif
		flgAbort = 1;
		goto gt_EndMethod;
	}

	int x, y;
	AbstractBoard::ConvertToXy(x, y, node);
	int libertyOfRen = pLibertyOfNodes->ValueOf(node);



	noHitMouth.Research(color, node, pBoard);		// ����̌��ɐ΂�ł����ޏ󋵂łȂ��������B


	Liberty liberties[4];// ��� �� �E�� �� ���� �� ����
	pBoard->ForeachArroundDirAndNodes(node, [&pBoard, &liberties](int iDir, int adjNode, bool& isBreak) {
		int adjColor = pBoard->ValueOf(adjNode);			// �㉺���E��(adjacent)�̐΂̐F
		liberties[iDir].Count(adjNode, adjColor, pBoard);	// �ׂ̐΁i�܂��͘A�j�̌ċz�_�@�̐��𐔂��܂��B
	});

	// �c�P�邩�ǂ�����]��
	int nTuke = hitTuke.Evaluate(invColor, node, liberties, pBoard);

	// �A�e�邩�ǂ�����]��
	int nAte = hitAte.Evaluate(core, color, node, pBoard, pLibertyOfNodes);

	if (noHitOwnEye.IsThis(color, node, liberties, pBoard)) {// �����̊�ɑł����ޏ󋵂�����
#ifdef CHECK_LOG
		core.PRT(_T("�����̊�ɑł����ނ̂�����B"));
		core.PRT(_T("\n"));
#endif
		flgAbort = 1;
		goto gt_EndMethod;
	}

	if (noHitSuicide.IsThis(core, color, node, liberties, pBoard)) {// ���E��ɂȂ�󋵂łȂ��������B
#ifdef CHECK_LOG
		core.PRT(_T("���E�������B"));
		core.PRT(_T("\n"));
#endif
		flgAbort = 1;
		goto gt_EndMethod;
	}

#ifdef EVAL_LOG
	core.PRT(_T("$(%d,%d) "), x, y);
	core.PRT(_T("LibRen=%d �X�R�A="), libertyOfRen);
#endif

	int nHitRandom = hitRandom.Evaluate(); // 0 �` 99 �̃����_���ȕ]���l��^����B

	//----------------------------------------
	// �����̊�𖄂߂�A���E���łA�̃`�F�b�N�I����ɂ��鏈��
	//----------------------------------------

	int nNoHitMouth = noHitMouth.Evaluate(noHitSuicide.flgCapture);

	noHitHasinoho.Research(node, pBoard);
	int nNoHitHasinoho = noHitHasinoho.Evaluate();

	// �m�r�邩�ǂ�����]��
	int nNobiSaver = hitNoviServer.Evaluate(core, color, node, pBoard, pLibertyOfNodes);

	// Gnugo1.2�݂����ɑł�����
	int nHitGnugo12Random = hitGnugo12Random.Evaluate(color,node,pBoard);

	//----------------------------------------
	// �W�v
	//----------------------------------------

	// �΂炵����
#ifdef EVAL_LOG
	core.PRT(_T("b%d,"), nHitRandom);
#endif
	score += nHitRandom;

	// �}�E�X�ɑł������Ȃ�
#ifdef EVAL_LOG
	core.PRT(_T("m%d,"), nNoHitMouth);
#endif
	score += nNoHitMouth;

	// �c�P����
#ifdef EVAL_LOG
	core.PRT(_T("t%d,"), nTuke);
#endif
	score += nTuke;

	// �A�e����
#ifdef EVAL_LOG
	core.PRT(_T("a%d,"), nAte);
#endif
	score += nAte;

	// �m�r����
#ifdef EVAL_LOG
	core.PRT(_T("n%d,"), nNobiSaver);
#endif
	score += nNobiSaver;

	// �[�̕��ɑł������Ȃ�
#ifdef EVAL_LOG
	core.PRT(_T("h%d,"), nNoHitHasinoho);
#endif
	score += nNoHitHasinoho;

	// Gnugo1.2�݂����ɑł�����
#ifdef EVAL_LOG
	core.PRT(_T("g%d,"), nHitGnugo12Random);
#endif
	score += nHitGnugo12Random;

#ifdef EVAL_LOG
	core.PRT(_T("[%d] \n"), score);
#endif

gt_EndMethod:
	return score;
}


