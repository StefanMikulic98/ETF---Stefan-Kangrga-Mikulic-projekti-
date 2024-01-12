package gui;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dialog;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.Dialog.ModalityType;
import java.awt.Dimension;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

public class Telefoni extends Frame {
	String broj1,boja1;
	Telefon telefon;
	Panel panel=new Panel();
	Label label=new Label();
	ArrayList<Telefon> telefoni = new ArrayList<>();
	
	public void populateWindow(){
		pack();
	}
	
	public void popuniProzor() {
		for(Telefon telefon: telefoni) {
			panel.add(telefon);
			add(panel);
		}
	}
	
	public Telefoni() {
		
		setBounds(700, 200, 500, 500);
		setResizable(true);
		
		setTitle("Telefoni");
		
		populateWindow();
		obavestenjeDialog();
		unosDialog();
		pack();
		
		addComponentListener(new ComponentAdapter() {
			public void componentResized(ComponentEvent e) {
				pack();
			}
		});
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				telefoni.clear();
				dispose();
			}
		});
		
		setVisible(true);
	}

	private void unosDialog() {
		Panel panel1=new Panel();
		Button dodaj=new Button("Dodaj");
		Button kraj=new Button("Kraj");
		TextField broj=new TextField(8);
		TextField boja=new TextField(8);
		Dialog unos = new Dialog(this, ModalityType.APPLICATION_MODAL);
		//Telefon telefon;
		
		unos.setTitle("Novi telefoni");
		
		panel1.setLayout(new GridLayout(0,1,0,0));
		panel1.add(new Label("Broj"));
		panel1.add(broj);
		panel1.add(new Label("Boja"));
		panel1.add(boja);
		panel1.add(dodaj);
		panel1.add(kraj);
		unos.add(panel1);
		
		unos.setBounds(700, 200, 200, 200);
		unos.setResizable(true);
		
		dodaj.addActionListener((ae) -> {
			
			broj1=broj.getText();
			boja1=boja.getText();
			telefon=new Telefon(broj1, Color.decode("#"+boja1));
			telefoni.add(telefon);
			broj.setText("");
			boja.setText("");
			panel.add(telefon);
			add(panel);
			repaint();
		});
		
		kraj.addActionListener((ae) -> {
			popuniProzor();
			unos.dispose();
		});
			
		unos.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				unos.dispose();
			}
		});
		
		unos.setVisible(true);
	}

	
	private void obavestenjeDialog() {
		Panel panel2=new Panel();
		TextArea text= new TextArea();
		Dialog obavestenje = new Dialog(this, ModalityType.APPLICATION_MODAL);
		obavestenje.setTitle("Pojasnjenje");
		
		text.insert("Potrebno je u sledecem prozoru uneti broj telefona\n (zapamtice se samo prvih 7 brojeva) i ime korisnika\n i kliknuti na dugme Dodaj da bi se uneo telefon\n i tako je moguce proizvoljan broj puta. \n Za kraj unosa telefona kliknuti na dugme Kraj.",0);;
		panel2.add(text);
		obavestenje.add(panel2);
		
		obavestenje.setBounds(700, 200, 150, 150);
		obavestenje.pack();
		obavestenje.setResizable(true);
			
		obavestenje.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				obavestenje.dispose();
			}
		});
		
		obavestenje.setVisible(true);
	}
	
	
	public static void main(String[] args) {
		new Telefoni();
	}

}
