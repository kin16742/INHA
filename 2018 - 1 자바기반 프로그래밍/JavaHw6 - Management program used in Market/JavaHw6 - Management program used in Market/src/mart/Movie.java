package mart;

import java.util.*;

public class Movie extends item {
	private String cdTitle;
	private int pubYear;

	public Movie(String id, String title, int pubYear, int importPrice) {
		super(id, importPrice);
		this.cdTitle = title;
		this.pubYear = pubYear;
	}

	public String getTitle() {
		return this.cdTitle;
	}

	public int getPublishYear() {
		return this.pubYear;
	}

	public String getInfo() {
		return this.cdTitle;
	}

	public int getSalePrice() {
		GregorianCalendar ca = new GregorianCalendar();
		int price = super.getSalePrice();
		int age = ca.get(Calendar.YEAR) - getPublishYear();
		if (age <= 1) {
			return price * 2;
		} else if (age > 1) {
			return price / 2;
		}
		return 0;
	}
}
