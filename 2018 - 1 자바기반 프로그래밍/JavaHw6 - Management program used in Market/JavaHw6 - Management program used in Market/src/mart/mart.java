package mart;

import java.util.*;

public class mart {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		cart c = new cart();
		int userInput1 = 0, userInput2 = 0;
		String itemID, CDtitle, artist;
		int importPrice, pubYear;
		while (userInput1 != 3) {
			System.out.println("----------------------------");
			System.out.println("Select option:");
			System.out.println("1. add item");
			System.out.println("2. print all items in cart");
			System.out.println("----------------------------");
			System.out.printf("user input : ");
			userInput1 = s.nextInt();
			System.out.println("----------------------------");
			if (userInput1 == 1) {
				System.out.println("1. CD");
				System.out.println("2. Movie");
				System.out.println("----------------------------");
				System.out.printf("user input : ");
				userInput2 = s.nextInt();
				System.out.println("----------------------------");
				if (userInput2 == 1) {
					System.out.printf("input itemID         : ");
					s.nextLine();
					itemID = s.nextLine();
					System.out.printf("input import Price   : ");
					importPrice = s.nextInt();
					System.out.printf("input CD title       : ");
					s.nextLine();
					CDtitle = s.nextLine();
					System.out.printf("input artist         : ");
					artist = s.nextLine();
					System.out.printf("input published year : ");
					pubYear = s.nextInt();

					if (CDtitle.length() > 30) {
						System.out.println("Invalid input");
					} else {
						CD a = new CD(itemID, CDtitle, artist, pubYear,
								importPrice);

						if (c.addItem(a) == false) {
							System.out.println("cart is full!!");
						}
					}
				} else if (userInput2 == 2) {
					System.out.printf("input itemID         : ");
					s.nextLine();
					itemID = s.nextLine();
					System.out.printf("input import Price   : ");
					importPrice = s.nextInt();
					System.out.printf("input CD title       : ");
					s.nextLine();
					CDtitle = s.nextLine();
					System.out.printf("input published year : ");
					pubYear = s.nextInt();

					if (CDtitle.length() > 30) {
						System.out.println("Invalid input");
					} else {
						Movie a = new Movie(itemID, CDtitle, pubYear,
								importPrice);
						
						if (c.addItem(a) == false) {
							System.out.println("cart is full!!");
						}
					}
				} else {
					System.out.println("Invalid input!");
				}
			} else if (userInput1 == 2) {
				c.printReceipt();
			}
		}
	}

}
