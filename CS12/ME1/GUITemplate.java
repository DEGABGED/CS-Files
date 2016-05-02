package me1.delacruz;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

public class GUITemplate extends Canvas implements MouseListener {
	private BufferedImage img;
	private int width = 600;
	private int height = 610;
	private int cardWidth = 70;
	private int cardHeight = 95;
	private int cardMarginX = 10;
	private int cardMarginY = 20;
	private int cardSliver = 20;
	private int marginX = 20;
	private int marginY = 25;

	public GUITemplate() {
		setSize(width, height);
	}

	private int row2PositionsX(int x) { return marginX+(cardMarginX+cardWidth)*x; }
	private int row2PositionsY(int y) { return marginY+cardHeight+cardMarginY+(y*cardSliver); }

	public void paint(Graphics ga) {
		int x,y;
		Graphics2D g = (Graphics2D) ga;
		g.setColor(new Color(0xfffdd0));
		g.fillRect(0, 0, width, height);

		g.setColor(Color.BLACK);
		for(x = 0; x < 7; x++) {
			if(x != 2) g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY, cardWidth, cardHeight);

			for(y = 0; y < x; y++) {
				g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardSliver);
			}
			g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardHeight);
		}
	}

	public void mouseEntered(MouseEvent e) {

	}

	public void mouseExited(MouseEvent e) {

	}

	public void mouseClicked(MouseEvent e) {

	}

	public void mousePressed(MouseEvent e) {

	}

	public void mouseReleased(MouseEvent e) {

	}
}
