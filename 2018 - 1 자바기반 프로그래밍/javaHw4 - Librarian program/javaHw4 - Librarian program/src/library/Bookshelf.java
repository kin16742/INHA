package library;

import java.util.*;

public class Bookshelf {
	private int bookHave; // ��ü å ����
	private Book[] books; // å ���� �迭
	private Scanner s;

	public Bookshelf() { // ������
		s = new Scanner(System.in);
		this.bookHave = 0;
	}

	public void insertBook() { // å �Է�
		while (true) {
			System.out.print("Insert title : ");
			String titleInput = s.nextLine();		// ���� �Է�
			System.out.print("Insert author(s) : ");
			String authorsInput = s.nextLine();		// �۰��� �Է�
			System.out.print("Insert section : ");
			String locationInput = s.nextLine();	// ��ġ �Է�

			String author[] = { " ", " ", " " };	// �۰� �迭 �ʱ�ȭ
			int idx = authorsInput.indexOf(",");	// authorsInput���� ù ��° ,�� ������ ���� idx
			if (idx == -1) {
				author[0] = authorsInput;			// ,�� ���ٸ� �迭 ��ü�� �۰� �̸��̹Ƿ� author �迭 0�� �ε����� ����
			} else {
				author[0] = authorsInput.substring(0, idx);	// ','���������� authorsInput ���ڿ��� author �迭�� 0�� �ε����� ����
				int idx2 = authorsInput.length();			// authorsInput�� ���� idx2
				if (idx2 > idx) {							// authorsInput�� ���̰� ','������ ���̺��� ũ�ٸ�
					authorsInput = authorsInput.substring(idx + 2);	// authorsInput�� author �迭�� �� �κа� ',', ' '�� �� ������ �κ����� ����
					idx = authorsInput.indexOf(",");				// ','�� ��ġ idx�� �ٽ� �����ش�
					if (idx == -1) {								// ','�� ���� ���
						author[1] = authorsInput;					// ���� �ִ� ���ڿ� ��ü�� �۰� �̸��̹Ƿ� 1�� �ε����� �迭 ��ü ����
					} else {
						author[1] = authorsInput.substring(0, idx);	// ','�� �ִ� ��� ','�ٷ� �������� ���ڿ��� 1�� �ε����� ����
						idx2 = authorsInput.length();				// ���� authorsInput�� ���� idx2
						if (idx2 > idx) {							// ���̰� ','������ ���̺��� ũ�ٸ�
							authorsInput = authorsInput.substring(idx + 2);	// ','���������� ���ڿ��� 2�� �ε����� ����
							idx = authorsInput.indexOf(",");				// ���� ���ڿ����� ','�� ��ġ idx
							if (idx == -1) {								// ','�� �������� �ʴ� ���
								author[2] = authorsInput;					// �迭�� 2�� �ε����� ���� ���ڿ� ����
							} else {										// ','�� �����ϴ� ���
								System.out.println("Invalid length");		// �ִ� �۰� ���� 3�� �Ѿ�Ƿ� ��°� �Բ� �Լ� ����
								return;
							}
						}
					}
				}
			}

			if (titleInput.length() > 30 || locationInput.length() > 10
					|| author[0].length() > 30 || author[1].length() > 30
					|| author[2].length() > 30) {							// ������ ���� ���̸� �Ѿ���� Ȯ��
				System.out.println("Invalid length");						// �Ѿ�� ��°� �Բ� ó������ �Լ� �����
			} else {
				Book temp[] = new Book[bookHave + 1];						// ���� ���� å�� ������ 1��ŭ ū ũ�⸦ ������ �迭 temp ����
				for (int k = 0; k < bookHave; k++) {						// temp �迭�� books �迭 ���� �� ��� ����
					temp[k] = books[k];
				}
				temp[bookHave++] = new Book(titleInput, author, locationInput);	// ���� å�� ������ �÷��ܰ� ���ÿ� temp�� ������ �ε����� �Է¹��� ������ ����
				this.books = temp;												// Bookshelf Ŭ���� ���� ��� books �迭�� temp �迭�� ����
				break;
			}
		}
	}

