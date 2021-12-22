#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "time.h"
#include "LogicServer.h"
#include "Sudo.h"
using namespace std;

static unsigned int state[16] = {
	0x8C12D566, 0x00C2793E, 0x5016EECF, 0x234869FA,
	0x6E4C8852, 0x32574386, 0x3573DC34, 0x7E4C00F0,
	0xC830516B, 0x085437E9, 0x32478EAC, 0xDEFCDCD0,
	0xFE09BBC2, 0x34EA087D, 0x112F367C, 0x0324EFAA
};

void winitseed(unsigned int seed)
{
	int i;

	if (!seed) seed = (unsigned int)time(NULL);

	for (i = 0; i < 16; ++i)
	{
		state[i] ^= seed;
	}
}

static unsigned int WELLRNG512()
{
	static unsigned int index = 0;
	unsigned int a, b, c, d;
	a = state[index];
	c = state[(index + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = state[(index + 9) & 15];
	c ^= (c >> 11);
	a = state[index] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	index = (index + 15) & 15;
	a = state[index];
	state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
	return state[index];
}

int wrand(unsigned int max)
{
	return (max == 0 ? 0 : (WELLRNG512() % max));
}

SuDoKo::~SuDoKo() {

}

SuDoKo::SuDoKo() {
	time_t rawtime;
	time(&rawtime);
	winitseed((unsigned int)rawtime);
}

void SuDoKo::ResetData()
{
	isAnswerInit = false;
	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		for (int j = 0; j < MAX_SUDO_NUM; ++j)
		{
			sudo_init[i][j] = 0;
			sudo_answer[i][j] = 0;
			sudo_game[i][j] = 0;
		}
	}
}

void SuDoKo::initData()
{
	ResetData();
	int t = 0;
	while (t < 15)
	{
		int x = wrand(MAX_SUDO_NUM);
		int y = wrand(MAX_SUDO_NUM);
		int realNum = wrand(MAX_SUDO_NUM + 1);
		if (sudo_init[x][y] == 0 && checkRightNum(realNum, x, y))
		{
			sudo_init[x][y] = realNum;
			++t;
		}
	}
}

void SuDoKo::NewGame(int grade, int index, int digerNum)
{
	initData();
	initAnswer();
	digerSudo(digerNum);
	time_t rawtime;

	time(&rawtime);  //靠靠靠
	stringstream sb;
	sb << "INSERT INTO sd_suduko_lib (id, sd_grade, sd_index, sd_arr_question, sd_answer) VALUES (";
	sb << rawtime << ", ";
	sb << grade << ", ";
	sb << index << ", '";
	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		for (int j = 0; j < MAX_SUDO_NUM; ++j)
		{
			sb << sudo_answer[i][j];
		}
		if (i != MAX_SUDO_NUM - 1)
		{
			sb << ", ";
		}
	}
	sb << "', '";

	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		for (int j = 0; j < MAX_SUDO_NUM; ++j)
		{
			sb << sudo_game[i][j];
		}
		if (i != MAX_SUDO_NUM - 1)
		{
			sb << ", ";
		}
	}
	sb << "');";
	char sql[2048];
	sprintf(sql, sb.str().c_str());
/*
	string s;
	char sql[2048];
	sprintf_s(sql, "INSERT INTO sd_suduko_lib (id, sd_grade, sd_index, sd_arr_question, sd_answer) VALUES (");
	sprintf_s(sql, "%d, ", m_id);
	sprintf_s(sql, "%d, ", grade);
	sprintf_s(sql, "%d, ", index);

	sprintf_s(sql, ", ");
	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		for (int j = 0; j < MAX_SUDO_NUM; ++j)
		{
			sprintf_s(sql, "%d", sudo_answer[i][j]);
		}
	}
	sprintf_s(sql, ", ");

	sprintf_s(sql, "'");
	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		for (int j = 0; j < MAX_SUDO_NUM; ++j)
		{
			sprintf_s(sql, "%d", sudo_game[i][j]);
		}
	}*/
	g_LogicServer->InsertSql(sql);
}

void SuDoKo::initAnswer()
{
	initSudoData(0, false);
}

void SuDoKo::digerSudo(int num)
{
	int temp_data[MAX_SUDO_NUM][MAX_SUDO_NUM] = { 0 };
	memcpy(temp_data, sudo_answer, sizeof(temp_data));
	int digerNum = num;
	while (digerNum > 0)
	{
		int x = wrand(MAX_SUDO_NUM);;
		int y = wrand(MAX_SUDO_NUM);;
		if (temp_data[x][y] != 0)
		{
			temp_data[x][y] = 0;
			--digerNum;
		}
	}

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			sudo_game[i][j] = temp_data[i][j];
		}
	}
}

bool SuDoKo::checkRightNum(int num)
{
	return num > 0 && num <= MAX_SUDO_NUM;
}

bool SuDoKo::checkRightNum(int num, int x, int y)
{
	if (!checkRightNum(x + 1) || !checkRightNum(y + 1) || !checkRightNum(num))
	{
		return false;
	}

	for (int i = 0; i < MAX_SUDO_NUM; ++i)
	{
		if (sudo_init[i][y] == num || sudo_init[x][i] == num)
		{
			return false;
		}
	}

	int sqrt_num = (int)sqrt(MAX_SUDO_NUM);
	int xStartIndex = (x / sqrt_num)*sqrt_num;
	int yStartIndex = (y / sqrt_num)*sqrt_num;
	for (int i = xStartIndex; i < xStartIndex + sqrt_num; ++i)
	{
		for (int j = yStartIndex; j < yStartIndex + sqrt_num; ++j)
		{
			if (sudo_init[i][j] == num)
			{
				return false;
			}
		}
	}

	return true;
}

void SuDoKo::initSudoData(int curIndex, bool isSuc)
{
	if (curIndex < MAX_SUDO_NUM * MAX_SUDO_NUM)
	{
		if (isAnswerInit && !isSuc)
		{
			return;
		}

		int x = curIndex / MAX_SUDO_NUM;
		int y = curIndex % MAX_SUDO_NUM;
		if (sudo_init[x][y] == 0)
		{
			for (int i = 1; i < 10; ++i)
			{
				if (checkRightNum(i, x, y))
				{
					sudo_init[x][y] = i;
					initSudoData(curIndex + 1, isSuc);
					sudo_init[x][y] = 0;
				}
			}
		}
		else
		{
			initSudoData(curIndex + 1, isSuc);
		}
	}
	else
	{
		if (!isSuc)
		{
			isAnswerInit = true;
			for (int i = 0; i < 9; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					sudo_answer[i][j] = sudo_init[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < 9; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					if (sudo_answer[i][j] != sudo_init[i][j])
					{
						sudo_game[i][j] = sudo_answer[i][j];
						i = 10;
						j = 10;
						break;
					}
				}
			}
		}
	}
}

void SuDoKo::OutToFile()
{
	time_t rawtime;

	time(&rawtime);  //结果是时间戳
	string ss;
	int time_str = (int)rawtime;
	char p[256];
	sprintf(p, "%d%s", time_str, ".txt");
	ofstream newFile(p, ios::out);
	if (!newFile)
	{
		cout << "error opening out file." << endl;
		return;
	}

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			newFile << sudo_answer[i][j];
		}
	}
	newFile << endl;

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			newFile << sudo_game[i][j];
		}
	}
	newFile << endl;

	newFile.close();
}
