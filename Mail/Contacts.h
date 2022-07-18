#pragma once
#ifndef CONTACTS_H
#define CONTACTS_H

#include <iostream>
#include <string>
#include <vector>
#include "Contact.h"
#include "Folder.h"
#include "Application.h"
#include "Mail.h"
#include <ostream>
using namespace std;
#define _CRTDBG_MAP_ALLOC
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
class Contacts
{
public:
	friend class Mail;
	friend class Folder;
	friend class Contact;
	friend class Application;
	Contacts();
	~Contacts();
	void Remove(Contact* person);
	void Add(string name, string address);
	virtual string name_list() const;
	void seralization(ofstream& ofs);
	friend ostream& operator<<(ostream& os, const Contacts& c);
	bool operator ==(const Contacts* other);
	Contact* find_contact(string name);
	bool contact_exsit(string name);
	int size_list()const;

protected:
	vector<Contact*> contact_list;
	string list_name;
};
class Rlist:public Contacts
{
public:
	Rlist(string name);
	~Rlist();
	void delete_contact(Contact* person);
	virtual string name_list() const;
	void AddToList(string name, string address);
	void RemoveFromList(string name, string address);
	void seralization(ofstream& ofs);

};
#endif



