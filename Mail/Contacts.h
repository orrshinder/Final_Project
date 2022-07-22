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
	Contacts();//constractor
	~Contacts();//distractor
	void Remove(Contact* person);//remove contact
	void Add(string name, string address);//add contact
	virtual string name_list() const;
	void seralization(ofstream& ofs);//writing infomation to file
	friend ostream& operator<<(ostream& os, const Contacts& c);
	bool operator ==(const Contacts* other);
	Contact* find_contact(string name);//find contact by mail or name
	bool contact_exsit(string name);//check if contact exist by name or mail
	int size_list()const;//returns the sie of the list

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
	string name_list() const;
	void AddToList(string name, string address);
	void RemoveFromList(string name, string address);
	void seralization(ofstream& ofs);

};
#endif



