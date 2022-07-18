#include "Mail.h"

Mail::Mail(string Date, string* Send_From, string* Send_To, string Subject, string Content, int mail_id,int size_send_from,int size_sent_to) : m_Date(Date),m_Subject(Subject), m_Content(Content),Mail_special_num(mail_id)//ctor
{
	sent_people=size_sent_to;
	recived_peeople= size_send_from;
	m_Send_From = NULL;
	m_Send_To = NULL;
	//string* temp = Send_From;
	//int size = temp->size();
	//string* temp1 = Send_To;
	//int size1 = temp1->size();
	m_Send_From=new string[size_send_from];
	//m_Send_From = temp;
	m_Send_To = new string[size_sent_to];
	for (int i = 0; i < size_send_from; i++)
	{
		m_Send_From[i] = Send_From[i];
	}
	for (int j = 0; j < size_sent_to; j++)
	{
		m_Send_To[j] = Send_To[j];
	}
}
Mail::Mail()
{
	
	m_Date="";
	m_Send_From=nullptr;
	m_Send_To=nullptr;
	m_Subject="";
	m_Content="";
	Mail_special_num=0;
}
Mail::~Mail()
{
	m_Content="";
	m_Date="";
	delete[] m_Send_From;
	delete[] m_Send_To;
	m_Subject="";

}
string Mail::get_Date() const
{
	return m_Date;
}
string Mail::get_Subject() const
{
	return m_Subject;
}
string Mail::get_Content() const
{
	return m_Content;
}
ostream& operator<<(ostream& os, const Mail& c)
{
	os << c.get_Content() <<endl;
	return os;
}
string* Recived_mail::get_Send_From() const
{
	return m_Send_From;
}
string* Recived_mail::get_Send_To() const
{
	return m_Send_To;
}
string* Sent_mail::get_Send_From() const
{
	return m_Send_From;
}
string* Sent_mail::get_Send_To() const
{
	return m_Send_To;
}

int Mail::get_uniqe_id() const
{
	return Mail_special_num;
}
void  Mail::seralization(ofstream& ofs)
{
	ofs << "Date:" << this->get_Date() << endl;
	seralization_contacts(ofs);
	ofs << "subject:";
	for (int i = 0; i < m_Subject.size(); i++)
	{
		ofs << m_Subject.at(i);
	}
	ofs << endl;
	ofs << "content:";
	for (int i = 0; i < m_Content.size(); i++)
	{
		ofs << m_Content.at(i);
	}
	ofs << endl;
	ofs <<"uniq id:" << this->get_uniqe_id() << endl;
}
void  Mail::seralization_contacts(ofstream& ofs)
{
	ofs << "sent from:";
	int size = this->m_Send_From->size();
	if (recived_peeople > 0)
	{
		for (int i = 0; i < recived_peeople; i++)
		{
			for (int j = 0; j < m_Send_From[i].size(); j++)
			{
				ofs << m_Send_From[i].at(j);
			}
			ofs << ",";
		}
	}
	ofs << endl;
	ofs << "sent to:";
	int size1 = this->m_Send_To->size();
	if (sent_people > 0)
	{
		for (int i = 0; i < sent_people; i++)
		{
			for (int j = 0; j < m_Send_To[i].size(); j++)
			{
				ofs << m_Send_To[i].at(j);
			}
			ofs <<",";
		}
	}
	ofs << endl;
}
void Mail::get_Send_From_print() const
{
	for (int i = 0; i < recived_peeople; i++)
	{
		for (int j = 0; j < m_Send_From[i].size(); j++)
		{
			cout << m_Send_From[i].at(j);
		}
		cout<< ",";
	}
}
