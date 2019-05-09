package library;

public class Book {
	private String title; // ����
	private String[] authors; // �۰�
	private String location; // ��ġ
	
	public Book(){
		this.title = " ";
	}
	
	public Book(String title, String[] authors, String location) { // ������
		this.title = title;
		this.authors = authors;
		this.location = location;
	}
	
	public String getTitle(){ // ���� get�Լ�
		return this.title;
	}
	
	public String[] getAuthors(){ // �۰� get�Լ�
		return this.authors;
	}
	
	public String getLocation(){ // ��ġ get�Լ�
		return this.location;
	}
	
	public void setTitle(String title){ // ���� set�Լ�
		this.title = title;
	}
	
	public void setAuthors(String[] authors){ // �۰� set�Լ�
		this.authors = authors;
	}
	
	public void setLocation(String location){ // ��ġ set�Լ�
		this.location = location;
	}
}
