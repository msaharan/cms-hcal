// To calculate the radiation length in (g/cm^2) for different materials
// valid for all types of incident particles, put mass of particle in 
// particle_mass (Mev/c^2) and change z.
// for jackson's expression, factor inside logarithm is 233 , and for
// Fernow's expression, the factor is 183
  

#include<iostream>
#include<math.h>
#include<string>
using namespace std;
 
double electron_radius = 2.8179*pow(10,-13), 
		fine_structure_constant = 1/137., electron_mass = 0.511;
 
double radiation_length (double Z, double rho, double A, double z, 
						double particle_mass)
{
	double length;
	length = pow(4*(rho/A)*Z*(Z+1)*fine_structure_constant*pow(z,2)*
			pow((electron_mass/particle_mass),2)*pow(electron_radius,2)*
			log(233*(particle_mass/electron_mass)/pow(Z,0.3333)), -1) * 
			rho ;
	return length;
} 
int main()
{
	double Z, rho, A, z, particle_mass;
	int n;
	
	
	do // To put the execution of the program in loop for as long as  
	  // the user wants.
	{
		cout<<"Enter the atomic number of the target: \n";
		cin>>Z;
	
		cout<<"Enter the density of the target in g/cm^2: \n";
		cin>>rho;
		rho = 7.87;
		
		cout<<"Enter the atomic weight of the target: \n";
		cin>>A;
	
	
		A = A * 1.67 * pow(10,-24); //mass of the nucleus
		
		cout<<"Enter the atomic number of the incident particle: \n";
		cin>>z;
		
//		z = 1; for muon
		
		cout<<"Enter the mass of the incident particle in Mev/c^2.\n";
		cout<<"For example, enter 0.511 for electron. \n";
		cin>>particle_mass;
	
//		particle_mass = 105.7; for muon
			
		cout<<"The radiation length for the given parameter in g/cm^2 is: \n";
		cout<<radiation_length(Z, rho, A, z, particle_mass)<<endl; 
		
		cout<<"Do you want to calculate again? If yes, press 1, if not";
		cout<<" press 0. \n";
		cin>>n;
		
// this if statement prevents the infinite loop, which could arise if 
// the user enters a non-numeric character in any if the anywhere during 
// the execution program.  		
		
		if(n==0&&n!=1)
		{
			break;
		}	
	}
	while(n == 1);
	{
		cout<<endl;
	}
	
return 0;	
} 
