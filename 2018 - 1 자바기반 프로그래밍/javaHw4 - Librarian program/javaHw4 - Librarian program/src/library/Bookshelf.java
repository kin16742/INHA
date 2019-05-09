package library;

import java.util.*;

public class Bookshelf {
	private int bookHave; // 전체 책 개수
	private Book[] books; // 책 저장 배열
	private Scanner s;

	public Bookshelf() { // 생성자
		s = new Scanner(System.in);
		this.bookHave = 0;
	}

	public void insertBook() { // 책 입력
		while (true) {
			System.out.print("Insert title : ");
			String titleInput = s.nextLine();		// 제목 입력
			System.out.print("Insert author(s) : ");
			String authorsInput = s.nextLine();		// 작가들 입력
			System.out.print("Insert section : ");
			String locationInput = s.nextLine();	// 위치 입력

			String author[] = { " ", " ", " " };	// 작가 배열 초기화
			int idx = authorsInput.indexOf(",");	// authorsInput에서 첫 번째 ,을 만나는 지점 idx
			if (idx == -1) {
				author[0] = authorsInput;			// ,이 없다면 배열 전체가 작가 이름이므로 author 배열 0번 인덱스에 삽입
			} else {
				author[0] = authorsInput.substring(0, idx);	// ','직전까지의 authorsInput 문자열을 author 배열의 0번 인덱스에 삽입
				int idx2 = authorsInput.length();			// authorsInput의 길이 idx2
				if (idx2 > idx) {							// authorsInput의 길이가 ','까지의 길이보다 크다면
					authorsInput = authorsInput.substring(idx + 2);	// authorsInput을 author 배열에 들어간 부분과 ',', ' '을 뺀 나머지 부분으로 설정
					idx = authorsInput.indexOf(",");				// ','의 위치 idx를 다시 구해준다
					if (idx == -1) {								// ','가 없는 경우
						author[1] = authorsInput;					// 남아 있는 문자열 전체가 작가 이름이므로 1번 인덱스에 배열 전체 삽입
					} else {
						author[1] = authorsInput.substring(0, idx);	// ','가 있는 경우 ','바로 전까지의 문자열을 1번 인덱스에 삽입
						idx2 = authorsInput.length();				// 남은 authorsInput의 길이 idx2
						if (idx2 > idx) {							// 길이가 ','까지의 길이보다 크다면
							authorsInput = authorsInput.substring(idx + 2);	// ','직전까지의 문자열을 2번 인덱스에 삽입
							idx = authorsInput.indexOf(",");				// 남은 문자열에서 ','의 위치 idx
							if (idx == -1) {								// ','가 존재하지 않는 경우
								author[2] = authorsInput;					// 배열의 2번 인덱스에 남은 문자열 삽입
							} else {										// ','가 존재하는 경우
								System.out.println("Invalid length");		// 최대 작가 수인 3을 넘어가므로 출력과 함께 함수 종료
								return;
							}
						}
					}
				}
			}

			if (titleInput.length() > 30 || locationInput.length() > 10
					|| author[0].length() > 30 || author[1].length() > 30
					|| author[2].length() > 30) {							// 각각의 제한 길이를 넘어가는지 확인
				System.out.println("Invalid length");						// 넘어가면 출력과 함께 처음부터 함수 재시작
			} else {
				Book temp[] = new Book[bookHave + 1];						// 현재 가진 책의 수보다 1만큼 큰 크기를 가지는 배열 temp 선언
				for (int k = 0; k < bookHave; k++) {						// temp 배열에 books 배열 내의 값 모두 복사
					temp[k] = books[k];
				}
				temp[bookHave++] = new Book(titleInput, author, locationInput);	// 가진 책의 개수를 올려줌과 동시에 temp의 마지막 인덱스에 입력받은 값들을 삽입
				this.books = temp;												// Bookshelf 클래스 내의 멤버 books 배열을 temp 배열로 변경
				break;
			}
		}
	}

