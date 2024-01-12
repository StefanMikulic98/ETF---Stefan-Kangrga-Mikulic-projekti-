package gui;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;

public abstract class Stavka extends Panel {
	Label naslov;
	Label tekst;
	Broj broj;
	String kod="", poziv="", poziv1="";
	
	public Stavka(String naslov, String tekst) {
		this.naslov=new Label(naslov);
		this.tekst=new Label(tekst);
		//this.naslov.setAlignment(Label.CENTER);
		//this.tekst.setAlignment(Label.CENTER);
		//this.naslov.setFont(new Font("Arial", Font.BOLD, 10));
		//this.tekst.setFont(new Font("Arial", Font.ITALIC, 10));
		this.setLayout(new GridLayout(0,1,0,0));
		this.tekst.setFont(new Font("Arial", Font.BOLD, 20));
		this.naslov.setAlignment(Label.LEFT);
		this.tekst.setAlignment(Label.LEFT);
		this.add(this.naslov);
		this.add(this.tekst);
		
	}

	public void setNaslov(String naslov) {
		this.naslov.setName(naslov); 
	}
	
	public void razdvojBroj(String broj) {
		int i=0;
		for(i=0;i<3;i++) {
			kod+=broj.charAt(i);
		}
		
		for(i=3;i<5;i++) {
			poziv+=broj.charAt(i);
		}
		
		for(i=5;i<7;i++) {
			poziv1+=broj.charAt(i);
		}
	}
}
