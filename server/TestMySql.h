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

	//连接数据库
	int connectMySql(const char *host, const char * port, const char * Db, const char * user, const char* passwd, const char * charset);
	//操作数据库
	int OpreateData(const char* SQL);
	//添加数据
	int InsertData(char* SQL, char* Msg);
	//删除数据
	int DeleteData(const char* SQL);
	//查找数据
	//string FindData(char* SQL, int Cnum, char* Msg);
	//更新数据
	int UpdateData(char* SQL, char* Msg);

	//关闭数据库
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

