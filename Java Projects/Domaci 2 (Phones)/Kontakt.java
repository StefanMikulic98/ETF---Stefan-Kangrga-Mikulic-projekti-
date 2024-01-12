package gui;

public class Kontakt extends Stavka {
	String imeKorisnika, brojTelefona;
	
	public Kontakt(String imeKorisnika, String brojTelefona) {
		super(imeKorisnika, brojTelefona);
		this.imeKorisnika=imeKorisnika;
		this.brojTelefona=brojTelefona;
	}
	public String getImeKorisnika() {
		return imeKorisnika;
	}
	public void setImeKorisnika(String imeKorisnika) {
		this.imeKorisnika = imeKorisnika;
	}
	public String getBrojTelefona() {
		return brojTelefona;
	}
	public void setBrojTelefona(String brojTelefona) {
		this.brojTelefona = brojTelefona;
	}

}
