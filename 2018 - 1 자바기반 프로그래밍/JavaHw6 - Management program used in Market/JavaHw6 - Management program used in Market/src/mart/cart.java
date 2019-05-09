package mart;

public class cart {
	private int MAX_ITEM = 100;
	private item items[];
	private int itemNum;
	public cart(){
		items = new item[MAX_ITEM];
		itemNum = 0;
	}
	public int getNumberOfItems(){
		return itemNum;
	}
	public boolean addItem(item i){
		if(itemNum<20){
			items[itemNum++]=i;
			return true;
		}
		else{
			return false;
		}
	}
	public void printReceipt(){
		if(itemNum==0){
			System.out.println("cart is empty!!");
		}
		else{
			int total = 0;
			for(int i=0;i<itemNum;i++){
				System.out.printf("%2d. %-30s %,8d W\n", i+1, items[i].getInfo(), items[i].getSalePrice());
				total += items[i].getSalePrice();
			}
			System.out.println("----------------------------");
			System.out.printf("Total :                            %,8d W\n", total);
		}
	}
}
