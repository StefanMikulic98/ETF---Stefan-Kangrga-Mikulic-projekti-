package gui;

import java.awt.Color;
import java.awt.Graphics;

public class Krtica extends Zivotinja {


	public Krtica(Rupa rupa) {
		super(rupa);
	}

	@Override
	protected void paint(Graphics graphics) {
		graphics.setColor(Color.decode("#696969"));
				
		try {
		//int angle = 0;  //********************************
		//while(angle<=360) { //********************************
		int trenutniKorak = 0, procenat=0, x=0, y=0;
		while(trenutniKorak<rupa.maksKoraka+1) {
			rupa.thread.sleep(100);
			if(rupa.thread.interrupted()) {
				break;
			}
			procenat=trenutniKorak/rupa.maksKoraka;
			x=rupa.getWidth()/2-trenutniKorak*(rupa.getWidth()/rupa.maksKoraka)/2;
			y=rupa.getWidth()/2-trenutniKorak*(2*rupa.getHeight()/(3*rupa.maksKoraka))/2;
			graphics.fillOval(x, y, trenutniKorak*(rupa.getWidth()/rupa.maksKoraka), trenutniKorak*(2*rupa.getHeight()/(3*rupa.maksKoraka)));///0, 0, procenat*(rupa.getWidth()), procenat*(2*rupa.getHeight()/3)/
			trenutniKorak++;
			
			
			
			
			//////////////////////////////////////////////////////////////////////
			//za testiranje
			//graphics.fillArc(40, 0, 40, 40, 0, angle);//********************************
			//if(angle>360-(360/rupa.maksKoraka)) {//********************************
			//	angle+=(359-angle);	//********************************
			//}//********************************
			//else {//********************************
			//	angle+=(360/rupa.maksKoraka);//********************************
			//}//********************************
		//} //********************************
			}
		} catch(InterruptedException e) {
			graphics.clearRect(-rupa.getWidth(), -rupa.getHeight(), 4*rupa.getWidth(), 4*rupa.getHeight());
		}
	}

}
