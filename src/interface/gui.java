// Java Program to create a text editor using java
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.awt.event.*;
import javax.swing.plaf.metal.*;
import javax.swing.text.*;

class editor extends JFrame implements ActionListener {
	// Text component
	/* JTextArea */JTextField t;
	JTextField p;

	// Frame
	JFrame f;

	// Constructor
	editor()
	{
		// Create a frame
		f = new JFrame("editor");

		try {
			// Set metal look and feel
			UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");

			// Set theme to ocean
			MetalLookAndFeel.setCurrentTheme(new OceanTheme());
		}
		catch (Exception e) {
		}
		// Text component
		t = new JTextField();//JTextArea();
		// Prompt component
		p = new JTextField();
		p.setEditable(false);
		//System.out.println(Prompt.toString());

		// Create a menubar
		JMenuBar mb = new JMenuBar();

		/* m1	| m2	| m3	| mc 	\
		 * -----+-------+-------+----	|
		 * m11	| m21	| m31	| close	|
		 * m12	| m22	| m32	|		 > mb
		 * m13	| m23	| m33	|		|
		 * m14	| m24	| m34	|		/
		 * ...
		 */

		// Create amenu for menu
		JMenu m1 = new JMenu("File");

		// Create menu items
		JMenuItem m11 = new JMenuItem("New");
		JMenuItem m12 = new JMenuItem("Open");
		JMenuItem m13 = new JMenuItem("Save");
		JMenuItem m14 = new JMenuItem("Print");

		// Add action listener
		m11.addActionListener(this);
		m12.addActionListener(this);
		m13.addActionListener(this);
		m14.addActionListener(this);

		m1.add(m11);
		m1.add(m12);
		m1.add(m13);
		m1.add(m14);

		// Create amenu for menu
		JMenu m2 = new JMenu("Edit");

		// Create menu items
		JMenuItem m21 = new JMenuItem("cut");
		JMenuItem m22 = new JMenuItem("copy");
		JMenuItem m23 = new JMenuItem("paste");

		// Add action listener
		m21.addActionListener(this);
		m22.addActionListener(this);
		m23.addActionListener(this);

		m2.add(m21);
		m2.add(m22);
		m2.add(m23);

		JMenuItem m3 = new JMenuItem("Exec");

		m3.addActionListener(this);

		JMenuItem mc = new JMenuItem("close");

		mc.addActionListener(this);

		mb.add(m1);
		mb.add(m2);
		mb.add(m3);
		mb.add(mc);

		f.setJMenuBar(mb);
		f.add(p);
		f.add(t);
		f.setSize(500, 500);
		//f.show();


		// Add a window listener for close button
		f.addWindowListener(
			new WindowAdapter()
			{
				public void windowClosing(WindowEvent e)
				{
					System.exit(0);
				}
			}
		);
	}

	// If a button is pressed
	public void actionPerformed(ActionEvent e) {
		String s = e.getActionCommand();

		if (s.equals("cut"))
		{
			t.cut();
		}
		else if (s.equals("copy")) {
			t.copy();
		}
		else if (s.equals("paste")) {
			t.paste();
		}
		else if (s.equals("Save")) {
			// Create an object of JFileChooser class
			JFileChooser j = new JFileChooser("f:");

			// Invoke the showsSaveDialog function to show the save dialog
			int r = j.showSaveDialog(null);

			if (r == JFileChooser.APPROVE_OPTION) {

				// Set the label to the path of the selected directory
				File fi = new File(j.getSelectedFile().getAbsolutePath());

				try {
					// Create a file writer
					FileWriter wr = new FileWriter(fi, false);

					// Create buffered writer to write
					BufferedWriter w = new BufferedWriter(wr);

					// Write
					w.write(t.getText());

					w.flush();
					w.close();
				}
				catch (Exception evt) {
					JOptionPane.showMessageDialog(f, evt.getMessage());
				}
			}
			// If the user cancelled the operation
			else
				JOptionPane.showMessageDialog(f, "the user cancelled the operation");
		}
		else if (s.equals("Print")) {
			try {
				// print the file
				t.print();
			}
			catch (Exception evt) {
				JOptionPane.showMessageDialog(f, evt.getMessage());
			}
		}
		else if (s.equals("Open")) {
			// Create an object of JFileChooser class
			JFileChooser j = new JFileChooser("f:");

			// Invoke the showsOpenDialog function to show the save dialog
			int r = j.showOpenDialog(null);

			// If the user selects a file
			if (r == JFileChooser.APPROVE_OPTION) {
				// Set the label to the path of the selected directory
				File fi = new File(j.getSelectedFile().getAbsolutePath());

				try {
					// String
					String s1 = "", sl = "";

					// File reader
					FileReader fr = new FileReader(fi);

					// Buffered reader
					BufferedReader br = new BufferedReader(fr);

					// Initialize sl
					sl = br.readLine();

					// Take the input from the file
					while ((s1 = br.readLine()) != null) {
						sl = sl + "\n" + s1;
					}

					// Set the text
					t.setText(sl);

					br.close();
				}
				catch (Exception evt) {
					JOptionPane.showMessageDialog(f, evt.getMessage());
				}
			}
			// If the user cancelled the operation
			else
				JOptionPane.showMessageDialog(f,
					"the user cancelled the operation");
		}
		else if (s.equals("New")) {
			StringBuilder prompt = new StringBuilder();


			ProcessBuilder processBuilder = new ProcessBuilder();
			processBuilder.command("./prompt");

			try {

				Process process = processBuilder.start();

				BufferedReader reader = new BufferedReader(
						new InputStreamReader(process.getInputStream()));

				String line;
				while ((line = reader.readLine()) != null) {
					prompt.append(line + "\n");
				}

				prompt.deleteCharAt(prompt.length() - 1);

				// int exitVal = process.waitFor();

			}
			catch (IOException e2) {
				e2.printStackTrace();
			} /*
			 * catch (InterruptedException e2) { e2.printStackTrace(); }
			 */
			p.setText(prompt.toString());
			t.setText(prompt.toString());
		}
		else if (s.equals("Exec")) {
			// Windows?
			// boolean isWindows =
			// System.getProperty("os.name").toLowerCase().startsWith("windows");

			ProcessBuilder processBuilder = new ProcessBuilder();
			processBuilder.command("../../output", t.getText());

			try {

				Process process = processBuilder.start();

				StringBuilder output = new StringBuilder();

				BufferedReader reader =
						new BufferedReader(new InputStreamReader(
								process.getInputStream()));

				String line;
				while ((line = reader.readLine()) != null) {
					output.append(line + "\n");
				}

				output.deleteCharAt(output.length() - 1);

				int exitVal = process.waitFor();
				if (exitVal == 0) {
					// System.out.println("Success!");
					System.out.println(output);
					System.exit(0);
				}
				else {
					// abnormal...
				}

			}
			catch (IOException e2) {
				e2.printStackTrace();
			}
			catch (InterruptedException e2) {
				e2.printStackTrace();
			}
		}
		else if (s.equals("close"))
		{
			f.setVisible(false);
			System.exit(0);
		}
	}

	// Main class
	public static void main(String args[]) {
		editor e = new editor();
	}
}
