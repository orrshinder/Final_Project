#include "Application.h"
#include <time.h>
#include <fstream>
string Application::my_name = "OrrandDenis";
string Application::my_mail = "OrrandDenis@gmail.com";
Application::Application()
{
	Mail_Value = 1;
	m_size_contacts = 0;
	m_top_contacts = 0;
	m_size_folders = 0;
	m_top_folders = 0;
	mail_folders = new Folder * [0];
	mail_contacts = new Contacts * [0];
	string date = __DATE__;
	m_date = date;
	ifstream my_file2;
	my_file2.open("app.text", ios::in);
	if (my_file2.is_open())//checing if the file is open else creating new folders and contacts
	{
		deseralization(my_file2);
		my_file2.close();
	}
	else
	{
		start_mail_check();
	}
	cout << "welcom to email system the mail connected is:" << my_mail << endl;
	main_screen();
	ofstream my_file1;
	my_file1.open("app.text", ios::trunc);
	seralization(my_file1);
	my_file1.close();

}
string Application::get_my_mail()
{
	return my_mail;
}
void Application::start_mail_check()//the basic folders and contact list
{
	if (m_size_contacts == 0)
	{
		Contacts* temp = new Contacts();
		push_contacts(temp);
	}
	mail_contacts[0]->Add(my_name, my_mail);
	if (m_size_folders == 0)
	{
		Folder* temp = new Folder("Inbox");
		push_folder(temp);
		Folder* temp1 = new Folder("Trash");
		push_folder(temp1);
		Folder* temp2 = new Folder("Starred");
		push_folder(temp2);
		Folder* temp3 = new Folder("Drafts");
		push_folder(temp3);
		Folder* temp4 = new Folder("Sent");
		push_folder(temp4);
	}
}
Application::~Application()
{
	for (int i = 0; i < m_size_folders; i++)
	{
		if (mail_folders[i] != nullptr)
		{
			mail_folders[i]->~Folder();
		}
	}
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i] != nullptr)
		{
			mail_contacts[i]->~Contacts();
		}
	}
}
void Application::main_screen()//the main screen of the app
{
	int more_flag = 1;
	string chose_option;
	List("Inbox");
	while (1)
	{
		chose_option = option();
		if (chose_option == "Compose")
		{
			Compose();
		}
		else if (chose_option == "Remove")
		{
			Remove();
		}
		else if (chose_option == "Print")
		{
			Print();
		}
		else if (chose_option == "Move")
		{
			Move();
		}
		else if (chose_option == "More")
		{
			More(more_flag, "Inbox");
			more_flag++;
		}
		else if (chose_option == "List")
		{
			List("Inbox");
		}
		else if (chose_option == "ListDir")
		{
			ListDir();
		}
		else if (chose_option == "RmDir")
		{
			RmDir();
		}
		else if (chose_option == "MkDir")
		{
			MkDir();
		}
		else if (chose_option == "CD")
		{
			CD();
		}
		else if (chose_option == "Contacts")
		{
			contacts();
		}
		else if (chose_option == "search")
		{
			Search();
		}
		else if (chose_option == "Rlist")
		{
			rlist();
		}
		else if (chose_option == "draft complete")
		{
			draft_complete();
		}
		else if (chose_option == "exit")
		{
			cout << "Goodby" << endl;
			break;
		}
		else if (chose_option == "help")
		{
			cout << "Compose: create new email" << endl;
			cout << "Remove: remove email by its uniqe id" << endl;
			cout << "Print: print email content" << endl;
			cout << "Move: moving mail to folder" << endl;
			cout << "More: print next 10 emails" << endl;
			cout << "List: print first 10 emails" << endl;
			cout << "ListDir: print all folders exist" << endl;
			cout << "RmDir: delete folder" << endl;
			cout << "MkDir: create folder" << endl;
			cout << "CD: go to folder" << endl;
			cout << "Contacts: manage contacts" << endl;
			cout << "search: search for a mail" << endl;
			cout << "rlist: contact lists" << endl;
			cout << "draft complete: complete draft mail" << endl;
			cout << "exit" << endl;
		}
		else
		{
			cout << "not valid chiose" << endl;
		}
	}
}
string Application::option()
{
	string option;
	cout << "Choose option:" << endl;
	cout << "Compose" << endl;
	cout << "Remove" << endl;
	cout << "Print" << endl;
	cout << "Move" << endl;
	cout << "More" << endl;
	cout << "List" << endl;
	cout << "ListDir" << endl;
	cout << "RmDir" << endl;
	cout << "MkDir" << endl;
	cout << "CD" << endl;
	cout << "Contacts" << endl;
	cout << "search" << endl;
	cout << "Rlist" << endl;
	cout << "draft complete" << endl;
	cout << "exit" << endl;
	cout << "or write help to disply all options" << endl;
	cout << "enter option:";
	getline(cin, option);
	if (option == "")
	{
		getline(cin, option);
	}
	return option;
}
void Application::Compose()//creating new mail
{
	string date = "";
	string* sent_from;
	string* sent_to = NULL;
	string subject = "";
	string content = "";
	int size_contacts = 0;
	int flag = 0;
	int flag_name = 0;
	while (1)
	{
		string option;
		cout << "Choose option:" << endl;
		cout << "1. Recipient" << endl;
		cout << "2. Subject" << endl;
		cout << "3. Content" << endl;
		cout << "4. Send" << endl;
		cout << "5. Back" << endl;
		cout << "enter option:";
		getline(cin, option);
		if (option == "Recipient")
		{
			for (int i = 0; i < m_size_contacts; i++)
			{
				if (mail_contacts[i]->name_list() == "")
				{
					cout << *mail_contacts[i] << endl;
				}

			}
			for (int i = 0; i < m_size_contacts; i++)
			{
				if (mail_contacts[i]->name_list() != "")
				{
					cout << mail_contacts[i]->name_list() << endl;
				}

			}
			string contact_option;
			vector<string> contact_mail;
			while (1)
			{
				cout << "which contact would you like:";
				getline(cin, contact_option);//can choose a contact or rlist and pusing it to a vactor until stopped
				if (serach_contact(contact_option))
				{
					Contact* temp = find_contact(contact_option);
					contact_mail.push_back(temp->get_address());
					if (temp->get_address() == get_my_mail())
						flag_name = 1;
				}
				else if (serach_rlist(contact_option))
				{
					Contacts* temp = find_rlist(contact_option);
					for (int i = 0; i < temp->size_list(); i++)
					{
						Contact* temp1 = temp->contact_list.at(i);
						contact_mail.push_back(temp1->get_address());
						cout << temp1->get_address() << endl;
						if (temp1->get_address() == get_my_mail())
							flag_name = 1;
					}
				}
				else
				{
					cout << "invalive person" << endl;
				}
				string continue_option;
				cout << "1. add another contact" << endl;
				cout << "2. finish contacts" << endl;
				cout << "3. back" << endl;
				cout << "enter option:";
				getline(cin, continue_option);
				//getline(cin, continue_option);
				if (continue_option == "add another contact")
				{
					continue;
				}
				if (continue_option == "finish contacts")
				{
					break;
				}
				if (continue_option == "back")
				{
					flag = 1;
					break;
				}
				if (continue_option == "help")
				{
					cout << "1. add another contact" << endl;
					cout << "2. finish contacts" << endl;
					cout << "3. back" << endl;
				}
				else
				{
					cout << "invalid option" << endl;
				}
			}
			size_contacts = contact_mail.size();//creating an array in the size of the array
			if (size_contacts > 0)
			{
				sent_to = new string[(size_contacts)];
				if (size_contacts > 1)
				{
					for (int i = 0; i < size_contacts; i++)
					{
						sent_to[(i)] = contact_mail.at(i);
					}
				}
				else
				{
					sent_to[0] = contact_mail.at(0);
				}
			}
			else
			{
				sent_to = new string[1];
				sent_to[0] = "";
			}

		}

		else if (option == "Subject")
		{
			string subject_option;
			cout << "1. add subject" << endl;
			cout << "2. back" << endl;
			cout << "enter option:";
			getline(cin, subject_option);
			if (subject_option == "add subject")
			{
				string test;
				cout << "enter subject:";
				//getline(cin, test);
				getline(cin, subject);
				cout << subject << endl;
			}
			if (subject_option == "back")
			{
				flag = 1;
				break;
			}
		}
		else if (option == "Content")
		{
			string subject_option;
			cout << "1. add content" << endl;
			cout << "2. back" << endl;
			cout << "enter option:";
			getline(cin, subject_option);
			if (subject_option == "add content")
			{
				cout << "enter content:";
				getline(cin, content);
				//getline(cin, content);
			}
			if (subject_option == " back")
			{
				flag = 1;
				break;
			}
		}
		else if (option == "Send")
		{
			if ((size_contacts > 0) && (subject != "") && (content != "") && flag == 0)//if all the fields are full sending the mail
			{
				Folder* temp = find_folder("Sent");
				sent_from = new string[1];
				sent_from[0] = get_my_mail();
				Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, Mail_Value, 1, size_contacts);
				temp->Add_new_mail(temp1);
				Mail_Value++;
				if (flag_name == 1)//if the app mail is shown it also reciving a mail
				{
					Folder* temp2 = find_folder("Inbox");
					sent_from = new string[1];
					sent_from[0] = get_my_mail();
					Recived_mail* temp3 = new Recived_mail(m_date, sent_from, sent_from, subject, content, Mail_Value, 1, size_contacts);
					temp2->Add_new_mail(temp3);
					Mail_Value++;
					flag_name = 0;
				}
				break;
			}
			else//if stopped before all fields copleted moving to draft folder
			{
				Folder* temp = find_folder("Drafts");
				sent_from = new string[1];
				sent_from[0] = get_my_mail();
				Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, Mail_Value, 1, size_contacts);
				temp->Add_new_mail(temp1);
				Mail_Value++;
				break;

			}

		}
		if (flag == 1)
		{
			Folder* temp = find_folder("Drafts");
			sent_from = new string[1];
			sent_from[0] = get_my_mail();
			Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, Mail_Value, 1, size_contacts);
			temp->Add_new_mail(temp1);
			flag = 1;
			Mail_Value++;
			break;
		}
		else if (option == "Back")
		{
			break;
		}
		else if (option == "help")
		{
			cout << "Recipient:contacts for the mail" << endl;
			cout << "Subject:enter subject of the mail" << endl;
			cout << "Content:enter content of mail" << endl;
			cout << "Send:send the mail" << endl;
			cout << "Back" << endl;
		}
		else if ((option != "Recipient") && (option != "Subject") && (option != "Content") && (option != "Send") && (option != "Back"))
		{
			cout << "invalid choise" << endl;
			Compose();
		}
	}
}
void Application::contacts()
{
	string contact_option;
	cout << "1. List" << endl;
	cout << "2. add contact" << endl;
	cout << "3. Remove contact" << endl;
	cout << "4. back " << endl;
	cout << "enter option:";
	getline(cin, contact_option);
	if (contact_option == "")
	{
		getline(cin, contact_option);
	}
	if (contact_option == "List")
	{
		cout << *mail_contacts[0];
	}
	else if (contact_option == "add contact")
	{
		string name = "";
		string address = "";
		cout << "contact name:" << endl;
		cin >> name;
		cout << "contact address:" << endl;
		cin >> address;
		try
		{
			if (!isValid(address))
			{
				throw address;
			}
			else
			{
				mail_contacts[0]->Add(name, address);
			}
		}
		catch (string adress)
		{
			cout << "not valid email" << endl;
			contacts();
		}
	}
	else if (contact_option == "Remove contact")
	{
		string name = "";
		cout << "contact name:" << endl;
		cin >> name;
		if (serach_contact(contact_option))
		{
			Contact* temp = find_contact(contact_option);
			remove_contact(temp);
		}
		else
		{
			cout << "contact not found" << endl;
			contacts();
		}
	}
	else if (contact_option == "back")
	{
	}
	else if (contact_option == "help")
	{
		cout << "List: list of contacts" << endl;
		cout << "add contact" << endl;
		cout << "Remove contact" << endl;
		cout << "back " << endl;
	}
	else
	{
		cout << "option not valid" << endl;
		contacts();
	}
}
void Application::Remove()
{
	string print_option;
	cout << "1. remove mail" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, print_option);
	if (print_option == "remove mail")
	{
		int mail_id = 0;
		cout << "what is the mail id:" << endl;
		cin >> mail_id;
		int flag = 0;
		for (int i = 0; i < m_size_folders; i++)
		{
			for (int j = 0; j < mail_folders[i]->size(); j++)
			{
				Mail* temp = mail_folders[i]->mail_list[j];
				if (temp->get_uniqe_id() == mail_id)//finding the mail by the uniqe id and moving to trash
				{
					Folder* temp1 = find_folder("Trash");
					temp1->Add_new_mail(temp);
					string name = mail_folders[i]->m_name;
					Folder* temp2 = find_folder(name);
					temp2->Remove(temp);
					flag = 1;
					break;
				}

			}
			if (flag == 1)
			{
				break;
			}

		}
		if (flag == 0)
		{
			cout << "mail  do not exict" << endl;
			Remove();
		}

	}
	else if (print_option == "back")
	{
	}
	else if (print_option == "help")
	{
		cout << "1. remove mail" << endl;
		cout << "2. back" << endl;
	}
	else
	{
		cout << "option not valid" << endl;
		Remove();
	}
}
void Application::List(string list_name)
{
	for (int i = 0; i < m_size_folders; i++)
	{
		if (mail_folders[i]->m_name == list_name)
		{
			int size = mail_folders[i]->size();
			if (size > 10)
			{
				for (int k = 0; k < 10; k++)
				{
					Mail* temp = mail_folders[i]->mail_list[k];
					cout << "Date:" << temp->get_Date() << endl;
					cout << "Sent from:";
					temp->get_Send_From_print();
					cout << endl;
					cout << "Subject:" << temp->get_Subject() << endl;
					cout << "Mail id:" << temp->get_uniqe_id() << endl;
					cout << endl;

				}
			}
			else
			{
				for (int k = 0; k < size; k++)//if the folder contain less then  mails print all mails
				{
					Mail* temp = mail_folders[i]->mail_list[k];
					cout << "Date:" << temp->get_Date() << endl;
					cout << "Sent from:";
					temp->get_Send_From_print();
					cout << endl;
					cout << "Subject:" << temp->get_Subject() << endl;
					cout << "Mail id:" << temp->get_uniqe_id() << endl;
					cout << endl;
				}
				cout << "no more mails" << endl;
				break;
			}
		}
	}
}
void Application::Search()
{

	string search_option;
	cout << "1. search mail" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, search_option);
	if (search_option == "")
	{
		getline(cin, search_option);
	}
	if (search_option == "search mail")
	{
		string mail_option;
		cout << "please enter name or subject:";
		getline(cin, mail_option);
		if (mail_option == "")
		{
			getline(cin, mail_option);
		}
		Mail* temp = 0;
		Folder* temp2 = 0;
		string options;
		for (int i = 0; i < m_size_folders; i++)
		{
			int size = mail_folders[i]->size();
			if (mail_folders[i]->size() > 0)
			{
				for (int j = 0; j < mail_folders[i]->size(); j++)
				{
					temp = mail_folders[i]->mail_list[j];

					if (temp->get_Subject() == mail_option || find_contact_in_mail(mail_folders[i]->mail_list[j], mail_option))//chicking if the mail conntain the subject or person
					{
						cout << "Date:" << temp->get_Date() << endl;
						cout << "Sent from:";
						temp->get_Send_From_print();
						cout << endl;
						cout << "Subject:" << temp->get_Subject() << endl;
						temp2 = mail_folders[i];
						cout << *temp << endl;
						cout << "1.star the message" << endl;
						cout << "2.reply" << endl;
						cout << "3.forword message" << endl;
						cout << "4.no change" << endl;
						cout << "enter option:";
						getline(cin, options);
						break;
					}
				}
				if (options == "star the message")
				{
					Folder* temp1 = find_folder("Starred");
					temp1->Add_new_mail(temp);
					temp2->Remove(temp);
					break;
				}
				else if (options == "reply")
				{
					reply_message(temp);
					break;
				}
				else if (options == "forword message")
				{
					forward_mail(temp);
					break;
				}
				else if (options == "no change")
				{
					break;
				}
				else if (options != "no change" && options != "forword message" && options != "reply" && options != "star the message")
				{
					cout << "no option avalable" << endl;
					break;
				}
			}

		}
	}
	else if (search_option == "back")
	{
	}
	else if (search_option == "help")
	{
		cout << "search mail by name or subject" << endl;
		cout << "back" << endl;
	}
	else
	{
		cout << "option not valid" << endl;
		Search();
	}


}
bool Application::find_contact_in_mail(Mail* mail, string name)
{
	if (serach_contact(name))
	{
		Contact* temp = find_contact(name);
		for (int i = 0; i < mail->recived_peeople; i++)
		{
			if (temp->get_address() == mail->get_Send_To()[i])
			{
				return true;
			}
		}
	}
	return false;
}
void Application::Move()
{
	string move_option;
	cout << "1. move mail" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, move_option);
	if (move_option == "")
	{
		getline(cin, move_option);
	}
	if (move_option == "move mail")
	{
		int flag = 0;
		string folder_name = "";
		int mail_id = 0;
		cout << "what is the mail id:" << endl;
		cin >> mail_id;
		cout << "what is the folder to move:" << endl;
		cin >> folder_name;
		if (serach_folder(folder_name))
		{
			int flag_folder = 0;
			Folder* temp2 = find_folder(folder_name);
			Folder* temp1 = 0;
			Mail* temp = 0;
			for (int i = 0; i < m_size_folders; i++)
			{
				for (int j = 0; j < mail_folders[i]->size(); j++)
				{
					temp = mail_folders[i]->mail_list[j];
					if (temp->get_uniqe_id() == mail_id)
					{
						temp1 = find_folder(mail_folders[i]->m_name);
						flag_folder = 1;
						break;
					}
				}
				if (flag_folder == 1)
				{
					break;
				}
			}
			temp2->Add_new_mail(temp);
			temp1->Remove(temp);
		}
		else
		{
			cout << "mail or folder do no exict" << endl;
			Move();
		}
	}
	else if (move_option == "back")
	{
	}
	else if (move_option == "help")
	{
		cout << "move mail to other folder" << endl;
		cout << "go back" << endl;
	}
	else
	{
		cout << "invalid choise" << endl;
		Move();
	}

}
void Application::More(int flag, string folder_name)
{
	for (int i = 0; i < m_size_folders; i++)
	{
		if (mail_folders[i]->m_name == folder_name)
		{
			int folder_size = mail_folders[i]->size();
			if (folder_size >= ((flag + 1) * 10))
			{
				for (int j = 0 + 10 * flag; j < 10 * (flag + 1); j++)
				{
					Mail* temp = mail_folders[i]->mail_list[j];
					cout << "Date:" << temp->get_Date() << endl;
					cout << "Sent from:";
					temp->get_Send_From_print();
					cout << endl;
					cout << "Subject:" << temp->get_Subject() << endl;
					cout << "Uniqe id:" << temp->get_uniqe_id() << endl;
				}
			}
			else
			{
				for (int j = 0 + 10 * flag; j < mail_folders[i]->size(); j++)//if the folder contain less then10mails print all mails
				{
					Mail* temp = mail_folders[i]->mail_list[j];
					cout << "Date:" << temp->get_Date() << endl;
					cout << "Sent from:";
					temp->get_Send_From_print();
					cout << endl;
					cout << "Subject:" << temp->get_Subject() << endl;
					cout << "Uniqe id:" << temp->get_uniqe_id() << endl;
				}
				cout << "no more mails" << endl;
			}

		}
	}
}
void Application::CD()
{
	string move_option;
	cout << "1. enter folder" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, move_option);
	if (move_option == "")
	{
		getline(cin, move_option);
	}

	if (move_option == "enter folder")
	{
		string folder_name = "";
		cout << "what is the folder to enter:" << endl;
		cin >> folder_name;
		if (serach_folder(folder_name))
		{

			while (1)
			{
				Folder* temp = find_folder(folder_name);
				List(temp->m_name);
				string chose_option;
				cout << "1. More" << endl;
				cout << "2. Remove" << endl;
				cout << "3. Print" << endl;
				cout << "4. Move" << endl;
				cout << "5. List" << endl;
				cout << "6. Back" << endl;
				cout << "enter option:";
				getline(cin, chose_option);
				if (chose_option == "")
				{
					getline(cin, chose_option);
				}
				int more_flag = 1;
				if (chose_option == "More")
				{
					More(more_flag, temp->m_name);
					more_flag++;
				}
				if (chose_option == "Remove")
				{
					Remove();
				}
				else if (chose_option == "Print")
				{
					Print();
				}
				else if (chose_option == "Move")
				{
					Move();
				}

				else if (chose_option == "List")
				{
					List(temp->m_name);
				}
				else if (chose_option == "Back")
				{
					break;
				}

				else if (chose_option == "help")
				{
					cout << "Compose: create new email" << endl;
					cout << "Remove: remove email by its uniqe id" << endl;
					cout << "Print: print email content" << endl;
					cout << "Move: moving mail to folder" << endl;
					cout << "More: print next 10 emails" << endl;
					cout << "List: print first 10 emails" << endl;
					cout << "ListDir: print all folders exist" << endl;
					cout << "RmDir: delete folder" << endl;
					cout << "MkDir: create folder" << endl;
					cout << "CD: go to folder" << endl;
					cout << "Contacts: manage contacts" << endl;
					cout << "search: search for a mail" << endl;
					cout << "exit" << endl;

				}
				else if (chose_option != "help" && chose_option != "More" && chose_option != "Remove" && chose_option != "Print" && chose_option != "Move" && chose_option != "List" && chose_option != "Back")
				{
					cout << "not valid chiose" << endl;
					CD();
				}
			}
		}
		else
		{
			cout << "folder do not exist" << endl;
			CD();
		}
	}
	else if (move_option == "back")
	{
	}
}
void Application::MkDir()
{
	string folder_option;
	cout << "1. add folder" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, folder_option);
	if (folder_option == "")
	{
		getline(cin, folder_option);
	}
	if (folder_option == "add folder")
	{
		string folder_name;
		cout << "enter folder name:";
		getline(cin, folder_name);
		if (folder_name == "")
		{
			getline(cin, folder_name);
		}
		if (find_folder(folder_name))
		{
			Folder* temp = new Folder(folder_name);
			push_folder(temp);
		}
		else
		{
			cout << "folder allredy exist" << endl;
			MkDir();
		}
	}
	else if (folder_option == "back")
	{
	}
	else if (folder_option == "help")
	{
		cout << "add mail folder" << endl;
		cout << "back" << endl;
	}
	else
	{
		cout << "invalid choise" << endl;
		MkDir();
	}
}
void Application::RmDir()
{
	string folder_option;
	cout << "1. delete folder" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, folder_option);
	if (folder_option == "")
	{
		getline(cin, folder_option);
	}
	if (folder_option == "delete folder")
	{
		string folder_name;
		cout << "enter folder name:" << endl;
		cin >> folder_name;
		if (folder_name != "Trash" && folder_name != "Starred" && folder_name != "Drafts" && folder_name != "Sent" && folder_name != "Inbox" && find_folder(folder_name))
		{
			Folder* temp = find_folder(folder_name);
			Folder* temp1 = find_folder("Trash");
			for (int i = temp->size() - 1; i >= 0; i--)
			{
				Mail* temp2;
				temp2 = temp->mail_list[i];
				temp->Remove(temp2);
				temp1->Add_new_mail(temp2);
			}
			pop_folder(temp);
		}
		else if (folder_name == "Trash")
		{
			Folder* temp1 = find_folder("Trash");
			for (int i = temp1->size() - 1; i >= 0; i--)
			{
				Mail* temp2;
				temp2 = temp1->mail_list[i];
				temp1->Remove(temp2);
			}
		}
		else if (folder_name == "Starred")
		{
			Folder* temp = find_folder("Starred");
			Folder* temp1 = find_folder("Trash");
			for (int i = temp->size() - 1; i >= 0; i--)
			{
				Mail* temp2;
				temp2 = temp->mail_list[i];
				temp->Remove(temp2);
				temp1->Add_new_mail(temp2);
			}

		}
		else if (folder_name == "Sent")
		{
			Folder* temp = find_folder("Sent");
			Folder* temp1 = find_folder("Trash");
			for (int i = temp->size() - 1; i >= 0; i--)
			{
				Mail* temp2;
				temp2 = temp->mail_list[i];
				temp->Remove(temp2);
				temp1->Add_new_mail(temp2);
			}

		}
		else if (folder_name == "Inbox")
		{
			Folder* temp = find_folder("Inbox");
			Folder* temp1 = find_folder("Trash");
			for (int i = temp->size() - 1; i >= 0; i--)
			{
				Mail* temp2;
				temp2 = temp->mail_list[i];
				temp->Remove(temp2);
				temp1->Add_new_mail(temp2);
			}
		}
		else
		{
			cout << "folder already exist" << endl;
			RmDir();
		}
	}
	else if (folder_option == "back")
	{
	}
	else if (folder_option == "help")
	{
		cout << "delete: delete folder" << endl;
		cout << "back" << endl;
	}
	else
	{
		cout << "invalid choise" << endl;
		RmDir();
	}
}
void Application::ListDir()
{
	for (int i = 0; i < m_size_folders; i++)
	{
		cout << mail_folders[i]->m_name << endl;
	}
}
void Application::Print()
{
	string print_option;
	cout << "1. print mail" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, print_option);
	if (print_option == "")
	{
		getline(cin, print_option);
	}
	if (print_option == "print mail")
	{
		int flag = 0;
		int mail_id = 0;
		cout << "what is the mail id:" << endl;
		cin >> mail_id;
		string mail_option;
		Mail* temp = 0;
		Folder* temp2 = 0;
		for (int i = 0; i < m_size_folders; i++)
		{
			for (int j = 0; j < mail_folders[i]->size(); j++)
			{
				if (mail_folders[i]->size() > 0)
				{
					temp = mail_folders[i]->mail_list[j];
					if (temp->get_uniqe_id() == mail_id)
					{
						temp2 = mail_folders[i];
						cout << *temp << endl;
						cout << "1.star the message" << endl;
						cout << "2.reply" << endl;
						cout << "3.forword message" << endl;
						cout << "4.no change" << endl;
						cout << "enter option:";
						getline(cin, mail_option);
						if (mail_option == "")
						{
							getline(cin, mail_option);
						}
						flag = 1;
						break;
					}
				}

			}
			if (flag == 1)
			{
				break;
			}
		}
		if (mail_option == "star the message")
		{
			Folder* temp1 = find_folder("Starred");
			temp1->Add_new_mail(temp);
			temp2->Remove(temp);
		}
		else if (mail_option == "reply")
		{
			reply_message(temp);
		}
		else if (mail_option == "forword message")
		{
			forward_mail(temp);
		}
		else if (mail_option == "no change")
		{
		}
		else if (mail_option != "star the message" && mail_option == "reply" && mail_option == "forword message" && mail_option == "no change")
		{
			cout << "no option avalable" << endl;
		}
		if (flag == 0)
		{
			cout << "mail does not exict" << endl;
			Print();
		}

	}
	else if (print_option == "back")
	{
	}
	else if (print_option == "help")
	{
		cout << "print mail by mail id" << endl;
		cout << "back" << endl;
	}
	else
	{
		cout << "invalid choise" << endl;
		Print();
	}
}
void Application::forward_mail(Mail* mail)
{
	string date = "";
	string* sent_from = NULL;
	string* sent_to = NULL;
	string subject = "";
	string content = "";
	int flag = 0;
	int flag_name = 0;
	int size_contacts = 0;
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i]->name_list() == "")
		{
			cout << *mail_contacts[i] << endl;
		}

	}
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i]->name_list() != "")
		{
			cout << mail_contacts[i]->name_list() << endl;
		}

	}
	string contact_option;
	vector<string> contact_mail;
	while (1)
	{
		cout << "which contact would you like:" << endl;
		cin >> contact_option;
		if (serach_contact(contact_option))
		{
			Contact* temp = find_contact(contact_option);
			contact_mail.push_back(temp->get_address());
			if (temp->get_address() == get_my_mail())
				flag_name = 1;
		}
		else if (serach_rlist(contact_option))
		{
			Contacts* temp = find_rlist(contact_option);
			for (int i = 0; i < temp->size_list(); i++)
			{
				Contact* temp1 = temp->contact_list.at(i);
				contact_mail.push_back(temp1->get_address());
				cout << temp1->get_address() << endl;
				if (temp1->get_address() == get_my_mail())
					flag_name = 1;
			}
		}
		else
		{
			cout << "invalive person" << endl;
		}
		string continu_option;
		cout << "1. add another contact" << endl;
		cout << "2. finish contacts" << endl;
		cout << "3. back" << endl;
		cout << "enter option:";
		getline(cin, continu_option); 
		getline(cin, continu_option);
		if (continu_option == "add another contact")
		{
			continue;
		}
		if (continu_option == "finish contacts")
		{
			break;
		}
		if (continu_option == "back")
		{
			flag = 1;
			break;
		}
		if (continu_option == "help")
		{
			cout << "1. add another contact" << endl;
			cout << "2. finish contacts" << endl;
			cout << "3. back" << endl;
		}
		else
		{
			cout << "invalid option" << endl;
		}
	}
	size_contacts = contact_mail.size();
	if (size_contacts > 0)
	{
		sent_to = new string[(size_contacts)];
		if (size_contacts > 1)
		{
			for (int i = 0; i < size_contacts; i++)
			{
				sent_to[(i)] = contact_mail.at(i);
			}
		}
		else
		{
			sent_to[0] = contact_mail.at(0);
		}
	}
	else
	{
		sent_to = new string[1];
		sent_to[0] = "";
	}
	subject = mail->get_Subject();
	content = mail->get_Content();
	if ((size_contacts > 0) && (subject != "") && (content != "") && flag == 0)
	{
		Folder* temp = find_folder("Sent");
		sent_from = new string[1];
		sent_from[0] = get_my_mail();
		Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, Mail_Value, 1, size_contacts);
		temp->Add_new_mail(temp1);
		flag = 1;
		if (flag_name == 1)
		{
			Folder* temp2 = find_folder("Inbox");
			sent_from = new string[1];
			sent_from[0] = get_my_mail();
			Recived_mail* temp3 = new Recived_mail(m_date, sent_from, sent_from, subject, content, Mail_Value, 1, size_contacts);
			temp2->Add_new_mail(temp3);
			flag_name = 0;
			flag = 1;
			Mail_Value++;
		}
	}
	else
	{
		Folder* temp = find_folder("Drafts");
		sent_from = new string[1];
		sent_from[0] = get_my_mail();
		Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, Mail_Value, 1, size_contacts);
		temp->Add_new_mail(temp1);
		flag = 1;
		Mail_Value++;

	}
}

