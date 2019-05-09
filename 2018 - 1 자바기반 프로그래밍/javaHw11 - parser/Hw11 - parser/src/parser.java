import java.io.*;
import java.util.*;

public class parser {

	public static void main(String[] args) throws IOException {
		Scanner s = null;
		BufferedWriter out1 = null;
		BufferedWriter out2 = null;

		try {
			s = new Scanner(new BufferedReader(new FileReader("input.txt")));
			out1 = new BufferedWriter(new FileWriter("output1.txt"));
			out2 = new BufferedWriter(new FileWriter("output2.txt"));
			String content = "";

			while (s.hasNextLine()) {
				content = s.nextLine();
				StringTokenizer str1 = new StringTokenizer(content, " ");
				StringTokenizer str2 = new StringTokenizer(content, ",");

				while (str1.hasMoreTokens()) {
					out1.write(str1.nextToken());
					out1.newLine();
				}

				while (str2.hasMoreTokens()) {
					out2.write(str2.nextToken());
					out2.newLine();
				}
			}
		} finally {
			if (s != null)
				s.close();
			if (out1 != null)
				out1.close();
			if (out2 != null)
				out2.close();
		}
	}

}
