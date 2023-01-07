#pragma once
#include<iostream>
#include "Functionimpl.h"
#include "classes.h"
using namespace std;
void mainmenu();                          /*���˵�*/
void slect1();                            /*����ѡ���û�*/

void menu2();                             /*����Աѡ���¼��ע��Ĳ˵�*/
void slect2();                          /*����Ա����ѡ��*/

void menu3();                            /*ѧ��ѡ���¼��ע��Ĳ˵�*/
void slect3();                           /*ѧ������ѡ��*/


void signin(user* p);                    /*ѧ���͹���Ա��¼�������麯��ʵ���˶�̬*/
void registe(user* p);                   /*ѧ���͹���Աע�ᣬ�����麯��ʵ���˶�̬*/
user* admincreat();                       /*����һ��admin���󣬷��ض���ָ��*/
user* studentcreat();                      /*����һ��student���󣬷��ض���ָ��*/





void mainmenu() {
	cout << "\t\t==========��ӭ����ͼ��ݹ���ϵͳ==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=          ***��ѡ���û�����***          =" << endl;
	cout << "\t\t= 1.����Ա                               =" << endl;
	cout << "\t\t= 2.ѧ��                                 =" << endl;
	cout << "\t\t==========================================" << endl;
	slect1();
}
void slect1() {
	int a;
	cin>>a;
	if (a == 1) { menu2(); }
	else if (a == 2) { menu3(); }
	else {
		cout << "����������������룺" << endl;
		slect1();
	}
}



void menu2() {
	cout << "\t\t==========��ӭ����ͼ��ݹ���ϵͳ==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t= 1.��¼                                 =" << endl;
	cout << "\t\t= 2.ע��                                 =" << endl;
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
		cout << "����������������룺" << endl;
		slect2();
	}
}



void menu3() {
	cout << "\t\t==========��ӭ����ͼ��ݹ���ϵͳ==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t= 1.��¼                                 =" << endl;
	cout << "\t\t= 2.ע��                                 =" << endl;
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
		cout << "����������������룺" << endl;
		slect3();
	}
}





user*  admincreat() {
	cout << "�������˺�" << endl;
	string num;
	cin >> num;
	cout << "����������" << endl;
	string pass;
	cin >> pass;
	user* p = new admin(num, pass);
	return p;
}

user* studentcreat() {
	cout << "�������˺�" << endl;
	string num;
	cin >> num;
	cout << "����������" << endl;
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
		cout << "���������Ҫ���µ�¼��" << endl;
		cout << "�������˺�" << endl;
		string num;
		cin >> num;
		cout << "����������" << endl;
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