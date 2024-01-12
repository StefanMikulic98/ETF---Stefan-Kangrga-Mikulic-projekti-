package gui;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;

public class Telefon extends Panel {
	Broj brojTelefona;
	Color boja;
	Imenik imenikTelefona=new Imenik();
	Tastatura tastaturaTelefona;
	String kod="", poziv="", poziv1="";
	Panel ekran= new Panel();   //za labele ekran1 i ekran2
	Label ekran1=new Label();  //za broj telefona kontakta
	Label ekran2=new Label();	// za ime kontakta
	Label br= new Label();
	Panel dugmad= new Panel();
	Button dodajKontakt;
	Button iskljuciTelefon;
	String novoImeKontakta, noviBrojTelefona;
	
	public Telefon(String brojTelefona, Color boja) {
		
		razdvojBroj(brojTelefona);
		this.brojTelefona= new Broj( Integer.parseInt(kod), Integer.parseInt(poziv),Integer.parseInt(poziv1));
		this.boja=boja;
		tastaturaTelefona= new Tastatura(this);
		
		popuniProzor();	
	}
	
	public void popuniProzor(){
		setPreferredSize(new Dimension(300, 550));
		ekran.setBackground(boja);
		ekran.setLayout(new GridLayout(0,1,0,0));
		ekran2.setFont(new Font("Arial", Font.BOLD, 20));
		ekran.add(ekran1);
		ekran.add(ekran2);
		ekran.setPreferredSize(new Dimension(300, 50));
		
		imenikTelefona.setBackground(boja);
		imenikTelefona.setPreferredSize(new Dimension(200, 300));
		tastaturaTelefona.setPreferredSize(new Dimension(300, 180));
		this.setLayout(new GridLayout(0,1,0,0));
		add(ekran);
		add(tastaturaTelefona);
		add(imenikTelefona);
		iskljuciTelefon= new Button("Iskljuci telefon");
		iskljuciTelefon.setBackground(Color.GRAY);
		dodajKontakt= new Button("Dodaj kontakt broj");
		dodajKontakt.setBackground(Color.LIGHT_GRAY);
		dugmad.setLayout(new GridLayout(1,0,0,0));
		dugmad.add(dodajKontakt);
		dugmad.add(iskljuciTelefon);
		dugmad.setPreferredSize(new Dimension(300, 10));
		dugmad.setBackground(Color.YELLOW);
		add(dugmad);
		br.setText(brojTelefona.toString());
		br.setBackground(boja);
		br.setPreferredSize(new Dimension(300, 10));
		br.setAlignment(Label.CENTER);
		add(br);
		
		iskljuciTelefon.addActionListener((ae) -> {
			if(ae.getActionCommand()=="Iskljuci telefon") {
				iskljuciTelefon.setActionCommand("Ukljuci telefon");
				iskljuciTelefon.setLabel("Ukljuci telefon");
				dodajKontakt.setEnabled(false);
				iskljuciTelefon.setBackground(Color.RED);
			} else {
				iskljuciTelefon.setActionCommand("Iskljuci telefon");
				iskljuciTelefon.setLabel("Iskljuci telefon");
				dodajKontakt.setEnabled(true);
				iskljuciTelefon.setBackground(Color.GRAY);
			}
		
		});
		
		dodajKontakt.addActionListener((ae) -> {
			if(ae.getActionCommand()=="Dodaj kontakt broj") {
				novoImeKontakta=ekran1.getText();
				dodajKontakt.setLabel("Dodaj kontakt ime");
				tastaturaTelefona.zameniTastaturu();
			} else {
				noviBrojTelefona=ekran2.getText();
				dodajKontakt.setLabel("Dodaj kontakt broj");
				imenikTelefona.dodajKontakte(new Kontakt(novoImeKontakta, noviBrojTelefona));
				ekran1.setText("");
				ekran2.setText("");
				tastaturaTelefona.zameniTastaturu();
				imenikTelefona.prikazStavki();
			}
			revalidate();
			repaint();
			
			
		});
		
	}
	
	public String dohvatiBrojtelefona() {
		return brojTelefona.toString();
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
