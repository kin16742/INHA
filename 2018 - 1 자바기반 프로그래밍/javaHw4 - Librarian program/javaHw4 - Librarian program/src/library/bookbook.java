package library;

import java.util.*;

public class bookbook {

	public static void main(String[] args) {
		Bookshelf bs = new Bookshelf();
		Scanner s = new Scanner(System.in);
		int option;
		String str;

		while (true) {
			System.out.println("Choose 1 option to search:");	// 무한 반복문
			System.out.println("1. Insert book");				// 1 : 책 넣기
			System.out.println("2. Search by title.");			// 2 : 제목으로 검색
			System.out.println("3. Search by author.");			// 3 : 작가로 검색		(4 : 모든 책 출력)

			option = s.nextInt();

			switch (option) {
			case 1:
				bs.insertBook();
				break;
			case 2:
				System.out.print("Insert title keyword : ");
				s.nextLine();									// 입력 버퍼 지우기
				str = s.nextLine();
				bs.print(bs.searchByTitle(str));
				break;
			case 3:
				System.out.print("Insert author keyword : ");
				s.nextLine();									// 입력 버퍼 지우기
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
