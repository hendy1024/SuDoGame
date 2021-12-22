#ifndef __TESTMYSQL_H__
#define __TESTMYSQL_H__
#include <stdio.h>
#include <string.h>
//#include <afxsock.h>
#include <mysql/mysql.h>
//#include "list.h"
//#include <iostream.h>
//using namespace std;
class TestMySql
{
public:
	TestMySql();
	~TestMySql();

	//�������ݿ�
	int connectMySql(const char *host, const char * port, const char * Db, const char * user, const char* passwd, const char * charset);
	//�������ݿ�
	int OpreateData(const char* SQL);
	//�������
	int InsertData(char* SQL, char* Msg);
	//ɾ������
	int DeleteData(const char* SQL);
	//��������
	//string FindData(char* SQL, int Cnum, char* Msg);
	//��������
	int UpdateData(char* SQL, char* Msg);

	//�ر����ݿ�
	void closeMySql();

	bool InsertOperateSql(char *sql);
	void OpreateSql();
	bool CanOperate() { return canOperate; }
private:
	MYSQL mysql;

//	list<std::string> sqllist;
	bool canOperate = false;
};
#endif

