#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

vector<string> split(string s); // Cat chuoi

int convert(string s); // Chuyen tu string sang int

int heSoMien(string s); // Tra ve he so mien

bool checkTime(string time); //Kiem tra thoi gian

class khachhang{
public:
	string name;
	string sdt;
	khachhang(string name,string sdt){
		this->name = name;
		this->sdt = sdt;
	}
};
class cuocgoi{
public:
	string sdt;
	int phut;
	string started;
	string day;
	string area;
	cuocgoi(string sdt,int phut,string started,string day,string area){
		this->sdt = sdt;
		this->phut = phut;
		this->started = started;
		this->day = day;
		this->area = area;
	}
};

int main(){
	vector<khachhang> khs;
	ifstream kh;
	kh.open("khachhang.txt");
	if(kh.is_open()){
		while(!kh.eof()){
			string t;
			getline(kh,t);
			vector<string> out = split(t);
			khs.push_back(khachhang(out[0],out[1]));
		}
	}
	else{
		cout<<"File khachhang.txt cannot open!!";
	}
	
	vector<cuocgoi> cgs;
	ifstream cg;
	cg.open("cuocgoi.txt");
	if(cg.is_open()){
		while(!cg.eof()){
			string t;
			getline(cg,t);
			vector<string> out = split(t);
			cgs.push_back(cuocgoi(out[0],convert(out[1]),out[2],out[3],out[4]));
		}
	}
	else{
		cout<<"File cuocgoi.txt cannot open!!";
	}
	
	ofstream kq("ketqua.txt");
	if(kq.is_open()){
		for(int i=0;i<khs.size();i++){
			int countNH = 0;
			int countLC = 0;
			int countX = 0;
			int countRX = 0;
			float tien = 0;
			for(int j=0;j<cgs.size();j++){
				if(khs[i].sdt == cgs[j].sdt){
					if(cgs[j].area[0] == 'N'){
						countNH++;
					}
					if(cgs[j].area[0] == 'L'){
						countLC++;
					}
					if(cgs[j].area[0] == 'X'){
						countX++;
					}
					if(cgs[j].area[0] == 'R'){
						countRX++;
					}
					if(checkTime(cgs[j].started)){
					tien += 1100 * cgs[j].phut * heSoMien(cgs[j].area)*0.7*1.0;
					}
					else{
						tien += 1100 * cgs[j].phut * heSoMien(cgs[j].area);
					}
				}
				
			}
			kq<<khs[i].name<<"; "<<khs[i].sdt<<"; "<<tien<<"; "
				<<countNH<<"; "<<countLC<<"; "<<countX<<"; "<<countRX<<endl;
			cout<<khs[i].name<<"; "<<khs[i].sdt<<"; "<<tien<<"; "
				<<countNH<<"; "<<countLC<<"; "<<countX<<"; "<<countRX<<endl;				
		}
	}
	else{
		cout<<"File Ketqua.txt cannot open!!";
	}
}


// Cat chuoi
vector<string> split(string s){
	vector<string> ans;
	int leftIndex = 0;
	while(leftIndex<s.length()){
		int i = leftIndex;
		while(s[i]!=';' && i<s.length()){
			i++;
		}
		string sub = s.substr(leftIndex,i-leftIndex);
		ans.push_back(sub);
		leftIndex = i+2;
	}
	return ans;
}
// Chuyen tu string sang int
int convert(string s){
	stringstream ss;
	ss<<s;
	int ans;
	ss>>ans;
	return ans;
}
int heSoMien(string s){
	if(s[0]=='N'){
		return 1;
	}
	else if(s[0]=='L'){
		return 2;
	}
	else if(s[0]=='X'){
		return 3;
	}
	else if(s[0]=='R'){
		return 4;
	}
}
bool checkTime(string time){
	int hour;
	string minute;
	stringstream ss;
	int index = 0;
	for(int i=0;i<time.length();i++){
		if(time[i]=='h'){
			index = i;
			break;
		}
	}
	ss<<time.substr(0,index)<<" "<<time.substr(index+1,time.length()-1-index);
	ss>>hour>>minute;
	if(hour>=23|| hour<5 || (hour == 5 && minute[0] == '0' && minute[1] == '0')){
		return true;
	}
	else return false;
}

