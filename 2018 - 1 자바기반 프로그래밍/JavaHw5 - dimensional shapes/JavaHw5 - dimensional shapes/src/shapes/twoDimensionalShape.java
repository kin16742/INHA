package shapes;
import java.util.*;

public class twoDimensionalShape {
	static String CLASS_NAME = "twoDimensionalShape";
	private String name;
	private double width;
	private double height;
	private double area;
	private double perimeter;
	Scanner s = new Scanner(System.in);
	
	public twoDimensionalShape(String name, double w, double h) {
		this.name = name;
		this.width = w;
		this.height = h;
		this.area = 0.0;
		this.perimeter = 0.0;
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

	public void setHeight(double h) {
		this.height = h;
	}

	public double calculateArea() {
		return 0.0;
	}

	public double calculatePerimeter() {
		return 0.0;
	}

	public double getWidth() {
		return this.width;
	}

	public double getHeight() {
		return this.height;
	}
}
