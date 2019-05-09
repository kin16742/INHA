//12141540 자바기반응용프로그래밍 2주차 과제 Drunken fly

import java.util.Random; //난수함수를 사용하기 위해 import

public class drunken_fly {

	public static void main(String[] args) {
		Random r = new Random(); //Random 클래스의 객체 r 생성
		char[][] arr = { { '*', '*', '*', '*', '*' }, //5x5 크기의 2차원 char 배열 arr를 초기화
				{ '*', '*', '*', '*', '*' }, { '*', '*', '*', '*', '*' },
				{ '*', '*', '*', '*', '*' }, { '*', '*', '*', '*', '#' } };
		int cnt = 0, currentX = 4, currentY = 4; //cnt : 시행 횟수, currentX = 파리의 현재 위치 x좌표, currentY = 파리의 현재 위치 y좌표
		
		while (arr[0][0] != '#') { //최종 목표 지점인 (0,0) 좌표에 #이 들어갈 때까지 반복문 사용
			System.out.println("------------"); //시행 횟수와 배열을 output에 맞춰 출력
			System.out.println(cnt + "번째 시행");
			System.out.println("------------");
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
			
			while (true) { //반복문 내에서 조건을 만족해 break를 만나기 전까지 무한루프
				int move = r.nextInt(10); //파리의 이동 방향을 결정할 int형 변수 move에 0~9사이의 난수 설정

				if (move >= 0 && move < 3) { //30% 확률로 왼쪽으로 이동
					if (currentX - 1 >= 0) { //파리의 현재 위치의 X좌표에서 1을 빼도 5x5 배열을 벗어나지 않을 때
						currentX--;			 //X좌표를 바꿔주고 break문으로 while 반복문 탈출
						break;
					}
				} else if (move >= 3 && move < 6) { //30% 확률로 위쪽으로 이동
					if (currentY - 1 >= 0) { //파리의 현재 위치의 Y좌표에서 1을 빼도 5x5 배열을 벗어나지 않을 때
											 //Y좌표를 바꿔주고 break문으로 while 반복문 탈출
						currentY--;
						break;
					}
				} else if (move >= 6 && move < 8) { //20% 확률로 오른쪽으로 이동
					if (currentX + 1 <= 4) { //파리의 현재 위치의 X좌표에서 1을 더해도 5x5 배열을 벗어나지 않을 때
						currentX++;			 //X좌표를 바꿔주고 break문으로 while 반복문 탈출
						break;
					}
				} else { //20% 확률로 아래쪽으로 이동
					if (currentY + 1 <= 4) { //파리의 현재 위치의 Y좌표에서 1을 더해도 5x5 배열을 벗어나지 않을 때
						currentY++;			 //Y좌표를 바꿔주고 break문으로 while 반복문 탈출
						break;
					}
				}
			}
			arr[currentX][currentY] = '#'; //바뀐 X, Y 좌표에 해당하는 배열 값을 #로 바꾼다.
			cnt++; //시행 횟수를 1 증가시킨다.
		}
		
		System.out.println("------------"); //while 반복문의 탈출 조건이 파리의 좌표가 (0,0)에 도달했을 때이므로
		System.out.println(cnt + "번째 시행");	//마지막에 완성된 배열이 출력되지 않았으니, 반복문 밖에서 마지막으로 시행 횟수와 배열을 출력해준다.
		System.out.println("------------");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
	}
}
