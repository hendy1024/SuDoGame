package main

/*
#cgo LDFLAGS: -L . -lsudo -lstdc++ -ldl -L /usr/lib64/mysql -lmysqlclient
#cgo CXXFLAGS: -std=c++11
#cgo CFLAGS: -I ./
#include "call.h"
*/
import "C"
func main(){
        C.NewGame(1, 1, 40);
}
