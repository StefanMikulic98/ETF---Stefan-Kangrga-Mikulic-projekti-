package gui;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

public class Sladoledzinica extends Frame {
	
	private int x,y,brojUkusa=0;
	AparatZaTocenje aparatZaTocenje = new AparatZaTocenje();
	TextField nazivSladoled = new TextField(10);
	TextField bojaSladoled = new TextField(10);
	TextArea log = new TextArea();
	Label naziv = new Label("Naziv:");
	Label boja = new Label("Boja:");
	Button dodajUkus = new Button("Dodaj ukus");
	Button novi ;
	Panel centralniPanel = new Panel();
	Panel juzniPanel = new Panel();
	Panel content = new Panel();
	private int a=0, b;
	private String text;
	private ArrayList<Button> dugmad = new ArrayList<>();
	
	private void popuniProzor() {
		
		//setPreferredSize(new Dimension(450, 450));
		centralniPanel.setLayout(new GridLayout(0,1,0,0));
		centralniPanel.add(aparatZaTocenje, BorderLayout.CENTER);
		add(centralniPanel, BorderLayout.CENTER);
		
		content.setPreferredSize(new Dimension(400, 30));
		content.add(naziv);
		content.add(nazivSladoled);
		content.add(boja);
		content.add(bojaSladoled);
		content.add(dodajUkus);
		juzniPanel.setLayout(new GridLayout(0, 1, 0, 0));
		content.setBackground(Color.decode("123123"));
		juzniPanel.add(content);
		add(juzniPanel, BorderLayout.SOUTH);
		
		dodajUkus.addActionListener((ae) -> {
			
			novi = new Button(nazivSladoled.getText());
			novi.setBackground(Color.decode("#"+bojaSladoled.getText()));
			aparatZaTocenje.noviUkus(nazivSladoled.getText(), bojaSladoled.getText(), novi);
			
			pack();
			revalidate();
			repaint();			
		});
		pack();
		revalidate();
		repaint();		

	}
	public Sladoledzinica() {
		
		setBounds(400, 200, 450, 400);
		setResizable(false);
		setTitle("Sladoledzinica");
		
		popuniProzor();
		
		pack();
		
		addWindowListener(new WindowAdapter() {
			
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
		
		setVisible(true);	
	}
	

	public static void main(String[] args) {
		new Sladoledzinica();
	}
	

}
