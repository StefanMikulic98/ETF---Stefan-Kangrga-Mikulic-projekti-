package gui;

import java.awt.Button;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.util.Timer;
import java.util.TimerTask;
	
public class Tastatura extends Panel {
	//private Thread thread;
	int i=1;
	String slova, slovo;
	int brojSlova;
	Timer timer=new Timer();;
	Boolean timer2=false,
			timer3=false,
			timer4=false,
			timer5=false,
			timer6=false,
			timer7=false,
			timer8=false,
			timer9=false;
	
	
	Button dugme1=new Button("1"),
		   dugme2=new Button("2"), 
		   dugme3=new Button("3"), 
		   dugme4=new Button("4"), 
		   dugme5=new Button("5"), 
		   dugme6=new Button("6"), 
		   dugme7=new Button("7"), 
		   dugme8=new Button("8"), 
		   dugme9=new Button("9"), 
		   dugme0=new Button("0"), 
		   dugmeZ=new Button("*"), 
		   dugmeP=new Button("+");
	Button dugmeABC,dugmeDEF, dugmeGHI, dugmeJKL, dugmeMNO, dugmePQRS, dugmeTUV, dugmeWXYZ;
	Telefon telefon;
	
	public Tastatura(Telefon telefon) {
		this.telefon=telefon;
		
		setLayout(new GridLayout(4,3,0,0));
		add(dugme0);
		add(dugme1);
		add(dugme2);
		add(dugme3);
		add(dugme4);
		add(dugme5);
		add(dugme6);
		add(dugme7);
		add(dugme8);
		add(dugme9);
		add(dugmeZ);
		add(dugme0);
		add(dugmeP);
		
		dugme0.addActionListener((ae) -> {
			if(ae.getActionCommand()=="0") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
			}
		});
		dugme1.addActionListener((ae) -> {
			if(ae.getActionCommand()=="1") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
			}		
		});
		dugme2.addActionListener((ae) -> {
			slova="ABC";
			brojSlova=3;
			if(ae.getActionCommand()=="2") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer2) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme3.addActionListener((ae) -> {
			if(ae.getActionCommand()=="3") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer3) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme4.addActionListener((ae) -> {
			if(ae.getActionCommand()=="4") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer4) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}			
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme5.addActionListener((ae) -> {
			if(ae.getActionCommand()=="5") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer5) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme6.addActionListener((ae) -> {
			if(ae.getActionCommand()=="6") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer6) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme7.addActionListener((ae) -> {
			if(ae.getActionCommand()=="7") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer7) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme8.addActionListener((ae) -> {
			if(ae.getActionCommand()=="8") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer8) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugme9.addActionListener((ae) -> {
			if(ae.getActionCommand()=="9") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				if(!timer9) {
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}	
				else {
					if(telefon.ekran2.getText()!="") {telefon.ekran2.setText(telefon.ekran2.getText().substring(0,telefon.ekran2.getText().length()-1));}
					telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				}
				promeniSlovo(ae);
			}
		});
		dugmeZ.addActionListener((ae) -> {
			if(ae.getActionCommand()=="*") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				promeniSlovo(ae);
			}
		});
		dugmeP.addActionListener((ae) -> {
			if(ae.getActionCommand()=="#") {
				telefon.ekran1.setText(telefon.ekran1.getText()+ ae.getActionCommand());
			}
			else {
				telefon.ekran2.setText(telefon.ekran2.getText()+ ae.getActionCommand());
				promeniSlovo(ae);
			}
		});
	}

	private void promeniSlovo(ActionEvent ae) {
		Boolean kraj=false;
		
		switch(ae.getActionCommand()) {
		case "C":{ ((Button)ae.getSource()).setActionCommand("A"); break;}
		case "B":{ ((Button)ae.getSource()).setActionCommand("C"); break;}
		case "A":{ ((Button)ae.getSource()).setActionCommand("B");timer.schedule(new RemindTask(), 1000);timer2=true;   break;}
		case "F":{ ((Button)ae.getSource()).setActionCommand("D"); break;}
		case "E":{ ((Button)ae.getSource()).setActionCommand("F"); break;}
		case "D":{ ((Button)ae.getSource()).setActionCommand("E");timer.schedule(new RemindTask(), 1000);timer3=true; break;}
		case "G":{ ((Button)ae.getSource()).setActionCommand("H"); timer.schedule(new RemindTask(), 1000);timer4=true; break;}
		case "H":{ ((Button)ae.getSource()).setActionCommand("I"); break;}
		case "I":{ ((Button)ae.getSource()).setActionCommand("G"); break;}
		case "J":{ ((Button)ae.getSource()).setActionCommand("K"); timer.schedule(new RemindTask(), 1000);timer5=true;break;}
		case "K":{ ((Button)ae.getSource()).setActionCommand("L"); break;}
		case "L":{ ((Button)ae.getSource()).setActionCommand("J"); break;}
		case "M":{ ((Button)ae.getSource()).setActionCommand("N");timer.schedule(new RemindTask(), 1000);timer6=true; break;}
		case "N":{ ((Button)ae.getSource()).setActionCommand("O"); break;}
		case "O":{ ((Button)ae.getSource()).setActionCommand("M"); break;}
		case "P":{ ((Button)ae.getSource()).setActionCommand("Q");timer.schedule(new RemindTask(), 1000);timer7=true; break;}
		case "Q":{ ((Button)ae.getSource()).setActionCommand("R"); break;}
		case "R":{ ((Button)ae.getSource()).setActionCommand("S"); break;}
		case "S":{ ((Button)ae.getSource()).setActionCommand("P"); break;}
		case "T":{ ((Button)ae.getSource()).setActionCommand("U"); timer.schedule(new RemindTask(), 1000);timer8=true;break;}
		case "U":{ ((Button)ae.getSource()).setActionCommand("V"); break;}
		case "V":{ ((Button)ae.getSource()).setActionCommand("T"); break;}
		case "W":{ ((Button)ae.getSource()).setActionCommand("X"); timer.schedule(new RemindTask(), 1000);timer9=true;break;}
		case "X":{ ((Button)ae.getSource()).setActionCommand("Y"); break;}
		case "Y":{ ((Button)ae.getSource()).setActionCommand("Z"); break;}
		case "Z":{ ((Button)ae.getSource()).setActionCommand("W"); break;}
		
		}
	}
	
	public void zameniTastaturu() {
		if(dugme0.getActionCommand()=="0") {
			dugme2.setActionCommand("A");
			dugme2.setLabel("ABC");
			dugme3.setActionCommand("D");
			dugme3.setLabel("DEF");
			dugme4.setActionCommand("G");
			dugme4.setLabel("GHI");
			dugme5.setActionCommand("J");
			dugme5.setLabel("JKL");
			dugme6.setActionCommand("M");
			dugme6.setLabel("MNO");
			dugme7.setActionCommand("P");
			dugme7.setLabel("PQRS");
			dugme8.setActionCommand("T");
			dugme8.setLabel("TUV");
			dugme9.setActionCommand("W");
			dugme9.setLabel("WXYZ");
			dugme0.setActionCommand("_");
			dugme0.setLabel("_");
			dugme1.setLabel("");
			dugmeZ.setLabel("");
			dugmeP.setLabel("");
		} //dugmeABC,dugmeDEF, dugmeGHI, dugmeJKL, dugmeMNO, dugmePQRS, dugmeTUV, dugmeWXYZ;
		else {
			dugme2.setActionCommand("2");
			dugme2.setLabel("2");
			dugme3.setActionCommand("3");
			dugme3.setLabel("3");
			dugme4.setActionCommand("4");
			dugme4.setLabel("4");
			dugme5.setActionCommand("5");
			dugme5.setLabel("5");
			dugme6.setActionCommand("6");
			dugme6.setLabel("6");
			dugme7.setActionCommand("7");
			dugme7.setLabel("7");
			dugme8.setActionCommand("8");
			dugme8.setLabel("8");
			dugme9.setActionCommand("9");
			dugme9.setLabel("9");
			dugme0.setActionCommand("0");
			dugme0.setLabel("0");
			dugme1.setLabel("1");
			dugmeZ.setLabel("+");
			dugmeP.setLabel("T");
		}
	}
	
	
	class RemindTask extends TimerTask{

		@Override
		public void run() {
			timer2=false;
			timer3=false;
			timer4=false;
			timer5=false;
			timer6=false;
			timer7=false;
			timer8=false;
			timer9=false;
			dugme2.setActionCommand("A");
			dugme3.setActionCommand("D");
			dugme4.setActionCommand("G");
			dugme5.setActionCommand("J");
			dugme6.setActionCommand("M");			
			dugme7.setActionCommand("P");
			dugme8.setActionCommand("T");
			dugme9.setActionCommand("W");
		}
		
	}
}
