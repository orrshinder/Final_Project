#include "Folder.h"
#include <string>


Folder::Folder(string name)
{
	m_name = name;
	mail_list = new Mail * [0];
	mail_list = NULL;
	m_size = 0;
	m_top = 0;
}
Folder::~Folder()
{
	
	if (!this->isEmpty())
	{
		for (int i = 0; i < m_top; i++)
		{
			delete mail_list[i];
		}
	}
}



void Folder::Remove(Mail* mail)
{
	unsigned index = 0;
	if (isEmpty())
	{
		cout << "folder nothing to pop." << endl;
	}
	else
	{
		for (int i = 0; i < m_top; i++)
		{
			if (mail_list[i] == mail)
			{
				index = i;

				break;
			}
		}
		for (unsigned j = index; j < m_top-1; j++)
		{
			mail_list[j] = mail_list[j + 1];
		}
		if (m_top == 1)
		{
			//delete mail_list[0];
			mail_list[0] = 0;
		}
		m_top--;
		m_size--;
	}
}
void  Folder::seralization(ofstream& ofs)
{
	ofs <<"Folder:" << " " << this->m_name << endl;
	for (int i = 0; i < m_top; i++)
	{ 
		Mail* temp = mail_list[i];
		temp->seralization(ofs);
		
	}
}
void Folder::Add_old_mail(Mail* mail)
{
	push_back(mail);
}
void Folder::Add_new_mail(Mail* mail)
{
	push(mail);
}
bool Folder::operator ==(const Folder* other)
{
	if (this->m_name == other->m_name && this->mail_list == other->mail_list)
	{
		return true;
	}
	return false;
}

void Folder::push(Mail* c)
{
	if (mail_list)
	{
		if (isEmpty())
		{
			mail_list[0] = (c);
			m_top++;
		}
		else
		{
			Mail** temp = new Mail * [m_size];
			for (int i = 0; i < m_size; i++) {
				temp[i] = mail_list[i];
			}
			for (int i = 0; i < m_size; i++) {
				mail_list[i + 1] = temp[i];
			}
			mail_list[0] = (c);
			m_top++;
		}
	}
	else
	{
		Mail** temp = new Mail * [m_size];
		for (int i = 0; i < m_size; i++) {
			temp[i] = (mail_list[i]);
		}
		mail_list = new  Mail * [m_size + 1];;
		for (int j = 0; j < (int)m_size; j++) {
			mail_list[j + 1] = temp[j];
		}
		mail_list[0] = 0;
		mail_list[0] = c;
		cout << mail_list[0]->get_uniqe_id() << endl;
		m_size = m_size + 1;
		m_top++;
	}
}
void Folder::push_back(Mail* c)
{
	if (!isFull())
	{
		if (isEmpty())
		{
			mail_list[m_top] = (c);
			m_top++;
		}
		else
		{
			Mail** temp = new Mail * [m_size];
			for (int i = 0; i < m_size; i++) {
				temp[i] = mail_list[i];
			}
			for (int i = 1; i < m_size; i++) {
				mail_list[i-1] = temp[i];
			}

			
			
			mail_list[m_top] = (c);
			m_top++;
		}
	}
	else
	{
		Mail** temp = new Mail * [m_size];
		for (int i = 0; i < m_size; i++) {
			temp[i] = (mail_list[i]);
		}
		mail_list = new  Mail * [m_size + 1];;
		for (int j = 0; j < (int)m_size; j++) {
			mail_list[j] = temp[j];
		}
		mail_list[m_top] = c;
		m_size = m_size + 1;
		m_top++;
	}
}
bool Folder::isEmpty()
{
	return m_top == 0;
}
bool Folder::isFull() const 
{
	return m_size == m_top;
}
unsigned Folder::size() const
{
	return m_size;
}
