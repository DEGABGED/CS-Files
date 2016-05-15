package me1.delacruz;

import java.awt.*;
import javax.swing.*;
import java.util.*;
import java.awt.image.*;


public class CanvasManager extends Thread {
	private final int FRAME_DELAY = 200; // 20ms. implies 50fps (1000/20) = 50

	private Canvas canvas;
	private long start;
	private int x, y;

	public CanvasManager(Canvas canvas) {
		this.canvas = canvas;
	}

	public void run() {
		start = System.currentTimeMillis();

		canvas.createBufferStrategy(2);
		BufferStrategy strategy = canvas.getBufferStrategy();
		Graphics g = null;
		// Ignore; the program won't loop forever
		// while (true) {
		// 	g = strategy.getDrawGraphics();
		// 	paint(g);
		// 	strategy.show();//SHOW BACK BUFFER
		// 	syncFramerate();
		// }
	}


	private void paint(Graphics g) {
		/**************************************************************/
		// THIS IS FOR THE BACK BUFFER OF THE CANVAS
		// YOU CAN PUT HERE EVERYTHING YOU NEED TO DISPLAY IN THE CANVAS
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
		g.setColor(Color.BLACK);
		g.fillRect(x++,y++,50,50);
		/**************************************************************/

		g.dispose();
	}

	private void syncFramerate() {
		start = start + FRAME_DELAY;
		long difference = start - System.currentTimeMillis();
		try {
			Thread.sleep(Math.max(0, difference));
		}
		catch(InterruptedException e) {
			e.printStackTrace();
		}
	}

}
