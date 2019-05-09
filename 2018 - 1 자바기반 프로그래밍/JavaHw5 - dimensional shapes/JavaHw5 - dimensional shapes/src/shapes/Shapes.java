package shapes;

public class Shapes {

	public static void main(String[] args) {
		Circle circle1 = new Circle("Circle 1", 0.0);
		Square square1 = new Square("Square 1", 0.0);
		Cone cone1 = new Cone("Cone 1", 0.0,0.0,0.0);
		Cube cube1 = new Cube("Cube 1", 0.0);
		Sphere sphere1 = new Sphere("Sphere 1", 0.0);
		
		circle1.setSize();
		square1.setSize();
		cone1.setSize();
		cube1.setSize();
		sphere1.setSize();
		
		System.out.println("1. " + circle1);
		System.out.println("2. " + square1);
		System.out.println("3. " + cone1);
		System.out.println("4. " + cube1);
		System.out.println("5. " + sphere1);

	}

}
