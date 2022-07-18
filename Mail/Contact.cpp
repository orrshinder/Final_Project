#pragma once
#include "Contact.h"
Contact::Contact(string name, string address)
{
	m_name = name;
	m_address = address;
}
Contact::Contact()
{
	m_name ="";
	m_address ="";
}
Contact::~Contact()
{

}
string Contact::get_name() const
{
	return m_name;
}
string Contact::get_address() const
{
	return m_address;
}
bool Contact::operator ==(const Contact& other)
{
	if ((this->get_name() == other.get_name()) && (this->get_address() == other.get_address()))
	{
		return true;
	}
	return false;
	
}
bool Contact::operator !=(const Contact& other)
{
	if ((this->get_name() != other.get_name()) || (this->get_address() != other.get_address()))
	{
		return true;
	}
	return false;

}
