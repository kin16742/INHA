package shapes;

public class Circle extends twoDimensionalShape {
	private static String CLASS_NAME = "Circle";

	public Circle(String name, double r) {
		super(name, r, r);
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public double getRadius() {
		return super.getWidth();
	}

	public void setSize() {
		System.out.printf("Input %s`s Radius : ", super.getName());
		double radius = s.nextDouble();
		super.setWidth(radius);
		super.setHeight(radius);
	}

	public double calculateArea() {
		return Math.PI * getRadius() * getRadius();
	}

	public double calculatePerimeter() {
		return 2 * Math.PI * getRadius();
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nArea = %.2f\nPerimeter = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculatePerimeter());
	}
}
