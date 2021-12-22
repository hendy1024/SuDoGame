#include "LogicServer.h"
#include "TestMySql.h"
#include "Sudo.h"
LogicServer*		g_LogicServer;//ȫ���߼�������
TestMySql*		g_TestMysql;//���ݿ�
SuDoKo*			g_SudoKo;//����

LogicServer::LogicServer()
{
	g_LogicServer = this;
	g_TestMysql = &m_Mysql;
	g_SudoKo = &m_SudoKo;
}

LogicServer::~LogicServer()
{
	g_LogicServer = nullptr;
	g_TestMysql = nullptr;
	g_SudoKo = nullptr;
}

void LogicServer::StartServer()
{
	if (m_isStart)
	{
		return;
	}

	m_isStart = true;

	StartMysql();
}

void LogicServer::StartMysql()
{
	const char* host = "119.23.53.16";
	const char* user = "root";
	const char* port = "3306";
	const char* passwd = "root";
	const char* dbname = "suduko";
	const char* charset = "GBK";//֧������
	g_TestMysql = new TestMySql;
	if (g_TestMysql->connectMySql(host, port, dbname, user, passwd, charset))
	{
		printf("���ӳɹ�\n");
	}
}

void LogicServer::InsertSql(char *sql)
{
	g_TestMysql->InsertOperateSql(sql);
}

void LogicServer::NewSudoGame(int grade, int index, int digerNum)
{
	g_SudoKo->NewGame(grade, index, digerNum);
}

void LogicServer::Update()
{
	if (0)
	{
		g_SudoKo->NewGame(1, 1, 50);
	}
	g_TestMysql->OpreateSql();
}
