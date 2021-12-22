#include "LogicServer.h"
#include "call.h"

void NewGame(int grade, int index, int digerNum)
{
	//printf("CallBack");
	LogicServer pLogicServer;
	pLogicServer.StartServer();
	pLogicServer.NewSudoGame(grade, index, digerNum);
}
