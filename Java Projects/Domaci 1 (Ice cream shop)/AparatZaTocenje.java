package gui;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;

public class AparatZaTocenje extends Panel{
	Thread thread;
	private Boolean kraj=false;
	private Boolean traje=true;
	private int x,y,brojUkusa=0;
	MestoZaTocenje mestoZaTocenje=new MestoZaTocenje(this);
	Sladoled sladoled=new Sladoled();
	ArrayList<String> dodatiUkusi = new ArrayList<>();
	Button prodaj=new Button("Prodaj");
	Panel sladoledPanel= new Panel();
	Panel dostupniUkusi= new Panel();
	Panel istocniPanel= new Panel();
	Panel juzniPanel= new Panel();
	Label sladoled1 = new Label("Sladoled:");
	Label opisSladoleda = new Label("");
	Button novi;
	
	public AparatZaTocenje() {
		
		setPreferredSize(new Dimension(400, 400));
		dostupniUkusi.setPreferredSize(new Dimension(350, 350));
		dostupniUkusi.setBackground(Color.LIGHT_GRAY);
		sladoledPanel.add(dostupniUkusi, BorderLayout.CENTER);
		
		istocniPanel.setPreferredSize(new Dimension(50, 350));
		istocniPanel.setLayout(new GridLayout(0,1,0,0));
		prodaj.setBackground(Color.LIGHT_GRAY);
		prodaj.setEnabled(false);
		istocniPanel.add(prodaj);
		istocniPanel.add(mestoZaTocenje);
		sladoledPanel.add(istocniPanel, BorderLayout.EAST);
		add(sladoledPanel);
		
		juzniPanel.setPreferredSize(new Dimension(500, 40));
		sladoled1.setFont(new Font("Arial", Font.BOLD, 10));
		sladoled1.setAlignment(Label.LEFT);
		opisSladoleda.setAlignment(Label.LEFT);
		opisSladoleda.setSize(new Dimension(40, 30));
		juzniPanel.add(sladoled1);
		juzniPanel.add(opisSladoleda);
		juzniPanel.setBackground(Color.GRAY);
		add(juzniPanel);
		
		prodaj.addActionListener((ae) -> {
			sladoled.setTrenutnaKolicina(0);
			for(Ukus ukus:sladoled.ukusi) {
				ukus.setKolicina(0);
			}
			dodatiUkusi.clear();
			//mestoZaTocenje.repaint();
			prodaj.setEnabled(false);
		});		
		
		revalidate();
	}
	
	public void noviUkus(String naziv, String boja, Button novi) {
		kraj=false;
		sladoled.dodajUkus(naziv, boja, novi);	// boja	
		brojUkusa++;
		novi.setActionCommand(naziv);
		
		if(brojUkusa%2==0) {
			x=y=brojUkusa/2;
			dostupniUkusi.setLayout(new GridLayout(x,y,0,0));
		}
		else {
			x=brojUkusa/2+1;
			y=brojUkusa/2;
			dostupniUkusi.setLayout(new GridLayout(x,y,0,0));
		}
		
		/*novi.addMouseListener(new MouseAdapter() {

			@Override
			public void mouseClicked(MouseEvent e) {}

			@Override
			public void mousePressed(MouseEvent e) {
				try {
					Thread.sleep(500);
				sladoled.puniSladoled(((Button)e.getSource()).getActionCommand());
				mestoZaTocenje.repaint();
				if(sladoled.trenutnaKolicina==200) {
					prodaj.setEnabled(true);
				}
				opisSladoleda.setText(sladoled.toString());
				for(String ime:dodatiUkusi) {
					if(((Button)e.getSource()).getActionCommand()==ime) {kraj=true; break;
					}
				}
				if(!kraj) {dodatiUkusi.add(((Button)e.getSource()).getActionCommand());kraj=false;}
				kraj=false;
				mestoZaTocenje.repaint();
				} catch (InterruptedException e1) {}
			}
			
			@Override
			public void mouseReleased(MouseEvent e) {traje=false;}
				
		});*/
		
		novi.addMouseMotionListener(new MouseMotionAdapter() {

			@Override
			public synchronized void mouseDragged(MouseEvent e) {
				try {
					Thread.sleep(500);
				sladoled.puniSladoled(((Button)e.getSource()).getActionCommand());
				mestoZaTocenje.repaint();
				if(sladoled.trenutnaKolicina==200) {
					prodaj.setEnabled(true);
				}
				opisSladoleda.setText(sladoled.toString());
				for(String ime:dodatiUkusi) {
					if(((Button)e.getSource()).getActionCommand()==ime) {kraj=true; break;
					}
				}
				if(!kraj) {dodatiUkusi.add(((Button)e.getSource()).getActionCommand());kraj=false;}
				kraj=false;
				mestoZaTocenje.repaint();
				} catch (InterruptedException e1) {}
					
			}

			@Override
			public void mouseMoved(MouseEvent e) {}
			
		});
		dostupniUkusi.add(novi);
		//pack();
		//revalidate();
		//repaint();
	}
	
	
};
