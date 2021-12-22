#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "SuDoWrapper.h"
#include "TestMySql.h"
#include <iostream>

#include "LogicServer.h"

using namespace std;
int main(void)
{

        LogicServer *pLogicServer = new LogicServer();
        pLogicServer->StartServer();

        //const char* sql = "DELETE FROM sd_suduko_lib WHERE sd_index = 9";
        //mysql->OpreateData(sql);
        while (1)
        {
                pLogicServer->Update();
        }
        //struct tagSudo * pSudo;
        //pSudo = GetInstance();
        //InitAnswer(pSudo);
        //DigerNum(pSudo, 50);
        //OutToFile(pSudo);
        //ReleaseInstance(&pSudo);
        //assert(pSudo == 0);
        delete pLogicServer;
        return 0;
}
