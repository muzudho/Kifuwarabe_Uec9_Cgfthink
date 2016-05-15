#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h190_board___/n190_150_liberty.h"
#include "../../header/h190_board___/n190_200_libertyOfNodes.h"

LibertyOfNodes::LibertyOfNodes()
{
}

LibertyOfNodes::~LibertyOfNodes()
{
}

void LibertyOfNodes::Initialize( Board* pBoard)
{
	this->SetSize( pBoard->GetSize());

	// �g�� 0 �ɏ������B
	this->ForeachAllNodesOfWaku([this](int node, bool& isBreak) {
		// �ċz�_�̐����o���Ă�����Ղł��B
		this->SetValue( node, 0);
	});

	pBoard->ForeachAllNodesWithoutWaku([this,&pBoard](int node, bool& isBreak) {
		Liberty liberty;
		liberty.Count(node, pBoard->ValueOf(node), pBoard);

		// �ċz�_�̐����o���Ă�����Ղł��B
		this->SetValue( node, liberty.liberty);
	});
}
