package mighty;

import java.util.*;

public class ShuffleCard {
	private LinkedList<Card> cardDeque;
	
	public ShuffleCard(LinkedList<Card> card){
		this.cardDeque = card;
		Collections.shuffle(cardDeque);		
	}
	
	public void allocateCard(Player player){
		
	}
}
