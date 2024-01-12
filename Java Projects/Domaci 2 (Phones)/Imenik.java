package gui;

import java.awt.GridLayout;

public class Imenik extends ListaStavki {
		
	public Imenik() {
		super();	
	}
	
	public void dodajKontakte(Kontakt noviKontakt){
		dodajStavku(noviKontakt);
	}
	
	public String dohvatiImeKorisnika(String brojTelefona) throws GNePostoji {
		for(Stavka kontakt: stavke) {
			if(((Kontakt) kontakt).getBrojTelefona()==brojTelefona) {
				return ((Kontakt) kontakt).getImeKorisnika();
			}
		}
		
		throw new GNePostoji();
	}
	
	public String dohvatiBrojTelefona(String imeKorisnika) throws GNePostoji {
		for(Stavka kontakt: stavke) {
			if(((Kontakt) kontakt).getImeKorisnika()==imeKorisnika) {
				return ((Kontakt) kontakt).getBrojTelefona();
			}
		}
		throw new GNePostoji();
	}
}
