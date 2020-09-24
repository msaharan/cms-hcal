#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream fin1;
	ifstream fin2;
	fin1.open("my25.txt");
	fin2.open("his25.txt");
	ofstream fout;
	fout.open("compare25.txt");
	
	double x1[100], x2[100];
	for(int i=0;i<25;i++)
	{
		fin1>>x1[i]>>junk;
		fin2>>x2[i]>>junk;
		fout<<x1[i]<<"\t"<<x2[i]<<endl;
	}
	cout<<"done\n";
	
	return 0;
}
