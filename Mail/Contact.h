#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include "Contacts.h"
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
using namespace std;
class Contact
{
public:
	friend class Mail;
	friend class Folder;
	friend class Contacts;
	friend class Application;
	Contact();
	Contact(string name,string address);
	~Contact();
	string get_name() const;
	string get_address() const;
	bool operator ==(const Contact& other);
	bool operator !=(const Contact& other);
protected:
	string m_name;
	string m_address;
};

#endif
