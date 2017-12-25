import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class InputThread extends Thread {

	private List<ProcessImage> blockedQueue;
	private List<ProcessImage> readyQueue;
	private Semaphore mutex;

	private boolean isRunning;

	public InputThread(Semaphore mtx, List<ProcessImage> blockedQ, List<ProcessImage> readyQ) {
		this.mutex = mtx;
		this.blockedQueue = blockedQ;
		this.readyQueue = readyQ;
	}


	public void run(Scanner in)
	{
		isRunning = true;
		while (isRunning) 
		{
			if(blockedQueue.size()!=0)
			{
				ProcessImage pi=blockedQueue.get(0);
				if(blockedQueue.size()==0)
				{
					stopThread();
				}
				blockedQueue.remove(0);
				 
				System.out.println("Enter an integer");
				int i = in.nextInt();
				pi.V = i;
				
				if(pi.V != 0)
				{
					System.out.println(pi.V);
				}
			
				readyQueue.add(pi);
				if(blockedQueue.size() == 0)
				{
					stopThread();
					mutex.release();
				}
			}
		}
	}


	public void stopThread() {
		isRunning = false;
	}
}
