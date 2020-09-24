void conduct()
{
	ifstream fin1;
	ifstream fin2;
	fin1.open("my17.txt");
	fin2.open("my25.txt");
	float junk, con1[100], con2[100];
	float n1[100], n2[100];
	for(int ii=0; ii<13; ii++)
	{
		fin1>>junk>>con1[ii];
		n1[ii] = ii+5;
	}
	for(int ii=0;ii<25;ii++)
	{
		fin2>>junk>>con2[ii];
		n2[ii] = ii;
	}
	fin1.close();
	fin2.close();
	
	TCanvas* c1 = new TCanvas();
	TGraph *g1 = new TGraph(13,n1,con1);  
	g1->SetMarkerStyle(20);
	g1->SetMarkerSize(0.7);
	g1->SetMarkerColor(kBlack);
	g1->GetXaxis()->SetTitle("Layer Number");
	g1->GetYaxis()->SetTitle("1/R (pS)");
	g1->SetTitle("Pixel 14: Conductance vs Layer Number");
	g1->Draw("AP");  
	
	TCanvas* c2 = new TCanvas();
	TGraph *g2 = new TGraph(25,n2,con2);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(0.7);
	g2->SetMarkerColor(kBlack);
	g2->GetXaxis()->SetTitle("Position Number");
	g2->GetYaxis()->SetTitle("1/R (pS)");
	g2->SetTitle("Undamaged part (25 positions): Conductance vs position");
	g2->Draw("AP");  
}
