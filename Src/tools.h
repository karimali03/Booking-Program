
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include<fstream>
#include <iostream>
#include <ctime>
#include<vector>
using namespace std;


#ifndef TOOLS_H
#define TOOLS_H

vector<string>flights_companies;
vector<string>Hotels_names;

pair<int,pair<int,int>>getDate(){
  time_t t = std::time(nullptr);
  tm *const pTInfo = std::localtime(&t);
  return {pTInfo->tm_mday ,{pTInfo->tm_mon+1,pTInfo->tm_year+1900}};
}

string ReadDate(string header=""){
	while(1){
		int d,m,y;
		if(header.size()) cout<<header<<"\n";
		cout<<"Please enter day && month && year (ex:25 3 2022): ";
		cin>>d>>m>>y;
		if(d<1 || d>31 || m<1 || m>12 || y<1){
			cout<<"Invalid Date try again\n\n";
			continue;
		}
		pair<int,pair<int,int>> date=getDate();
		if(y<date.second.second || y==date.second.second && m<date.second.first
		|| y==date.second.second && m==date.second.first && d<date.first ){
			cout<<date.first<<" "<<date.second.first<<" "<<date.second.second<<"\n";
			cout<<"Invalid Date try again\n\n";
			continue;
		}
		string s=to_string(d);
		s+="-";
		s+=to_string(m);
		s+="-";
		s+=to_string(y); 
		return s;
	}
	return {};
}

int ReadInt(int low, int high, bool cancel_choice_allowed = false) {
	
	while(1){
     if(!cancel_choice_allowed)
		cout << "\nEnter number in range " << low << " - " << high << ": ";
	else
		cout << "\nEnter -1 to cancel or number in range " << low << " - " << high << ": ";
        int ch; cin>>ch;
        if(ch==-1 && cancel_choice_allowed ) return -1;
        if(ch >=low && ch<=high ) return ch;
        cout<<"Please Enter a valid number\n\n";
    }
}

int ShowReadMenu(const vector<string> &choices, string header="",string ending="") {	// Added parameter. Respect backward compatibility
	if(!header.empty()) cout << "\n"<<header<<":\n";
	for (int ch = 0; ch < (int) choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
    if(!ending.empty()) cout<<"\n"<<ending<<":\n";
	return ReadInt(1, choices.size());
}

string GetCurrentTimeDate() {	// src: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

vector<string> ReadFileLines(const string &path) {
	vector<string> lines;

	fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}

void WriteFileLines(const string &path, const vector<string> &lines, bool append = true) {
	auto status = ios::in | ios::out | ios::app;

	if (!append)
		status = ios::in | ios::out | ios::trunc;	// overwrite

	fstream file_handler(path.c_str(), status);

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return;
	}
	for (const auto &line : lines)
		file_handler << line << "\n";

	file_handler.close();
}

vector<string> SplitString(const string &str, const string &delimiter = ",") {
	string s = str;
	vector<string> strs;

	int pos = 0;
	string substr;
	while ((pos = (int) s.find(delimiter)) != -1) {
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimiter.length());
	}
	strs.push_back(s);
	return strs;
}


void load_data(){
	vector<string>paths=ReadFileLines("Hotels.txt");
	// Hotels
	for(auto & x : paths)   Hotels_names.push_back(x);
	// airways companies
	paths=ReadFileLines("airways.txt");
	for(auto & x : paths)  	flights_companies.push_back(x);
		
}

#endif 
