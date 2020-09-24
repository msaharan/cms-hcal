// v 4.2 Added temperature graph and differential dark current hist. - Raghu

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#define center_pixelx 40
#define center_pixely 34
#define rad 20 
//--------Dont edit -----------//
#define hdr_len 16
#define npts 500
//------------------------------//


void analysis_2D_v4_2(int run_no)
{
  int row_no=0;
  char file_hdr[200];
  FILE *f1;
  char fname[100];
  char rfname[100];  

  float x_pos[npts], y_pos[npts], z_pos[npts];
  float temperature[npts];
  float temp_t[npts];
  float pin_iavg[npts][npts];   // [row][col]
  float pin_iavg_net[npts][npts];   // [row][col]
  float pin_diff[npts];
  float nvsteps[npts];
  
  float evt_hdr[hdr_len];
  float dark_i;
  float i_data[500];
  
  
  TCanvas *c1 = new TCanvas("c1","c1",700,650);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);

  sprintf(fname,"HPD_Run%05d_r_%04d.txt",run_no, row_no); 
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

  // hsteps = evt_hdr[12]; vsteps = evt_hdr[13];
  // hstep size = evt_hdr[11] vstep size = evt_hdr[14]
  // 
  
  TProfile* hprof = new TProfile("hprof","Profile of dark current vs temp",150,15,30,0,150);
     
  for(int i=0; i<hdr_len; i++)
      fscanf(f1,"%f\t",&evt_hdr[i]);
	
  int hsteps = evt_hdr[12];
  int vsteps = evt_hdr[13];
  float hstep_size = evt_hdr[11];   // in mm
  float vstep_size = evt_hdr[14];   // in mm
  
  cout<< " Steps  "<< "H Steps : " << hsteps << "  V Steps : " << vsteps <<
         " H & V step size (mm) : " << hstep_size << ", " << vstep_size << endl;
   
  float dcurrent[npts];
  float dcurrent_temp;
  float dcurrent_old;

  fclose(f1);

  sprintf(rfname,"HPD_Run%05d.root",run_no);
  
  TFile *rf=new TFile(rfname,"recreate");
  
  TGraph *gr[npts];
  
  TH1F *h3 = new TH1F("h3","Dark Current",1000,0,100);  // bin size = 0.1 nA
  
  TH1F *h8 = new TH1F("h8","Dark Current Diff",1000,-50,50);  // bin size = 0.1 nA
  
  dcurrent_old=0;
