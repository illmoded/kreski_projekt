void macro(){
	TH1F *hist = new TH1F("hist","czas uwiezienia",100,1,100);
	fstream plik("hist.txt",std::fstream::in);
	double t;
	while(plik >> t){
		hist->Fill(t);
	}
	hist->Draw();
}