import java.awt.*;

import javax.swing.*;

public class CarRace extends JFrame {
	private JLabel labelCountDown;
	private int carx[];

	class CountDown extends Thread { // ����� Countdown�� ���� Thread
		public void run() { // run() ����
			for (int i = 3; i >= 0; i--) {
				try {
					Thread.sleep(1000); // 1�� �������� 3�� �ݺ� (3�ʰ� ����)
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				labelCountDown.setText(i + ""); // 3, 2, 1, 0 ������ label�� ���
			}
		}
	}

	class Race extends Thread {				// �� �ڵ����� ��ġ�� �����Ű�� Thread
		private JLabel labelCar;			// �ڵ��� �̹����� ��Ÿ�� label
		private int x, y;					// �ڵ��� ��ȣ x, �ڵ����� y��ǥ

		public Race(String fname, int carNum, int y) {	// ������
			this.x = carNum;							// �ڵ��� ��ȣ ����
			this.y = y;									// �ڵ����� y��ǥ ����
			labelCar = new JLabel();					// �� label �Ҵ�
			ImageIcon originIcon = new ImageIcon(fname);// �Է¹��� file name�� �̹��� �ҷ�����
			Image originImg = originIcon.getImage();
			Image changedImg = originImg.getScaledInstance(100, 100,
					Image.SCALE_SMOOTH);				// �̹��� ũ�� ����
			labelCar.setIcon(new ImageIcon(changedImg));// ����� �̹����� ����
			labelCar.setBounds(carx[x], y, 100, 100);	// �̹����� ��ġ, ũ�� ����
			add(labelCar, BorderLayout.CENTER);			// frame�� �߰�
		}

		public void run() {	// run() ����
			boolean goal = false;			// � ���� goal�ߴ����� ��Ÿ���� boolean ����
			for (int i = 3; i >= 0; i--) {	// Countdown 3�ʸ� ��ٸ�
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			for (int i = 0; i < 200; i++) {	
				carx[x] += 50 * Math.random();	// ������ �Ÿ���ŭ �̵���Ŵ

				if (carx[x] > 500) {			// 500���� Ŀ������ 500���� ����
					carx[x] = 500;
				}

				labelCar.setBounds(carx[x], y, 100, 100);	
				repaint();									// �̹��� ��ġ �缳��

				try {
					Thread.sleep(1000);			// �Ÿ� �̵��� 1���� ������ ��
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				for (int j = 0; j < 3; j++) {	// ������� ������ ������ �����ϸ� Thread�� �ݺ��� break
					if (carx[j] >= 500) {
						goal = true;
					}
				}
				if (goal)
					break;
			}
		}
	}

	public CarRace() {
		setTitle("CarRace");
		setSize(600, 600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(null);

		carx = new int[3];
		for (int i = 0; i < 3; i++) {				// �� ���� ��ġ�� 0���� ����
			carx[i] = 0;
		}

		labelCountDown = new JLabel();
		labelCountDown.setFont(new Font("Serif", Font.BOLD, 100));
		labelCountDown.setBounds(0, 0, 100, 100);	
		add(labelCountDown, BorderLayout.NORTH);	// countdown Thread�� ���� label�� frame�� �߰�

		(new CountDown()).start();					// countdown Thread�� run��Ŵ

		(new Race("car1.gif", 0, 150)).start();		// �̹��� ����, ���� ��ȣ, y��ǥ�� Thread�� �Ѱ��ָ鼭 run��Ŵ
		(new Race("car2.gif", 1, 280)).start();
		(new Race("car3.gif", 2, 410)).start();

		setVisible(true);
	}

	public static void main(String[] args) {
		CarRace CR = new CarRace();
	}
}
