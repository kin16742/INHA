package library;

import java.util.*;

public class bookbook {

	public static void main(String[] args) {
		Bookshelf bs = new Bookshelf();
		Scanner s = new Scanner(System.in);
		int option;
		String str;

		while (true) {
			System.out.println("Choose 1 option to search:");	// ���� �ݺ���
			System.out.println("1. Insert book");				// 1 : å �ֱ�
			System.out.println("2. Search by title.");			// 2 : �������� �˻�
			System.out.println("3. Search by author.");			// 3 : �۰��� �˻�		(4 : ��� å ���)

			option = s.nextInt();

			switch (option) {
			case 1:
				bs.insertBook();
				break;
			case 2:
				System.out.print("Insert title keyword : ");
				s.nextLine();									// �Է� ���� �����
				str = s.nextLine();
				bs.print(bs.searchByTitle(str));
				break;
			case 3:
				System.out.print("Insert author keyword : ");
				s.nextLine();									// �Է� ���� �����
				str = s.nextLine();
				bs.print(bs.searchByAuthor(str));
				break;
			case 4:
				bs.print(bs.allBook());
				break;
			}
		}
	}

}
