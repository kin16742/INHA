package shapes;

public class Rectangle extends twoDimensionalShape {
	private static String CLASS_NAME = "Rectangle";

	public Rectangle(String name, double width, double height) {
		super(name, width, height);
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public double getWidth() {
		return super.getWidth();
	}

	public double getHeight() {
		return super.getHeight();
	}

	public void setSize() {
		System.out.printf("Input %s`s Width : ", super.getName());
		double width = s.nextDouble();
		System.out.printf("Input %s`s Height : ", super.getName());
		double height = s.nextDouble();
		super.setWidth(width);
		super.setHeight(height);
	}

	public double calculateArea() {
		return getHeight() * getWidth();
	}

	public double calculatePerimeter() {
		return 2 * getHeight() + 2 * getWidth();
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nArea = %.2f\nPerimeter = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculatePerimeter());
	}
}
