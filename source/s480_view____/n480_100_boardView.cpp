#include <tchar.h>		// Unicode�Ή��� _T() �֐����g�p���邽�߂ɁB
#include "../../header/h090_core____/n090_100_core.h"
#include "../../header/h480_view____/n480_100_boardView.h"


void BoardView::PrintBoard(Core core, Board* pBoard)
{
	_TCHAR* str[4] = {
		_T("�E"),	// ��
		_T("��"),	// ����
		_T("��"),	// ����
		_T("�{")		// �g
	};

	pBoard->ForeachAllXyWithWaku([&pBoard,&core,&str](int x,int y, bool& isBreak) {
		int node = Board::ConvertToNode(x, y);
		core.PRT(_T("%s"), str[pBoard->ValueOf(node)]);
		if (x == pBoard->GetSize() + 1) {
			core.PRT(_T("\n"));
		}
	});
}

