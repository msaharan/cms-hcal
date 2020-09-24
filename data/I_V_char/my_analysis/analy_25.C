void analy_25()
{
	ifstream fin;
	fin.open("25.txt");
	float current[1000], volt[1000], 
			d_current[1000], b_volt[1000],l_no[1000], m[1000];

	TGraph* gr;
	TGraph* gr1;
	TF1* f1 = new TF1("f1", "[0]+[1]*x", 0,2);
//	TF1* f2 = new TF1("f2", "[0]+[1]*x", 3.5,7);
	TF1* f2 = new TF1("f2", "[0]+[1]*x", 5.3,7);
	float c_1,m_1,c_2,m_2;
	auto mg = new TMultiGraph();

	TCanvas* c1 = new TCanvas();
	for(int jj=0;jj<25;jj++)
	{
		c_1 = 0;
		m_1 = 0;
		c_2 = 0;
		m_2 = 0;
		cout<<"jj "<<jj<<endl;
		for(int counter=0;counter<29;counter++)
		{
			fin>>d_current[counter]>>volt[counter]>>current[counter];
			cout<<volt[counter]<<"\t"<<current[counter]<<endl;
			
		}
		gr = new TGraph(29, volt, current);
		gr->Fit(f1,"R");	
		gr->Fit(f2,"R");	
		c_1 = f1->GetParameter(0);
		m_1 = f1->GetParameter(1);
		c_2 = f2->GetParameter(0);
		m_2 = f2->GetParameter(1);
		gr1 = new TGraph(29,volt,current);
		gr1->GetXaxis()->SetTitle("Voltage (kV)");
		gr1->GetYaxis()->SetTitle("HPD Current (nA)");
		gr1->SetMarkerStyle(20);
		gr1->SetMarkerSize(1);
		gr1->SetMarkerColor(4);
		gr1->SetLineWidth(2);
		gr1->Draw("ACP");
		mg->Add(gr1);
		cout<<"........................................................\n";
		c1 = new TCanvas();
		
	cout<<"c_1 "<<c_1<<endl;
	cout<<"m_1 "<<m_1<<endl;
	cout<<"c_2 "<<c_2<<endl;
	cout<<"m_2 "<<m_2<<endl;
	
	b_volt[jj] = (c_2 - c_1)/(m_1-m_2);
	m[jj] = m_2;
	}
	
	cout<<endl<<endl;
	float mean_volt = 0.;
	
	ofstream fout;
	fout.open("my25.txt");
	
	for(int ii=0;ii<25;ii++)
	{	
		l_no[ii]=ii;
		cout<<"Position No = "<<l_no[ii]<<" \t"<<"Breakdown voltage = "
			<<b_volt[ii]<<"\t"<<"conductance = "<<m[ii]<<endl;
		mean_volt = mean_volt + b_volt[ii];
		fout<<b_volt[ii]<<"\t"<<m[ii]<<endl;
	}
	fout.close();
	cout<<"Mean Breakdown voltage "<<mean_volt/25<<endl;
	   mg->SetTitle("Multi-graph Title; X-axis Title; Y-axis Title");
	   mg->Draw("ACP");
	   
	TCanvas* c2 = new TCanvas();
	TGraph* gr2 = new TGraph(13,l_no, b_volt);
	gr2->SetTitle("Layer Number vs Breakdown Voltage (5 #times 5)");
	gr2->SetMarkerStyle(20);
	gr2->SetMarkerSize(1);
	gr2->SetMarkerColor(kBlue);
	gr2->SetLineWidth(2);
	gr2->SetLineColor(3);
	gr2->GetXaxis()->SetTitle("Layer Number");
	gr2->GetYaxis()->SetTitle("Breakdown Voltage (kV)");
	
	
	gr2->Draw("ACP");


}
