import java.awt.*;

import javax.swing.*;

public class CarRace extends JFrame {
	private JLabel labelCountDown;
	private int carx[];

	class CountDown extends Thread { // 상단의 Countdown을 위한 Thread
		public void run() { // run() 정의
			for (int i = 3; i >= 0; i--) {
				try {
					Thread.sleep(1000); // 1초 간격으로 3번 반복 (3초간 실행)
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				labelCountDown.setText(i + ""); // 3, 2, 1, 0 순으로 label에 출력
			}
		}
	}

	class Race extends Thread {				// 각 자동차의 위치를 변경시키는 Thread
		private JLabel labelCar;			// 자동차 이미지를 나타낼 label
		private int x, y;					// 자동차 번호 x, 자동차의 y좌표

		public Race(String fname, int carNum, int y) {	// 생성자
			this.x = carNum;							// 자동차 번호 설정
			this.y = y;									// 자동차의 y좌표 설정
			labelCar = new JLabel();					// 새 label 할당
			ImageIcon originIcon = new ImageIcon(fname);// 입력받은 file name의 이미지 불러오기
			Image originImg = originIcon.getImage();
			Image changedImg = originImg.getScaledInstance(100, 100,
					Image.SCALE_SMOOTH);				// 이미지 크기 변경
			labelCar.setIcon(new ImageIcon(changedImg));// 변경된 이미지로 설정
			labelCar.setBounds(carx[x], y, 100, 100);	// 이미지의 위치, 크기 설정
			add(labelCar, BorderLayout.CENTER);			// frame에 추가
		}

		public void run() {	// run() 정의
			boolean goal = false;			// 어떤 차가 goal했는지를 나타내는 boolean 변수
			for (int i = 3; i >= 0; i--) {	// Countdown 3초를 기다림
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			for (int i = 0; i < 200; i++) {	
				carx[x] += 50 * Math.random();	// 임의의 거리만큼 이동시킴

				if (carx[x] > 500) {			// 500보다 커졌으면 500으로 설정
					carx[x] = 500;
				}

				labelCar.setBounds(carx[x], y, 100, 100);	
				repaint();									// 이미지 위치 재설정

				try {
					Thread.sleep(1000);			// 거리 이동에 1초의 간격을 둠
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				for (int j = 0; j < 3; j++) {	// 결승점에 도달한 차량이 존재하면 Thread의 반복문 break
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
		for (int i = 0; i < 3; i++) {				// 각 차의 위치를 0으로 설정
			carx[i] = 0;
		}

		labelCountDown = new JLabel();
		labelCountDown.setFont(new Font("Serif", Font.BOLD, 100));
		labelCountDown.setBounds(0, 0, 100, 100);	
		add(labelCountDown, BorderLayout.NORTH);	// countdown Thread에 쓰일 label을 frame에 추가

		(new CountDown()).start();					// countdown Thread를 run시킴

		(new Race("car1.gif", 0, 150)).start();		// 이미지 파일, 차의 번호, y좌표를 Thread에 넘겨주면서 run시킴
		(new Race("car2.gif", 1, 280)).start();
		(new Race("car3.gif", 2, 410)).start();

		setVisible(true);
	}

	public static void main(String[] args) {
		CarRace CR = new CarRace();
	}
}
