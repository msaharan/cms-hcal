


void analy1()
{
	ifstream fin;
//	fin.open("HE-HPD_fiber location_Laser Intensity_1.6V_01032018.txt");
	fin.open("1.6V.txt");
	float current_1[1000],current_2[1000], current[1000], volt[1000], d_current[1000];
	int junk;
	char junk_1[1000];
	int n_lines = 377;
	
	
	TGraph* gr;
	TGraph* gr1;
	TF1* f1 = new TF1("f1", "[0]+[1]*x", 0,4);
	TF1* f2 = new TF1("f2", "[2]+[3]*x", 3.2,7);
	float c_1,m_1,c_2,m_2;
/*
	
	int x1[2]; 
	int y1[2]; 
	TCanvas* c1;
	c1 = new TCanvas();
	for(int ii=0; ii<2;ii++)
	{	
		int a = 1+ii;
		int b = 2+ii;
		x1[0]=a;
		x1[1]=b;
		y1[0]=a;
		y1[1]=b;
		
		gr = new TGraph(2,x1,y1);
		//gr->Draw("A*");
		gr->Fit(f1,"","",0,4);	
		//gr->Fit(f2,"","",4.2,7);	

		f1->SetParameter(0,c_1);
		f1->SetParameter(1,m_1);
		f2->SetParameter(2,c_2);
		f2->SetParameter(3,m_2);
		TGraph *gr = new TGraph(2,x1,y1);
		gr->GetXaxis()->SetTitle("Voltage (kV)");
		gr->GetYaxis()->SetTitle("HPD Current (nA)");
		gr->Draw("A*");
		f1->SetLineColor(6);
		f1->Draw("Same");
		f1->SetLineColor(3);
		f2->Draw("Same");
		c1->BuildLegend();	
		
		
		c1 = new TCanvas();
	}
		
	fin.close();
*/

	TCanvas* c1 = new TCanvas();
	for(int jj=0;jj<17;jj++)
	{
		cout<<"jj "<<jj<<endl;
		for(int counter=0;counter<28;counter++)
		{
			
			cout<<"counter "<<counter<<endl;
			fin>>d_current[counter]>>volt[counter]>>current_1[counter]
			>>current_2[counter];
			current[counter] = (current_1[counter]+current_2[counter])/2;
			
			cout<<volt[counter]<<"\t"<<current[counter]<<endl;
			
			gr = new TGraph(29, volt, current);
			gr->Fit(f1,"","",0,4);	
			gr->Fit(f2,"","",4.2,7);	
			c_1 = f1->GetParameter(0);
			m_1 = f1->GetParameter(1);
			c_2 = f2->GetParameter(2);
			m_2 = f2->GetParameter(3);
			f1->SetParameter(0,c_1);
			f1->SetParameter(1,m_1);
			f2->SetParameter(2,c_2);
			f2->SetParameter(3,m_2);
			TGraph *gr = new TGraph(29,volt,current);
			gr->GetXaxis()->SetTitle("Voltage (kV)");
			gr->GetYaxis()->SetTitle("HPD Current (nA)");
			gr->Draw("A*");
			f1->SetLineColor(6);
			f1->Draw("Same");
			f1->SetLineColor(3);
			f2->Draw("Same");
			c1->BuildLegend();	
			
			c1 = new TCanvas();
				
		}
	cout<<"c_1 "<<c_1<<endl;
	cout<<"m_1 "<<m_1<<endl;
	cout<<"c_2 "<<c_2<<endl;
	cout<<"m_2 "<<m_2<<endl;
//	gr1 = new TGraph(29,volt,current);
//	gr1->Draw("A*")
	
	
	}



}
