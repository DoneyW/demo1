#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include "classes.h"
using namespace std;
vector<book> getbookvector(string adress);                  /*���ļ������ڻ�ȡ���е��鼮��Ϣ������һ��vector*/
bool slectbook(vector<book> &t,vector<book>::iterator &i);  /*����һ��vector ��һ������������λҪѡ����鼮*/
void writebook(string address, vector<book> a);             /*�����º���鼮��Ϣ��vectorд���ļ�*/
void coutbook(book a);                                      /*���ڴ�ӡ�鼮��Ϣ*/
void addborrowbookrecord(string num,book b);                /*��������Ϣ��׷��д�ķ�ʽд���ļ�*/
void writeborrowbookrecord(vector<borrowbookrecord> t);      /*�����º�Ľ�����Ϣд���ļ�*/
vector<borrowbookrecord> getborrowrecord(string address);    /*���ļ��ж�ȡ���н�����Ϣ������һ��vector*/
void Deletebook(int num);                                     /*ɾ���鼮��Ϣ*/
bool Deleteborrowbookrecord(int num);                         /*ɾ��������Ϣ*/
void coutborrowbookrecord(borrowbookrecord t);                    /*��ӡ���ļ�¼*/
void renewbookrecord(borrowbookrecord t);                     /*���ӽ���ʱ��*/
vector<borrowbookrecord> screenBorrowBookRecord(string name);
void datechange(date &day);
user::user(string number, string password) {          /*����һ��user����ʱ��ʼ���˺�����*/
	this->number = number;
	this->password = password;
}
void user::renew(string number, string password) {  /*�����˺�����*/
	this->number = number;
	this->password = password;
}
void user::searchbook() {                                     
	vector<book> t = getbookvector("book.txt");
	vector<book>::iterator i = t.begin();
	if (slectbook(t, i)) {                         /*�����飬����Ϊ1����ţ�����Ϊ2����������*/
		coutbook((*i));
	}
	returntomenu();
}
void user::returntomenu() {
	cout << "---------------------" << endl;
	cout << "- 1.�������˵�      -" << endl;
	cout << "- 2. �˳�           -" << endl;
	cout << "---------------------" << endl;
	int ins;
	cin >> ins;
	if (ins == 1) menu();
	else if (ins == 2) exit(0);
	else {
		cout << "����������������룡" << endl;
		returntomenu();
	}
}




admin::admin(string number, string password)   /*��ʼ��admin*/
	:user(number, password) {}
