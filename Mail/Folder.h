#pragma once
#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include <string>
#include "Mail.h"
#include "Application.h"
#include "Contacts.h"
#include "Contact.h"
#include <vector>

using namespace std;
class Folder
{
public:
	friend class Mail;
	friend class Contacts;
	friend class Contact;
	friend class Application;
	Folder(string m_name);
	~Folder();
	void Remove(Mail* mail);
	void Add_old_mail(Mail* mail);
	void Add_new_mail(Mail* mail);
	void seralization(ofstream& ofs);
	bool operator ==(const Folder* other);
	void push(Mail* c);
	void push_back(Mail* c);
	bool isFull() const;
	bool isEmpty();
	unsigned size()const;

protected:
	string m_name;
	Mail** mail_list;
	int m_size; 
	int m_top;
};
#endif