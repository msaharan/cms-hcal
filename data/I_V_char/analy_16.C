void analy_16()
{
	ifstream fin;
	fin.open("1.6V.txt");
	float current_1[100], volt[100],d_current[100], b_volt[100],l_no[100], junk[100];
	TGraph* gr;
	TGraph* gr1;
	TF1* f1 = new TF1("f1", "[0]+[1]*x", 0,2);
	TF1* f2 = new TF1("f2", "[0]+[1]*x", 4.4,7);	
	float c_1,m_1,c_2,m_2;
	auto mg = new TMultiGraph();
	TCanvas* c1 = new TCanvas();
	for(int jj=0;jj<13;jj++)
	{
		c_1 = 0;
		m_1 = 0;
		c_2 = 0;
		m_2 = 0;
		cout<<"jj "<<jj<<endl;
		for(int counter=0;counter<29;counter++)
		{
			fin>>d_current[counter]>>volt[counter]>>current_1[counter]>>junk[counter];
			cout<<volt[counter]<<"\t"<<current_1[counter]<<endl;
		}
		gr = new TGraph(29, volt, current_1);
		gr->Fit(f1,"R");	
		gr->Fit(f2,"R");	
		c_1 = f1->GetParameter(0);
		m_1 = f1->GetParameter(1);
		c_2 = f2->GetParameter(0);
		m_2 = f2->GetParameter(1);
		
		gr1 = new TGraph(29,volt,current_1);
		gr1->GetXaxis()->SetTitle("Voltage (kV)");
		gr1->GetYaxis()->SetTitle("HPD Current (nA)");
		gr1->SetTitle("HPD current vs Applied Voltage");
		gr1->SetMarkerStyle(20);
		gr1->SetMarkerSize(1);
		gr1->SetMarkerColor(4);
		gr1->SetLineWidth(2);
		gr1->GetXaxis()->SetRangeUser(0,7);
		gr1->Draw("AP");
		mg->Add(gr1);
		cout<<"........................................................\n";
		c1 = new TCanvas();
		
	cout<<"c_1 "<<c_1<<endl;
	cout<<"m_1 "<<m_1<<endl;
	cout<<"c_2 "<<c_2<<endl;
	cout<<"m_2 "<<m_2<<endl;
	
	b_volt[jj] = (c_2 - c_1)/(m_1-m_2);
	}
	
	float mean_volt = 0.;
	cout<<endl<<endl;
	for(int ii=0;ii<13;ii++)
	{	
		l_no[ii]=ii+5;
		cout<<"Layer No "<<l_no[ii]<<"\t"<<"Breakdown voltage "<<ii<<"\t"<<b_volt[ii]<<endl;
		mean_volt = mean_volt + b_volt[ii];
	}
			cout<<"Mean Breakdown voltage "<<mean_volt/13<<endl;

	   mg->SetTitle("HPD current vs Applied Voltage; Voltage (kV); HPD Current (nA)");

	   mg->Draw("AP");
	   
	TCanvas* c2 = new TCanvas();
	TGraph* gr2 = new TGraph(13,l_no, b_volt);
	gr2->SetTitle("Layer Number vs Breakdown Voltage (Laser Intensity 1.7 V)");
	gr2->SetMarkerStyle(20);
	gr2->SetMarkerSize(1);
	gr2->SetMarkerColor(kBlue);
	gr2->SetLineWidth(2);
	gr2->SetLineColor(3);
	gr2->GetXaxis()->SetTitle("Layer Number");
	gr2->GetYaxis()->SetTitle("Breakdown Voltage (kV)");
	
	
	gr2->Draw("ACP");


}