bool admin::Signin(){                          /*��¼���ɹ�����1��ʧ�ܷ���0*/
	ifstream p;
	p.open("administrators.txt", ios::in);
	if (!p) {
		cout << "�ļ���ʧ�ܣ�" << endl;
	}
	struser d;
	while (p >> d.number && p >> d.password) {      /*�����ļ��е��˺�����*/
		if (d.number ==getnumber()) {                    /*�˺Ŵ��ڲ�������ȷ����¼�ɹ�����1*/
			if (d.password == getpassword()) { 
				cout << "��¼�ɹ�!" << endl;
				return 1;
			}
			else {
				cout << "�������,���������룺" << endl;        /*�˺Ŵ������벻��ȷ����¼ʧ�ܷ���0*/
				return 0;
			}
		}
	}
	cout << "�˺Ų�����,��ת��ע�ᣡ" << endl;                 /*�����ļ��е��˺����������֮ǰû�з������˺Ų����ڷ���0*/
	return Register();
}
bool admin::Register() {                          /*ע���˺Ų�д���ļ���*/
	ofstream p;
	p.open("administrators.txt", ios::app);
	if (!p) {
		cout << "�ļ���ʧ�ܣ�" << endl;
	}
	struser u = { getnumber(),getpassword()};
	p << getnumber() << endl;
	p << getpassword() << endl;
	p.close();
	cout << "ע��ɹ�!" << endl;
	return 1;
}
void admin::addbook() {                          /*���ͼ��*/
	cout << "������ͼ����Ϣ,��ʽΪ:" << endl;
	cout << "����" << endl;
	cout << "����" << endl;
	cout << "���" << endl;
	book a;
	cin >> a.bookname;
	cin >> a.author;
	cin >> a.booknumber;
	a.bookstate = 1;
	vector<book> t = getbookvector("book.txt");   /*��ȡ�ļ��е������ļ���Ϣ��������t��*/
	vector<book>::iterator i;                     /*�õ�������������*/
	bool flag = 0;
	for (i = t.begin(); i != t.end(); ++i) {
		if (a.booknumber < (*i).booknumber) { /*Ѱ���ʵ�λ�ò���Ҫ�����ͼ����Ϣ*/
			t.insert(i, a);
			flag = 1;
			break;
		}
	}
	if (flag == 0) t.push_back(a);
	writebook("book.txt",t);                 /*�����º������д���ļ�*/
	cout << "��ӳɹ�!" << endl;
	returntomenu();
}
void admin::deletebook() {
	vector<book> t = getbookvector("book.txt");   /*��ȡ�ļ��е������ļ���Ϣ��������t��*/
	vector<book>::iterator i = t.begin();          /*�õ�����ѡ��һ��ͼ��*/
	if (slectbook(t, i)) {
		t.erase(i);
		writebook("book.txt", t);
	}
	returntomenu();
}
void admin::borrowbook() {                                 /*����*/
	cout << "������ѧ��" << endl;
	string num;
	cin >> num;                                             /*��ȡѧ��*/
	vector<book> t = getbookvector("book.txt");
	vector<book>::iterator i = t.begin();
	if (slectbook(t, i)) {
		if ((*i).bookstate) {                                     /*��������*/
				(*i).bookstate = 0;                                  /*��ͼ��״̬��Ϊ���*/
				addborrowbookrecord(num, (*i));
			}
		else cout << "�����ѱ������" << endl;                 /*���ڹ�����ʾ*/
	}
	writebook("book.txt", t);
	returntomenu();
}
void admin::returnbook() {
	cout << "�������ţ�" << endl;
	int s;
	cin >> s;/*��ȡ���*/
	if (Deleteborrowbookrecord(s)) {
			vector<book> b;
			b = getbookvector("book.txt");         /*��ȡ�����鼮��Ϣ*/
			vector<book>::iterator j = b.begin();
			for (j; j!= b.end(); ++j) {                  /*���������鼮��Ϣ���ҵ���������*/
				if ((*j).booknumber == s) {
					(*j).bookstate = 1;               /*���鼮״̬��Ϊ�ڹ�*/
					break;
				}
			}
			writebook("book.txt",b);
			cout << "����ɹ���" << endl;
			returntomenu();              
	}
			
	else {
		cout << "�Ҳ������ļ�¼" << endl;
		returntomenu();
	}
}
void admin::brokenbook(){
	cout << "�������𻵻�ʧ��ͼ����" << endl;
	int num;
	cin >> num;   /*��ȡ���*/
	if (Deleteborrowbookrecord(num)) {
		Deletebook(num);         /*ɾ������鼮*/
		cout << "�Ǽǳɹ����뼰ʱ�⳥" << endl;
		returntomenu();
	}
	else {
		cout << "�Ҳ��������¼" << endl;
		returntomenu();
	}
}
void admin::menu() {
	cout << "\t\t==========��ӭ����ͼ��ݹ���ϵͳ==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=            ***������ָ��***            =" << endl;
	cout << "\t\t= 1.���ͼ��                             =" << endl;
	cout << "\t\t= 2.ɾ��ͼ��                             =" << endl;
	cout << "\t\t= 3.���ĵǼ�                             =" << endl;
	cout << "\t\t= 4.����                                 =" << endl;
	cout << "\t\t= 5.����ͼ��                             =" << endl;
	cout << "\t\t= 6.ͼ���𻵵Ǽ����⳥                   =" << endl;
	cout << "\t\t= 7.�˳�ϵͳ                             =" << endl;
	cout << "\t\t==========================================" << endl;
	select();
}
void admin::select() {
	int ins;
	cin >> ins;
	switch (ins) {
	case(1): this->addbook(); break;
	case(2):this->deletebook(); break;
	case(3):this->borrowbook(); break;
	case(4):this->returnbook(); break;
	case(5):this->searchbook(); break;
	case(6):this->brokenbook(); break;
	case(7):exit(0);
	default:cout << "����������������룺" << endl; this->select();
	}
}


