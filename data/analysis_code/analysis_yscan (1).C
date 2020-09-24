#define hdr_len 16
#define run_no 177
// v run = 0 for horizontal and = 1 for vertical
#define vrun 0
#define gaus_range_fit 0

#define npts 500

// par0  = beam spot size at 1 sigma 
// par1  = Z0 = Focal plance position
// par2  = M^2

Double_t fitf3(Double_t *x,Double_t *par)
{
  Double_t wavelength = 0.520;   //micron 
  Double_t a1 = par[0];
  Double_t a2 = (x[0]-par[1])*(x[0]-par[1]);
  //Double_t a3 = (wavelength*(par[2]*par[2]))/(4.*3.14159*par[0]*par[0]);
  Double_t a3 = (wavelength*par[2])/(4.*3.14159*par[0]*par[0]);
  a3 = a3*a3;
  Double_t fitval = a1*TMath::Sqrt(1+a2*a3);
  return fitval;
}


void analysis_yscan()
{
  int row_no=0;
  char file_hdr[200];
  FILE *f1;
  char fname[100];
  char rfname[100];  

  float x_pos[npts], y_pos[npts], z_pos[npts];
  float pin_iavg[npts][npts];   // [row][col]
  float pin_diff[npts];
  float evt_hdr[hdr_len];
  float dark_i;
  float i_data[500];
  
  float gY_pos[npts];

  float sigma[npts];

  sprintf(fname,"HPD_Yscan_Run%05d_r_%04d.txt",run_no, row_no); 
  // open 0th file and read header to know how many files to be read
  cout << fname << endl;
  f1=fopen(fname,"r");
  fgets(file_hdr,200,f1);   // remove first line
  fgets(file_hdr,200,f1);   // remove second line, dark current readings, 4 values. 
  // taken for each row 
  
  //After first line file format is :
  //---------------------------------------
  // Scan point 1 hdr  : 16 entries %f
  // Scan point 1 data : entries user definable = evt_hdr[3] i.e fourth entry
  // Scan point 2 hdr
  // Scan point 2 data
  // .
  // .
  // Scan point n hdr   : n = evt_hdr[12]
  // Scan point n data
  //---------------------------------------
  // dark current = evt_hdr[2] = first dark current reading, while starting 2D scan run

  // hsteps = evt_hrd[12]; vsteps = evt_hrd[13];
   
  for(int i=0; i<hdr_len; i++)
      fscanf(f1,"%f\t",&evt_hdr[i]);

	int hsteps = evt_hdr[12];
	int vsteps = evt_hdr[13];

  cout<< " Stpes  "<< "H Steps : " << hsteps << "  V Steps : " << vsteps << endl;
   
  float dcurrent[npts];
  float dcurrent_temp;

  fclose(f1);
  
  sprintf(rfname,"HPD_Yscan_Run%05d.root",run_no);
  
  TFile *rf=new TFile(rfname,"recreate");
  
  TGraph *gr[npts];
  TGraph *gr1[npts];

  TF1* g1 = new TF1("g1","gaus");
   	
  if(gaus_range_fit)
    g1 = new TF1("g1","gaus",10.96,11.05);
//  else
//   TF1 g1("g1","gaus");

  // Now processing all files in a loop
  char grname[100];

  for(int ii=0; ii<vsteps; ii++)
  {
    sprintf(fname,"HPD_Yscan_Run%05d_r_%04d.txt",run_no, ii);
    
    f1=fopen(fname,"r");
    fgets(file_hdr,200,f1);   // remove first line
 
    dcurrent_temp =0;
    dcurrent[ii]=0;
    for(int i=0; i<4; i++){   
      fscanf(f1,"%f\t",&dcurrent_temp);
      dcurrent[ii] = dcurrent[ii] + dcurrent_temp;  
    }
    dcurrent[ii] = dcurrent[ii]/4;
  
    int np= 0;

    while(!feof(f1))
    {
      float i_add=0;

      for(int i=0; i<hdr_len; i++)
        fscanf(f1,"%f\t",&evt_hdr[i]);
    
      x_pos[np] = evt_hdr[6];
      y_pos[np] = evt_hdr[7];
      z_pos[np] = evt_hdr[8]; 
      dark_i    = evt_hdr[2];

      for(int i=0; i < (int)evt_hdr[3] ; i++){
        fscanf(f1,"%f\t",&i_data[i]);
        i_add = i_add + i_data[i];
      }
     
      pin_iavg[ii][np] = i_add / (int)evt_hdr[3];
  
      np++;
   
    }// while(!feof(f1))
  
    gY_pos[ii] = y_pos[np-1] * 1000.0;  // covert into microns for fit function

    cout << "Events read = " << np << endl;

    for(int j=0;j<np;j++)
    {
      pin_diff[j]= fabs(pin_iavg[ii][j+1]-pin_iavg[ii][j]);
    }
    
    pin_diff[np-1] =0;

    if(vrun)
      gr[ii]=new TGraph(np,z_pos,pin_iavg[ii]); 
    else
      gr[ii]=new TGraph(np,x_pos,pin_iavg[ii]); 

 //   char grname[100];
    sprintf(grname,"Row_scan_r_%04d",ii);

    gr[ii]->SetTitle(grname);
    if(vrun)
      gr[ii]->GetXaxis()->SetTitle("Z (mm)");
    else
      gr[ii]->GetXaxis()->SetTitle("X (mm)");
   
    gr[ii]->GetXaxis()->SetTitleSize(0.05);
    gr[ii]->GetXaxis()->SetLabelSize(0.045);
    gr[ii]->GetYaxis()->SetTitleSize(0.05);
    gr[ii]->GetYaxis()->SetLabelSize(0.045);
    gr[ii]->GetYaxis()->SetTitle("HPD Current (nA)");
    gr[ii]->SetLineWidth(1);
    gr[ii]->SetMarkerSize(1);   
    gr[ii]->SetLineColor(4);
    gr[ii]->SetMarkerColor(2);
    gr[ii]->SetMarkerStyle(8);
    gr[ii]->Draw("ALP");

    gr[ii]->Write(grname);

    if(vrun)
      gr1[ii]=new TGraph(np,z_pos,pin_diff); 
    else
      gr1[ii]=new TGraph(np,x_pos,pin_diff);
 
    sprintf(grname,"Diff_Row_scan_r_%04d",ii);

    gr1[ii]->SetTitle(grname);
     if(vrun)
      gr1[ii]->GetXaxis()->SetTitle("Z (mm)");
    else
      gr1[ii]->GetXaxis()->SetTitle("X (mm)");
   
    gr1[ii]->GetXaxis()->SetTitleSize(0.05);
    gr1[ii]->GetXaxis()->SetLabelSize(0.045);
    gr1[ii]->GetYaxis()->SetTitleSize(0.05);
    gr1[ii]->GetYaxis()->SetLabelSize(0.045);
    gr1[ii]->GetYaxis()->SetTitle("Diff. HPD Current (nA)");
    gr1[ii]->SetLineWidth(1);
    gr1[ii]->SetMarkerSize(1);   
    gr1[ii]->SetLineColor(4);
    gr1[ii]->SetMarkerColor(1);
    gr1[ii]->SetMarkerStyle(8);

    if(gaus_range_fit){
      g1->SetParLimits(2,10,35);
      gr1[ii]->Fit(g1,"RQ");
    
    }
    else
      gr1[ii]->Fit(g1,"Q");

    gStyle->SetOptFit();
    gr1[ii]->Draw("ALP");	
 
    gr1[ii]->Write(grname);
   
    sigma[ii] = 1000.0 * g1->GetParameter(2);
    
    cout << "sigma =" << sigma[ii] << " at y = " << gY_pos[ii] << endl;
    

  }// for(int ii=0; ii<vsteps; ii++)

  

  TGraph *gsig =new TGraph(vsteps,gY_pos,sigma); 
  
  TF1 *func = new TF1("fit3",fitf3, 9900, 10250, 3);
  
  func->SetParameters(20, 10160, 50);
  //func->SetParLimits(0,17,18.5);
  gsig->Fit("fit3","R");
  

  gsig->SetTitle(grname);
  gsig->GetXaxis()->SetTitle("Beam axis Y (#mum)");
  gsig->GetXaxis()->SetTitleSize(0.05);
  gsig->GetXaxis()->SetLabelSize(0.045);
  gsig->GetYaxis()->SetTitleSize(0.05);
  gsig->GetYaxis()->SetLabelSize(0.045);
  gsig->GetYaxis()->SetTitle("Beam spot size at 1 #sigma (#mum)");
  gsig->SetLineWidth(1);
  gsig->SetMarkerSize(1);   
  gsig->SetLineColor(4);
  gsig->SetMarkerColor(2);
  gsig->SetMarkerStyle(8);

  gsig->Draw("ALP");
 
  gsig->Write("Sigma_plot");
   

  /* 
  TH2F *h2 = new TH2F("h","2D Scan",hsteps,1,hsteps,vsteps,1,vsteps);

  for(int i=1;i<=vsteps;i++)
    for(int j=1;j<=hsteps;j++)
      h2->SetBinContent(j,i,pin_iavg[i-1][j-1]);
  
  h2->Draw();
  
  h2->Write();
  */
  rf->Close();
}
