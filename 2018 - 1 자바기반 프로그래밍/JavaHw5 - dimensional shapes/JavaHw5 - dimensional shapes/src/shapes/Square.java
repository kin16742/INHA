package shapes;

public class Square extends Rectangle {
	private static String CLASS_NAME = "Square";

	public Square(String name, double side) {
		super(name, side, side);
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public double getSide() {
		return getWidth();
	}

	public void setSize() {
		System.out.printf("Input %s`s Side : ", super.getName());
		double side = s.nextDouble();
		super.setWidth(side);
		super.setHeight(side);
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nArea = %.2f\nPerimeter = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculatePerimeter());

	}
}
