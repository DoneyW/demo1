#pragma once
#include<iostream>
#include<string>
#include "Functionimpl.h"
using namespace std;
struct struser {      /*����һ���ṹ�����������û���ر��������а����˺ź�����*/
	string number;
	string password;
};
struct book {         /*����һ���ṹ�����ڴ����鼮�����Ϣ��������������鼮״̬*/
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
class user {                                    /*����user*/
public:
	user(string number, string password);       /*�����˺����룬�����˺����룬��¼��ע��*/
	void renew(string number, string password);
	string getnumber() { return number; }
	string getpassword() { return password; }
	virtual bool Signin() =0;
	virtual bool Register()=0;
	virtual void menu() = 0;
	void searchbook();                         /*������*/
	void returntomenu();
private:                                      /*�˺�����*/
	string number;
	string password;
};
class admin:public user{                    /*������admin*/
public:                                      /*�����ͼ�飬ɾ��ͼ�飬���飬���飬��*/
	admin(string number, string password); /*��ʧ��������*/
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
class student :public user {              /*������student*/
public:
	student(string number, string password);
	bool Signin();
	bool Register();
	void findrecord();
	void bookrenew();
	void menu();
	void select();
};