void macro(){
	int tryb = 1;

	if(tryb){
		TH1F *hist = new TH1F("hist","czas uwiezienia",100,2,100);
		fstream plik("czas_uw.txt",std::fstream::in);
		double t;

		while(plik >> t){
			hist->Fill(t);
		}

		hist->Draw();
	}

	if(!tryb){
		TH1F *hist = new TH1F("hist","promienie",100,1,200);
		TH1F *hist2 = new TH1F("hist","promienie",100,1,200);
		fstream plik("promien.txt",std::fstream::in);
		fstream plik2("promien2.txt",std::fstream::in);
		double t, u, v;

		while(plik >> t >> u >> v){
			hist->Fill(v);
		}

		while(plik2 >> t >> u >> v){
			hist2->Fill(v);
		}

		hist->SetLineColor(1);
		hist->Draw();

		hist2->SetLineColor(2);
		hist2->Draw("SAME");

		TLegend* leg = new TLegend(.7, .8, .9, .9);
		leg->AddEntry(hist, "Miniball.h", "l");
		leg->AddEntry(hist2, "Nasz algorytm", "l");
		leg->Draw();
	}
}