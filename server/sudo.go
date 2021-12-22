package main

/*
#cgo LDFLAGS: -L . -lsudo -lstdc++ -ldl -L /usr/lib64/mysql -lmysqlclient
#cgo CXXFLAGS: -std=c++11
#cgo CFLAGS: -I ./
#include "call.h"
*/
import "C"
import (
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
)

type Request struct {
	Grade int `json:"grade"`
	Index int `json:"index"`
	DigerNum int `json:"diger_num"`
}

type SudoError struct {
	Code int `json:"code"`
	Message string `json:"message"`
}

func (s *SudoError) String() string {
	return s.Message
}

func postSudo(req *http.Request) *SudoError {
	if req.Method != http.MethodPost {
		log.Printf("method not allowed, %s", req.Method)
		return &SudoError{Code: http.StatusMethodNotAllowed, Message: "MethodNotAllowed"}
	}
	body, err := ioutil.ReadAll(req.Body)
	if err != nil {
		log.Printf("read body err, %v", err)
		return &SudoError{Code: http.StatusBadRequest, Message: err.Error()}
	}
	log.Println("json:", string(body))

	var r Request
	if err := json.Unmarshal(body, &r); err != nil {
		log.Printf("Unmarshal err, %v", err)
		return &SudoError{Code: http.StatusBadRequest, Message: err.Error()}
	}
	if r.Grade == 0 || r.Index == 0 || r.DigerNum == 0 {
		return &SudoError{Code: http.StatusBadRequest, Message: "ParamsInvalid"}
	}
	C.NewGame(C.int(r.Grade), C.int(r.Index), C.int(r.DigerNum))
	return &SudoError{Code: http.StatusOK, Message: "Success"}
}

func main() {
	http.HandleFunc("/sudo", func(w http.ResponseWriter, req *http.Request) {
		w.Header().Set("content-type", "application/json")
		err := postSudo(req)
		w.WriteHeader(err.Code)
		res, _ := json.Marshal(err)
		w.Write(res)
	})
	log.Println("start server ...")
	log.Fatal(http.ListenAndServe(":9527", nil))
}
