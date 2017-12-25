public class CPU {

	private Memory memory;
	private String processName;
	private int S0;
	private int S1;
	private int S2;
	private int S3;
	private int S4;
	private int S5;
	private int S6;
	private int S7;
	private int $0;
	private int PC;
	private int V;
	private int IR;
	private int BR;
	private int LR;
	private int[] registerArray= {S0,S1,S2,S3,S4,S5,S6,S7,PC,V,IR,BR,LR,$0};

	public CPU(char[] mem,int size) {
		memory=new Memory(size);
		memory.setMemory(mem);
	}

	public String getProcessName() {
		return processName;
	}

	public void setProcessName(String processName) {
		this.processName = processName;
	}

	public int getS0() {
		return registerArray[0];
	}

	public void setS0(int s0) {
		registerArray[0] = s0;
	}

	public int getS1() {
		return registerArray[1];
	}

	public void setS1(int s1) {
		registerArray[1] = s1;
	}

	public int getS2() {
		return registerArray[2];
	}

	public void setS2(int s2) {
		registerArray[2] = s2;
	}

	public int getS3() {
		return registerArray[3];
	}

	public void setS3(int s3) {
		registerArray[3] = s3;
	}

	public int getS4() {
		return registerArray[4];
	}

	public void setS4(int s4) {
		registerArray[4] = s4;
	}

	public int getS5() {
		return registerArray[5];
	}

	public void setS5(int s5) {
		registerArray[5] = s5;
	}

	public int getS6() {
		return registerArray[6];
	}

	public void setS6(int s6) {
		registerArray[6] = s6;
	}

	public int getS7() {
		return registerArray[7];
	}

	public void setS7(int s7) {
		registerArray[7] = s7;
	}

	public int get$0() {
		return registerArray[13];
	}

	public void set$0(int $0) {
		registerArray[13] = $0;
	}

	public int getPC() {
		return registerArray[8];
	}

	public void setPC(int pC) {
		registerArray[8] = pC;
	}

	public int getV() {
		return registerArray[9];
	}

	public void setV(int v) {
		registerArray[9] = v;
	}

	public int getIR() {
		return registerArray[10];
	}

	public void setIR(int iR) {
		registerArray[10] = iR;
	}

	public int getBR() {
		return registerArray[11];
	}

	public void setBR(int bR) {
		registerArray[11] = bR;
	}

	public int getLR() {
		return registerArray[12];
	}

	public void setLR(int lR) {
		registerArray[12] = lR;
	}

	String[]reg = {"S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7", "PC", "V","IR","BR","LR","$0"};
	String[]binReg = {"00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "00000", "00010","dummy","01011","00010","01100"};
	String[]op = {"ADDI", "SUBI", "ORI", "BEQ", "ADD", "SUB","LUI", "LW", "SW", "SYSCALL"};
	String[]binOp = {"000010", "000011", "011111", "000111", "010000", "010001","001000", "001001", "001010", "00000000000000000000000000000000"};

	private int registerNumber(String j)
	{
		for(int i=0; i<14; i++)
		{
			if(j.equals(binReg[i]))
			{
				return i;
			}
		}
		return -1;
	}

	public void fetch()
	{
		int num;
		String s = "";
		int[] r = new int[4];
		for(int i=registerArray[8]; i<registerArray[8]+4; i++)
		{
			r[i%4]=memory.get(i);
		}
		for(int j=0; j<4; j++)
		{
			String s1= Integer.toBinaryString((int)r[j]);
			if(s1.length()<8)
			{
				String s2=s1;
				for(int i=0;i<8-s1.length();i++)
				{
					s2="0"+s2;
				}
				s+=s2;
			}
			else
			{
				s+=s1;
			}
		}
		num = Integer.parseInt(s, 2);
		registerArray[10] = num;
		registerArray[8] += 4;
	}

	public int decodeExecute()
	{
		String s = "";
		s = Integer.toBinaryString(registerArray[10]);
		String str = s;
		if(s.equals("0"))
		{
			//SYSCALL 
			return 0;
		}
		if(str.length()<32)
		{
			for(int i=0; i<32-s.length(); i++)
			{
				str = "0" + str;
			}
			s = str;
		}
		String op = s.substring(0, 6);
		String reg = s.substring(6,11);
		int n = registerNumber(reg);
		String r1 = s.substring(11,16);
		int n1 = registerNumber(r1);
		String c = s.substring(16,s.length());
		String reg2 = s.substring(16,21);
		int n2 = registerNumber(reg2);
		int cNum = Integer.parseInt(c, 2);

		for(int i=0;i<4;i++)
		{
			if(op.equals(binOp[i]))
			{
				if(i==0)
				{
					registerArray[n] = registerArray[n1] + cNum;
				}
				else if(i==1)
				{
					registerArray[n] = registerArray[n1] - cNum;
				}
				else if(i==2)
				{
					registerArray[n] = registerArray[n1] | cNum; 
				}
				else if(i==3)
				{
					if(registerArray[n] == registerArray[n1])
					{
						registerArray[8] = cNum;
					}
				}
				return 1;
			}
		}
		for(int i=4;i<6;i++)
		{
			if(op.equals(binOp[i]))
			{
				if(i==4)
				{
					registerArray[n] = registerArray[n1] + registerArray[n2];
				}
				else if(i==5)
				{
					registerArray[n] = registerArray[n1] - registerArray[n2];
				}
				return 1;
			}
		}

		if(op.equals(binOp[6]))
		{
			registerArray[n] = cNum*256*256;
			return 1;
		}

		for(int i=7;i<9;i++)
		{
			if(op.equals(binOp[i]))
			{
				if(i==7)
				{
					registerArray[n] = registerArray[n1];
				}
				else if(i==8)
				{
					registerArray[n1] = registerArray[n];
				}
				return 1;
			}
		}
		return -1;
	}
}



