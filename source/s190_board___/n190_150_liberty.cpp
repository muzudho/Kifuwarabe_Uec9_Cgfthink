#include "../../header/h190_board___/n190_150_liberty.h"




Liberty::Liberty()
{
	this->liberty = 0;
	this->renIshi = 0;
};




void Liberty::Count(int node, int color, Board* pBoard)
{

	// ��ɑł����܂Ȃ����A���̒��ɑł����܂Ȃ����A�̏����̂��Ƃ�
	if (color == EMPTY || color == WAKU) {
		// ����ۂ��A�g�Ȃ�B
		//PRT(_T("����ۂ��A�g�B \n"));
		goto gt_EndMethod;
	}

	int i;

	this->liberty = 0;
	this->renIshi = 0;
	for (i = 0; i < BOARD_MAX; i++) {
		this->checkedBoard[i] = 0;
	}

	this->CountElement(node, color, pBoard);
	//this->CountElement(node, pBoard->ValueOf(node), pBoard);

gt_EndMethod:
	return;
}




void Liberty::CountElement(int tNode, int color, Board* pBoard)
{

	this->checkedBoard[tNode] = 1;					// ���̐΂͌����ς�	
	this->renIshi++;								// �ċz�_�𐔂��Ă���i�P�܂��͘A�́j
													// �΂̐�

	pBoard->ForeachArroundNodes(tNode, [this, color,&pBoard](int adjNode, bool& isBreak) {
		if (this->checkedBoard[adjNode]) {
			goto gt_Next;
		}
		if (pBoard->ValueOf(adjNode) == 0) {				// ��_
			this->checkedBoard[adjNode] = 1;			// ���̋�_�͌����ς݂Ƃ���
			this->liberty++;							// ���o�e�B�̐�
		}
		if (pBoard->ValueOf(adjNode) == color) {
			this->CountElement(adjNode, color, pBoard);	// ���T���̎����̐�
		}
	gt_Next:
		;
	});
}