void Application::reply_message(Mail* mail)
{
	string date = "";
	string* sent_from = mail->get_Send_From();
	string* sent_to = mail->get_Send_To();
	string subject = mail->get_Subject();
	string content = "";
	int flag = 0;
	int flag_name = 0;
	int size_contacts = 0;
	string subject_option;
	cout << "1. add content" << endl;
	cout << "2. back" << endl;
	cout << "enter option:";
	getline(cin, subject_option);
	if (subject_option == "add content")
	{
		cout << "enter content:";
		getline(cin, content);
		//getline(cin, content);
	}
	if (subject_option == "back")
	{
		flag = 1;
	}
	if (flag == 0)
	{
		Folder* temp = find_folder("Sent");
		sent_from = new string[1];
		sent_from[0] = get_my_mail();
		Sent_mail* temp1 = new Sent_mail(m_date, sent_to, sent_from, subject, content, Mail_Value, mail->sent_people, mail->recived_peeople);
		temp->Add_new_mail(temp1);
		Mail_Value++;
	}
	if (flag == 1)
	{
		Folder* temp = find_folder("Drafts");
		sent_from = new string[1];
		sent_from[0] = get_my_mail();
		Sent_mail* temp1 = new Sent_mail(m_date, sent_to, sent_from, subject, content, Mail_Value, mail->sent_people, mail->recived_peeople);
		temp->Add_new_mail(temp1);
		Mail_Value++;
	}
}
void Application::rlist()
{
	string rlist_option;
	cout << "1. List" << endl;
	cout << "2. Add list" << endl;
	cout << "3. Remove List" << endl;
	cout << "4. Add To list" << endl;
	cout << "5. Remove from list" << endl;
	cout << "6. back " << endl;
	cout << "enter option:";
	getline(cin, rlist_option);
	if (rlist_option == "List")
	{
		for (int i = 0; i < m_size_contacts; i++)
		{
			if (mail_contacts[i]->name_list() != "")
			{
				cout << mail_contacts[i]->name_list() << endl;
			}
		}
	}
	else if (rlist_option == "Add list")
	{
		string rlist_name;
		cout << "enter rlist name:";
		getline(cin, rlist_name);

		if (!serach_rlist(rlist_name))
		{
			Rlist* temp = new Rlist(rlist_name);
			push_contacts(temp);
		}
		else
		{
			cout << "rlist allredy exist" << endl;
			rlist();
		}
	}
	else if (rlist_option == " Remove List")
	{
		string rlist_name1;
		cout << "enter rlist name:" << endl;
		cin >> rlist_name1;
		if (!serach_rlist(rlist_name1))
		{
			Contacts* temp = find_rlist(rlist_name1);
			pop_contacts(temp);
		}
		else
		{
			cout << "rlist not found" << endl;
			rlist();
		}
	}
	else if (rlist_option == "Add To list")
	{
		string rlist_name2;
		cout << "enter rlist name:" << endl;
		cin >> rlist_name2;
		if (serach_rlist(rlist_name2))
		{
			Contacts* temp = find_rlist(rlist_name2);
			string name = "";
			string address = "";
			cout << "contact name:" << endl;
			cin >> name;
			cout << "contact address:" << endl;
			cin >> address;
			try
			{
				if (!isValid(address))
				{
					throw address;
				}
				else
				{
					temp->Add(name, address);
				}
			}
			catch (string adress)
			{
				cout << "not valid email" << endl;
				rlist();
			}
		}
		else
		{
			cout << "rlist not found" << endl;
			rlist();
		}
	}
	else if (rlist_option == "Remove from list")
	{
		string rlist_name2;
		cout << "enter rlist name:" << endl;
		cin >> rlist_name2;
		if (find_rlist(rlist_name2))
		{
			int flag = 0;
			Contacts* temp = find_rlist(rlist_name2);
			string name = "";
			string address = "";
			cout << "contact name:" << endl;
			cin >> name;
			cout << "contact address:" << endl;
			cin >> address;
			try
			{
				if (!isValid(address))
				{
					throw address;
				}
				else
				{
					if (find_contact(name))
					{
						Contact* temp1 = find_contact(name);
						if (temp1->get_address() == address)
						{
							temp->Remove(temp1);
							flag = 1;
						}
						else
						{
							cout << "mail and name do not match" << endl;
							rlist();
						}

					}
				}
			}
			catch (string adress)
			{
				cout << "not valid list" << endl;
				rlist();
			}
			if (flag == 0)
			{
				cout << "contact not found" << endl;
				rlist();
			}
		}
		else
		{
			cout << "rlist not found" << endl;
			rlist();
		}
	}
	else if (rlist_option == "back")
	{
	}
	else if (rlist_option == "help")
	{
		cout << "List: list of contact lists" << endl;
		cout << "Add list" << endl;
		cout << "Remove List" << endl;
		cout << "Add person To list" << endl;
		cout << "Remove person from list" << endl;
		cout << "back " << endl;
	}
	else
	{
		cout << "option not valid" << endl;
		rlist();
	}
}
void Application::seralization(ofstream& ofs)
{
	for (int i = 0; i < m_size_folders; i++)
	{
		mail_folders[i]->seralization(ofs);
	}
	for (int j = 0; j < m_size_contacts; j++)
	{
		mail_contacts[j]->seralization(ofs);
	}
	ofs << "mail value:" << Mail_Value << endl;
}
void Application::deseralization(ifstream& ifs)
{
	string single_line;
	streampos oldpos = ifs.tellg();
	while (getline(ifs, single_line))
	{
		string name = "Folder:";
		if (!single_line.rfind(name))
		{
			size_t pos = single_line.find(" ") + 1;
			string str_line = single_line.substr(pos);
			Folder* temp = new Folder(str_line);
			push_folder(temp);
			oldpos = ifs.tellg();
			getline(ifs, single_line);
			string date = "";
			string* sent_from = NULL;
			string* sent_to = NULL;
			string subject = "";
			string content = "";
			int uniqe_d = 0;
			int size1 = 0;
			int size2 = 0;
			int counter_sent = 0;
			int counter_recive = 0;
			while (single_line.rfind("Folder:") && single_line.rfind("contacts:") && single_line.rfind("contact list:") && single_line.rfind(""))
			{
				/*find the strat of mails in every folder*/
				counter_recive = 0;
				counter_sent = 0;
				size2 = 0;
				size1 = 0;
				uniqe_d = 0;
				content = "";
				subject = "";
				sent_to = NULL;
				sent_from = NULL;
				if (!single_line.rfind("Date:"))
				{
					size_t pos = single_line.find(":");
					date = single_line.substr(pos + 1);
					oldpos = ifs.tellg();
					getline(ifs, single_line);

				}
				if (!single_line.rfind("sent from:"))
				{
					size_t pos = single_line.find(":");
					string sent_from1 = single_line.substr(pos + 1);
					size1 = sent_from1.size();
					for (int i = 0; i < size1; i++)
					{
						if (sent_from1.at(i) == *(","))
						{
							counter_sent++;
						}
					}
					sent_from = new string[counter_sent];
					int place = 0;
					string address_new = sent_from1;
					string adrees1;
					for (int j = 0; j < counter_sent; j++)
					{
						size_t pos = address_new.find(",");
						adrees1 = address_new.substr(0, pos);
						sent_from[place] = adrees1;
						place++;
						if (j < counter_sent)
						{
							address_new = address_new.substr(pos + 1);
						}
					}
					oldpos = ifs.tellg();
					getline(ifs, single_line);
				}
				if (!single_line.rfind("sent to:"))
				{
					size_t pos = single_line.find(":");
					string sent_to1 = single_line.substr(pos + 1);
					size2 = sent_to1.size();
					for (int i = 0; i < size2; i++)
					{
						if (sent_to1.at(i) == *(","))
						{
							counter_recive++;
						}
					}
					sent_to = new string[counter_recive];
					int place = 0;
					string address_new = sent_to1;
					string adrees1;
					for (int j = 0; j < counter_recive; j++)
					{
						size_t pos = address_new.find(",");
						adrees1 = address_new.substr(0, pos);
						address_new = address_new.substr(pos + 1);
						sent_to[place] = adrees1;
						place++;
					}
					oldpos = ifs.tellg();
					getline(ifs, single_line);
				}
				if (!single_line.rfind("subject:"))
				{
					size_t pos = single_line.find(":");
					subject = single_line.substr(pos + 1);
					oldpos = ifs.tellg();
					getline(ifs, single_line);
				}
				if (!single_line.rfind("content:"))
				{
					size_t pos = single_line.find(":");
					content = single_line.substr(pos + 1);
					oldpos = ifs.tellg();
					getline(ifs, single_line);
				}
				if (!single_line.rfind("uniq id:"))
				{
					size_t pos = single_line.find(":");
					uniqe_d = stoi(single_line.substr(pos + 1));
					oldpos = ifs.tellg();
					getline(ifs, single_line);
				}
				int mail_flag = 0;
				if (mail_folders[0]->m_name == "Sent")
				{
					Sent_mail* temp = new Sent_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
				else if (mail_folders[0]->m_name == ("Inbox"))
				{
					Recived_mail* temp = new Recived_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
				else if (mail_folders[0]->m_name == ("Drafts"))
				{
					Sent_mail* temp = new Sent_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
				else if (mail_folders[0]->m_name == ("Starred"))
				{
					Recived_mail* temp = new Recived_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
				else if (mail_folders[0]->m_name == ("Trash"))
				{
					Recived_mail* temp = new Recived_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
				else if (mail_folders[0]->m_name != ("Trash") && mail_folders[0]->m_name != ("Starred") && mail_folders[0]->m_name != ("Drafts") && mail_folders[0]->m_name != ("Inbox") && mail_folders[0]->m_name != ("Sent"))
				{
					Sent_mail* temp = new Sent_mail(date, sent_from, sent_to, subject, content, uniqe_d, 1, counter_recive);
					mail_folders[0]->push_back(temp);
				}
			}
			ifs.seekg(oldpos);
		}
		if (!single_line.rfind("contacts:"))
		{
			/*find contact list*/
			Contacts* temp = new Contacts();
			push_contacts(temp);
			oldpos = ifs.tellg();
			getline(ifs, single_line);
			if (!single_line.rfind("contacts:"))
			{
				getline(ifs, single_line);
			}
			string* temp1 = &single_line;
			while (single_line.rfind("Folder:") && single_line.rfind("contact list:") && single_line.rfind("mail value:"))
			{
				string name = "";
				string address = "";
				int counter = 0;
				size_t pos = single_line.find(",");
				name = single_line.substr(0, pos);
				address = single_line.substr(pos + 1);
				mail_contacts[0]->Add(name, address);
				oldpos = ifs.tellg();
				getline(ifs, single_line);
			}
			ifs.seekg(oldpos);
		}
		if (!single_line.rfind("contact list:"))
		{
			/*find rlist and name*/
			size_t pos = single_line.find(":");
			string str_line = single_line.substr(pos + 1);
			Rlist* temp = new Rlist(str_line);
			push_contacts(temp);
			getline(ifs, single_line);
			if (!single_line.rfind("contact list:"))
			{
				getline(ifs, single_line);
			}
			while (single_line.compare("Folder:") && single_line.rfind("contacts:") && single_line.rfind("mail value:") && single_line.rfind("contact list:"))
			{
				string name = "";
				string address = "";
				int counter = 0;
				size_t pos = single_line.find(",");
				name = single_line.substr(0, pos);
				address = single_line.substr(pos + 1);
				mail_contacts[0]->Add(name, address);
				oldpos = ifs.tellg();
				getline(ifs, single_line);
			}

			ifs.seekg(oldpos);
		}
		if (!single_line.rfind("mail value:", 0))
		{
			size_t pos = single_line.find(":") + 1;
			string str_line = single_line.substr(pos);
			Mail_Value = stoi(single_line.substr(pos));
			break;
		}
	}
}
bool  Application::serach_contact(string name)
{
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i]->name_list() == "")
		{
			if (mail_contacts[i]->contact_exsit(name))
			{
				return true;
			}
		}
	}
	return false;
}
bool  Application::serach_rlist(string name)
{
	if (m_size_contacts > 1)
	{
		for (int i = 0; i < m_size_contacts; i++)
		{
			if (mail_contacts[i]->name_list() == name)
			{
				return true;
			}
		}
	}
	return false;
}
Contact* Application::find_contact(string name)
{
	Contact* temp;
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i]->name_list() == "")
		{
			temp = mail_contacts[i]->find_contact(name);
			return temp;
		}
	}

}
Contacts* Application::find_rlist(string name)
{
	if (m_size_contacts > 1)
	{
		for (int i = 0; i < m_size_contacts; i++)
		{
			if (mail_contacts[i]->name_list() == name)
			{
				return mail_contacts[i];
			}
		}
	}
}
void Application::remove_contact(Contact* c)
{
	for (int i = 0; i < m_size_contacts; i++)
	{
		if (mail_contacts[i]->contact_exsit(c->get_name()))
		{
			mail_contacts[i]->Remove(c);
		}
	}
}
Folder* Application::find_folder(string name)
{
	for (int i = 0; i < m_size_folders; i++)
	{
		if (mail_folders[i]->m_name == name)
		{
			return mail_folders[i];
		}
	}
}
bool Application::serach_folder(string name)
{
	for (int i = 0; i < m_size_folders; i++)
	{
		if (mail_folders[i]->m_name == name)
		{
			return true;
		}
	}
	return false;
}
void Application::push_folder(Folder* c)
{
	if (!folder_isFull())
	{
		if (folder_isEmpty())
		{
			mail_folders[0] = c;
			m_top_folders++;
		}
		else
		{
			Folder** temp = new Folder * [m_size_folders];
			for (int i = 0; i < m_size_folders; i++) {
				temp[i] = mail_folders[i];
			}
			for (int i = 0; i < m_size_folders; i++) {
				mail_folders[i + 1] = temp[i];
			}
			mail_folders[0] = (c);
			m_top_folders++;
		}
	}
	else
	{
		Folder** temp = new Folder * [m_size_folders];
		for (int i = 0; i < m_size_folders; i++) {
			temp[i] = (mail_folders[i]);
		}
		mail_folders = new  Folder * [m_size_folders + 1];;
		for (int j = 0; j < m_size_folders; j++) {
			mail_folders[j + 1] = temp[j];
		}
		mail_folders[0] = c;
		m_size_folders++;
		m_top_folders++;
	}
}
void Application::push_contacts(Contacts* c)
{
	if (!contacts_isFull())
	{
		if (contacts_isEmpty())
		{
			mail_contacts[0] = c;
			m_top_contacts++;
		}
		else
		{
			Contacts** temp = new Contacts * [m_size_folders];
			for (int i = 0; i < m_size_folders; i++) {
				temp[i] = mail_contacts[i];
			}
			for (int i = 0; i < m_size_folders; i++) {
				mail_contacts[i + 1] = temp[i];
			}
			mail_contacts[0] = (c);
			m_top_contacts++;
		}
	}
	else
	{
		Contacts** temp = new Contacts * [m_size_contacts];
		for (int i = 0; i < m_size_contacts; i++) {
			temp[i] = (mail_contacts[i]);
		}
		mail_contacts = new  Contacts * [m_size_contacts + 1];;
		for (int j = 0; j < m_size_contacts; j++) {
			mail_contacts[j + 1] = temp[j];
		}
		mail_contacts[0] = c;
		m_size_contacts++;
		m_top_contacts++;
	}
}
void Application::pop_contacts(Contacts* folder)
{
	unsigned index = 0;
	if (contacts_isEmpty())
	{
		cout << "contacts nothing to pop." << endl;
	}
	else
	{
		for (int i = 0; i < m_size_folders; i++)
		{
			if (mail_contacts[i] == folder)
			{
				index = i;

				break;
			}
		}
		for (unsigned j = index; j < m_size_folders; j++)
		{
			mail_contacts[j] = mail_contacts[j + 1];
		}
		m_size_contacts--;
		m_top_contacts--;
	}
}
void Application::pop_folder(Folder* folder)
{
	unsigned index = 0;
	if (folder_isEmpty())
	{
		cout << "folder nothing to delete." << endl;
	}
	else
	{
		for (int i = 0; i < m_size_folders; i++)
		{
			if (mail_folders[i] == folder)
			{
				index = i;
				break;
			}
		}
		for (unsigned j = index; j < m_size_folders; j++)
		{
			mail_folders[j] = mail_folders[j + 1];
		}
		m_size_folders--;
		m_top_folders--;
	}
}
bool Application::folder_isFull() const
{
	return m_size_folders == m_top_folders;
}
bool Application::folder_isEmpty()
{
	return m_size_folders == 0;
}
unsigned Application::folder_size()const
{
	return m_size_folders;
}
bool Application::contacts_isFull() const
{
	return  m_size_contacts == m_top_contacts;
}
bool Application::contacts_isEmpty()
{
	return m_size_contacts == 0;
}
unsigned Application::contacts_size()const
{
	return m_size_contacts;
}
bool Application::isValid(const string& email)
{
	// Regular expression definition
	const regex pattern(
		"(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	// Match the string pattern
	// with regular expression
	return regex_match(email, pattern);
}
void Application::draft_complete()
{
	Folder* temp = find_folder("Drafts");
	List("Drafts");
	string chose_option;
	cout << "1. More" << endl;
	cout << "2. complete" << endl;
	cout << "3. Back" << endl;
	cout << "enter option:";
	getline(cin, chose_option);
	int more_flag = 1;
	if (chose_option == "More")
	{
		More(more_flag, temp->m_name);
		more_flag++;
	}
	if (chose_option == "complete")
	{
		string print_option;
		cout << "1. Complete mail" << endl;
		cout << "2. Back" << endl;
		cout << "enter option:";
		getline(cin, print_option);
		if (print_option == "Complete mail")
		{
			int mail_id = 0;
			cout << "what is the mail id:" << endl;
			cin >> mail_id;
			int flag = 0;
			Mail* temp1 = 0;
			string date = "";
			string* sent_from = NULL;
			string* sent_to = NULL;
			string subject = "";
			string content = "";
			for (int j = 0; j < temp->size(); j++)
			{
				temp1 = temp->mail_list[j];
				if (temp1->get_uniqe_id() == mail_id)
				{
					sent_from = temp1->get_Send_From();
					sent_to = temp1->get_Send_To();
					subject = temp1->get_Subject();
					content = temp1->get_Content();
					int flag = 0;
					int flag_name = 0;
					int size_contacts = 0;
					size_contacts = temp1->sent_people;
					int complete_draft_mail_id = temp1->get_uniqe_id();
					vector<string> contact_mail;
					string contact_option;
					if (sent_from == NULL)
					{
					}
					if (sent_to == NULL)//if didnt finish sent to complete the contacts
					{
						cout << "complete contact list to send" << endl;
						while (1)
						{
							cout << "which contact would you like:" << endl;
							cin >> contact_option;
							if (serach_contact(contact_option))
							{
								Contact* temp = find_contact(contact_option);
								contact_mail.push_back(temp->get_address());
								if (temp->get_address() == get_my_mail())
									flag_name = 1;
							}
							else if (serach_rlist(contact_option))
							{
								Contacts* temp = find_rlist(contact_option);
								for (int i = 0; i < temp->size_list(); i++)
								{
									Contact* temp1 = temp->contact_list.at(i);
									contact_mail.push_back(temp1->get_address());
									cout << temp1->get_address() << endl;
									if (temp1->get_address() == get_my_mail())
										flag_name = 1;
								}
							}
							else
							{
								cout << "invalive person" << endl;
							}
							string continu_option;
							cout << "1. add another contact" << endl;
							cout << "2. finish contacts" << endl;
							cout << "3. back" << endl;
							cout << "enter option:";
							getline(cin, continu_option);
							if (continu_option == "add another contact")
							{
								continue;
							}
							if (continu_option == "finish contacts")
							{
								break;
							}
							if (continu_option == "back")
							{
								flag = 1;
								break;
							}
							if (continu_option == "help")
							{
								cout << "1. add another contact" << endl;
								cout << "2. finish contacts" << endl;
								cout << "3. back" << endl;
							}
							else
							{
								cout << "invalid option" << endl;
							}
						}
						size_contacts = contact_mail.size();
						if (size_contacts > 0)
						{
							sent_to = new string[(size_contacts)];
							if (size_contacts > 1)
							{
								for (int i = 0; i < size_contacts; i++)
								{
									sent_to[(i)] = contact_mail.at(i);
								}
							}
							else
							{
								sent_to[0] = contact_mail.at(0);
							}
						}
						else
						{
							sent_to = new string[1];
							sent_to[0] = "";
						}
					}
					if (subject == "")//if didnt finish sent to complete the subject
					{
						string test;
						cout << "complete subject:";
						getline(cin, test);
						getline(cin, subject);
					}
					if (content == "")//if didnt finish sent to complete the content
					{
						string test;
						cout << "complete content:";
						getline(cin, test);
						getline(cin, content);
					}

					if ((size_contacts > 0) && (subject != "") && (content != "") && flag == 0)
					{
						Folder* temp = find_folder("Sent");
						sent_from = new string[1];
						sent_from[0] = get_my_mail();
						Sent_mail* temp1 = new Sent_mail(m_date, sent_from, sent_to, subject, content, complete_draft_mail_id, 1, size_contacts);
						temp->Add_new_mail(temp1);
						flag = 1;
						if (flag_name == 1)
						{
							Folder* temp2 = find_folder("Inbox");
							sent_from = new string[1];
							sent_from[0] = get_my_mail();
							Recived_mail* temp3 = new Recived_mail(m_date, sent_from, sent_from, subject, content, Mail_Value, 1, size_contacts);
							temp2->Add_new_mail(temp3);
							flag_name = 0;
							flag = 1;
							Mail_Value++;
						}
						Folder* temp4 = find_folder("Drafts");
						temp4->Remove(temp1);
					}
					else
					{
						Folder* temp3 = find_folder("Drafts");
						sent_from = new string[1];
						sent_from[0] = get_my_mail();
						Sent_mail* temp4 = new Sent_mail(m_date, sent_from, sent_to, subject, content, complete_draft_mail_id, 1, size_contacts);
						temp3->Add_new_mail(temp4);
						flag = 1;
					}
					break;
				}
			}

		}
	}
	else if (chose_option == "Back")
	{
	}
	else if (chose_option == "help")
	{
		cout << "complete draft and send it" << endl;
	}
	else
	{
		cout << "not valid chiose" << endl;
		draft_complete();
	}
}
