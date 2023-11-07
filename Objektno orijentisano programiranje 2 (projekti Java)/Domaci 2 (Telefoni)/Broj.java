package gui;

public class Broj {
	int kodDrzave, pozivniBroj, brojPretplatnika;

	public Broj(int kodDrzave, int pozivniBroj, int brojPretplatnika) {
		this.kodDrzave=kodDrzave;
		this.pozivniBroj=pozivniBroj;
		this.brojPretplatnika=brojPretplatnika;
	}
	
	public Broj(String brojTelefona) {
		razdvojBroj(brojTelefona);
		this.kodDrzave=kodDrzave;
		this.pozivniBroj=pozivniBroj;
		this.brojPretplatnika=brojPretplatnika;
	}
	
	public int getKodDrzave() {
		return kodDrzave;
	}

	public void setKodDrzave(int kodDrzave) {
		this.kodDrzave = kodDrzave;
	}

	public int getPozivniBroj() {
		return pozivniBroj;
	}

	public void setPozivniBroj(int pozivniBroj) {
		this.pozivniBroj = pozivniBroj;
	}

	public int getBrojPretplatnika() {
		return brojPretplatnika;
	}

	public void setBrojPretplatnika(int brojPretplatnika) {
		this.brojPretplatnika = brojPretplatnika;
	}

	public boolean istaDrzava(Object obj) {
		if (!(obj instanceof Broj)) {
			return false;
		}
		Broj f = (Broj) obj;
		return this.kodDrzave == f.kodDrzave;
	}

	public boolean istaMreza(Object obj) {
		if (!(obj instanceof Broj)) {
			return false;
		}
		Broj f = (Broj) obj;
		return this.kodDrzave == f.kodDrzave && this.pozivniBroj == f.pozivniBroj;
	}
	
	public boolean istiBroj(Object obj) {
		if (!(obj instanceof Broj)) {
			return false;
		}
		Broj f = (Broj) obj;
		return this.kodDrzave == f.kodDrzave && this.pozivniBroj == f.pozivniBroj && this.brojPretplatnika == f.brojPretplatnika;
	}
	
	@Override
	public String toString() {
		return "+" + kodDrzave + " " + pozivniBroj + " " + brojPretplatnika;
	}
	
	public void razdvojBroj(String broj) {
		int i=0;
		String kod="", poziv="", poziv1="";
		
		for(i=0;i<3;i++) {
			kod+=broj.charAt(i);
		}
		kodDrzave=Integer.parseInt(kod);
		
		for(i=3;i<5;i++) {
			poziv+=broj.charAt(i);
		}
		pozivniBroj=Integer.parseInt(poziv);
		
		for(i=5;i<7;i++) {
			poziv1+=broj.charAt(i);
		}
		pozivniBroj=Integer.parseInt(poziv1);
	}
}