/* now here */
  char x_t[100],z_t[100];
  
  // Now processing all files in a loop
  for(int ii=0; ii<vsteps; ii++)
  {
    sprintf(fname,"HPD_Run%05d_r_%04d.txt",run_no, ii);
    
    f1=fopen(fname,"r");
    fgets(file_hdr,200,f1);   // remove first line
 
    dcurrent_temp =0;
    dcurrent[ii]=0;
    for(int i=0; i<4; i++){   
      fscanf(f1,"%f\t",&dcurrent_temp);
      dcurrent[ii] = dcurrent[ii] + dcurrent_temp;
      h3->Fill(dcurrent_temp);  
    }
    dcurrent[ii] = dcurrent[ii]/4;
    if(ii != 0)   // skip first entry
      h8->Fill(dcurrent[ii] - dcurrent_old);
    dcurrent_old = dcurrent[ii];
    
    int np= 0;

    while(!feof(f1))
    {
      float i_add=0;

      for(int i=0; i<hdr_len; i++)
        fscanf(f1,"%f\t",&evt_hdr[i]);
    
      x_pos[np]  = evt_hdr[6];
      y_pos[np]  = evt_hdr[7];
      z_pos[np]  = evt_hdr[8];
      temp_t[np] = evt_hdr[15]; 
      dark_i     = evt_hdr[2];

      for(int i=0; i < (int)evt_hdr[3] ; i++){
        fscanf(f1,"%f\t",&i_data[i]);
        i_add = i_add + i_data[i];
      }
     
      pin_iavg[ii][np] = i_add / (int)evt_hdr[3];
  
      pin_iavg_net[ii][np] = pin_iavg[ii][np] - dcurrent[ii];
      np++;
   
    }// while(!feof(f1))
  
    fclose(f1);

    //cout << "Events read = " << np << endl;
    
    float x_steps[npts];

    for(int i=0; i < hsteps ; i++){
        x_steps[i] = (float) i;    
    }
         
    temperature[ii]=temp_t[0];
    hprof->Fill(temperature[ii], dcurrent[ii]);
/*
    //cout << " temp: " << temperature[vsteps] << endl; 
     // gr[ii]=new TGraph(np,x_pos,pin_iavg[ii]);  // current as function of absolute horizontal position
*/
//	cout << " temp: " << temperature[vsteps] << endl; 
 
    
    gr[ii]=new TGraph(np,x_steps,pin_iavg_net[ii]); // net current as function of horizontal step 
    	
    char grname[100];
    sprintf(grname,"Row_scan_r_%04d",ii);
   
/*    char x_t[100],z_t[100]; was here */

    sprintf(x_t,"Horizontal steps (#times %d #mum)", hstep_size*1000);
    sprintf(z_t,"Vetical steps (#times %d #mum)", vstep_size*1000);
   
    gr[ii]->SetTitle(grname);
    //gr[ii]->GetXaxis()->SetTitle("X Steps (#times )");
    gr[ii]->GetXaxis()->SetTitle(x_t);
    gr[ii]->GetXaxis()->SetTitleOffset(1.2);
    gr[ii]->GetXaxis()->SetTitleSize(0.05);
    gr[ii]->GetXaxis()->SetLabelSize(0.045);
    gr[ii]->GetYaxis()->SetTitleSize(0.05);
    gr[ii]->GetYaxis()->SetLabelSize(0.045);
    gr[ii]->GetYaxis()->SetTitle("HPD Net Current (nA)");
    gr[ii]->GetYaxis()->SetTitleOffset(1.2);
    gr[ii]->SetLineWidth(1);
    gr[ii]->SetMarkerSize(1);   
    gr[ii]->SetLineColor(4);
    gr[ii]->SetMarkerColor(2);
    gr[ii]->SetMarkerStyle(8);

//	TCanvas* c8 = new TCanvas(); 
    gr[ii]->Draw("ALP"); // plot on canvas c1

    gr[ii]->Write(grname);


  }// for(int ii=0; ii<vsteps; ii++)

   
  TH2F *h2 = new TH2F("h","2D Scan",hsteps,1,hsteps,vsteps,1,vsteps);
  //TH2F *h2 = new TH2F("h","2D Scan",hsteps,0,hsteps,vsteps,0,vsteps);
  TH2F *h4 = new TH2F("h4","2D Scan: Net signal current",hsteps,1,hsteps,vsteps,1,vsteps);
  
  TH2F *h6 = new TH2F("h6","2D Scan: Net signal current Mod",hsteps,1,hsteps,vsteps,1,vsteps);

  TH1F *h5 = new TH1F("h5","Net Signal Current",1000,0,100);  // bin size = 0.1 nA
  
  TH1F *h7 = new TH1F("h7","Net Signal Current: Local Region",1000,0,100); // bin size = 0.1 nA

  for(int i=1;i<=vsteps;i++)
    for(int j=1;j<=hsteps;j++)
      h2->SetBinContent(j,i,pin_iavg[i-1][j-1]);
  
  f1=fopen("2d_dump.txt","w");

  for(int i=1;i<=vsteps;i++)
    {
     //fprintf(f1,"\n");  
     for(int j=1;j<=hsteps;j++)
      {
        h4->SetBinContent(j,i,pin_iavg_net[i-1][j-1]);
        if(pin_iavg_net[i-1][j-1] > 3.0)
          h5->Fill(pin_iavg_net[i-1][j-1]);
        //if( (j > 10) && ( j < 69) && (i > 11) && ( i < 63))
        if(pin_iavg_net[i-1][j-1] > 3.0)
          fprintf(f1,"%d   %d   %f\n",j-1,i-1, 2*pin_iavg_net[i-1][j-1]);
        
      }
    }

  h5->SetAxisRange(1., 50,"X");
  float isig_mean = h5->GetMean();  // 48.2
  cout <<" Mean Signal current = " << isig_mean <<endl;

  float isig_norm =0;

  for(int i=1;i<=vsteps;i++)
    {
     //fprintf(f1,"\n");  
     for(int j=1;j<=hsteps;j++)
      {
        if(pin_iavg_net[i-1][j-1] > 5.0)
          {
            isig_norm = pin_iavg_net[i-1][j-1]/isig_mean;
            //isig_norm = pow(isig_norm,2);
            h6->SetBinContent(j,i, isig_norm);

          }
      }
    }

  
  fclose(f1);

