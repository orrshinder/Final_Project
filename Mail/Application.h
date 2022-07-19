
#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include "Contacts.h"
#include "Folder.h"
#include "Mail.h"
#include <fstream>
#include <ostream>
#include <regex>
#include <typeinfo>
using namespace std;
#define _CRTDBG_MAP_ALLOC
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
class Application
{
public:
	friend class Mail;
	friend class Contacts;
	friend class Contact;
	friend class Folder;
	Application();
	~Application();
	void Compose();
	void Remove();
	void List(string folder_name);
	void Search();
	void Move();
	void More(int flag, string folder_name);
	void CD();
	void MkDir();
	void RmDir();
	void ListDir();
	void contacts();
	void main_screen();
	void rlist();
	string option();
	void Print();
	void seralization(ofstream& ofs);
	void deseralization(ifstream& ofs);
	bool serach_contact(string name);
	Contact* find_contact(string name);
	Contacts* find_rlist(string name);
	void remove_contact(Contact* c);
	Folder* find_folder(string name);
	bool serach_folder(string name);
	void push_folder(Folder* c);
	void pop_folder(Folder* mail);
	bool folder_isFull() const;
	bool folder_isEmpty();
	unsigned folder_size()const;
	unsigned contacts_size()const;
	bool contacts_isEmpty();
	bool contacts_isFull() const;
	void push_contacts(Contacts* c);
	void pop_contacts(Contacts* folder);
	bool isValid(const string& email);
	bool find_contact_in_mail(Mail* mail,string name);
	void start_mail_check();
	bool serach_rlist(string name);
	void forward_mail(Mail* mail);
	void reply_message(Mail* mail);
	void draft_complete();
protected:
	Folder** mail_folders;
	Contacts** mail_contacts;
	string my_mail = "orrshinder@gmail.com";
	string my_name = "orr";
	//static int Mail_Value;
	int m_size_contacts;  
	int m_top_contacts;   
	int m_size_folders;  
	int m_top_folders;   
	int Mail_Value;
	string m_date;

};

#endif