	public Book[] searchByTitle(String keyword) { // 제목으로 책 검색
		Book[] titleBook;					// 검색된 Book을 넣을 배열 titleBook 생성
		Book[] temp = new Book[bookHave];	// 가진 책 개수만큼 크기의 temp 배열 생성
		int idx=0;							// temp에 값이 들어갈 때마다 증가할 인덱스 값
		for(int i=0;i<bookHave;i++){	
			if(books[i].getTitle().contains(keyword)){	// books[i]의 제목에 keyword가 포함되어있는지 확인
				temp[idx++]=books[i];					// 포함되어있다면 idx를 증가시킴과 동시에 temp[idx]에 일치하는 제목이 들어있는 Book을 삽입
			}
		}
		titleBook = new Book[idx];						// 연산 종료 후 idx 크기만큼의 배열 titleBook 선언
		for(int i=0;i<idx;i++){
			titleBook[i] = temp[i];						// titleBook 배열에 temp 배열 내의 값 모두 복사
		}
		return titleBook;								// titleBook 배열 반환
	}

	public Book[] searchByAuthor(String keyword) { // 작가로 책 검색
		Book[] authorBook;					// 검색된 Book을 넣을 배열 authorBook 생성		
		Book[] temp = new Book[bookHave];	// 가진 책 개수만큼 크기의 temp 배열 생성
		int idx=0;							// temp에 값이 들어갈 때마다 증가할 인덱스 값
		for(int i=0;i<bookHave;i++){
			String st[] = books[i].getAuthors();	// st라는 배열에 books[i]의 authors 배열 복사
			for(int j=0;j<3;j++){
				if(st[j].contains(keyword)){		// st 배열 내에 keyword가 포함되는 문자열이 있는지 확인
					temp[idx++]=books[i];			// 포함되어 있다면 idx를 증가시킴과 동시에 temp 배열에 해당 Book을 삽입하고 내부 for문 탈출
					break;
				}
			}
		}
		authorBook = new Book[idx];					// 연산 종료 후 idx 크기만큼의 배열 authorBook 선언
		for(int i=0;i<idx;i++){
			authorBook[i] = temp[i];				// authorBook 배열에 temp 배열 내의 값 모두 복사
		}
		return authorBook;							// authorBook 배열 반환
	}

	public Book[] allBook() {						// 확인용 함수, 클래스의 books 함수를 반환하는 get함수
		return books;
	}

	public void print(Book[] searchedBooks) {		// Book 배열을 받아 그 안의 모든 Book을 출력하는 함수
		int i = 1;									// 책의 번호를 나타낼 값
		int t = searchedBooks.length;				// 인자로 받은 배열의 길이
		if (bookHave == 0) {								// 가진 모든 책의 개수가 0일 경우
			System.out.println("Bookshelf is empty");		
		} else if (searchedBooks.length == 0) {				// 인자로 받은 배열의 크기가 0일 경우
			System.out.println("No matching Books found");	
		} else {
			while (t > 0) {															// 인자로 받은 배열 길이만큼 반복
				String str[] = searchedBooks[i - 1].getAuthors();					// authors 배열 str 배열에 복사
				System.out.printf("%d. %s - ", i,
						searchedBooks[i - 1].getTitle());							// 인자로 받은 배열의 인덱스에 맞는 title 출력
				if (str[2] == " ") {												// 인자로 받은 배열의 인덱스에 맞는 authors 출력 (개수 확인하면서)
					if (str[1] == " ") {
						System.out.printf("%s - ", str[0]);
					} else {
						System.out.printf("%s, %s - ", str[0], str[1]);
					}
				} else {
					System.out.printf("%s, %s, %s - ", str[0], str[1], str[2]);
				}
				System.out.printf("%s\n", searchedBooks[i - 1].getLocation());		// 인자로 받은 배열의 인덱스에 맞는 location 출력
				t--;
				i++;
			}
		}
	}
}
