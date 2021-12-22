#include "TestMySql.h"
#include <stdio.h>
TestMySql::TestMySql()
{

}

TestMySql::~TestMySql()
{

}

void TestMySql::OpreateSql()
{
/*	if (sqllist.empty())
	{
		return;
	}

	auto sql = sqllist.front();
	if (sql.empty())
	{
		return;
	}
	sqllist.pop_front();
	canOperate = false;
	OpreateData(sql.c_str());
	canOperate = true;*/
}

bool TestMySql::InsertOperateSql(char* sql)
{
	/*string s = sql;
	if (s.empty())
	{
		return false;
	}

	sqllist.push_back(s);*/
	OpreateData(sql);
	return true;
}

int TestMySql::connectMySql(const char *host, const char * port, const char * Db, const char * user, const char* passwd, const char * charset)
{
	if (mysql_init(&mysql) == NULL)
	{

		printf("init mysql error \n");
		return 0;
	}

	if (mysql_real_connect(&mysql, host, user, passwd, Db, 0, NULL, 0) == NULL)
	{
		//AfxMessageBox(mysql_error(&mysql));
		printf("fail to connect mysql \n");
		return 0;
	}

	if (mysql_set_character_set(&mysql, "GBK") != 0)
	{
		return 0;
	}

	return 1;
}

int TestMySql::OpreateData(const char* SQL)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) == 0)
	{
		printf("OpreateData Suc");
		return 1;
	}
	printf("opreate mysql error /n");
	return 0;
}

int TestMySql::InsertData(char* SQL, char* Msg)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		return 1;
	}
	printf("insert mysql data error /n");
	return 0;
}

int TestMySql::DeleteData(const char* SQL)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) == 0)
	{
		return 1;
	}
	printf("delete mysql data error \n");
	return 0;
}
/*
string TestMySql::FindData(char* SQL, int Cnum, char* Msg)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf(sql, SQL);
	
	int rnum = 0;
	char rg = 0x06;
	char cg = { 0x05 };

	if (mysql_query(&mysql, sql) != 0)
	{
		return "";
	}


}

int TestMySql::UpdateData(char* SQL, char* Msg)
{
	char sql[2048];
	sprintf(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		return 1;
	}
	return 0;
}*/

void TestMySql::closeMySql()
{
	mysql_close(&mysql);
}
