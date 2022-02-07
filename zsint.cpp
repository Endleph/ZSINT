#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <Windows.h>
#include <cstdio>
#include "TextTable.h"

/*
This is a simple cpp osint software 
which uses a lot of api.
I'm a beginner so please be indulgent
Discord: ZELEPH#1225
Discord Server: https://discord.gg/BYEusTEqWA
*/

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//bssid (mac) lookup
void bssid(std::string bssid) {
	cpr::Response r = cpr::Get(cpr::Url{ "https://api.mylnikov.org/wifi?v=1.1&bssid=" + bssid }); 
	boost::replace_all(r.text, ",", ",\n");
	SetConsoleTextAttribute(hConsole, 9);
	std::cout << "\n" + r.text + "\n";
	SetConsoleTextAttribute(hConsole, 15);
}

//phone lookup
void phone(std::string nphone) {
	cpr::Response r = cpr::Get(cpr::Url{ "https://www.infos-numero.com/ajax/NumberInfo?num=" + nphone });
	boost::replace_all(r.text, ",", ",\n");
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "\n" + r.text + "\n";
	SetConsoleTextAttribute(hConsole, 15);

}


//ip lookup
void lkip(std::string ip) {

	cpr::Response r = cpr::Get(cpr::Url{ "https://ipapi.co/" + ip + "/json/"});
	boost::replace_all(r.text, ",", ",\n");
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "\n" + r.text + "\n";
	SetConsoleTextAttribute(hConsole, 15);


}

//chack if a url with username is valid
void ss(std::string url, std::string username) {
	cpr::Response r = cpr::Get(cpr::Url{ url + username });

	//get status requette 200 is valid
	if (r.status_code == 200)  { 
		std::cout << "valid -> " << r.url << std::endl;
	}

	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "invalid -> " << r.url << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

}

//search username with ss()
void searchf(std::string username) {
	ss("https://www.instagram.com/", username);
	ss("https://www.facebook.com/", username);
	ss("https://www.twitch.tv/", username);
	ss("https://twitter.com/", username);
	ss("https://xhamster.com/users/", username);
	ss("https://pr0gramm.com/user/", username);
	ss("https://www.npmjs.com/~", username);
	ss("https://note.com/", username);
	ss("http://www.authorstream.com/", username);
	ss("https://youporn.com/uservids/", username);
	ss("https://youpic.com/photographer/", username);
	ss("https://xvideos.com/profiles/", username);
	ss("https://www.virustotal.com/ui/users/", username);
	ss("https://vimeo.com/", username);
	ss("https://tryhackme.com/p/", username);
	ss("https://tenor.com/users/", username);
	ss("https://open.spotify.com/user/", username);
	ss("https://sourceforge.net/u/", username);
	ss("https://soundcloud.com/", username);
	ss("https://www.smule.com/", username);
	ss("https://scratch.mit.edu/users/", username);
	ss("https://replit.com/@", username);
	ss("https://raidforums.com/User-", username);
	ss("https://pypi.org/user/", username);
	ss("https://pornhub.com/users/", username);
	ss("https://www.pinterest.com/", username);
	ss("https://onlyfans.com/", username);
	ss("https://imgur.com/user/", username);
	ss("https://forum.hackthebox.eu/profile/", username);
	ss("https://www.github.com/", username);

}

//generate and check e-mail adresse
void fmail(std::string pren, std::string name) {
	std::cout << "" << std::endl;

	std::string gmail = name + "." + pren + "@gmail.com";
	std::string gmailb = pren + "." + name + "@gmail.com";
	std::string orange = name + "." + pren + "@orange.fr";
	std::string orangeb = pren + "." + name + "@orange.fr";

	auto gdata = cpr::Get(cpr::Url{ "https://isitarealemail.com/api/email/validate?email=" + gmail });
	auto gbdata = cpr::Get(cpr::Url{ "https://isitarealemail.com/api/email/validate?email=" + gmailb });
	auto ordata = cpr::Get(cpr::Url{ "https://isitarealemail.com/api/email/validate?email=" + orange });
	auto orbdata = cpr::Get(cpr::Url{ "https://isitarealemail.com/api/email/validate?email=" + orangeb });


	//create table  +-----+
	TextTable t('-', '|', '+');

	t.add("EMAIL");
	t.add("RESULT");
	t.endOfRow();

	t.add(gmail);
	t.add(gdata.text);
	t.endOfRow();

	t.add(gmailb);
	t.add(gbdata.text);
	t.endOfRow();

	t.add(orange);
	t.add(ordata.text);
	t.endOfRow();

	t.add(orangeb);
	t.add(orbdata.text);
	t.endOfRow();

	t.setAlignment(2, TextTable::Alignment::RIGHT);

	SetConsoleTextAttribute(hConsole, 14);
	std::cout << t << std::endl;
	SetConsoleTextAttribute(hConsole, 15);

}