	public Book[] searchByTitle(String keyword) { // �������� å �˻�
		Book[] titleBook;					// �˻��� Book�� ���� �迭 titleBook ����
		Book[] temp = new Book[bookHave];	// ���� å ������ŭ ũ���� temp �迭 ����
		int idx=0;							// temp�� ���� �� ������ ������ �ε��� ��
		for(int i=0;i<bookHave;i++){	
			if(books[i].getTitle().contains(keyword)){	// books[i]�� ���� keyword�� ���ԵǾ��ִ��� Ȯ��
				temp[idx++]=books[i];					// ���ԵǾ��ִٸ� idx�� ������Ŵ�� ���ÿ� temp[idx]�� ��ġ�ϴ� ������ ����ִ� Book�� ����
			}
		}
		titleBook = new Book[idx];						// ���� ���� �� idx ũ�⸸ŭ�� �迭 titleBook ����
		for(int i=0;i<idx;i++){
			titleBook[i] = temp[i];						// titleBook �迭�� temp �迭 ���� �� ��� ����
		}
		return titleBook;								// titleBook �迭 ��ȯ
	}

	public Book[] searchByAuthor(String keyword) { // �۰��� å �˻�
		Book[] authorBook;					// �˻��� Book�� ���� �迭 authorBook ����		
		Book[] temp = new Book[bookHave];	// ���� å ������ŭ ũ���� temp �迭 ����
		int idx=0;							// temp�� ���� �� ������ ������ �ε��� ��
		for(int i=0;i<bookHave;i++){
			String st[] = books[i].getAuthors();	// st��� �迭�� books[i]�� authors �迭 ����
			for(int j=0;j<3;j++){
				if(st[j].contains(keyword)){		// st �迭 ���� keyword�� ���ԵǴ� ���ڿ��� �ִ��� Ȯ��
					temp[idx++]=books[i];			// ���ԵǾ� �ִٸ� idx�� ������Ŵ�� ���ÿ� temp �迭�� �ش� Book�� �����ϰ� ���� for�� Ż��
					break;
				}
			}
		}
		authorBook = new Book[idx];					// ���� ���� �� idx ũ�⸸ŭ�� �迭 authorBook ����
		for(int i=0;i<idx;i++){
			authorBook[i] = temp[i];				// authorBook �迭�� temp �迭 ���� �� ��� ����
		}
		return authorBook;							// authorBook �迭 ��ȯ
	}

	public Book[] allBook() {						// Ȯ�ο� �Լ�, Ŭ������ books �Լ��� ��ȯ�ϴ� get�Լ�
		return books;
	}

	public void print(Book[] searchedBooks) {		// Book �迭�� �޾� �� ���� ��� Book�� ����ϴ� �Լ�
		int i = 1;									// å�� ��ȣ�� ��Ÿ�� ��
		int t = searchedBooks.length;				// ���ڷ� ���� �迭�� ����
		if (bookHave == 0) {								// ���� ��� å�� ������ 0�� ���
			System.out.println("Bookshelf is empty");		
		} else if (searchedBooks.length == 0) {				// ���ڷ� ���� �迭�� ũ�Ⱑ 0�� ���
			System.out.println("No matching Books found");	
		} else {
			while (t > 0) {															// ���ڷ� ���� �迭 ���̸�ŭ �ݺ�
				String str[] = searchedBooks[i - 1].getAuthors();					// authors �迭 str �迭�� ����
				System.out.printf("%d. %s - ", i,
						searchedBooks[i - 1].getTitle());							// ���ڷ� ���� �迭�� �ε����� �´� title ���
				if (str[2] == " ") {												// ���ڷ� ���� �迭�� �ε����� �´� authors ��� (���� Ȯ���ϸ鼭)
					if (str[1] == " ") {
						System.out.printf("%s - ", str[0]);
					} else {
						System.out.printf("%s, %s - ", str[0], str[1]);
					}
				} else {
					System.out.printf("%s, %s, %s - ", str[0], str[1], str[2]);
				}
				System.out.printf("%s\n", searchedBooks[i - 1].getLocation());		// ���ڷ� ���� �迭�� �ε����� �´� location ���
				t--;
				i++;
			}
		}
	}
}
