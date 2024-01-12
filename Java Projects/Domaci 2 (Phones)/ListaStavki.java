package gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Panel;
import java.util.ArrayList;

public class ListaStavki extends Panel {
	ArrayList<Stavka> stavke = new ArrayList<>();
	
	public void dodajStavku(Stavka novaStavka){
		stavke.add(novaStavka);
	}
	
	public void prikazStavki() {
		this.setLayout(new GridLayout(0,1,0,0));
		for(Stavka stavka: stavke) {
			add(stavka);
		}
	}	
}
