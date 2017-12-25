import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;

public class MainApplication {

	public static void main(String[] args)  {
		
		
		String asmFileName = "assemblyInput.asm";
		String binFileName = "assemblyCode.bin";
		Assembler assem = new Assembler();
		int size = assem.createBinaryFile(asmFileName, binFileName);
		
		OS myOS = new OS(size);
		myOS.run();
		return;
	}
}
