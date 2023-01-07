#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include "classes.h"
using namespace std;
vector<book> getbookvector(string adress);                  /*从文件中用于获取所有的书籍信息，存入一个vector*/
bool slectbook(vector<book> &t,vector<book>::iterator &i);  /*引用一个vector 和一个迭代器，定位要选择的书籍*/
void writebook(string address, vector<book> a);             /*将更新后的书籍信息从vector写入文件*/
void coutbook(book a);                                      /*用于打印书籍信息*/
void addborrowbookrecord(string num,book b);                /*将借书信息用追加写的方式写入文件*/
void writeborrowbookrecord(vector<borrowbookrecord> t);      /*将更新后的借书信息写入文件*/
vector<borrowbookrecord> getborrowrecord(string address);    /*从文件中读取所有借书信息并存入一个vector*/
void Deletebook(int num);                                     /*删除书籍信息*/
bool Deleteborrowbookrecord(int num);                         /*删除借书信息*/
void coutborrowbookrecord(borrowbookrecord t);                    /*打印借阅记录*/
void renewbookrecord(borrowbookrecord t);                     /*增加借书时间*/
vector<borrowbookrecord> screenBorrowBookRecord(string name);
void datechange(date &day);
user::user(string number, string password) {          /*创建一个user对象时初始化账号密码*/
	this->number = number;
	this->password = password;
}
void user::renew(string number, string password) {  /*更新账号密码*/
	this->number = number;
	this->password = password;
}
void user::searchbook() {                                     
	vector<book> t = getbookvector("book.txt");
	vector<book>::iterator i = t.begin();
	if (slectbook(t, i)) {                         /*搜索书，参数为1按编号，参数为2按书名搜索*/
		coutbook((*i));
	}
	returntomenu();
}
void user::returntomenu() {
	cout << "---------------------" << endl;
	cout << "- 1.返回主菜单      -" << endl;
	cout << "- 2. 退出           -" << endl;
	cout << "---------------------" << endl;
	int ins;
	cin >> ins;
	if (ins == 1) menu();
	else if (ins == 2) exit(0);
	else {
		cout << "输入错误，请重新输入！" << endl;
		returntomenu();
	}
}




admin::admin(string number, string password)   /*初始化admin*/
	:user(number, password) {}
