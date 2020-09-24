void exercise_2(){
	ifstream file;
	file.open("name");
	
	int v1, junk;
	
	file>>junk>>junk>>junk>>junk>>junk>>junk>>junk>>junk>>junk>>junk>>junk>>junk;
	
	while(file.eof()){
		file>>v1;
		for(v1)