//search number in .txt files
void searchtel() {
	std::string myText;
	std::ifstream MyReadFile("search.txt");

	std::string search = "colBtn";


	while (getline(MyReadFile, myText)) {

		if (myText.find(search) != std::string::npos) {
			boost::replace_all(myText, "&nbsp;", ".");
			boost::replace_all(myText, " ", "");
			boost::replace_all(myText, "<span>Appeler</span></a>", "");
			boost::replace_all(myText, ">", "");
			boost::replace_all(myText, "<", "");
			boost::replace_all(myText, "aclass=", "");
			boost::replace_all(myText, "colBtn", "");
			boost::replace_all(myText, "href=", "");

			SetConsoleOutputCP(CP_UTF8);

			
			setvbuf(stdout, nullptr, _IOFBF, 1000);


			TextTable t('-', '|', '+');

			t.add("PHONE NUMBER");
			t.endOfRow();

			t.add(myText);
			t.endOfRow();

			t.setAlignment(1, TextTable::Alignment::RIGHT);
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << t << std::endl;
			SetConsoleTextAttribute(hConsole, 15);




		}
	}
	MyReadFile.close();


}


//search in .txt file
void searchadd() {
	std::string myText;
	std::ifstream MyReadFile("search.txt");

	std::string search = "<br/>";


	while (getline(MyReadFile, myText)) {

		if (myText.find(search) != std::string::npos) {

			boost::replace_all(myText, "<br/>", "");
			boost::replace_all(myText, "  ", "");
			SetConsoleOutputCP(CP_UTF8);

			// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
			setvbuf(stdout, nullptr, _IOFBF, 1000);

			TextTable t('-', '|', '+');

			t.add("ADRESSE");
			t.endOfRow();

			t.add(myText);
			t.endOfRow();

			t.setAlignment(1, TextTable::Alignment::RIGHT);
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << t << std::endl;
			SetConsoleTextAttribute(hConsole, 15);


		}
	}
	MyReadFile.close();



}

//shearch person with firstname & last name
void PersonLookup(std::string fname, std::string lname) {

	auto data = cpr::Get(cpr::Url{ "https://www.annuaire-inverse.mobi/pro/search?q=" + fname + "+" + lname });

	std::ofstream myfile;
	myfile.open("search.txt");
	myfile << data.text;
	myfile.close();
	searchtel();
	searchadd();
	fmail(fname, lname);

}

//main program
int main(int argc, char* argv[]) {
	

	std::string choice = argv[1];


	//check arguments
	if (choice == "plookup") {
		PersonLookup(argv[2], argv[3]);
	}

	else if (choice == "ulookup") {
		searchf(argv[2]);

	}

	else if (choice == "iplookup") {
		lkip(argv[2]);
	}

	else if (choice == "maclookup") {
		bssid(argv[2]);
	}

	else if (choice == "phonelookup") {
		phone(argv[2]);
	}

	else if (choice == "help") {
		SetConsoleTextAttribute(hConsole, 9);
		std::cout << "ZSINT by ZELEPH#1225\nCOMMANDS:" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "\t-> help (view all commands)\n\t-> plookup <firstname> <lastname> (search phone and adresse by name)\n\t-> ulookup <username> (shearch account by username)\n\t-> iplookup <ip> (search information by ip)\n\t-> maclookup <mac/bssid> (localize mac or bssid adress if it is in the database)\n\t-> phonelookup <number> (get country,service,type)" << std::endl;
	}

	//invalid command
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "<- invalid command ->\n" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		SetConsoleTextAttribute(hConsole, 9);
		std::cout << "ZSINT by ZELEPH#1225\nCOMMANDS:" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "\t->help(view all commands)\n\t->plookup <firstname> <lastname> (search phone and adresse by name)\n\t->ulookup <username>(shearch account by username)\n\t->iplookup <ip>(search information by ip)\n\t-> maclookup <mac/bssid> (localize mac or bssid adress if it is in the database)\n\t-> phonelookup <number> (get country,service,type)" << std::endl;

	}

}
