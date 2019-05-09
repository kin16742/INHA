package mart;

public abstract class item implements ForSale{
	private String itemID;
	private int importPrice;
	
	public item(String id, int price){
		this.itemID = id;
		this.importPrice = price;
	}
	public abstract String getInfo();
	
	public int getSalePrice(){
		return this.importPrice;
	}
}