//  TCanvas* c2 = new TCanvas(); 
  h2->Draw(); // plot on canvas c2
  h2->GetXaxis()->SetTitle(x_t);
  h2->GetXaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitle(z_t);
  h2->GetYaxis()->SetTitleOffset(1.2);
 
  h2->Write("2D_Sig_Current");
  
  
  
  h4->GetXaxis()->SetTitle(x_t);
  h4->GetXaxis()->SetTitleOffset(1.2);
  h4->GetYaxis()->SetTitle(z_t);
  h4->GetYaxis()->SetTitleOffset(1.2);
  h4->Write("2D_Net_Sig_Current");
  
  h6->GetXaxis()->SetTitle(x_t);
  h6->GetXaxis()->SetTitleOffset(1.2);
  h6->GetYaxis()->SetTitle(z_t);
  h6->GetYaxis()->SetTitleOffset(1.2);
  h6->Write("2D_Net_Sig_norm");  

  h3->GetXaxis()->SetTitle("Dark Current (nA)");
  h3->GetXaxis()->SetTitleOffset(1.2);
  h3->GetXaxis()->SetTitleSize(0.05);
  h3->GetXaxis()->SetLabelSize(0.045);
  h3->GetYaxis()->SetTitleSize(0.05);
  h3->GetYaxis()->SetLabelSize(0.045);
  h3->GetYaxis()->SetTitle("Frequency");
  h3->GetYaxis()->SetTitleOffset(1.2);

  h3->Write("Dark_current");
  
  h8->GetXaxis()->SetTitle("Dark Current Diff (nA)");
  h8->GetXaxis()->SetTitleOffset(1.2);
  h8->GetXaxis()->SetTitleSize(0.05);
  h8->GetXaxis()->SetLabelSize(0.045);
  h8->GetYaxis()->SetTitleSize(0.05);
  h8->GetYaxis()->SetLabelSize(0.045);
  h8->GetYaxis()->SetTitle("Frequency");
  h8->GetYaxis()->SetTitleOffset(1.2);

  h8->Write("Dark_current_diff");


  
  h5->GetXaxis()->SetTitle("Net Current (nA)");
  h5->GetXaxis()->SetTitleOffset(1.2);
  h5->GetXaxis()->SetTitleSize(0.05);
  h5->GetXaxis()->SetLabelSize(0.045);
  h5->GetYaxis()->SetTitleSize(0.05);
  h5->GetYaxis()->SetLabelSize(0.045);
  h5->GetYaxis()->SetTitle("Frequency");
  h5->GetYaxis()->SetTitleOffset(1.2);
  h5->Write("Net_sig_current");
  
  for(int i=0; i<vsteps; i++)
    nvsteps[i] = i;

  TGraph *gr_dcur =new TGraph(vsteps,nvsteps,dcurrent);

  gr_dcur->SetTitle("Dark Current");
  gr_dcur->GetXaxis()->SetTitle(z_t); //("Vertical Scan Steps (#times 200 #mum)");
  gr_dcur->GetXaxis()->SetTitleOffset(1.2);
  gr_dcur->GetXaxis()->SetTitleSize(0.05); 
  gr_dcur->GetXaxis()->SetLabelSize(0.045);
  gr_dcur->GetYaxis()->SetTitleSize(0.05);
  gr_dcur->GetYaxis()->SetLabelSize(0.045);
  gr_dcur->GetYaxis()->SetTitle("HPD Current (nA)");
  gr_dcur->GetYaxis()->SetTitleOffset(1.2);
  gr_dcur->SetLineWidth(1);
  gr_dcur->SetMarkerSize(1);   
  gr_dcur->SetLineColor(4);
  gr_dcur->SetMarkerColor(2);
  gr_dcur->SetMarkerStyle(8);
  
