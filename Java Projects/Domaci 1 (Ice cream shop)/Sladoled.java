package gui;

import java.awt.Button;
import java.util.ArrayList;

public class Sladoled {
	ArrayList<Ukus> ukusi = new ArrayList<>();
	int trenutnaKolicina, maksKolicina;
	Ukus noviUkus;
	
	public Sladoled() {
		this.trenutnaKolicina=0;
		this.maksKolicina=200;
	}
	
	public void dodajUkus(String ime, String boja, Button novi) {
		Boolean kraj=false;
		if(ukusi.isEmpty()) {
			noviUkus= new Ukus(ime, boja, novi);
			ukusi.add(noviUkus);
			kraj=true;
		}
		else {
			for(Ukus ukus: ukusi) {
				if(ukus.naziv == ime) {
					kraj=true;
					break;
				}
			}
		}
		if(!kraj) {
			noviUkus= new Ukus(ime, boja, novi);
			ukusi.add(noviUkus);
		}
	}
	
	public void puniSladoled(String naziv){
		Boolean kraj=false;
		for(Ukus ukus: ukusi) {
			if(ukus.naziv == naziv) {
				if((trenutnaKolicina+20)>maksKolicina) {
					int i=maksKolicina-trenutnaKolicina;
					ukus.setKolicina(ukus.kolicina+=i);
					trenutnaKolicina+=i;
				}
				else {
					ukus.setKolicina(ukus.kolicina+=20);
					trenutnaKolicina+=20;
				}				
				break;
			}
		}
	}
	
	public int getTrenutnaKolicina() {
		return trenutnaKolicina;
	}

	public void setTrenutnaKolicina(int trenutnaKolicina) {
		this.trenutnaKolicina = trenutnaKolicina;
	}

	public int getMaksKolicina() {
		return maksKolicina;
	}

	public void setMaksKolicina(int maksKolicina) {
		this.maksKolicina = maksKolicina;
	}
	
	@Override
	public String toString() {
		String tekst="";
		for(Ukus ukus: ukusi) {
			tekst+= ukus.kolicina + "[" + ukus.naziv + ukus.boja +"] ";
		}
		return tekst;
	}
		
}
