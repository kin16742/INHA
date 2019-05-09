package library;

public class Book {
	private String title; // 제목
	private String[] authors; // 작가
	private String location; // 위치
	
	public Book(){
		this.title = " ";
	}
	
	public Book(String title, String[] authors, String location) { // 생성자
		this.title = title;
		this.authors = authors;
		this.location = location;
	}
	
	public String getTitle(){ // 제목 get함수
		return this.title;
	}
	
	public String[] getAuthors(){ // 작가 get함수
		return this.authors;
	}
	
	public String getLocation(){ // 위치 get함수
		return this.location;
	}
	
	public void setTitle(String title){ // 제목 set함수
		this.title = title;
	}
	
	public void setAuthors(String[] authors){ // 작가 set함수
		this.authors = authors;
	}
	
	public void setLocation(String location){ // 위치 set함수
		this.location = location;
	}
}
