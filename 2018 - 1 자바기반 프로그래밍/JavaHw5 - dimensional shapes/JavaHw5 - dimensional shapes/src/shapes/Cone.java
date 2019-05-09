package shapes;

public class Cone extends threeDimensionalShape {
	private static String CLASS_NAME = "Cone";

	public Cone(String name, double radius, double side, double height) {
		super(name, radius, side, height);
	}

	public String getClassName() {
		return CLASS_NAME;
	}

	public double getRadius() {
		return super.getWidth();
	}

	public double getSide() {
		return super.getLength();
	}

	public double getHeight() {
		return super.getHeight();
	}

	public void setSize() {
		System.out.printf("Input %s`s Radius : ", super.getName());
		double radius = s.nextDouble();
		System.out.printf("Input %s`s Side : ", super.getName());
		double side = s.nextDouble();
		System.out.printf("Input %s`s Height : ", super.getName());
		double height = s.nextDouble();
		super.setWidth(radius);
		super.setLength(side);
		super.setHeight(height);
	}

	public double calculateArea() {
		return Math.PI * getRadius() * (getRadius() + getSide());
	}

	public double calculateVolume() {
		return Math.PI * getRadius() * getRadius() * getHeight() / 3;
	}

	public String toString() {
		return String
				.format("%s is a %s inherited from %s class.\nSurface area = %.2f\nVolume = %.2f\n",
						super.getName(), getClassName(), super.getClassName(),
						calculateArea(), calculateVolume());
	}
}
