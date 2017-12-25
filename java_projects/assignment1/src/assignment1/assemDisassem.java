package assignment1;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.ArrayList;

public class assemDisassem 
{
	public static void main(String[] args) 
	{
		String[]registers = {"PC", "SP", "V", "S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7", "BR", "$0"}; 
		String[]registerToBinary = {"00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100"};
		String[]operations = {"ADDI", "SUBI", "MULI", "DIVI", "ORI", "BEQ", "ADD", "SUB", "MUL", "DIV","LUI", "LW", "SW", "SYSCALL"};
		String[]operationToBinary = {"000010", "000011", "000100", "000101", "011111", "000111", "010000", "010001", "010011", "010100", "001011", "001001", "001010", "00000000000000000000000000000000"};

		int operationLength = operations.length;
		int registerLength = registers.length;

		try 
		{
			String inputFile = "assembly.txt";
			BufferedReader br = new BufferedReader (new FileReader(inputFile));
			String line = "";
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("binaryOutput.txt"), "UTF-8"));

			//from assembly to binary
			while((line = br.readLine()) != null && line.trim().isEmpty()==false)
			{
				String[]storage = line.split(" ");
				int digitLength = 0;
				int storageLength = storage.length;

				for(int i=0; i<storageLength; i++)
				{
					for(Integer j=0; j<operationLength; j++) //compares with operators
					{
						if(storage[i].equals(operations[j]))
						{
							if(j.equals(13)) //for SYSCALL
								digitLength+=32;
							else
								digitLength+=6;

							writer.write(operationToBinary[j]);
						}
					}
					for(int k=0; k<registerLength; k++)
					{
						if(storage[i].equals(registers[k])) //compares with registers
						{							
							writer.write(registerToBinary[k]);
							digitLength+=5;
						}
					}
					Integer x = storage[i].length(); 
					Integer y = 16;
					if (x.equals(y)) //if there are 16 digits left at the end, write it to the output
					{	
						writer.write(storage[i]);
						digitLength+=16;
					}
				}
				while(digitLength != 32) //if the number of digits are less than 32, add 0's to the end of the line
				{
					writer.write("0");
					digitLength++;
				}
				writer.write("\r\n");
			}
			writer.close();
			br.close();
		}
		catch (IOException e) 
		{
			e.printStackTrace();
		}

		try
		{
			String inputFile = "binaryOutput.txt";
			BufferedReader br = new BufferedReader (new FileReader(inputFile));
			String line = "";
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("assemblyOutput.txt"), "UTF-8"));
			//from binary to assembly
			while((line = br.readLine()) != null && line.trim().isEmpty()==false)
			{
				String op0 = line.substring(0, 6); //operator 
				String reg0 = line.substring(6, 11); //register

				if (op0.equals("000000"))//if SYSCALL
				{
					writer.write("SYSCALL\r\n");
				}
				else
				{
					for (int i=0; i<6; i++) 
					{
						if(op0.equals(operationToBinary[i])) //if ADDI, SUBI, MULI, DIVI, ORI, or BEQ
						{
							writer.write(operations[i] + " ");

							String reg1 = line.substring(11, 16); //register
							String[] regs= {reg0, reg1};
							String rest = line.substring(16, line.length());

							for(int num=0; num<2; num++)
							{
								for(int j=0; j<registerLength; j++)
								{
									if(regs[num].equals(registerToBinary[j]))
									{
										writer.write(registers[j] + " ");
									}
								}
							}
							writer.write(rest + "\r\n");
						}
					}

					for (int i=6; i<10; i++)
					{
						if(op0.equals(operationToBinary[i])) //if ADD, SUB, MUL, or DIV
						{
							writer.write(operations[i] + " ");
							String reg1 = line.substring(11,16);
							String reg2 = line.substring(16, 21);  //register
							String[] regs = {reg0, reg1, reg2};

							for(int num=0; num<3; num++)
							{
								for(int j=0; j<registerLength; j++)
								{
									if(regs[num].equals(registerToBinary[j]))
									{
										writer.write(registers[j] + " ");
									}
								}
							}
							writer.write("\r\n");
						}
					}

					for (int i=11; i<13; i++)
					{
						if(op0.equals(operationToBinary[i])) //if LW or SW
						{
							writer.write(operations[i] + " ");
							String reg1 = line.substring(11,16);
							String[] regs = {reg0, reg1};
							for(int num=0; num<2; num++)
							{
								for(int j=0; j<registerLength; j++)
								{
									if(regs[num].equals(registerToBinary[j]))
									{
										writer.write(registers[j] + " ");
									}
								}
							}

							writer.write("\r\n");
						}
					}
					if (op0.equals(operationToBinary[10])) //if LUI
					{
						String c = line.substring(11, 27);
						writer.write(operations[10] + " ");
						for(int j=0; j<registerLength; j++)
						{
							if(reg0.equals(registerToBinary[j]))
							{
								writer.write(registers[j] + " ");
							}
						}
						writer.write(c + "\r\n");
					}
				}
			}
			writer.close();
			br.close();
		}
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
}