bool admin::Signin(){                          /*登录，成功返回1，失败返回0*/
	ifstream p;
	p.open("administrators.txt", ios::in);
	if (!p) {
		cout << "文件打开失败！" << endl;
	}
	struser d;
	while (p >> d.number && p >> d.password) {      /*遍历文件中的账号密码*/
		if (d.number ==getnumber()) {                    /*账号存在并密码正确，登录成功返回1*/
			if (d.password == getpassword()) { 
				cout << "登录成功!" << endl;
				return 1;
			}
			else {
				cout << "密码错误,请重新输入：" << endl;        /*账号存在密码不正确，登录失败返回0*/
				return 0;
			}
		}
	}
	cout << "账号不存在,跳转到注册！" << endl;                 /*遍历文件中的账号如果函数在之前没有返回则账号不存在返回0*/
	return Register();
}
bool admin::Register() {                          /*注册账号并写入文件中*/
	ofstream p;
	p.open("administrators.txt", ios::app);
	if (!p) {
		cout << "文件打开失败！" << endl;
	}
	struser u = { getnumber(),getpassword()};
	p << getnumber() << endl;
	p << getpassword() << endl;
	p.close();
	cout << "注册成功!" << endl;
	return 1;
}
void admin::addbook() {                          /*添加图书*/
	cout << "请输入图书信息,格式为:" << endl;
	cout << "书名" << endl;
	cout << "作者" << endl;
	cout << "编号" << endl;
	book a;
	cin >> a.bookname;
	cin >> a.author;
	cin >> a.booknumber;
	a.bookstate = 1;
	vector<book> t = getbookvector("book.txt");   /*读取文件中的所以文件信息存入向量t中*/
	vector<book>::iterator i;                     /*用迭代器遍历容器*/
	bool flag = 0;
	for (i = t.begin(); i != t.end(); ++i) {
		if (a.booknumber < (*i).booknumber) { /*寻找适当位置插入要插入的图书信息*/
			t.insert(i, a);
			flag = 1;
			break;
		}
	}
	if (flag == 0) t.push_back(a);
	writebook("book.txt",t);                 /*将更新后的向量写入文件*/
	cout << "添加成功!" << endl;
	returntomenu();
}
void admin::deletebook() {
	vector<book> t = getbookvector("book.txt");   /*读取文件中的所以文件信息存入向量t中*/
	vector<book>::iterator i = t.begin();          /*用迭代器选择一个图书*/
	if (slectbook(t, i)) {
		t.erase(i);
		writebook("book.txt", t);
	}
	returntomenu();
}
void admin::borrowbook() {                                 /*借书*/
	cout << "请输入学号" << endl;
	string num;
	cin >> num;                                             /*获取学号*/
	vector<book> t = getbookvector("book.txt");
	vector<book>::iterator i = t.begin();
	if (slectbook(t, i)) {
		if ((*i).bookstate) {                                     /*馆则借出在*/
				(*i).bookstate = 0;                                  /*将图书状态改为借出*/
				addborrowbookrecord(num, (*i));
			}
		else cout << "该书已被借出！" << endl;                 /*不在馆则提示*/
	}
	writebook("book.txt", t);
	returntomenu();
}
void admin::returnbook() {
	cout << "请输入编号：" << endl;
	int s;
	cin >> s;/*获取编号*/
	if (Deleteborrowbookrecord(s)) {
			vector<book> b;
			b = getbookvector("book.txt");         /*获取所有书籍信息*/
			vector<book>::iterator j = b.begin();
			for (j; j!= b.end(); ++j) {                  /*遍历所有书籍信息，找到被还的书*/
				if ((*j).booknumber == s) {
					(*j).bookstate = 1;               /*将书籍状态改为在馆*/
					break;
				}
			}
			writebook("book.txt",b);
			cout << "还书成功！" << endl;
			returntomenu();              
	}
			
	else {
		cout << "找不到借阅记录" << endl;
		returntomenu();
	}
}
void admin::brokenbook(){
	cout << "请输入损坏或丢失的图书编号" << endl;
	int num;
	cin >> num;   /*获取编号*/
	if (Deleteborrowbookrecord(num)) {
		Deletebook(num);         /*删除相关书籍*/
		cout << "登记成功，请及时赔偿" << endl;
		returntomenu();
	}
	else {
		cout << "找不到借书记录" << endl;
		returntomenu();
	}
}
void admin::menu() {
	cout << "\t\t==========欢迎进入图书馆管理系统==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=            ***请输入指令***            =" << endl;
	cout << "\t\t= 1.添加图书                             =" << endl;
	cout << "\t\t= 2.删除图书                             =" << endl;
	cout << "\t\t= 3.借阅登记                             =" << endl;
	cout << "\t\t= 4.还书                                 =" << endl;
	cout << "\t\t= 5.搜索图书                             =" << endl;
	cout << "\t\t= 6.图书损坏登记与赔偿                   =" << endl;
	cout << "\t\t= 7.退出系统                             =" << endl;
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
	default:cout << "输入错误请重新输入：" << endl; this->select();
	}
}


