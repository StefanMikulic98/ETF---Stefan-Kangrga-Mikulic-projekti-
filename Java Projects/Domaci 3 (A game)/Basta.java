package gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Panel;
import java.util.ArrayList;

import gui.Rupa.Stanje1;
import gui.Rupa.Stanje2;

public class Basta extends Panel implements Runnable{
	ArrayList<Rupa> rupe = new ArrayList<>();
	int kolicinaPovrca=100;
	int intervalCekanja, noviIntervalCekanja, brojKoraka, redovi, kolone, brojRupe, trenutniKorakRupe=0;
	Igra vlasnik;
	Thread thread1;
	boolean radi=false, kraj=false;
	
	public Basta(int redovi, int kolone, Igra igra){
		this.vlasnik=igra;
		//setPreferredSize(new Dimension(320, 300));
		setLayout(new GridLayout(4,4,15,15));
		for(int i=0; i<16; i++) {
			Rupa rupa=new Rupa(this);
			rupe.add(rupa);
			add(rupa);
		}
		
		setBackground(Color.GREEN);
	}

	public synchronized int getBrojKoraka() {
		return brojKoraka;
	}

	public synchronized void setBrojKoraka(int brojKoraka) {
		this.brojKoraka = brojKoraka;
		for(Rupa rupa:rupe) {
			rupa.setMaksKoraka(brojKoraka);
		}
	}
		
	public synchronized void setIntervalCekanja(int intervalCekanja) {
		this.intervalCekanja = intervalCekanja;
	}

	public synchronized void smanjiKolicinu() {
		this.kolicinaPovrca -=1;
	}

	@Override
	public void run() {
		try {
			while(!thread1.isInterrupted()) { 
				
				synchronized (this) {
					while(!radi){	
						//noviIntervalCekanja=intervalCekanja;
						wait();
					}
				}
				
				thread1.sleep(intervalCekanja);
				intervalCekanja=(int)(intervalCekanja*0.99);
				brojRupe=(int)(Math.random() * 16);
					
				if(rupe.get(brojRupe).getStanje1()==Stanje1.SLOBODNO) {
					Krtica krtica=new Krtica(rupe.get(brojRupe));
					//rupe.get(brojRupe).setTrenutniKorak(trenutniKorakRupe);
					rupe.get(brojRupe).setStanje1(Stanje1.ZAUZETO);
					rupe.get(brojRupe).setZivotinja(krtica);
					rupe.get(brojRupe).repaint();
				}
				
				if(kraj) {
					vlasnik.prikazKrajDijalog();
					stani();
					vlasnik.stop=true;
					for(Rupa rupa:rupe){
						if(rupa.thread!=null) {
							rupa.stani();
						}
					}
				}
			}
		} catch(InterruptedException e) {}
	}
	
	/*public synchronized void zavrsi() {
		if(thread1 != null) {
			thread1.interrupt();
		}
		while (thread1 != null) {
			try {
				wait();
			} catch (InterruptedException e) {}
		}
	}*/
	
	public synchronized void kreni() {
		radi = true;
		notify();
	}
	
	public synchronized void stani() {
		radi = false;
	}
	
}