//  TCanvas* c3 = new TCanvas(); 
  
  gr_dcur->Draw("ALP"); // plot on canvas c3
  
  gr_dcur->Write("Dark Current vs Rows");

  
  TGraph *gr_tem =new TGraph(vsteps,nvsteps,temperature);

  gr_tem->SetTitle("Temperature");
  gr_tem->GetXaxis()->SetTitle(z_t); //("Vertical Scan Steps (#times 200 #mum)");
  gr_tem->GetXaxis()->SetTitleOffset(1.2);
  gr_tem->GetXaxis()->SetTitleSize(0.05);
  gr_tem->GetXaxis()->SetLabelSize(0.045);
  gr_tem->GetYaxis()->SetTitleSize(0.05);
  gr_tem->GetYaxis()->SetLabelSize(0.045);
  gr_tem->GetYaxis()->SetTitle("Temperature #^{circ} C");
  gr_tem->GetYaxis()->SetTitleOffset(1.2);
  gr_tem->SetLineWidth(1);
  gr_tem->SetMarkerSize(1);
  gr_tem->SetLineColor(4);
  gr_tem->SetMarkerColor(2);
  gr_tem->SetMarkerStyle(8);
//     TCanvas* c4 = new TCanvas(); // plot on canvas c4
  gr_tem->Draw("ALP");

  gr_tem->Write("Temperature at strat of each row");

  


  // make a net current histogram local to a region
  // region to be a circle around user defined center pixel (#define) 
  // d = sqrt( (x-x1)^2 + (y-y1)^2 )  should be <= radius

  // net current  pin_iavg_net[v][h]  2d array, i.e 1 row will be pin_iavg_net 

  // loop over all data
  float dist=0;

  //printf("\n -----------------------------------------------------------");
  //printf("\n ---------Selected pixels for local i_net histogram --------");
  //printf("\n -----------------------------------------------------------");
  for(int i=0;i<vsteps;i++)
   {
     for(int j=0;j<hsteps;j++)
      {
        dist = sqrt(pow(j-center_pixelx,2) + pow(i-center_pixely,2) );
        if( dist <= rad )
         {
           //printf("\n x_pixel = %d , y_pixel = %d, distance from center = %f", j, i, dist); 
           h7->Fill( pin_iavg_net[i][j] );

         }
      }
   }

  h7->GetXaxis()->SetTitle("Net Current (nA)");
  h7->GetXaxis()->SetTitleOffset(1.2);
  h7->GetXaxis()->SetTitleSize(0.05);
  h7->GetXaxis()->SetLabelSize(0.045);
  h7->GetYaxis()->SetTitleSize(0.05);
  h7->GetYaxis()->SetLabelSize(0.045);
  h7->GetYaxis()->SetTitle("Frequency");
  h7->GetYaxis()->SetTitleOffset(1.2);

  h7->Write("Net_sig_current:Local");

  hprof->GetXaxis()->SetTitle("Temperature #circC");
  hprof->GetXaxis()->SetTitleOffset(1.2);
  hprof->GetXaxis()->SetTitleSize(0.05);
  hprof->GetXaxis()->SetLabelSize(0.045);
  hprof->GetYaxis()->SetTitleSize(0.05);
  hprof->GetYaxis()->SetLabelSize(0.045);
  hprof->GetYaxis()->SetTitle("HPD Current (nA)");
  hprof->GetYaxis()->SetTitleOffset(1.2);

//   TCanvas* c5 = new TCanvas(); 

  hprof->Draw("ALP");
  hprof->Write("DC_PROF_TEMP");

  rf->Close();

  //**************************************
  //
  // Extract net current array into a file
  // For analysis using opencv
  //
  //**************************************

  {
    char run_no_str[20];
    sprintf(run_no_str,"HPD_Run_%04d.txt", run_no);

    //ofstream ofile("HPD_Run_"+to_string(run_no)+".txt");
    ofstream ofile(run_no_str);
    for(int i=0; i<vsteps; i++) {
      for(int j=0;j<hsteps; j++) {
        ofile<<setw(10)<<pin_iavg_net[i][j];    
      }
      ofile<<endl;
    }
    ofile.close();
  }

}
