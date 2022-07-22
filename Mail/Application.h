
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
	Application();//constractor
	~Application();//distractor
	void Compose();//creating new mail
	void Remove();//remove mail by uniqe id
	void List(string folder_name);//printing 10 first new mails
	void Search();//search mail by name or subject
	void Move();//move mail by uniqe id to other folder
	void More(int flag, string folder_name);//printing the next 10 mails in the folder
	void CD();//folder entering
	void MkDir();//creating folder
	void RmDir();//removing folder
	void ListDir();// list of all folders
	void contacts();//managing the cintacts of the app
	void main_screen();//the main screen of the app
	void rlist();//managing contacts lists
	string option();//printing the main screen options
	void Print();//print mail by uniqe id
	void seralization(ofstream& ofs);//writing infomation to file
	void deseralization(ifstream& ofs);//reading information from a file
	bool serach_contact(string name);//search if exist contact by mail or name
	Contact* find_contact(string name);//findind the contact by mail or name
	Contacts* find_rlist(string name);//findind the contact list by name
	void remove_contact(Contact* c);//remove contact
	Folder* find_folder(string name);//findind foldr by name
	bool serach_folder(string name);//search if exist folder by name
	void push_folder(Folder* c);//pushing new folder
	void pop_folder(Folder* mail);//removing folder
	bool folder_isFull() const;//checking if folder list is full
	bool folder_isEmpty();//checking if folder list is Empty
	unsigned folder_size()const;//returning the size of the foldrs list
	unsigned contacts_size()const;//returning the size of the contacts list
	bool contacts_isEmpty();//checking if contacts list is Empty
	bool contacts_isFull() const;//checking if contacts list is full
	void push_contacts(Contacts* c);//pushing new contacts list
	void pop_contacts(Contacts* folder);//removing contacts list
	bool isValid(const string& email);//checking if mail pattern is valid 
	bool find_contact_in_mail(Mail* mail,string name);//checking if the person is un the mail sent or recived people
	void start_mail_check();//checking and creating if no text file exist
	bool serach_rlist(string name);//checking if contact list exist with this name
	void forward_mail(Mail* mail);
	void reply_message(Mail* mail);
	void draft_complete();//complete draft mail
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
