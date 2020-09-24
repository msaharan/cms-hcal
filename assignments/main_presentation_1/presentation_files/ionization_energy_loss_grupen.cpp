#include<iostream>
#include<math.h>

using namespace std;

float ionization_loss(int Z, float A, float rho)
{
	float loss;
	
	loss = 0.3071 * (Z/A) * (log (0.2894/pow(Z,0.9)) - 8.1633 - log(1.8 * sqrt(rho*Z/A) / pow(Z,0.9)));
	
	return loss;
}

int main()
{
	int Z, user_response;
	float rho, A;
	
	do
	{
		cout<<"Enter the atomic number of target element.\n";
		cin>>Z;
		
		cout<<"Enter the atomic weight of target element.\n";
		cin>>A;
		
		cout<<"Enter the density of target element in g/cm^3\n";
		cin>>rho;
		
		cout<<"Average energy loss by 225 GeV muon inside the specified material is: \n"<<ionization_loss(Z,A,rho);
		
		cout<<"\nPress 1 to calculate again, press any other key to exit.\n";
		cin>>user_response;
		
		if(user_response != 1)
		{
			cout<<"\nExiting....\n";
			return 0;
		}
			
	}
	while (user_response == 1);

}
