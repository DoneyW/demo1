#pragma once
#include<iostream>
#include "Functionimpl.h"
#include "classes.h"
using namespace std;
void mainmenu();                          /*主菜单*/
void slect1();                            /*用于选择用户*/

void menu2();                             /*管理员选择登录或注册的菜单*/
void slect2();                          /*管理员输入选择*/

void menu3();                            /*学生选择登录或注册的菜单*/
void slect3();                           /*学生输入选择*/


void signin(user* p);                    /*学生和管理员登录，利用虚函数实现了多态*/
void registe(user* p);                   /*学生和管理员注册，利用虚函数实现了多态*/
user* admincreat();                       /*创建一个admin对象，反回对象指针*/
user* studentcreat();                      /*创建一个student对象，反回对象指针*/





void mainmenu() {
	cout << "\t\t==========欢迎进入图书馆管理系统==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=          ***请选择用户类型***          =" << endl;
	cout << "\t\t= 1.管理员                               =" << endl;
	cout << "\t\t= 2.学生                                 =" << endl;
	cout << "\t\t==========================================" << endl;
	slect1();
}
void slect1() {
	int a;
	cin>>a;
	if (a == 1) { menu2(); }
	else if (a == 2) { menu3(); }
	else {
		cout << "输入错误，请重新输入：" << endl;
		slect1();
	}
}



void menu2() {
	cout << "\t\t==========欢迎进入图书馆管理系统==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t= 1.登录                                 =" << endl;
	cout << "\t\t= 2.注册                                 =" << endl;
	cout << "\t\t==========================================" << endl;
	slect2();
}
void slect2() {
	int a;
	cin >> a;
	user* p = admincreat();
	if (a == 1) {
		signin(p);
	}
	else if (a == 2) {
		registe(p);
	}
	else {
		cout << "输入错误，请重新输入：" << endl;
		slect2();
	}
}



void menu3() {
	cout << "\t\t==========欢迎进入图书馆管理系统==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t= 1.登录                                 =" << endl;
	cout << "\t\t= 2.注册                                 =" << endl;
	cout << "\t\t==========================================" << endl;
	slect3();
}
void slect3() {
	int a;
	cin >> a;
	user* p = studentcreat();
	if (a == 1) {
		signin(p);
	}
	else if (a == 2) {
		registe(p);
	}
	else {
		cout << "输入错误，请重新输入：" << endl;
		slect3();
	}
}





user*  admincreat() {
	cout << "请输入账号" << endl;
	string num;
	cin >> num;
	cout << "请输入密码" << endl;
	string pass;
	cin >> pass;
	user* p = new admin(num, pass);
	return p;
}

user* studentcreat() {
	cout << "请输入账号" << endl;
	string num;
	cin >> num;
	cout << "请输入密码" << endl;
	string pass;
	cin >> pass;
	user* p = new student(num, pass);
	return p;
}


void signin(user* p) {
	if (p->Signin()) {
		p->menu();
	}
	else {
		cout << "密码错误需要重新登录！" << endl;
		cout << "请输入账号" << endl;
		string num;
		cin >> num;
		cout << "请输入密码" << endl;
		string pass;
		cin >> pass;
		p->renew(num, pass);
		signin(p);
	}
}

void registe(user* p) {
	if (p->Register()) {
		p->menu();
	}
}