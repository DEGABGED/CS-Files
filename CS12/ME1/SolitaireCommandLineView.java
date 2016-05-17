package me1.delacruz;

public class SolitaireCommandLineView implements SolitaireView {
	public void updateView(Solitaire game, int[] args) {
		int b = 0;
		int fndtotal = 0;

		//Print Stock, Talon, and Foundations
		System.out.println(Constant.STFTOP);
		System.out.print(String.format(Constant.CARDTEXT, game.getStock().peek() == null ? "   " : game.getStock().peek()) +
			String.format(Constant.CARDTEXT, game.getTalon().peek() == null ? "   " : game.getTalon().peek()) + Constant.CARDWIDTH);
		for(Deck x : game.getFoundations()){
			System.out.print(String.format(Constant.CARDTEXT, x.peek() == null ? "   " : x.peek()));
			fndtotal += x.getSize();
		}
		System.out.print("\n");
		for(b=0; b<3; b++){
			System.out.println(Constant.STFBODY);
		}
		System.out.println(Constant.STFBOTTOM);

		//Print Labels
		System.out.println(" Stock  Talon " + Constant.CARDWIDTH +
			String.format(Constant.CARDMARGIN, Constant.SPDS) +
			String.format(Constant.CARDMARGIN, Constant.HRTS) +
			String.format(Constant.CARDMARGIN, Constant.DMND) +
			String.format(Constant.CARDMARGIN, Constant.CLBS));
		System.out.println(" Redeals left: " + game.getRedealsLeft() +
			", Stock: " + game.getStock().getSize() +
			", Foundations: " + fndtotal + "");
		System.out.println(" Moves: " + game.getMoveCount() + "\n");
		for(int x=1; x<8; x++){
			System.out.print(String.format(Constant.CARDMARGIN, x));
		}
		System.out.print("\n");

		//Print Tableus
		Deck[] tableuRev = new Deck[7];
		for(b=0; b<7; b++){
			tableuRev[b] = new Deck();
			while(!game.getTableus()[b].isEmpty()) tableuRev[b].push(game.getTableus()[b].pop());
		}

		boolean someRemain = true;
		while(someRemain){
			someRemain = false;
			for(b=0; b<7; b++){
				if(!tableuRev[b].isEmpty()){
					game.getTableus()[b].push(tableuRev[b].pop());
					System.out.print(String.format(Constant.CARDTOPTMPL, game.getTableus()[b].peek()));
					someRemain = true;
				} else  {
					System.out.print(Constant.CARDWIDTH);
				}
			}
			System.out.print("\n");
		}
	}
}
