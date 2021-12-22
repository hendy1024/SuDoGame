#ifndef __LOGIC_SERVER_H__
#define __LOGIC_SERVER_H__

#include "TestMySql.h"
#include "Sudo.h"

class LogicServer
{
public:
	LogicServer();
	~LogicServer();

	void StartServer();
	void Update();

	void InsertSql(char *sql);
	void NewSudoGame(int grade, int index, int digerNum);
private:
	void StartMysql();
private:

	bool m_isStart = false;
	TestMySql m_Mysql;
	SuDoKo m_SudoKo;
};

extern LogicServer*		g_LogicServer;//ȫ���߼�������
extern TestMySql*		g_TestMysql;//���ݿ�
extern SuDoKo*			g_SudoKo;//����

#endif
