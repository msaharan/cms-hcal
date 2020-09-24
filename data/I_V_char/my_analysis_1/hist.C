void hist()
{
	ifstream fin17;
	fin17.open("my17.txt");
	ifstream fin25;
	fin25.open("my25.txt");
	TH1F* h17 = new TH1F("h17","17", 60, 3,4.5);
	TH1F* h25 = new TH1F("h25","25", 60, 3,4.5);
	TH1F* h3 = new TH1F(*h17);
	h3->Add(h25,1.);
	
	
	double x17,x25, junk;
	
	for(int ii=0;ii<13;ii++)
	{
		fin17>>x17>>junk;
		cout<<x17<<endl;
		h17->Fill(x17);
	}
	cout<<endl;
	for(int ii=0;ii<25;ii++)
	{
		fin25>>x25>>junk;
		cout<<x25<<endl;
		h25->Fill(x25);
	}
	fin17.close();
	fin25.close();
	TCanvas* c1 = new TCanvas();
	h17->SetFillColor(2);
	h17->GetXaxis()->SetTitle("Breakdown Voltage (kV)");
	h17->GetYaxis()->SetTitle("Entries");
	h17->SetTitle("Pixel 14 (Fitting range- 5.3kV to 7kV)");
	gStyle->SetOptStat(1110);
	h17->Draw();
	TCanvas* c2 = new TCanvas();
	h25->SetFillColor(3);
	h25->GetXaxis()->SetTitle("Breakdown Voltage (kV)");
	h25->GetYaxis()->SetTitle("Entries");
	h25->SetTitle("Undamaged region (Fitting range- 5.3kV to 7kV)");
	gStyle->SetOptStat(1110);
	h25->Draw();
	
	TCanvas* c3 = new TCanvas();
	h3->GetYaxis()->SetRangeUser(0,7);
//	h3->GetXaxis()->SetRangeUser(3,3.6);
	h3->GetXaxis()->SetTitle("Breakdown Voltage (kV)");
	h3->GetYaxis()->SetTitle("Entries");
	h3->SetTitle("Breakdown voltage in damaged and undamaged region(Fitting range- 5.3kV to 7kV))");
	gStyle->SetOptStat(0000);
	h3->Draw("hist");
	h17->Draw("SameHist");
	h25->Draw("SameHist");
}
	
	
	
