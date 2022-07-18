#include "Contacts.h"


Contacts::Contacts()
{
	//contact_list.resize(0);
	list_name = "";
}
string Contacts::name_list()const
{
	return list_name;
}
Contacts::~Contacts()
{
	contact_list.clear();
	contact_list.~vector();
}
void Contacts::Remove(Contact* person)
{
	int counter = 0;
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		if (temp->operator==(*person))
		{
			Contact* x = contact_list.at(counter);
			contact_list.erase(it);
		}
		counter++;
	}
}
void Contacts::Add(string name, string address)
{
	Contact* temp = new Contact(name, address);
	//contact_list.emplace(contact_list.begin(),temp);
	contact_list.insert(contact_list.begin(), temp);
}

void Rlist::AddToList(string name, string address)
{
	Contact* temp = new Contact(name, address);
	//contact_list.emplace(contact_list.begin(),temp);
	contact_list.insert(contact_list.begin(), temp);
}
void Rlist::RemoveFromList(string name, string address)
{
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		if (name == temp->get_name() && address == temp->get_address())
			contact_list.erase(it);
	}
}
Rlist::~Rlist()
{
	contact_list.~vector();
}
string Rlist::name_list()const
{
	return list_name;
}
Rlist::Rlist(string name):Contacts()
{
	list_name=name;
}

void Contacts::seralization(ofstream& ofs)
{
	if (name_list() == "")
	{
		ofs << "contacts:" << endl;
	}
	else
	{
		ofs << "contact list:" << name_list() << endl;
	}
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		ofs << temp->get_name() << "," << temp->get_address() << endl;
	}
}
void Rlist::seralization(ofstream& ofs)
{
	ofs << "contact list:" << this->list_name << endl;
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		ofs << temp->get_name() << "," << temp->get_address() << endl;
	}
}
ostream& operator<<(ostream& os, const Contacts& c)
{
	for (auto it = c.contact_list.begin(); it != c.contact_list.end(); ++it)
	{
		Contact* temp = *it;
		os << temp->get_address() << "  " << temp->get_name() << endl;
	}
	return os;
}
bool Contacts::operator ==(const Contacts* other)
{
	if (this->contact_list.size() == other->contact_list.size())
	{
		for (int i = 0; i < this->contact_list.size(); i++)
		{
			if (this->contact_list.at(i) != other->contact_list.at(i))
			{
				return false;
			}
		}
		return true;
	}
	return false;

}
Contact* Contacts::find_contact(string name)
{
	int counter = 0;
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		if (temp->get_address()==name||temp->get_name()==name)
		{
			return temp;
		}
		counter++;
	}
}
bool Contacts::contact_exsit(string name)
{
	for (auto it = contact_list.begin(); it != contact_list.end(); ++it)
	{
		Contact* temp = *it;
		if (temp->get_address() == name || temp->get_name() == name)
		{
			return true;
		}
		
	}
	return false;
}
int Contacts::size_list()const
{
	return contact_list.size();
}