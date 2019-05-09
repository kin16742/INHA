package shapes;

public class Cube extends threeDimensionalShape {
	private static String CLASS_NAME = "Cube";

	public Cube(String name, double side) {
		super(name, side, side, side);
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public double getSide() {
		return super.getWidth();
	}

	public void setSize() {
		System.out.printf("Input %s`s Side : ", super.getName());
		double side = s.nextDouble();
		super.setWidth(side);
		super.setLength(side);
		super.setHeight(side);
	}

	public double calculateArea() {
		return 6 * getSide() * getSide();
	}

	public double calculateVolume() {
		return getSide() * getSide() * getSide();
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nSurface area = %.2f\nVolume = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculateVolume());
	}
}