student::student(string number, string password):user(number,password) {} /*��ʼ��student��*/
bool student::Signin() {
	ifstream p;
	p.open("student.txt", ios::in);
	struser d;
	while (p >> d.number && p >> d.password) {      /*�����ļ��е��˺�����*/
		if (d.number == getnumber()) {                    /*�˺Ŵ��ڲ�������ȷ����¼�ɹ�����1*/
			if (d.password == getpassword()) {
				cout << "��¼�ɹ�!" << endl;
				return 1;
			}
			else {
				cout << "�������!" << endl;        /*�˺Ŵ������벻��ȷ����¼ʧ�ܷ���0*/
				return 0;
			}
		}
	}
	cout << "�˺Ų�����!" << endl;                 /*�����ļ��е��˺����������֮ǰû�з������˺Ų����ڷ���0*/
	return 0;
}
bool student::Register() {                          /*ע���˺Ų�д���ļ���*/
	ofstream p;
	p.open("student.txt", ios::app);
	if (!p) {
		cout << "�ļ���ʧ�ܣ�" << endl;
	}
	struser u = { getnumber(),getpassword() };
	p << getnumber() << endl;
	p << getpassword() << endl;
	p.close();
	cout << "ע��ɹ�!" << endl;
	return 1;
}
void student::menu(){
	cout << "\t\t==========��ӭ����ͼ��ݹ���ϵͳ==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=            ***������ָ��***            =" << endl;
	cout << "\t\t= 1.��ѯ���ļ�¼                         =" << endl;
	cout << "\t\t= 2.����ͼ��                             =" << endl;
	cout << "\t\t= 3.ͼ������                              =" << endl;
	cout << "\t\t= 4.�˳�ϵͳ                             =" << endl;
	cout << "\t\t==========================================" << endl;
	select();
}

