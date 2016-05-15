#include <tchar.h> // Unicode�Ή��� _T() �֐����g�p���邽�߂ɁB
#include "../../header/h090_core____/n090_100_core.h"
#include "../../header/h190_board___/n190_150_liberty.h"
#include "../../header/h300_move____/n300_100_move.h"
#include "..\..\header\h675_hit_____\n675_150_hitAte.h"

int HitAte::Evaluate(Core core, int color, int node, Board* pBoard, LibertyOfNodes* pLibertyOfNodes)
{
	int goodScore	= 0;
	int badScore	= 0;

#ifndef RANDOM_MOVE_ONLY
#ifdef ENABLE_MOVE_ATTACK

	bool isBadMove	= false; // �ł��Ȃ������}�V�ȂƂ��B
	int opponent	= INVCLR(color);

	// ��E�����ɁA����̐΂��Ȃ����T���܂��B
	pBoard->ForeachArroundNodes(node, [&core,&pBoard,&pLibertyOfNodes,&goodScore, &badScore,&isBadMove, color, opponent](int adjNode, bool& isBreak) {
		int libertyOfRen = pLibertyOfNodes->ValueOf(adjNode);
		int x, y;
		AbstractBoard::ConvertToXy(x, y, adjNode);
		//core.PRT(_T("adj(%d,%d)LibRen=%d"), x, y, libertyOfRen);

		if (pBoard->ValueOf(adjNode) == opponent && libertyOfRen<4)
		{
			// ����̐΁i�܂��͘A�j�ŁA�ċz�_�� 3 �ӏ��ȉ��̕���I�т܂��B

			std::vector<int> openNodes = pBoard->GetOpenNodesOfStone(core, adjNode, libertyOfRen);
			//core.PRT(_T("�J%d"), openNodes.size());

			if (!openNodes.empty())
			{
				// ����̐΁i�A�ł͂Ȃ��j�̊J���Ă�������i�P�����`�R�����j������ꍇ�B
				int openSize = openNodes.size();

				if (openSize == 1)
				{
					//core.PRT(_T("Ate!"));

					// �A�^���@�̏�Ԃł��B
					if (goodScore < 120)
					{
						// ���̎w����Ɂ@����Ƃ������肪�Ȃ��悤�Ȃ�A�A�e�ɂ����܂��傤�B
						goodScore += 120;
					}
				}
				else {
					// �A�^���@�ł͂Ȃ��ꍇ�B

					// �킽���i�R���s���[�^�[�j���u�����Ƃ��ƁA����i�l�ԁj�ɒu���Ԃ��ꂽ�Ƃ���
					// �S�p�^�[���ɂ���

					// �z��̃C���f�b�N�X�� 0,1 ��A0,2 ��A 1,2 �ȂǁA�قȂ�y�A com,man �ɂȂ����
					// �S�Ăɂ��āB

					for (int me = 0; me < openSize; me++)
					{
						for (int you = 0; you < openSize; you++)
						{
							if (me != you)
							{
								// �ċz�_�̐���ׁB
								Liberty myLiberty;
								myLiberty.Count(openNodes[me], color, pBoard);

								if (0 < myLiberty.liberty)    // �Ó����`�F�b�N
								{
									// �΂������ɒu���܂��B
									Move move;
									move.MoveOne(core, openNodes[me], color, pBoard);

									Liberty yourLiberty;
									yourLiberty.Count(openNodes[you], opponent, pBoard);

									if (
										1 == myLiberty.liberty  // �אڂ��鎄�i�R���s���[�^�[�j���́i�A�܂��́j�΂̌ċz�_�͂P�B
										&&
										0 < yourLiberty.liberty   // �אڂ��邠�Ȃ��i�l�ԁj���́i�A�܂��́j�΂̌ċz�_�͂P�ȏ�B
									)
									{
										// �l�ԑ��̌ċz�_�̕����A�R���s���[�^�[���Ɠ����A���邢�͑����̂ŁA
										// �ʒu a �ɒu�����l�Ȃ��B
										//score += 0;
										isBadMove = true;
									}
									else
									{
										// �R���s���[�^�[���u��������A
										// �l�Ԃ��u����ɁA�ċz�_�������A�܂������肪�Ȃ��ꍇ�A�u�����l����B
										goodScore += 120 - 20 * yourLiberty.liberty;
									}

									// �΂�u���O�̏�Ԃɖ߂��܂��B
									move.UndoOnce(core, pBoard);
								}
							}
						}
					}
					// 

				}
			}
		}

		//core.PRT(_T(";"));
	});

	if (badScore < 1 && isBadMove)
	{
		// �ł���ׂāA�ł��Ȃ������}�V�Ɣ��f���ꂽ�Ƃ��B
		badScore -= 120;
	}

	//----------------------------------------
	// �����ڂɔ{�����|���܂��B
	//----------------------------------------
	goodScore	*= 80 / 10;
	badScore	*= 120 / 10;

#endif
#endif

	return goodScore + badScore;
}
