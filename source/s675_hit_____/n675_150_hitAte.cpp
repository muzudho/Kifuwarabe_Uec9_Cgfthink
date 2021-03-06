#include <tchar.h> // Unicode対応の _T() 関数を使用するために。
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

	bool isBadMove	= false; // 打たない方がマシなとき。
	int opponent	= INVCLR(color);

	// 上右下左に、相手の石がないか探します。
	pBoard->ForeachArroundNodes(node, [&core,&pBoard,&pLibertyOfNodes,&goodScore, &badScore,&isBadMove, color, opponent](int adjNode, bool& isBreak) {
		int libertyOfRen = pLibertyOfNodes->ValueOf(adjNode);
		int x, y;
		AbstractBoard::ConvertToXy(x, y, adjNode);
		//core.PRT(_T("adj(%d,%d)LibRen=%d"), x, y, libertyOfRen);

		if (pBoard->ValueOf(adjNode) == opponent && libertyOfRen<4)
		{
			// 相手の石（または連）で、呼吸点が 3 箇所以下の物を選びます。

			std::vector<int> openNodes = pBoard->GetOpenNodesOfStone(core, adjNode, libertyOfRen);
			//core.PRT(_T("開%d"), openNodes.size());

			if (!openNodes.empty())
			{
				// 相手の石（連ではなく）の開いている方向（１方向〜３方向）がある場合。
				int openSize = openNodes.size();

				if (openSize == 1)
				{
					//core.PRT(_T("Ate!"));

					// アタリ　の状態です。
					if (goodScore < 120)
					{
						// 他の指し手に　これといった手がないようなら、アテにいきましょう。
						goodScore += 120;
					}
				}
				else {
					// アタリ　ではない場合。

					// わたし（コンピューター）が置いたときと、相手（人間）に置き返されたときの
					// 全パターンについて

					// 配列のインデックスが 0,1 や、0,2 や、 1,2 など、異なるペア com,man になるもの
					// 全てについて。

					for (int me = 0; me < openSize; me++)
					{
						for (int you = 0; you < openSize; you++)
						{
							if (me != you)
							{
								// 呼吸点の数比べ。
								Liberty myLiberty;
								myLiberty.Count(openNodes[me], color, pBoard);

								if (0 < myLiberty.liberty)    // 妥当性チェック
								{
									// 石を試しに置きます。
									Move move;
									move.MoveOne(core, openNodes[me], color, pBoard);

									Liberty yourLiberty;
									yourLiberty.Count(openNodes[you], opponent, pBoard);

									if (
										1 == myLiberty.liberty  // 隣接する私（コンピューター）側の（連または）石の呼吸点は１個。
										&&
										0 < yourLiberty.liberty   // 隣接するあなた（人間）側の（連または）石の呼吸点は１個以上。
									)
									{
										// 人間側の呼吸点の方が、コンピューター側と同じ、あるいは多いので、
										// 位置 a に置く価値なし。
										//score += 0;
										isBadMove = true;
									}
									else
									{
										// コンピューターが置いた手より、
										// 人間が置く手に、呼吸点が同じ、また多い手がない場合、置く価値あり。
										goodScore += 120 - 20 * yourLiberty.liberty;
									}

									// 石を置く前の状態に戻します。
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
		// 打ち比べて、打たない方がマシと判断されたとき。
		badScore -= 120;
	}

	//----------------------------------------
	// 効き目に倍率を掛けます。
	//----------------------------------------
	goodScore	*= 80 / 10;
	badScore	*= 120 / 10;

#endif
#endif

	return goodScore + badScore;
}
