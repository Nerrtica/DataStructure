package AB;

import java.util.Scanner;

import javax.swing.JOptionPane;

public class ABTest {

	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub
		Manager manager = new Manager();
		MainThread t1 = new MainThread(manager);
		TimerThread t2 = new TimerThread(manager);
		
		
		t1.start();
		t2.start();
		t1.join();
		t2.join();
	}

}

class MainThread extends Thread{
	Manager mainManager;
	private String str;
	
	MainThread(Manager manager){
		mainManager = manager;
	}
	public void run(){
		while(mainManager.life > 0){
			mainManager.setCount();
			while(mainManager.count > 0){
				mainManager.showQ();
				str = JOptionPane.showInputDialog("문제맞춰");
				if(str.equalsIgnoreCase(mainManager.word[mainManager.random])){
					mainManager.life++;
					System.out.println("Bingo! life: " + mainManager.life);
					mainManager.score++;
					break;
				}
				else{
					mainManager.life--;
					System.out.println("Fail life: " + mainManager.life);
					break;
				}
			}
		}
		System.out.println("Game end!");
		System.out.println("Final Score : " + mainManager.score);
		System.exit(0);
	}
	
}

class TimerThread extends Thread{
	Manager tmanager;
	
	TimerThread(Manager manager){
		tmanager = manager;
	}
	public void run(){
		while(tmanager.life > 0){
			tmanager.setCount();
			while(tmanager.count > 0){
				System.out.println("Time: " + tmanager.count + "..");
				try {
					sleep((long)1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				tmanager.count--;
			}
			tmanager.life--;
			System.out.println("Time minus life: " + tmanager.life);
			if(tmanager.life == 0) break;
			tmanager.showQ();
		}
		System.out.println("Game end!");
		System.out.println("Final Score : " + tmanager.score);
		System.exit(0);
	}
	
}

class Manager{
	public String[] word = {"SnowMan","Make","With","me","Angry","Sad","Write","Java"};
	public int random, count;
	public int life = 4, score = 0;
	
	public void showQ() {
		random =(int)(Math.random() * word.length);
		System.out.println("Problem : " + word[random]);
	}
	
	public void setCount(){
		if(score == 0) count = 10;
		else{
			count = 10 - (score/2);
		}
	}
}