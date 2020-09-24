#include<iostream>
#include<math.h>

using namespace std;

double photon_absorption_length(float A, int Z)
{
	double length;
	length = A / ( pow(Z,2) * 1.396 * pow(10,-3) * (((7*log(183/pow(Z,0.3333))/9)- (1/54))));
	return length;
}

int main()
{
	float A;
	int Z;
	int response;
	
	do
	{
		cout<<"Enter the atomic number of the target element. \n";
		cin>>Z;
	
		cout<<"\nEnter the atomic weight of the target element. \n";
		cin>>A;
	
		cout<<"The photon absorption length in the material is "<<photon_absorption_length(A,Z)<<endl;
		
		cout<<"Press 1 to calculate again, press 0  to exit.\n";
		cin>>response;
		
		if(response == 0 && response != 1)
		{
			break;
		}
	}
	while(response = 1);
	{
		cout<<endl;
	}
return 0;
}

