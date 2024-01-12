package gui;

import java.awt.Button;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


public class MestoZaTocenje extends Canvas {
	private Boolean kraj;
	private int x,y; 
	AparatZaTocenje vlasnik;
	//Sladoled sladoled;
	String ime;
	
	public MestoZaTocenje(AparatZaTocenje vlasnik) {
		this.vlasnik = vlasnik;	
		repaint();
		//this.sladoled=new Sladoled();
	}
	
	public String getIme() {
		return ime;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}

	public void paint(Graphics g) {
		int x1,y1, z;
		x=getWidth();
		y=getHeight();
		//y=0;
		z=getHeight()/10;
		//g.translate(0, y);
		
		for(String ime: vlasnik.dodatiUkusi) {
			for(Ukus ukus: vlasnik.sladoled.ukusi) {
				if(ime==ukus.getNaziv()) {
					g.setColor(Color.decode(ukus.getBoja()));					
					y1=(ukus.getKolicina()/20)*z;
					g.fillRect(0, y-y1, x, y1);
					y-=y1;
					//g.setColor(Color.decode(ukus.getBoja()));					
					//y1=(ukus.getKolicina()/20)*z;
					//g.fillRect(0, y  , x, y1);
					//y+=y1;
					break;
				}
			}
		}	
	}
	
}
