#ifndef __SUDO_H__
#define __SUDO_H__

const int MAX_SUDO_NUM = 9;	//数独格子数量 x*x

int wrand(unsigned int max);

class SuDoKo
{
public:
	SuDoKo();
	~SuDoKo();
	void ResetData();
	void NewGame(int grade, int index, int digerNum);
	void initAnswer();
	void digerSudo(int num);
	void OutToFile();
private:
	void initData();
	void initSudoData(int curIndex, bool isSuc);
	bool checkRightNum(int num);
	bool checkRightNum(int num, int x, int y);


private:
	bool isAnswerInit = false;
	int m_id = 0;
	int sudo_init[MAX_SUDO_NUM][MAX_SUDO_NUM] = { 0 };
	int sudo_answer[MAX_SUDO_NUM][MAX_SUDO_NUM] = { 0 };	//最终答案
	int sudo_game[MAX_SUDO_NUM][MAX_SUDO_NUM] = { 0 };		//游戏初始数据
};
#endif
