package gui;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Rupa extends Canvas implements Runnable{
	enum Stanje1{
		SLOBODNO,
		ZAUZETO		
	};
	enum Stanje2{
		UHVACEN,
		NEUHVACEN		
	};
	Basta vlasnik;
	Krtica zivotinja;
	Stanje1 stanje1=Stanje1.SLOBODNO;
	Stanje2 stanje2=Stanje2.NEUHVACEN;
	int maksKoraka=10, trenutniKorak=0;
	Thread thread;
	private boolean radi=false;
	
	public Rupa(Basta basta){
		this.vlasnik=basta;
		//this.zivotinja=new Krtica(this);
		this.zivotinja=null;
		setBackground(Color.decode("#CD853F"));
		
		addMouseListener(new MouseAdapter() {

			@Override
			public void mousePressed(MouseEvent e) {
				stanje2=Stanje2.UHVACEN;
				//setBackground(Color.decode("#FF0000"));
			}
		});
	}
	
	@Override
	public void paint(Graphics g) {
		/*zavrsi();
		thread = new Thread(this);
		thread.start();*/
		if (thread != null) {
			thread.interrupt();
		}
		thread = new Thread(this);
		thread.start();
		kreni();
	}
	
	public synchronized Krtica getZivotinja() {
		return zivotinja;
	}

	public synchronized void setZivotinja(Krtica zivotinja) {
		this.zivotinja = zivotinja;
	}
	
	public synchronized int getMaksKoraka() {
		return maksKoraka;
	}

	public synchronized void setMaksKoraka(int maksKoraka) {
		this.maksKoraka = maksKoraka;
	}

	public synchronized int getTrenutniKorak() {
		return trenutniKorak;
	}

	public synchronized void setTrenutniKorak(int trenutniKorak) {
		this.trenutniKorak = trenutniKorak;
	}
	
	public synchronized Stanje1 getStanje1() {
		return stanje1;
	}

	public synchronized void setStanje1(Stanje1 stanje) {
		this.stanje1 = stanje;
	}
	
	public synchronized Stanje2 getStanje2() {
		return stanje2;
	}

	public synchronized void setStanje2(Stanje2 stanje2) {
		this.stanje2 = stanje2;
	}
	
	public synchronized boolean isSlobodan() {
		return stanje1==Stanje1.SLOBODNO;
	}

	@Override
	public void run() {	
		Graphics g = this.getGraphics();
		try {
			synchronized (this) {			
				while(!radi){				
					wait();					
				}							
			} 	
			
			//setBackground(Color.decode("#CD853F"));
			g.translate(this.getWidth() / 2, this.getHeight() / 2);		
			if(zivotinja!=null) {
				zivotinja.paint(getGraphics());
			}
			thread.sleep(2000);
			
			g.clearRect(-this.getWidth() , -this.getHeight(), 4*this.getWidth(), 4*this.getHeight());
			stanje1=Stanje1.SLOBODNO;
			this.stani();
			
			synchronized (this.vlasnik) {
				if(stanje2==Stanje2.UHVACEN) {
					stanje2=Stanje2.NEUHVACEN;
					//setBackground(Color.decode("#FF0000"));
					//setBackground(Color.decode("#CD853F"));
				} else {
					if(vlasnik.vlasnik.stop!=true) {
						vlasnik.smanjiKolicinu();
						if(vlasnik.kolicinaPovrca<=0) {
							vlasnik.kraj=true;
						}else {
							vlasnik.vlasnik.povrce1.setText(String.valueOf(vlasnik.kolicinaPovrca));
							vlasnik.vlasnik.povrce1.revalidate();
						}
					}
				}
			}
		} catch(InterruptedException e) {g.clearRect(-this.getWidth(), -this.getHeight(), 4*this.getWidth(), 4*this.getHeight());}//-this.getWidth() / 2, -this.getHeight() / 2, 2*this.getWidth(), 2*this.getHeight());
		
		synchronized (this) {
			g.clearRect(-this.getWidth(), -this.getHeight(), 4*this.getWidth(), 4*this.getHeight());
			this.zivotinja=null;
			thread = null;
			notify();
		}
	}
	
	public synchronized void zavrsi() {
		if(thread != null) {
			thread.interrupt();
			thread= null;
		}
	}
	
	public synchronized void kreni() {
		radi = true;
		//notify();
	}
	
	public synchronized void stani() {
		radi = false;
	}
 
	public synchronized boolean pokrenut() {
		return thread.isAlive();	
	}
}
