package mart;

import java.util.*;

public class CD extends item {
	private String cdTitle;
	private String cdArtist;
	private int pubYear;

	public CD(String id, String title, String artist, int pubYear,
			int importPrice) {
		super(id, importPrice);
		this.cdTitle = title;
		this.cdArtist = artist;
		this.pubYear = pubYear;
	}
	
	public String getTitle(){
		return this.cdTitle;
	}
	
	public String getArtist(){
		return this.cdArtist;
	}
	
	public int getPublishYear(){
		return this.pubYear;
	}

	public String getInfo() {
		return this.cdTitle + " - " + this.cdArtist;
	}

	public int getSalePrice() {
		GregorianCalendar ca = new GregorianCalendar();
		int price = super.getSalePrice();
		int age = ca.get(Calendar.YEAR) - getPublishYear();
		if(age <= 1){
			return price * 3 / 2;
		}
		else if(age > 1 && age <=2){
			return price;
		}
		else if(age > 2){
			return price * 7 / 10;
		}
		return 0;
	}
	
}
