#pragma once
#include<iostream>
#include<string>
#include "Functionimpl.h"
using namespace std;
struct struser {      /*定义一个结构体用来储存用户相关变量，其中包括账号和密码*/
	string number;
	string password;
};
struct book {         /*定义一个结构体用于储存书籍相关信息，包括书名编号书籍状态*/
	string bookname;
	string author;
	int booknumber;
	bool bookstate;
};
int d[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
struct date {
	int year;
	int month;
	int day;
};
struct borrowbookrecord {
	string bookname;
	string author;
	int booknumber;
	string number;
	date startday;
	date deadline;
};
class user {                                    /*基类user*/
public:
	user(string number, string password);       /*更新账号密码，返回账号密码，登录，注册*/
	void renew(string number, string password);
	string getnumber() { return number; }
	string getpassword() { return password; }
	virtual bool Signin() =0;
	virtual bool Register()=0;
	virtual void menu() = 0;
	void searchbook();                         /*搜索书*/
	void returntomenu();
private:                                      /*账号密码*/
	string number;
	string password;
};
class admin:public user{                    /*派生类admin*/
public:                                      /*有添加图书，删除图书，借书，还书，损坏*/
	admin(string number, string password); /*丢失报备功能*/
	bool Signin();
	bool Register();
	void addbook();
	void deletebook();
	void borrowbook();
	void returnbook();
	void brokenbook();
	void menu();
	void select();
private:

};
class student :public user {              /*派生类student*/
public:
	student(string number, string password);
	bool Signin();
	bool Register();
	void findrecord();
	void bookrenew();
	void menu();
	void select();
};