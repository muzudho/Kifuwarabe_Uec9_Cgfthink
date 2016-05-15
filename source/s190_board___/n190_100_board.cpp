#include <vector>
#include "../../header/h090_core____/n090_100_core.h"
#include "../../header/h190_board___/n190_100_board.h"




void Board::Initialize(int initBoard[])
{
	// ���݋ǖʂ������Ə����Ֆʂ�����
	for (int iNode = 0; iNode < BOARD_MAX; iNode++) {
		this->SetValue(iNode, initBoard[iNode]);	// �����Ֆʂ��R�s�[
	}
}



Board::Board()
{
	this->kouNodeForUndo = 0;
	this->moveNodeForUndo = 0;
	this->kouNode = 0;		// �R�E�ɂȂ�ʒu�B

	this->hama[0] = 0;	
	this->hama[BLACK] = 0;	// ������΂̐�
	this->hama[WHITE] = 0;
}

Board::~Board()
{
}

std::vector<int> Board::GetOpenNodesOfStone(Core core, int node, int size123)
{
	std::vector<int> openNodes;

	// �㑤 �� �E�� �� ���� �� ����
	this->ForeachArroundNodes(node,[this,&core,size123,&openNodes](int adjNode, bool& isBreak) {

		if (this->ValueOf(adjNode) == EMPTY && adjNode != this->kouNode)
		{
			// �󂫃X�y�[�X�ŁA�R�E�ɂȂ�Ȃ��ʒu�Ȃ�B
			openNodes.push_back(adjNode);

			if (openNodes.size() == size123) {
				// �v�Z��ł��؂�B
				isBreak = true;
				goto gt_Next;
			}
		}

	gt_Next:
		;
	});

gt_EndMethod:
	return openNodes;
}




void Board::DeleteRenStones(
	int tNode,
	int color
	)
{
	// �w�肵���ʒu�̐΂��폜�B
	this->SetValue(tNode, 0);

	// �S�����̐΂ɂ������������s���܂��B
	this->ForeachArroundNodes(tNode, [this,color]( int adjNode,	bool& isBreak) {
		if (this->ValueOf(adjNode) == color) {
			this->DeleteRenStones(adjNode, color);
		}
	});
}

