void macro(){
	int tryb = 0;

	if(tryb){
		TH1F *hist = new TH1F("hist","czas uwiezienia",100,1,100);
		fstream plik("czas_uw.txt",std::fstream::in);
		double t;

		while(plik >> t){
			hist->Fill(t);
		}

		hist->Draw();
	}

	if(!tryb){
		TH1F *hist = new TH1F("hist","promienie",100,1,100);
		fstream plik("promien.txt",std::fstream::in);
		double t, u, v;

		while(plik >> t >> u >> v){
			hist->Fill(v);
		}

		hist->Draw();
	}
}