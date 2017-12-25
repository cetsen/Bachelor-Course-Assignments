import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class OS extends Thread {

	private final int QUANTUM = 5;

	private CPU cpu;
	private Memory memory;
	private List<ProcessImage> readyQueue;
	private List<ProcessImage> blockedQueue;
	private Semaphore mutex;	
	private InputThread inputThread;

	public OS(int size) {
		Assembler assem = new Assembler();
		String binFileName = "assemblyCode.bin";
		char[] arr = assem.readBinaryFile(size, binFileName);

		this.memory = new Memory(size);
		this.memory.setMemory(arr);
		this.cpu = new CPU(arr, size);
		this.mutex = new Semaphore(1);
		this.readyQueue = new ArrayList<ProcessImage>();
		this.blockedQueue = new ArrayList<ProcessImage>();

		cpu.setLR(size);
		ProcessImage proIma = new ProcessImage();
		proIma.LR = size;
		readyQueue.add(proIma);

		this.inputThread = new InputThread(mutex, blockedQueue, readyQueue);
		inputThread.start();
	}


	@Override
	public void run() {
		//TODO implement OS Logic
		Scanner in = new Scanner(System.in); 
		while(true)
		{
			if(readyQueue.size() != 0)
			{
				ProcessImage prIm = readyQueue.get(0);
				readyQueue.remove(0);

				cpu.setS0(prIm.S0);
				cpu.setS1(prIm.S1);
				cpu.setS2(prIm.S2);
				cpu.setS3(prIm.S3);
				cpu.setS4(prIm.S4);
				cpu.setS5(prIm.S5);
				cpu.setS6(prIm.S6);
				cpu.setS7(prIm.S7);
				cpu.setBR(prIm.BR);
				cpu.set$0(prIm.$0);
				cpu.setIR(prIm.IR);
				cpu.setLR(prIm.LR);
				cpu.setPC(prIm.PC);
				cpu.setV(prIm.V);

				int temp = 0;
				while(temp != QUANTUM)
				{
					cpu.fetch();

					if(cpu.decodeExecute() == 0)
					{
						prIm.IR=cpu.getIR();
						prIm.PC=cpu.getPC();

						blockedQueue.add(prIm);

						try {
							mutex.acquire();
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

						inputThread.run(in);
						break;
					}

					prIm.$0=cpu.get$0();
					prIm.PC=cpu.getPC();
					prIm.S0=cpu.getS0();
					prIm.S1=cpu.getS1();
					prIm.S2=cpu.getS2();
					prIm.S3=cpu.getS3();
					prIm.S4=cpu.getS4();
					prIm.S5=cpu.getS5();
					prIm.S6=cpu.getS6();
					prIm.S7=cpu.getS7();
					prIm.IR=cpu.getIR();
					prIm.V=cpu.getV();

					temp++;
					if(cpu.getPC() == cpu.getLR())
					{
						break;
					}
				}

				if(cpu.getPC()!=cpu.getLR())
				{
					readyQueue.add(prIm);
				}
				else
				{
					inputThread.stopThread();

					try {
						BufferedWriter writer;
						writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("processRegisterDump.bin"), "UTF-8"));
						writer.write("S0 " + cpu.getS0() + "\r\n");
						writer.write("S1 " + cpu.getS1()  + "\r\n");
						writer.write("S2 " + cpu.getS2()  + "\r\n");
						writer.write("S3 " + cpu.getS3()  + "\r\n");
						writer.write("S4 " + cpu.getS4()  + "\r\n");
						writer.write("S5 " + cpu.getS5()  + "\r\n");
						writer.write("S6 " + cpu.getS6()  + "\r\n");       
						writer.write("S7 " + cpu.getS7()  + "\r\n");
						writer.write("$0 " + cpu.get$0()  + "\r\n");
						writer.write("PC " + cpu.getPC()  + "\r\n");
						writer.write("V " +  cpu.getV()  + "\r\n");
						writer.write("IR " + cpu.getIR() + "\r\n");
						writer.write("BR " + cpu.getBR()  + "\r\n");
						writer.write("LR " + cpu.getLR()  + "\r\n");
						System.out.println("end of execution");
						in.close();
						writer.close();
					}
					catch(FileNotFoundException e)
					{
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					break;
				}

			}
			if(readyQueue.size() == 0 && blockedQueue.size() == 0)
			{
				//When OS thread stops, stop the InputTHreadx
				inputThread.stopThread();
				BufferedWriter writer;
				try {
					writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("processRegisterDump.bin")));
					writer.write("S0 " + cpu.getS0() + "\r\n");
					writer.write("S1 " + cpu.getS1()  + "\r\n");
					writer.write("S2 " + cpu.getS2()  + "\r\n");
					writer.write("S3 " + cpu.getS3()  + "\r\n");
					writer.write("S4 " + cpu.getS4()  + "\r\n");
					writer.write("S5 " + cpu.getS5()  + "\r\n");
					writer.write("S6 " + cpu.getS6()  + "\r\n");	
					writer.write("S7 " + cpu.getS7()  + "\r\n");
					writer.write("$0 " + cpu.get$0()  + "\r\n");
					writer.write("PC " + cpu.getPC()  + "\r\n");
					writer.write("V " + cpu.getV()  + "\r\n");
					writer.write("IR " + cpu.getIR()  + "\r\n");
					writer.write("BR " + cpu.getBR()  + "\r\n");
					writer.write("LR " + cpu.getLR()  + "\r\n");
					writer.close();
					in.close();
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				break;
			}
		}
	}
}

