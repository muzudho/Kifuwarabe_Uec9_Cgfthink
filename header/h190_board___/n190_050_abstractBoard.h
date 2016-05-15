#pragma once


#define BOARD_MAX ((19+2)*256)	// 19�H�Ղ��ő�T�C�Y�Ƃ���


// ��Ղ�z�肵���A�g�t���̃e�[�u���ł��B
class AbstractBoard {
private:
	// �Տ�̐΂̐F�B
	int table[BOARD_MAX];

	// ��A�E�A���A���@�Ɉړ�����̂Ɏg�������l
	int dir4[4] = {
		-0x100,	// ��
		+0x001,	// �E
		+0x100,	// ��
		-0x001	// ��
	};// �I���W�i����cgfthink�ł͉E�A���A���A��̏��������B

	// ���H��
	int size;

public:
	// (x,y)��1�̍��W�ɕϊ�
	static int ConvertToNode(
		int x,
		int y
	);

	// (node)��(x,y)���W�ɕϊ�
	static void ConvertToXy(
		int& x,
		int& y,
		int node
	);

	AbstractBoard();
	~AbstractBoard();

	// �㑤�ɗאڂ��Ă���ʒu
	int NorthOf(int node);

	// �E���ɗאڂ��Ă���ʒu
	int EastOf(int node);

	// �����ɗאڂ��Ă���ʒu
	int SouthOf(int node);

	// �����ɗאڂ��Ă���ʒu
	int WestOf(int node);

	void	SetSize(int size);
	int		GetSize();

	// �Z���̒l
	void	SetValue(int node, int value);
	int		ValueOf(int node);


	// ��Ղ̘g��S�����B����p���玞�v���B
	// .cpp �ɖ{�̂������ƂȂ񂩃G���[���o���̂ŁA.h �ɏ����Ă���񂾂����i�O���O�j
	template<typename Func> void ForeachAllNodesOfWaku(Func func)
	{
		// ��Ӂi�Ō�̎�O�܂Łj
		{
			int y = 0;
			for (int x = 0; x < this->size + 2 - 1; x++)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}

		// �E�Ӂi�Ō�̎�O�܂Łj
		{
			int x = this->size + 2 - 1;
			for (int y = 0; y < this->size + 2 - 1; y++)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}

		// ���Ӂi�Ō�̎�O�܂Łj
		{
			int y = this->size + 2 - 1;
			for (int x = this->size + 2 - 1; 0 < x; x--)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}

		// ���Ӂi�Ō�̎�O�܂Łj
		{
			int x = 0;
			for (int y = this->size + 2 - 1; 0 < y; y--)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}
	}

	// �g���܂߂Č�Ղ�S�����B���ォ��E��ցA�[�ŉ��s���Ď��̍s�̐擪����B
	// .cpp �ɖ{�̂������ƂȂ񂩃G���[���o���̂ŁA.h �ɏ����Ă���񂾂����i�O���O�j
	template<typename Func> void ForeachAllNodesWithWaku(Func func)
	{
		for (int y = 0; y < this->size + 2; y++)
		{
			for (int x = 0; x < this->size + 2; x++)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}
	}

	// �g���܂߂Č�Ղ�S�����B���ォ��E��ցA�[�ŉ��s���Ď��̍s�̐擪����B
	// .cpp �ɖ{�̂������ƂȂ񂩃G���[���o���̂ŁA.h �ɏ����Ă���񂾂����i�O���O�j
	template<typename Func> void ForeachAllXyWithWaku(Func func)
	{
		for (int y = 0; y < this->size + 2; y++)
		{
			for (int x = 0; x < this->size + 2; x++)
			{
				bool isBreak = false;
				func(x, y, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}
	}

	// �g���܂߂Ȃ���Ղ�S�����B���ォ��E��ցA�[�ŉ��s���Ď��̍s�̐擪����B
	// .cpp �ɖ{�̂������ƂȂ񂩃G���[���o���̂ŁA.h �ɏ����Ă���񂾂����i�O���O�j
	template<typename Func> void ForeachAllNodesWithoutWaku(Func func)
	{
		for (int y = 1; y < this->size + 1; y++)
		{
			for (int x = 1; x < this->size + 1; x++)
			{
				int node = AbstractBoard::ConvertToNode(x, y);

				bool isBreak = false;
				func(node, isBreak);
				if (isBreak)
				{
					break;
				}
			}
		}
	}

	// �w��̃m�[�h�ɗאڂ����A�E�A���A���̃m�[�h�𑖍��B
	template<typename Func> void ForeachArroundNodes(int node, Func func)
	{
		for (int iDir = 0; iDir < 4; iDir++) {
			bool isBreak = false;
			func(node + this->dir4[iDir], isBreak);
			if (isBreak)
			{
				break;
			}
		}
	}

	// �w��̃m�[�h�ɗאڂ����A�E�A���A���̃m�[�h�𑖍��B
	template<typename Func> void ForeachArroundDirAndNodes(int node, Func func)
	{
		for (int iDir = 0; iDir < 4; iDir++) {
			bool isBreak = false;
			func(iDir, node + this->dir4[iDir], isBreak);
			if (isBreak)
			{
				break;
			}
		}
	}
};