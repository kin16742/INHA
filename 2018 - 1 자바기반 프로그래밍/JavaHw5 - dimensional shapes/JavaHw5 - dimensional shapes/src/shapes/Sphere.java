package shapes;

public class Sphere extends threeDimensionalShape {
	private static String CLASS_NAME = "Sphere";

	public Sphere(String name, double radius) {
		super(name, radius, radius, radius);
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
		super.setLength(radius);
		super.setHeight(radius);
	}

	public double calculateArea() {
		return 4 * Math.PI * getRadius() * getRadius();
	}

	public double calculateVolume() {
		return 4 / 3 * Math.PI * getRadius() * getRadius() * getRadius();
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nSurface area = %.2f\nVolume = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculateVolume());
	}
}
