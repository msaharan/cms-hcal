void hist25()
{
	ifstream finh;
	finh.open("his.txt");
	ifstream finm;
	finm.open("my25.txt");
	TH1F* hish = new TH1F("his","25", 40, 3,4);
	TH1F* myh = new TH1F("my","25", 40, 3,4);
	TH1F* h3 = new TH1F(*hish);
	h3->Add(myh,1.);
	
	double his25,my25, junk;
	
	for(int ii=0;ii<25;ii++)
	{
		finh>>his25;
		hish->Fill(his25);
	}
	for(int ii=0;ii<25;ii++)
	{
		finm>>my25>>junk;
		myh->Fill(my25);
	}
	finh.close();
	finm.close();
	TCanvas* c1 = new TCanvas();
	hish->SetFillColor(2);
	hish->Draw();
	TCanvas* c2 = new TCanvas();
	myh->SetFillColor(3);
	myh->Draw();
	
	TCanvas* c3 = new TCanvas();
	h3->GetYaxis()->SetRangeUser(0,10);
	h3->GetXaxis()->SetRangeUser(3,3.6);
	h3->GetXaxis()->SetTitle("Breakdown Voltage (kV)");
	h3->GetYaxis()->SetTitle("Entries");
	h3->Draw("hist");
	hish->Draw("SameHist");
	myh->Draw("SameHist");
}
	
	
	
