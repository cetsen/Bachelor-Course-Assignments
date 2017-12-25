
public class Memory {

	private int memorySize;
	private char[] memory;
	
	public Memory(int size) {
		memorySize = size;
		memory = new char[size];
	}
	
	public char get(int index) {
		return memory[index];
	}

	public void set(char decVal, int i) {
		// TODO Auto-generated method stub
		memory[i] = decVal;
	}
	
	void setMemory(char[] arr)
	{
		for(int i=0; i<memorySize; i++)
		{
			memory[i] = arr[i];
		}
	}
	
	public char[] getMemory() {
		return memory;
	}
	
	public int getMemoSize() {
		return memorySize;
	}
			
}