student::student(string number, string password):user(number,password) {} /*初始化student类*/
bool student::Signin() {
	ifstream p;
	p.open("student.txt", ios::in);
	struser d;
	while (p >> d.number && p >> d.password) {      /*遍历文件中的账号密码*/
		if (d.number == getnumber()) {                    /*账号存在并密码正确，登录成功返回1*/
			if (d.password == getpassword()) {
				cout << "登录成功!" << endl;
				return 1;
			}
			else {
				cout << "密码错误!" << endl;        /*账号存在密码不正确，登录失败返回0*/
				return 0;
			}
		}
	}
	cout << "账号不存在!" << endl;                 /*遍历文件中的账号如果函数在之前没有返回则账号不存在返回0*/
	return 0;
}
bool student::Register() {                          /*注册账号并写入文件中*/
	ofstream p;
	p.open("student.txt", ios::app);
	if (!p) {
		cout << "文件打开失败！" << endl;
	}
	struser u = { getnumber(),getpassword() };
	p << getnumber() << endl;
	p << getpassword() << endl;
	p.close();
	cout << "注册成功!" << endl;
	return 1;
}
void student::menu(){
	cout << "\t\t==========欢迎进入图书馆管理系统==========" << endl;
	cout << "\t\t=                                        =" << endl;
	cout << "\t\t=            ***请输入指令***            =" << endl;
	cout << "\t\t= 1.查询借阅记录                         =" << endl;
	cout << "\t\t= 2.搜索图书                             =" << endl;
	cout << "\t\t= 3.图书续借                              =" << endl;
	cout << "\t\t= 4.退出系统                             =" << endl;
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
	default:cout << "输入错误请重新输入：" << endl; this->select();
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
	cout << "请输入要续借的图书编号，输入0退出" << endl;
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
						cout << "续借成功" << endl;
						break;
					}
				}
			}
		}
		if (!flag) { cout << "输入错误请重新输入" << endl; }
		else break;
	}
}
vector<book>  getbookvector(string adress) {          /*用于读取书籍信息到vector中*/
	ifstream p;
	p.open(adress, ios::in);
	if (!p) {
		cout << "打开失败！" << endl;
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
void writebook(string address,vector<book> a) {     /*将vector中的图书信息写入文件*/
	ofstream p;
	p.open(address, ios::out);
	if (!p) {
		cout << "打开失败！" << endl;
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
	cout << "书名；"<<a.bookname << endl;
	cout << "作者："<<a.author << endl;
	cout <<"编号："<< a.booknumber << endl;
	cout << "状态：";
	if (a.bookstate) cout << "在馆" << endl;
	else cout << "借出" << endl;
}
bool slectbook(vector<book> &t,vector<book>::iterator &i) {         /*检索图书并返回迭代器*/                 
																  /*搜索书，参数为1按编号，参数为2按书名搜索*/
	cout << "请选择检索方式：" << endl;
	cout << "1.按编号检索" << endl;
	cout << "2.按书名检索" << endl;
	int a;
	cin >> a;                                  
	if (a == 1) {
		cout << "请输入编号：" << endl;
		int num;
		cin >> num;
		for (i ; i != t.end(); ++i) {
			if (num == (*i).booknumber) {
				return true;
			}
		}

		cout << "未找到图书请重新检索" << endl;
		return slectbook(t,i);
	}
	else if (a == 2) {
		cout << "请输入书名：" << endl;
		string name;
		cin >> name;
		for (i ; i != t.end(); ++i) {
			if (name == (*i).bookname) {
				return true;
			}
		}
		cout << "未找到图书请重新检索" << endl;
		return slectbook(t, i);
	
	}
	else {
		cout << "输入错误请重新检索" << endl;
		return slectbook(t, i);
	}
}
void addborrowbookrecord(string num,book b) {
	ofstream p;
	p.open("borrowbookrecord.txt", ios::app);
	if (!p) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	p << b.bookname << endl;
	p << b.author << endl;
	p << b.booknumber << endl;
	p << num << endl;
	time_t now = time(0);
	tm ptm;
	localtime_s(&ptm,&now);              /*获取当前时间*/
	date nowdate;                               /*将当前日期存入结构体*/
	nowdate.year = ptm.tm_year + 1900;
	nowdate.month = ptm.tm_mon + 1;
	nowdate.day = ptm.tm_mday;
	p << nowdate.year << endl;                   /*写入文件*/
	p << nowdate.month << endl;
	p << nowdate.day << endl;
	datechange(nowdate);                 /*加30天*/
	p << nowdate.year << endl;                /*再写入文件*/
	p << nowdate.month << endl;
	p << nowdate.day << endl;
	p.close();
	cout << "借书成功！" << endl;
}
vector<borrowbookrecord> getborrowrecord(string address) {
	ifstream p;
	p.open(address, ios::in);
	vector<borrowbookrecord> t;                               
	borrowbookrecord a;                                    /*临时存放借书记录*/
	while (p >> a.bookname && p >> a.author && p >> a.booknumber && p >> a.number&&p>>a.startday.year&&p>>a.startday.month&&p>>a.startday.day&&p>>a.deadline.year&&p>>a.deadline.month&&p>>a.deadline.day) {         /*利用迭代器将借书记录存入向量a*/
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
	vector < book > t= getbookvector("book.txt");           /*获取所有图书信息*/
	vector<book>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {
		if (num == (*i).booknumber) {                        /*遍历所有图书信息删除*/
			t.erase(i);
			break;
		}
	}
}
bool Deleteborrowbookrecord(int num) {
	vector<borrowbookrecord> t = getborrowrecord("borrowbookrecord.txt"); /*获取借书记录存入向量t*/
	vector<borrowbookrecord>::iterator i = t.begin();
	for (i; i != t.end(); ++i) {                      /*遍历借书记录寻找编号*/
		if ((*i).booknumber == num) {
			t.erase(i);                           /*删除对应的借书记录*/
			writeborrowbookrecord(t);                    /*将删除后的借书记录写回文件*/
			return 1;
		}
	}
	return 0;
}
void coutborrowbookrecord(borrowbookrecord t) {
	cout <<"书名："<< t.bookname << endl;
	cout <<"作者："<< t.author << endl;
	cout << "编号：" << t.booknumber << endl;
	cout << "借书人学号：" << t.number << endl;
	cout << "借书时间：" << t.startday.year << "-" << t.startday.month << "-" << t.startday.day << endl;
	cout << "还书时间：" << t.deadline.year << "-" << t.deadline.month << "-" << t.deadline.day << endl;
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
	vector<borrowbookrecord> t = getborrowrecord("borrowbookrecord.txt"); /*获取借书记录存入向量t*/
	vector<borrowbookrecord>::iterator i = t.begin();
	vector<borrowbookrecord> s;
	for (i; i != t.end(); ++i) {
		if (name == (*i).number) {
			s.push_back((*i));
		}
	}
	return s;
}