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
	h17->Draw();
	TCanvas* c2 = new TCanvas();
	h25->SetFillColor(3);
	h25->Draw();
	
	TCanvas* c3 = new TCanvas();
	h3->GetYaxis()->SetRangeUser(0,10);
//	h3->GetXaxis()->SetRangeUser(3,3.6);
	h3->GetXaxis()->SetTitle("Breakdown Voltage (kV)");
	h3->GetYaxis()->SetTitle("Entries");
	h3->Draw("hist");
	h17->Draw("SameHist");
	h25->Draw("SameHist");
}
	
	
	
