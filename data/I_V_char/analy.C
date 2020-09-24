


void analy()
{
	ifstream fin;
//	fin.open("HE-HPD_fiber location_Laser Intensity_1.6V_01032018.txt");
	fin.open("1.6V.txt");
	float current_1[1000],current_2[1000], current[1000], volt[1000], d_current[1000];
	int junk;
	char junk_1[1000];
	int n_lines = 377;
	
	for(int counter=0;counter<n_lines;counter++)
	{
		fin>>d_current[counter]>>volt[counter]>>current_1[counter]
		>>current_2[counter];
		current[counter] = (current_1[counter]+current_2[counter])/2;
	}
	fin.close();
	for(int ii=0;ii<n_lines;ii++)
	{
		cout<<d_current[ii]<<"\t"<<volt[ii]<<"\t"<<current_1[ii]
		<<"\t"<<current_2[ii]<<"\t"<<current[ii]<<endl;
		if(ii>=0&&ii<=28)
		{	
			volt_5[ii] = volt[ii];
			d_current_5[ii]=d_current[ii];
			current_1_5[ii]=current_1[ii];
			current_2_5[ii]=current_2[ii];
			current_5[ii]=current[ii];
		}
		if(ii>=(0+29)&&ii<=(28+29))
		{	
			volt_6[ii] = volt[ii];
			d_current_6[ii]=d_current[ii];
			current_1_6[ii]=current_1[ii];
			current_2_6[ii]=current_2[ii];
			current_6[ii]=current[ii];
		}
		if(ii>=(0+(29*2))&&ii<=(28+(29*2)))
		{	
			volt_7[ii] = volt[ii];
			d_current_7[ii]=d_current[ii];
			current_1_7[ii]=current_1[ii];
			current_2_7[ii]=current_2[ii];
			current_7[ii]=current[ii];
		}
		
		if(ii>=(0+(29*3))&&ii<=(28+(29*3)))
		{	
			volt_8[ii] = volt[ii];
			d_current_8[ii]=d_current[ii];
			current_1_8[ii]=current_1[ii];
			current_2_8[ii]=current_2[ii];
			current_8[ii]=current[ii];
		}
		if(ii>=(0+(29*4))&&ii<=(28+(29*4)))
		{	
			volt_9[ii] = volt[ii];
			d_current_9[ii]=d_current[ii];
			current_1_9[ii]=current_1[ii];
			current_2_9[ii]=current_2[ii];
			current_9[ii]=current[ii];
		}
		if(ii>=(0+(29*5))&&ii<=(28+(29*5)))
		{	
			volt_10[ii] = volt[ii];
			d_current_10[ii]=d_current[ii];
			current_1_10[ii]=current_1[ii];
			current_2_10[ii]=current_2[ii];
			current_10[ii]=current[ii];
		}
		if(ii>=(0+(29*6))&&ii<=(28+(29*6)))
		{	
			volt_11[ii] = volt[ii];
			d_current_11[ii]=d_current[ii];
			current_1_11[ii]=current_1[ii];
			current_2_11[ii]=current_2[ii];
			current_11[ii]=current[ii];
		}
		if(ii>=(0+(29*7))&&ii<=(28+(29*7)))
		{	
			volt_12[ii] = volt[ii];
			d_current_12[ii]=d_current[ii];
			current_1_12[ii]=current_1[ii];
			current_2_12[ii]=current_2[ii];
			current_12[ii]=current[ii];
		}
		if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			volt_13[ii] = volt[ii];
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}
		if(ii>=(0+(29*9))&&ii<=(28+(29*9)))
		{	
			volt_14[ii] = volt[ii];
			d_current_14[ii]=d_current[ii];
			current_1_14[ii]=current_1[ii];
			current_2_14[ii]=current_2[ii];
			current_14[ii]=current[ii];
		}
		if(ii>=(0+(29*10))&&ii<=(28+(29*10)))
		{	
			volt_15[ii] = volt[ii];
			d_current_15[ii]=d_current[ii];
			current_1_15[ii]=current_1[ii];
			current_2_15[ii]=current_2[ii];
			current_15[ii]=current[ii];
		}
		if(ii>=(0+(29*11))&&ii<=(28+(29*11)))
		{
			volt_16[ii] = volt[ii];	
			d_current_16[ii]=d_current[ii];
			current_1_16[ii]=current_1[ii];
			current_2_16[ii]=current_2[ii];
			current_16[ii]=current[ii];
		}
		if(ii>=(0+(29*12))&&ii<=(28+(29*12)))
		{
			volt_17[ii] = volt[ii];	
			d_current_17[ii]=d_current[ii];
			current_1_17[ii]=current_1[ii];
			current_2_17[ii]=current_2[ii];
			current_17[ii]=current[ii];
		}
		
/*		if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}if(ii>=(0+(29*8))&&ii<=(28+(29*8)))
		{	
			d_current_13[ii]=d_current[ii];
			current_1_13[ii]=current_1[ii];
			current_2_13[ii]=current_2[ii];
			current_13[ii]=current[ii];
		}		
*/		
	
	for(int ii=0;ii<17;ii++)
	{
//		cout<<d_current[ii]<<"\t"<<volt[ii]<<"\t"<<current_1[ii]
//		<<"\t"<<current_2[ii]<<"\t"<<current[ii]<<endl;
		gr
			

		
	}
	TF1* f1 = new TF1("f1", "[0]+[1]*x", 0,4);
	TF1* f2 = new TF1("f2", "[2]+[3]*x", 3.2,7);
	
	TGraph* g5 = new TGraph(29,volt_5,current_5);
	TGraph* g6 = new TGraph(29,volt_6,current_6);
	TGraph* g7 = new TGraph(29,volt_7,current_7);
	TGraph* g8 = new TGraph(29,volt_8,current_8);
	TGraph* g9 = new TGraph(29,volt_9,current_9);
	TGraph* g10 = new TGraph(29,volt_10,current_10);
	TGraph* g11 = new TGraph(29,volt_11,current_11);
	TGraph* g12 = new TGraph(29,volt_12,current_12);
	TGraph* g13 = new TGraph(29,volt_13,current_13);
	TGraph* g14 = new TGraph(29,volt_14,current_14);
	TGraph* g15 = new TGraph(29,volt_15,current_15);
	TGraph* g16 = new TGraph(29,volt_16,current_16);
	TGraph* g17 = new TGraph(29,volt_17,current_17);	
	
}
