import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

public class calculator extends JFrame implements ActionListener {
	private double first, second;
	private String operate;
	private boolean error;
	private JPanel panel1, panel2;
	private JTextField tField;
	private JButton[] buttons;
	private String[] labels = { "7", "8", "9", "4", "5", "6", "1", "2", "3",
			"", "0", "", "+", "-", "*", "/", "=", "Clear" };

	public calculator() {
		first = 0;
		second = 0;
		operate = "";
		error = false;
		tField = new JTextField(35);
		panel1 = new JPanel();
		panel2 = new JPanel();
		tField.setText("");
		tField.setEnabled(false);
		tField.setFont(new Font("Serif", Font.PLAIN, 25));

		panel1.setLayout(new GridLayout(0, 3, 2, 2));
		panel2.setLayout(new GridLayout(0, 1, 2, 2));
		buttons = new JButton[18];

		for (int i = 0; i < 18; i++) {
			buttons[i] = new JButton(labels[i]);
			buttons[i].addActionListener(this);
			buttons[i].setFont(new Font("Serif", Font.PLAIN, 25));
		}
		for (int i = 0; i < 12; i++) {
			panel1.add(buttons[i]);
		}
		for (int i = 12; i < 18; i++) {
			panel2.add(buttons[i]);
		}

		add(tField, BorderLayout.NORTH);
		add(panel1, BorderLayout.CENTER);
		add(panel2, BorderLayout.EAST);

		setSize(500, 500);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Calculator");
		setVisible(true);
	}

	public void firstCheck(String toI) throws ArithmeticException {
		double check = first;
		boolean isZero = false;
		int fromS = Integer.parseInt(toI);

		check = check * 10 + fromS;
		if (first * 10 + fromS > 2000000000 || check != first * 10 + fromS) {
			throw new ArithmeticException();
		} else {
			if (first == 0)
				isZero = true;

			first = first * 10 + fromS;

			String str = tField.getText();
			if (str.length() >= 1) {
				char last = str.charAt(str.length() - 1);
				if (last == '0') {
					if (isZero) {
						str = str.substring(0, str.length() - 1);
						tField.setText(str);
					}
				}
			}

			tField.setText(tField.getText() + toI);
		}
	}

	public void operation(String ope) {
		try {
			if (operate == "") {
				second = first;
				first = 0;
				if (first == 0 && second == 0) {
					tField.setText("" + 0 + ope);
				} else {
					tField.setText(tField.getText() + ope);
				}
			} else {
				if (first == 0 && second != 0) {
					String dd = tField.getText();
					dd = dd.substring(0, dd.length() - 1);
					tField.setText(dd + ope);
				} else if (first == 0 && second == 0) {
					tField.setText("" + 0 + ope);
				} else if (first != 0 && second == 0) {
					equals();
					second = first;
					first = 0;
					if (second % 1.0 == 0) {
						int a = (int) second;
						tField.setText("" + a + ope);
					} else {
						tField.setText("" + second + ope);
					}
				} else if (first != 0 && second != 0) {
					equals();
					second = first;
					first = 0;
					if (second % 1.0 == 0) {
						int a = (int) second;
						tField.setText("" + a + ope);
					} else {
						tField.setText("" + second + ope);
					}
				}
			}
			operate = ope;
		} catch (ArithmeticException arithmeticException) {
			tField.setText("값의 범위를 초과하였습니다.");
			error = true;
		} catch (Exception exception) {
			tField.setText("0으로 나눌 수 없습니다.");
			error = true;
		}
	}

	public void equals() throws ArithmeticException, Exception {
		if (operate == "+") {
			double check = first;
			check = check + second;

			if (first + second > 2000000000 || check != first + second) {
				throw new ArithmeticException();
			} else {
				operate = "";
				first += second;
				second = 0;
				if (first % 1.0 == 0) {
					int a = (int) first;
					tField.setText("" + a);
				} else {
					tField.setText("" + first);
				}
			}
		} else if (operate == "-") {
			double check = first;
			check = check - second;

			if (first - second < -2000000000 || check != first - second) {
				throw new ArithmeticException();
			} else {
				operate = "";
				second -= first;
				first = second;
				second = 0;
				if (first % 1.0 == 0) {
					int a = (int) first;
					tField.setText("" + a);
				} else {
					tField.setText("" + first);
				}
			}
		} else if (operate == "*") {
			double check = first;
			check = check * second;

			if (first * second > 2000000000 || first * second < -2000000000
					|| check != first * second) {
				throw new ArithmeticException();
			} else {
				operate = "";
				first *= second;
				second = 0;
				if (first % 1.0 == 0) {
					int a = (int) first;
					tField.setText("" + a);
				} else {
					tField.setText("" + first);
				}
			}
		} else if (operate == "/") {
			double check = second;
			if (first == 0) {
				throw new Exception();
			}
			if (!error) {
				check = check / first;

				if (second / first > 2000000000 || second / first < -2000000000
						|| check != second / first) {
					throw new ArithmeticException();
				} else {
					operate = "";
					second /= first;
					first = second;
					second = 0;
					if (first % 1.0 == 0) {
						int a = (int) first;
						tField.setText("" + a);
					} else {
						tField.setText("" + first);
					}

				}
			}
		}

	}

	public void actionPerformed(ActionEvent e) {
		try {
			String actionCommand = e.getActionCommand();

			if (!error) {
				if (actionCommand == "1" || actionCommand == "2"
						|| actionCommand == "3" || actionCommand == "4"
						|| actionCommand == "5" || actionCommand == "6"
						|| actionCommand == "7" || actionCommand == "8"
						|| actionCommand == "9" || actionCommand == "0") {
					firstCheck(actionCommand);
				}

				else if (actionCommand == "+" || actionCommand == "-"
						|| actionCommand == "*" || actionCommand == "/") {
					operation(actionCommand);
				}

				else if (actionCommand == "=") {
					equals();
				}
			}

			if (actionCommand == "Clear") {
				first = 0;
				second = 0;
				operate = "";
				error = false;
				tField.setText("");
			}
		} catch (ArithmeticException arithmeticException) {
			tField.setText("값의 범위를 초과하였습니다.");
			error = true;
		} catch (Exception exception) {
			tField.setText("0으로 나눌 수 없습니다.");
			error = true;
		}
	}

	public static void main(String[] args) {
		calculator c = new calculator();
	}
}
