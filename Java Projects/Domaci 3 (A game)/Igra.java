package gui;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.Color;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Dialog.ModalityType;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Igra extends Frame {
	Panel centralniPanel=new Panel();
	Panel istocniPanel=new Panel();
	Panel tezinaPanel=new Panel();
	Panel rezultatPanel=new Panel();
	Button igra=new Button("Kreni");
	CheckboxGroup grupa= new CheckboxGroup();
	Checkbox lako= new Checkbox("Lako", grupa, false);
	Checkbox srednje= new Checkbox("Srednje", grupa, false);
	Checkbox tesko= new Checkbox("Tesko", grupa, false);
	Label povrce= new Label("Povrce:");
	Label povrce1= new Label("100");
	Basta basta;
	Boolean stop=false;
	

	void populateWindow() {
		
		Basta basta=new Basta(4,4,this);
		basta.setPreferredSize(new Dimension(400, 300));
		centralniPanel.add(basta);
		centralniPanel.setPreferredSize(new Dimension(400, 300));
		centralniPanel.setBackground(Color.GREEN);
		istocniPanel.setLayout(new GridLayout(0,1,0,0));
		povrce.setFont(new Font("Arial", Font.BOLD, 10));
		povrce1.setFont(new Font("Arial", Font.BOLD, 10));
		igra.setBackground(Color.LIGHT_GRAY);
		
		tezinaPanel.setLayout(new GridLayout(4,1));
		rezultatPanel.setLayout(new GridLayout(2,1,0,0));
		rezultatPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
		tezinaPanel.add(lako);
		tezinaPanel.add(srednje);
		tezinaPanel.add(tesko);
		tezinaPanel.add(igra);
		povrce.setAlignment(Label.CENTER);
		rezultatPanel.add(povrce);
		rezultatPanel.add(povrce1);
		istocniPanel.add(tezinaPanel);
		istocniPanel.add(rezultatPanel);
		
		add(centralniPanel, BorderLayout.CENTER);
		add(istocniPanel, BorderLayout.EAST);
		
		igra.addActionListener((ae) -> {
			if(ae.getActionCommand()=="Kreni") {
				igra.setActionCommand("Stani");
				igra.setLabel("Stani");               
				igra.setBackground(Color.RED);
				if(lako.getState()) {
					basta.intervalCekanja=1000;
				}
				if(srednje.getState()) {
					basta.intervalCekanja=750;
				}
				if(tesko.getState()) {
					basta.intervalCekanja=500;
				}
				
				basta.kolicinaPovrca=100;
				povrce1.setText(String.valueOf(basta.kolicinaPovrca));
				stop=false;
				basta.kraj=false;
				if (basta.thread1 != null) {
					basta.thread1.interrupt();
				}
				
				basta.thread1 = new Thread(basta);
				basta.thread1.start();
				basta.kreni();
			} else {
				igra.setActionCommand("Kreni");
				igra.setLabel("Kreni");
				igra.setBackground(Color.LIGHT_GRAY);  
				synchronized (this) {
					basta.kolicinaPovrca=100;
					basta.stani();
					stop=true;
					for(Rupa rupa:basta.rupe){
						if(rupa.thread!=null) {
							rupa.stani();
						}
					}
				}	
			}		
		});
		
		lako.addItemListener((ie) -> {
			basta.setIntervalCekanja(1000);
			basta.setBrojKoraka(10);
		});
		
		srednje.addItemListener((ie) -> {
			basta.setIntervalCekanja(750);
			basta.setBrojKoraka(8);
		});

		tesko.addItemListener((ie) -> {
			basta.setIntervalCekanja(500);
			basta.setBrojKoraka(6);
		});	
	}
	
	
	
	public Igra() {
		setBounds(700, 200, 500, 300);
		setResizable(true);
		
		setTitle("Igra");
		
		populateWindow();
		pack();
				
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
		
		setVisible(true);		
	}
	
	void prikazKrajDijalog() {
		Dialog kraj = new Dialog(this, ModalityType.APPLICATION_MODAL);
		kraj.setTitle("Kraj");
		kraj.add(new Label("Kraj igre", Label.CENTER));
		
		kraj.setBounds(700, 200, 100, 100);
		kraj.setResizable(false);
		
		povrce1.setText("0");
		igra.setActionCommand("Kreni");
		igra.setLabel("Kreni");
		igra.setBackground(Color.LIGHT_GRAY);  
		
		
		kraj.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				kraj.dispose();
			}
		});;
		
		kraj.setVisible(true);
	}
	
	public static void main(String[] args) {
		new Igra();
	}

}
