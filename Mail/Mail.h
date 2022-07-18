#pragma once
#ifndef MAIL_H
#define MAIL_H

#include <iostream>
#include <string>
#include "Folder.h"
#include "Application.h"
#include "Contacts.h"
#include "Contact.h"
using namespace std;
#define _CRTDBG_MAP_ALLOC
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

class Mail
{
public:
	friend class Folder;
	friend class Contacts;
	friend class Contact;
	friend class Application;
	Mail(string date, string* send_From, string* send_To, string subject, string content, int mail_id,int size_send_from,int size_sent_to);
	Mail();
	virtual ~Mail();
	string get_Date() const;
	virtual string* get_Send_From() const=0;
	virtual string* get_Send_To() const=0;
	void get_Send_From_print() const;
	string get_Subject() const;
	string get_Content() const;
	int get_uniqe_id()const;
	void seralization(ofstream& ofs);
	void seralization_contacts(ofstream& ofs);
	friend ostream& operator<<(ostream& os, const Mail& c);

protected:

	string m_Date;
	string*  m_Send_From;
	string*  m_Send_To;
	string  m_Subject;
	string  m_Content;
	int Mail_special_num;
	int sent_people;
	int recived_peeople;

};


class Recived_mail : public Mail
{
public:
	Recived_mail(string Date, string* Send_From, string* Send_To, string Subject, string Content, int mail_id, int size_send_from, int size_sent_to):Mail(Date,Send_From,Send_To,Subject,Content,mail_id, size_send_from,size_sent_to) {};
	~Recived_mail() {};
	string* get_Send_From() const;
	string* get_Send_To() const;

};

class Sent_mail: public Mail
{
public:
	Sent_mail(string Date, string* Send_From, string* Send_To, string Subject, string Content, int mail_id, int size_send_from, int size_sent_to) :Mail(Date, Send_From, Send_To, Subject, Content,mail_id, size_send_from, size_sent_to) {};
	~Sent_mail() {};
	string* get_Send_From() const;
	string* get_Send_To() const;
};

#endif