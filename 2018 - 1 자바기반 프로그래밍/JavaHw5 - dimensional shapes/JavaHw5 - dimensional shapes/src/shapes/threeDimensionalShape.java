package shapes;

import java.util.*;

public class threeDimensionalShape {
	static String CLASS_NAME = "threeDimensionalShape";
	private String name;
	private double width;
	private double length;
	private double height;
	private double area;
	private double volume;
	Scanner s = new Scanner(System.in);

	public threeDimensionalShape(String name, double w, double l, double h) {
		this.name = name;
		this.width = w;
		this.length = l;
		this.height = h;
		this.area = 0.0;
		this.volume = 0.0;
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public String getName() {
		return this.name;
	}

	public void setWidth(double w) {
		this.width = w;
	}

	public void setLength(double l) {
		this.length = l;
	}

	public void setHeight(double h) {
		this.height = h;
	}

	public double calculateArea() {
		return 0.0;
	}

	public double calculateVolume() {
		return 0.0;
	}

	public double getWidth() {
		return this.width;
	}

	public double getLength() {
		return this.length;
	}

	public double getHeight() {
		return this.height;
	}
}