void student::select(){
	int ins;
	cin >> ins;
	switch (ins) {
	case(1):this->findrecord(); break;
	case(2):this->searchbook(); break;
	case(3):this->bookrenew();  break;
	case(4):exit(0); break;
	default:cout << "����������������룺" << endl; this->select();
	}
}
void student::findrecord(){
	vector<borrowbookrecord> t = screenBorrowBookRecord(getnumber());
	vector<borrowbookrecord>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {
			coutborrowbookrecord((*i));
	}
	returntomenu();
}
void student::bookrenew(){
	cout << "������Ҫ�����ͼ���ţ�����0�˳�" << endl;
	int num;
	bool flag = false;
	while (1) {
		cin >> num;
		if (num == 0) { break; }
		else {
			vector<borrowbookrecord> t = getborrowrecord("borrowbookrecord.txt");
			vector<borrowbookrecord>::iterator i = t.begin();
			for (i; i != t.end(); ++i) {
				if (getnumber() == (*i).number) {
					if ((*i).booknumber == num) {
						datechange((*i).deadline);
						writeborrowbookrecord(t);
						flag = true;
						cout << "����ɹ�" << endl;
						break;
					}
				}
			}
		}
		if (!flag) { cout << "�����������������" << endl; }
		else break;
	}
}
vector<book>  getbookvector(string adress) {          /*���ڶ�ȡ�鼮��Ϣ��vector��*/
	ifstream p;
	p.open(adress, ios::in);
	if (!p) {
		cout << "��ʧ�ܣ�" << endl;
		exit(0);
	}
	vector<book> a;
	book temp;
	while (p >> temp.bookname && p >> temp.author && p >> temp.booknumber && p >> temp.bookstate) {
		a.push_back(temp);
	}
	p.close();
	return a;
}
void writebook(string address,vector<book> a) {     /*��vector�е�ͼ����Ϣд���ļ�*/
	ofstream p;
	p.open(address, ios::out);
	if (!p) {
		cout << "��ʧ�ܣ�" << endl;
		exit(0);
	}
	vector<book>::iterator i=a.begin();
	while (i!=a.end()) {
		p << (*i).bookname << endl;
		p << (*i).author << endl;
		p << (*i).booknumber << endl;
		p << (*i).bookstate << endl;
		++i;
	}
	p.close();
}
void coutbook(book a) {
	cout << "������"<<a.bookname << endl;
	cout << "���ߣ�"<<a.author << endl;
	cout <<"��ţ�"<< a.booknumber << endl;
	cout << "״̬��";
	if (a.bookstate) cout << "�ڹ�" << endl;
	else cout << "���" << endl;
}
bool slectbook(vector<book> &t,vector<book>::iterator &i) {         /*����ͼ�鲢���ص�����*/                 
																  /*�����飬����Ϊ1����ţ�����Ϊ2����������*/
	cout << "��ѡ�������ʽ��" << endl;
	cout << "1.����ż���" << endl;
	cout << "2.����������" << endl;
	int a;
	cin >> a;                                  
	if (a == 1) {
		cout << "�������ţ�" << endl;
		int num;
		cin >> num;
		for (i ; i != t.end(); ++i) {
			if (num == (*i).booknumber) {
				return true;
			}
		}

		cout << "δ�ҵ�ͼ�������¼���" << endl;
		return slectbook(t,i);
	}
	else if (a == 2) {
		cout << "������������" << endl;
		string name;
		cin >> name;
		for (i ; i != t.end(); ++i) {
			if (name == (*i).bookname) {
				return true;
			}
		}
		cout << "δ�ҵ�ͼ�������¼���" << endl;
		return slectbook(t, i);
	
	}
	else {
		cout << "������������¼���" << endl;
		return slectbook(t, i);
	}
}
void addborrowbookrecord(string num,book b) {
	ofstream p;
	p.open("borrowbookrecord.txt", ios::app);
	if (!p) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	p << b.bookname << endl;
	p << b.author << endl;
	p << b.booknumber << endl;
	p << num << endl;
	time_t now = time(0);
	tm ptm;
	localtime_s(&ptm,&now);              /*��ȡ��ǰʱ��*/
	date nowdate;                               /*����ǰ���ڴ���ṹ��*/
	nowdate.year = ptm.tm_year + 1900;
	nowdate.month = ptm.tm_mon + 1;
	nowdate.day = ptm.tm_mday;
	p << nowdate.year << endl;                   /*д���ļ�*/
	p << nowdate.month << endl;
	p << nowdate.day << endl;
	datechange(nowdate);                 /*��30��*/
	p << nowdate.year << endl;                /*��д���ļ�*/
	p << nowdate.month << endl;
	p << nowdate.day << endl;
	p.close();
	cout << "����ɹ���" << endl;
}
vector<borrowbookrecord> getborrowrecord(string address) {
	ifstream p;
	p.open(address, ios::in);
	vector<borrowbookrecord> t;                               
	borrowbookrecord a;                                    /*��ʱ��Ž����¼*/
	while (p >> a.bookname && p >> a.author && p >> a.booknumber && p >> a.number&&p>>a.startday.year&&p>>a.startday.month&&p>>a.startday.day&&p>>a.deadline.year&&p>>a.deadline.month&&p>>a.deadline.day) {         /*���õ������������¼��������a*/
		t.push_back(a);
	}
	p.close();
	return t;
}
void writeborrowbookrecord(vector<borrowbookrecord> t) {
	ofstream p;
	p.open("borrowbookrecord.txt", ios::out);
	vector<borrowbookrecord>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {
		p << (*i).bookname << endl;
		p << (*i).author << endl;
		p << (*i).booknumber << endl;
		p << (*i).number << endl;
		p << (*i).startday.year << endl;
		p << (*i).startday.month << endl;
		p << (*i).startday.day << endl;
		p << (*i).deadline.year << endl;
		p << (*i).deadline.month << endl;
		p << (*i).deadline.day << endl;
	}
	p.close();
}
void Deletebook(int num) {
	vector < book > t= getbookvector("book.txt");           /*��ȡ����ͼ����Ϣ*/
	vector<book>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {
		if (num == (*i).booknumber) {                        /*��������ͼ����Ϣɾ��*/
			t.erase(i);
			break;
		}
	}
}
bool Deleteborrowbookrecord(int num) {
	vector<borrowbookrecord> t = getborrowrecord("borrowbookrecord.txt"); /*��ȡ�����¼��������t*/
	vector<borrowbookrecord>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {                      /*���������¼Ѱ�ұ��*/
		if ((*i).booknumber == num) {
			t.erase(i);                           /*ɾ����Ӧ�Ľ����¼*/
			writeborrowbookrecord(t);                    /*��ɾ����Ľ����¼д���ļ�*/
			return 1;
		}
	}
	return 0;
}
void coutborrowbookrecord(borrowbookrecord t) {
	cout <<"������"<< t.bookname << endl;
	cout <<"���ߣ�"<< t.author << endl;
	cout << "��ţ�" << t.booknumber << endl;
	cout << "������ѧ�ţ�" << t.number << endl;
	cout << "����ʱ�䣺" << t.startday.year << "-" << t.startday.month << "-" << t.startday.day << endl;
	cout << "����ʱ�䣺" << t.deadline.year << "-" << t.deadline.month << "-" << t.deadline.day << endl;
}
void datechange(date &day) {
	day.day += 30;
	while (day.day > d[day.month]) {
		day.day -= d[day.month];
		day.month++;
	}
	while (day.month > 12) {
		day.month-=12;
		day.year++;
	}
}
vector<borrowbookrecord> screenBorrowBookRecord(string name){
	vector<borrowbookrecord> t = getborrowrecord("borrowbookrecord.txt"); /*��ȡ�����¼��������t*/
	vector<borrowbookrecord>::iterator i = t.begin();
	vector<borrowbookrecord> s;
	for (i; i != t.end(); ++i) {
		if (name == (*i).number) {
			s.push_back((*i));
		}
	}
	return s;
}