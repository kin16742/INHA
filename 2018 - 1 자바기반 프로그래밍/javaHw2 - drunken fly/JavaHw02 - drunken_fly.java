//12141540 �ڹٱ���������α׷��� 2���� ���� Drunken fly

import java.util.Random; //�����Լ��� ����ϱ� ���� import

public class drunken_fly {

	public static void main(String[] args) {
		Random r = new Random(); //Random Ŭ������ ��ü r ����
		char[][] arr = { { '*', '*', '*', '*', '*' }, //5x5 ũ���� 2���� char �迭 arr�� �ʱ�ȭ
				{ '*', '*', '*', '*', '*' }, { '*', '*', '*', '*', '*' },
				{ '*', '*', '*', '*', '*' }, { '*', '*', '*', '*', '#' } };
		int cnt = 0, currentX = 4, currentY = 4; //cnt : ���� Ƚ��, currentX = �ĸ��� ���� ��ġ x��ǥ, currentY = �ĸ��� ���� ��ġ y��ǥ
		
		while (arr[0][0] != '#') { //���� ��ǥ ������ (0,0) ��ǥ�� #�� �� ������ �ݺ��� ���
			System.out.println("------------"); //���� Ƚ���� �迭�� output�� ���� ���
			System.out.println(cnt + "��° ����");
			System.out.println("------------");
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
			
			while (true) { //�ݺ��� ������ ������ ������ break�� ������ ������ ���ѷ���
				int move = r.nextInt(10); //�ĸ��� �̵� ������ ������ int�� ���� move�� 0~9������ ���� ����

				if (move >= 0 && move < 3) { //30% Ȯ���� �������� �̵�
					if (currentX - 1 >= 0) { //�ĸ��� ���� ��ġ�� X��ǥ���� 1�� ���� 5x5 �迭�� ����� ���� ��
						currentX--;			 //X��ǥ�� �ٲ��ְ� break������ while �ݺ��� Ż��
						break;
					}
				} else if (move >= 3 && move < 6) { //30% Ȯ���� �������� �̵�
					if (currentY - 1 >= 0) { //�ĸ��� ���� ��ġ�� Y��ǥ���� 1�� ���� 5x5 �迭�� ����� ���� ��
											 //Y��ǥ�� �ٲ��ְ� break������ while �ݺ��� Ż��
						currentY--;
						break;
					}
				} else if (move >= 6 && move < 8) { //20% Ȯ���� ���������� �̵�
					if (currentX + 1 <= 4) { //�ĸ��� ���� ��ġ�� X��ǥ���� 1�� ���ص� 5x5 �迭�� ����� ���� ��
						currentX++;			 //X��ǥ�� �ٲ��ְ� break������ while �ݺ��� Ż��
						break;
					}
				} else { //20% Ȯ���� �Ʒ������� �̵�
					if (currentY + 1 <= 4) { //�ĸ��� ���� ��ġ�� Y��ǥ���� 1�� ���ص� 5x5 �迭�� ����� ���� ��
						currentY++;			 //Y��ǥ�� �ٲ��ְ� break������ while �ݺ��� Ż��
						break;
					}
				}
			}
			arr[currentX][currentY] = '#'; //�ٲ� X, Y ��ǥ�� �ش��ϴ� �迭 ���� #�� �ٲ۴�.
			cnt++; //���� Ƚ���� 1 ������Ų��.
		}
		
		System.out.println("------------"); //while �ݺ����� Ż�� ������ �ĸ��� ��ǥ�� (0,0)�� �������� ���̹Ƿ�
		System.out.println(cnt + "��° ����");	//�������� �ϼ��� �迭�� ��µ��� �ʾ�����, �ݺ��� �ۿ��� ���������� ���� Ƚ���� �迭�� ������ش�.
		System.out.println("------------");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
	}
}
