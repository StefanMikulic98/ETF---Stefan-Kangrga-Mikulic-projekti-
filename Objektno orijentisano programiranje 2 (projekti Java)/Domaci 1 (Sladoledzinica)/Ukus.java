package gui;

import java.awt.Button;
import java.awt.Graphics;

public class Ukus {
	String naziv, boja;
	int kolicina;
	Button dugme;
	
	public Ukus(String naziv, String boja, Button dugme) {
		this.naziv = naziv;
		this.boja = "#"+boja;
		this.kolicina=0;
		this.dugme=dugme;
		
		dugme.addActionListener((ae)->{
			
		});
	}
	
	public int getKolicina() {
		return kolicina;
	}

	public void setKolicina(int kolicina) {
		this.kolicina = kolicina;
	}
	
	public String getNaziv() {
		return naziv;
	}

	public void setNaziv(String naziv) {
		this.naziv = naziv;
	}

	public String getBoja() {
		return boja;
	}

	public void setBoja(String boja) {
		this.boja = boja;
	}

	public boolean equals(Object obj) {
		if(!(obj instanceof Ukus)) {
			return false;
		}
		Ukus f = (Ukus)obj;
		return this.naziv == f.naziv && this.boja == f.boja;
	}
	
	@Override
	public String toString() {
		return "[" + naziv + "]";
	}	
}
