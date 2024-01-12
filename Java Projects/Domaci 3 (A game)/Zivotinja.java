package gui;

import java.awt.Color;
import java.awt.Graphics;

public abstract class Zivotinja {
	Rupa rupa;
	
	public Zivotinja(Rupa rupa) {
		this.rupa=rupa;		
	}

	protected abstract void paint(Graphics graphics);
}
