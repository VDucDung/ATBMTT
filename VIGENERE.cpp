#include<bits/stdc++.h>
using namespace std;
string GiaiMa(string x, string k)
{
	string C = "";
	int i=0; int j=0;
	do
	{
		if(j==k.length()) j=0;
		if(isupper(x[i]) && isupper(k[j]) ) C += char (65 + int( (x[i]-k[j])%26 + 26)%26);
		else
		{
			if(isupper(x[i])) C += char (65 + int( (x[i]-k[j] - 65 + 97)%26 + 26)%26);
			else if(isupper(k[j])) C += char (97 + int( (x[i]-k[j] - 97 + 65)%26 + 26)%26);
			else C += char (97 + int( (x[i]-k[j] )%26 + 26)%26);
	    }
	    i++; j++;
	} while(i<x.length());
	return C;
}
string MaHoa(string x, string k)
{
	string P = "";
	int i=0; int j=0;
	do
	{
		if(j==k.length()) j=0;
		if(isupper(x[i]) && isupper(k[j]) ) P +=char (65 + int(x[i]+k[j]-2*65)%26);
		else
		{
			if(isupper(x[i])) P += char (65 + int(x[i]+k[j] - 65 - 97)%26);
			else if(isupper(k[j])) P += char (97 + int(x[i]+k[j] - 97 - 65)%26);
			else P += char (97 + int(x[i]+k[j] - 2*97)%26);
		}
		i++; j++;
	} while(i<x.length());
	return P;
}
int main()
{
	string x; string k; int chose;
	bool ktra=true;
	do
	{
		cout<<"Menu:               1.Ma hoa                2.Giai ma                3.Exit\n==============================================================================================\n";
		cout<<"Lua chon thuc hien: "; cin>>chose;
		switch(chose)
		{
			case 1:
				cout<<"Nhap xau can ma hoa: "; cin>>x;
				cout<<"Nhap KEY: "; cin>>k;
				cout<<"Xau sau khi ma hoa co dang: "<<MaHoa(x,k)<<endl;
				break;
			case 2:
				cout<<"Nhap xau can gia ma: "; cin>>x;
				cout<<"Nhap KEY: "; cin>>k;
				cout<<"Xau sau khi giai ma co dang: "<<GiaiMa(x,k)<<endl;
				break;
			case 3: ktra=false;
			cout<<"==================EXIT================="; break;
			default: cout<<"Thuc hien lai thao tac!!!!"<<endl; 
			break;
		}
	} while(ktra==true);
	
  return (0);
}

