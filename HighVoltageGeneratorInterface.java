package HighVoltageGeneratorInterface;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import javax.swing.*;
import java.awt.*; 
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.geom.Line2D;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.TooManyListenersException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
import javax.swing.text.PlainDocument;



 public class HighVoltageGeneratorInterface extends JFrame implements SerialPortEventListener{
     
   //----------------Arduino Communcation---------------------------------
   // modified from http://playground.arduino.cc/Interfacing/Java
     
    public SerialPort serialPort;
        
	private static final String PORT_NAMES[] = { 
			//"COM6", // Windows
                        "COM5", //Arduino Mega
            //"COM3", //Arduino Uno
	};
	
     
	private BufferedReader input;
	/** The output stream to the port */
	public static OutputStream output;
	/** Milliseconds to block while waiting for port to open */
	private static final int TIME_OUT = 2000;
	/** Default bits per second for COM port. */
	private static final int DATA_RATE = 9600;
        
         public void initialize() {

		CommPortIdentifier portId = null;
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

		
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
			for (String portName : PORT_NAMES) {
				if (currPortId.getName().equals(portName)) {
					portId = currPortId;
					break;
				}
			}
		}
		if (portId == null) {
			//System.out.println("Could not find COM port.");
			return;
		}

		try {
			// open serial port
			serialPort = (SerialPort) portId.open(this.getClass().getName(),
					TIME_OUT);

			// set port parameters
			serialPort.setSerialPortParams(DATA_RATE,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);

			// open the streams
			input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
			output = serialPort.getOutputStream();

			// add event listeners
			serialPort.addEventListener(this);
			serialPort.notifyOnDataAvailable(true);
		} catch (PortInUseException | UnsupportedCommOperationException | IOException | TooManyListenersException e) {
			System.err.println(e.toString());
		}
	}

   //-----------------GUI Building-----------------------------------
        
    public static float frequency;
    public static float voltage;
    public static boolean WaveFlag = false;
    public static int wave;
    
    public WaveSinDraw sines = new WaveSinDraw(voltage, frequency);
    public SquareDraw square = new SquareDraw(voltage, frequency);
    public TriangleDraw triangle = new TriangleDraw(voltage, frequency);
    
    private static final JPanel panelSouth = new JPanel();
    private static final JPanel panelEast = new JPanel();
    private static final JPanel VoltPanel = new JPanel();
    private static final JPanel WavePanel = new JPanel();
    JToggleButton SinButton = new JToggleButton("Sin", false);
    JToggleButton TriangButton = new JToggleButton("Tri", false);
    JToggleButton SquareButton = new JToggleButton("Sqr", false);
    
    private static final JLabel voltLabel = new JLabel("Voltage");
    private static final JLabel frequencyLabel = new JLabel("Frequency");
    private static final JLabel voltPoint = new JLabel(".");
    private static final JTextField voltText1 = new JTextField();
    private static final JTextField voltText2 = new JTextField();
    private static final JTextField voltText3 = new JTextField();
    private static final JPanel FreqPanel = new JPanel();
     private static final JLabel freqPoint = new JLabel(".");
    private static final JTextField freqText1 = new JTextField();
    private static final JTextField freqText2 = new JTextField();
    private static final JTextField freqText3 = new JTextField();
    
    private static final JButton ApplyButton = new JButton("APPLY");
    
    private static final JLabel voltDisplayLabel = new JLabel("Voltage");
    private static final JLabel frequencyDisplayLabel = new JLabel("Frequency");
    
    private static final JTextArea Voltage = new JTextArea();
    private static final JTextArea Frequency = new JTextArea();
    
    private static final JLabel LED = new JLabel();
    
    
    public class LEDPanel extends JPanel
 {
    
    public void paintComponent(Graphics g) { 
    super.paintComponent(g); 
    g.setColor(Color.RED);
    g.fillOval(20,20,8,8); 
} 
 }
    
    public HighVoltageGeneratorInterface() {
        
         PlainDocument filter = (PlainDocument) voltText1.getDocument();
        filter.setDocumentFilter(new InterfaceFilter(6, 1));
        
        
        PlainDocument filter1 = (PlainDocument) voltText2.getDocument();
        filter1.setDocumentFilter(new InterfaceFilter(10, 1));
        
        PlainDocument filter2 = (PlainDocument) voltText3.getDocument();
        filter2.setDocumentFilter(new InterfaceFilter(10, 1));
        
        
        PlainDocument filterf1 = (PlainDocument) freqText1.getDocument();
        filterf1.setDocumentFilter(new InterfaceFilter(11, 2));
        
        PlainDocument filterf2 = (PlainDocument) freqText2.getDocument();
        filterf2.setDocumentFilter(new InterfaceFilter(10, 1));
        
        PlainDocument filterf3 = (PlainDocument) freqText3.getDocument();
        filterf3.setDocumentFilter(new InterfaceFilter(10, 1));
        
           
        setTitle("High Voltage Generator");
        add(BorderLayout.EAST, panelEast);
        add(BorderLayout.SOUTH, panelSouth);
        
        //--------------Panel East-------------------------------------
        TitledBorder title = BorderFactory.createTitledBorder(null, "Settings", TitledBorder.LEFT, TitledBorder.TOP, new Font("Verdana",Font.BOLD,20));
        panelEast.setBorder(title);
        
        panelEast.setLayout(new BoxLayout(panelEast, BoxLayout.Y_AXIS));
        
        panelEast.add(Box.createRigidArea(new Dimension(200, 30)));
        
        WavePanel.add(SinButton);
        WavePanel.add(TriangButton);
        WavePanel.add(SquareButton);
        panelEast.add(WavePanel);
        
        //---------------Voltage-----------------------
        voltLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        voltLabel.setFont(new Font(voltLabel.getName(), Font.BOLD, 16));
        voltLabel.setForeground(Color.red);
        panelEast.add(voltLabel);
        //---------------Voltage Input --------------------
        voltText1.setColumns(2);
        Font bigFont = voltText1.getFont().deriveFont(Font.PLAIN, 50f);
        voltText1.setFont(bigFont);
        voltText1.setHorizontalAlignment(voltText1.CENTER);
        
        voltText2.setColumns(1);
        Font bigFont2 = voltText2.getFont().deriveFont(Font.PLAIN, 50f);
        voltText2.setFont(bigFont2);
        voltText2.setHorizontalAlignment(voltText2.CENTER);
        voltText3.setColumns(1);
        Font bigFont3 = voltText3.getFont().deriveFont(Font.PLAIN, 50f);
        voltText3.setFont(bigFont3);
        voltText3.setHorizontalAlignment(voltText3.CENTER);
        
        Font bigFont4 = voltPoint.getFont().deriveFont(Font.PLAIN, 50f);
        voltPoint.setFont(bigFont4);
        
        VoltPanel.add(voltText1);
        VoltPanel.add(voltPoint);
        VoltPanel.add(voltText2);
        VoltPanel.add(voltText3);
        VoltPanel.setSize(new Dimension(80, 100));
        
        panelEast.add(VoltPanel);
        
        //-----------------Frequency------------------------
        frequencyLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        frequencyLabel.setFont(new Font(frequencyLabel.getName(), Font.BOLD, 16));
        frequencyLabel.setForeground(Color.red);
        panelEast.add(frequencyLabel);
        
        //-------------------Frequency Input -----------------------
               
        freqText1.setColumns(2);
        Font bigFontf1 = freqText1.getFont().deriveFont(Font.PLAIN, 50f);
        freqText1.setFont(bigFontf1);
        freqText1.setHorizontalAlignment(freqText1.CENTER);
        freqText2.setColumns(1);
        Font bigFontf2 = freqText2.getFont().deriveFont(Font.PLAIN, 50f);
        freqText2.setFont(bigFontf2);
        freqText2.setHorizontalAlignment(freqText2.CENTER);
        freqText3.setColumns(1);
        Font bigFontf3 = freqText3.getFont().deriveFont(Font.PLAIN, 50f);
        freqText3.setFont(bigFontf3);
        freqText3.setHorizontalAlignment(freqText3.CENTER);
        Font bigFontf4 = freqPoint.getFont().deriveFont(Font.PLAIN, 50f);
        freqPoint.setFont(bigFontf4);
        
        
        FreqPanel.add(freqText1);
        FreqPanel.add(freqPoint);
        FreqPanel.add(freqText2);
        FreqPanel.add(freqText3);
        
        panelEast.add(FreqPanel);
       
        
        ApplyButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        ApplyButton.setFont(new Font( ApplyButton.getName(), Font.BOLD, 50));
        ApplyButton.setFocusPainted(false);
        ApplyButton.setBackground(Color.BLUE);
        ApplyButton.setForeground(Color.WHITE);
        ApplyButton.setMinimumSize(new Dimension(200, 300));
        panelEast.add(ApplyButton);
        
       panelEast.add(Box.createRigidArea(new Dimension(20, 10)));
        
        //------------Panel South--------------------------
        TitledBorder title2 = BorderFactory.createTitledBorder(null, "Monitoring", TitledBorder.LEFT, TitledBorder.TOP, new Font("Verdana",Font.BOLD,20));
        panelSouth.setBorder(title2);
        panelSouth.setLayout(new BoxLayout(panelSouth, BoxLayout.X_AXIS));
        
        panelSouth.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        
        Voltage.setColumns(4);
        Voltage.setEditable(false);
        Voltage.setMaximumSize(new Dimension(65, 50));
        
        Frequency.setColumns(4);
        Frequency.setEditable(false);
        Frequency.setMaximumSize(new Dimension(80, 70));
        LED.setMaximumSize(new Dimension(80, 70));
        LED.setOpaque(true);
        LED.setBackground(Color.RED);
        Border border = BorderFactory.createLineBorder(Color.BLACK, 2);
        LED.setBorder(border);
        
        panelSouth.add(Box.createRigidArea(new Dimension(250, 30)));
        Font bigFont7 = voltDisplayLabel.getFont().deriveFont(Font.CENTER_BASELINE, 20f);
        voltDisplayLabel.setFont(bigFont7);
        Voltage.setFont(bigFont7);
        panelSouth.add(voltDisplayLabel);
        panelSouth.add(Box.createRigidArea(new Dimension(10, 30)));
        panelSouth.add(Voltage);
        panelSouth.add(Box.createRigidArea(new Dimension(100, 30)));
        frequencyDisplayLabel.setFont(bigFont7);
        Frequency.setFont(bigFont7);
        panelSouth.add(frequencyDisplayLabel);
        panelSouth.add(Box.createRigidArea(new Dimension(10, 30)));
        panelSouth.add(Frequency);
        panelSouth.add(Box.createRigidArea(new Dimension(140, 30)));
        panelSouth.add(LED);
        //panelSouth.add(new LEDPanel());
       
        setSize(1080, 720);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        
        
            ApplyButton.addActionListener((java.awt.event.ActionEvent evt) -> {
                try {
                    Apply(evt);
                } catch (IOException ex) {
                    Logger.getLogger(HighVoltageGeneratorInterface.class.getName()).log(Level.SEVERE, null, ex);
                }
        });
        
    ItemListener itemListener1 = new ItemListener() {
      public void itemStateChanged(ItemEvent itemEvent) {
        int state = itemEvent.getStateChange();
        if (state == ItemEvent.SELECTED) {
          TriangButton.setSelected(false);
          SquareButton.setSelected(false);
        } else {
        }
      }
    };
    
    ItemListener itemListener2 = new ItemListener() {
      public void itemStateChanged(ItemEvent itemEvent) {
        int state = itemEvent.getStateChange();
        if (state == ItemEvent.SELECTED) {
          SinButton.setSelected(false);
          SquareButton.setSelected(false);
        } else {
        }
      }
    };
    
     ItemListener itemListener3 = new ItemListener() {
      public void itemStateChanged(ItemEvent itemEvent) {
        int state = itemEvent.getStateChange();
        if (state == ItemEvent.SELECTED) {
          TriangButton.setSelected(false);
          SinButton.setSelected(false);
        } else {
        }
      }
    };
            
     SinButton.addItemListener(itemListener1);  
     TriangButton.addItemListener(itemListener2);  
     SquareButton.addItemListener(itemListener3);  
            
    }

    
    
    public synchronized void close() {
		if (serialPort != null) {
			serialPort.removeEventListener();
			serialPort.close();
		}
	}

     

    public static void main(String[] args) {
        
        try {
            for (UIManager.LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e) {
            
        }
       
        
        
        HighVoltageGeneratorInterface main = new HighVoltageGeneratorInterface();
		main.initialize();
		Thread t=new Thread() {
                        @Override
			public void run() {
			}
		};
		t.start();
               LED.setBackground(Color.GREEN);
               // System.out.println("Started");
        
      
        
        
    }
    
    @Override
    public synchronized void serialEvent(SerialPortEvent oEvent) {
 if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
 try {
 String inputLine=input.readLine();
 System.out.println(inputLine);
 LED.setBackground(Color.GREEN);
        
 } catch (Exception e) {
 System.err.println(e.toString());
 }
  }
    }

  
    
    
private void Apply(java.awt.event.ActionEvent evt) throws IOException {  
   
    if (SinButton.isSelected() || TriangButton.isSelected() || SquareButton.isSelected()){
    
    WaveFlag = true;
    
    }
    
    if(WaveFlag == true && !voltText1.getText().equals("") && !voltText2.getText().equals("") && !voltText3.getText().equals("") && !freqText1.getText().equals("") && !freqText2.getText().equals("") && !freqText3.getText().equals("") ){           
 
 
        
//-------------------------- voltage ------------------------------------------     
 LED.setBackground(Color.RED);
        
       String voltage1 = voltText1.getText();
       String voltage2 = voltText2.getText();
       String voltage3 = voltText3.getText();
       
       voltText1.requestFocus();
       voltText2.requestFocus();       
       voltText3.requestFocus();
       Voltage.setText(null);
       ApplyButton.requestFocus();
       
       int volt1 = Integer.valueOf(voltage1);
       int volt2 = Integer.valueOf(voltage2);
       int volt3 = Integer.valueOf(voltage3);
        
       voltage = volt1 + (volt2/10) + (volt3 /100);
       
//-------------------------- frequency ------------------------------------------
       
       String frequency1 = freqText1.getText();
       String frequency2 = freqText2.getText();
       String frequency3 = freqText3.getText();
       
       freqText1.requestFocus();
       freqText2.requestFocus();       
       freqText3.requestFocus();
       Frequency.setText(null);
       
       int freq1 = Integer.valueOf(frequency1);
       int freq2 = Integer.valueOf(frequency2);
       int freq3 = Integer.valueOf(frequency3);
        
       float frequ1 = Float.valueOf(frequency1);
       float frequ2 = Float.valueOf(frequency2);
       float frequ3 = Float.valueOf(frequency3);
       
       frequency = frequ1 + (frequ2/10) + (frequ3 /100);
       
 //-------------------------- wave form ----------------------------------------       
        
 if (SinButton.isSelected()) { 
     add(sines);
     sines.setVoltageandFrequency(voltage, frequency);
     
     wave = 0;

        }   
 if (TriangButton.isSelected()) { 
     add(triangle);
     triangle.setVoltageandFrequency3(voltage, frequency);
     wave = 1;
     
        }   
 if (SquareButton.isSelected()) { 
     add(square);
     square.setVoltageandFrequency2(voltage, frequency);
     wave = 2;
     
        }        
       
// ---------------------------- monitor fields ------------------------------------       
       
       if(voltage < 5.00){
       Voltage.append( "  " + voltage1 + "." + voltage2 + voltage3);
       
       } else {
            voltage1 = "5";
            voltage2 = "0";
            voltage3 = "0";
           
          Voltage.append("  " + voltage1 + "." + voltage2 + voltage3);
            
       }
       
       if(frequency < 10.00){
       Frequency.append("  " + frequency1 + "." + frequency2 + frequency3);
       
       } else {
            frequency1 = "10";
            frequency2 = "0";
            frequency3 = "0";
           
           Frequency.append( " " + frequency1 + "." + frequency2 + frequency3);
            
       }
      
 //------------------------------sending to arduino --------------------
 
 try
        {
//wave form
       output.write(wave);
       output.flush();

       
        
//-----------------------------------------------------------------------       
//voltage     
        if(voltage < 5.00){
       
        output.write(volt1);
        output.flush();
            
        output.write(volt2);
        output.flush();
            
        output.write(volt3);
        output.flush();
        
        
       } else {
            
            
            volt1 = 5;
            volt2 = 0;
            volt3 = 0;
            
        output.write(volt1);
        output.flush();
            
        output.write(volt2);
        output.flush();
            
        output.write(volt3);
        output.flush();
            
            
       }
        
   //---------------------------frequency-------------------------------------
      
      if(frequency < 10.00){
       
        output.write(freq1);
        output.flush();
            
        output.write(freq2);
        output.flush();
            
        output.write(freq3);
        output.flush();
        
        
       } else {
            
            freq1 = 10;
            freq2 = 0;
            freq3 = 0;
            
            
        output.write(freq1);
        output.flush();
            
        output.write(freq2);
        output.flush();
            
        output.write(freq3);
        output.flush();
            
           
            }
        
            
       }  catch (Exception e)        {
           
        }         
    }
        
         }
}



final class WaveSinDraw extends JPanel {
    
   private float amplitude;
   private float freq;
   
public WaveSinDraw(float volts, float freqs) {
        
        
     setVoltageandFrequency((float) 0.00, (float) 0.00);
          
    }
           
public void setVoltageandFrequency(float newVoltage, float newFrequency) {
    amplitude = newVoltage;
    freq = newFrequency;
    
    if(amplitude >= 5.00){
    amplitude = (float) 5.00;
    }
    
    repaint();
     
} 




   @Override
    public void paint( Graphics g )
    {   super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setStroke(new BasicStroke(5));
            g.setFont(new Font("TimesRoman", Font.PLAIN, 25)); 
            
        int xBase   = 55;
        float floatxBase = (float) 55.00;
        int top     = 0;
        int yScale  = getHeight()- 20;
        float floatyScale = getHeight()- 20;
        int xAxis   = getWidth();

        int yBase   = top + yScale;
        float floatyBase = top + yScale;
        float offset = top + yBase - yScale * 1/6*amplitude/2;
        float x, y;
        
        //draw the axis
        g.drawLine( xBase, top, xBase, yBase );
        g.drawLine( xBase, yBase, xBase + xAxis, yBase );
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(2));
        g.drawLine( xBase+360, top, xBase+360, yBase);
        g.drawLine( xBase+720, top, xBase+720, yBase);
        
        g.setColor( Color.RED );
        g2.setStroke(new BasicStroke(2)); 
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 1, xBase + xAxis, yBase - yScale * 1/6 * 1);
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 2, xBase + xAxis, yBase - yScale * 1/6 * 2 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 3, xBase + xAxis, yBase - yScale * 1/6 * 3 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 4, xBase + xAxis, yBase - yScale * 1/6 * 4 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 5, xBase + xAxis, yBase - yScale * 1/6 * 5 );
        
        
        g2.setStroke(new BasicStroke(2)); 
        g.drawString("1 V", 10, yBase - yScale * 1/6 * 1);
        g.drawString("2 V", 10, yBase - yScale * 1/6 * 2);
        g.drawString("3 V", 10, yBase - yScale * 1/6 * 3);
        g.drawString("4 V", 10, yBase - yScale * 1/6 * 4);
        g.drawString("5 V", 10, yBase - yScale * 1/6 * 5);
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(2));
        g.setFont(new Font("TimesRoman", Font.PLAIN, 50));
        g.drawString("2\u03C0", xBase+510, top+70);
        
        
        // plot the graph
        g2.setColor( Color.BLUE );
        
        if(freq == 0.00){
            for(int i=0; i < getWidth(); i++ )
        {  
            x = (float) (floatxBase + i);
            y = (float) floatyBase - floatyScale * 1/6 * amplitude;
            
            g2.draw(new Line2D.Float(x, y, x, y));
            
        }
            
        
        } else{
        for(int i=0; i < getWidth()*freq; i++ )
        {       
                x = (float) (floatxBase + i/freq);
                y = (float) ( offset - Math.sin( Math.toRadians(i) ) * floatyScale * 1/6 * amplitude/2);
            
                
                g2.draw(new Line2D.Float(x, y, x, y));
               
                
        }
        
        }
        
       
    }
        
        
    }

final class TriangleDraw extends JPanel {
    
   private float amplitude;
   private float freq;
   
public TriangleDraw(float volts, float freqs) {
        
        
     setVoltageandFrequency3((float) 0.00, (float) 0.00);
          
    }
           
public void setVoltageandFrequency3(float newVoltage, float newFrequency) {
    amplitude = newVoltage;
    freq = newFrequency;
    
    if(amplitude >= 5.00){
    amplitude = (float) 5.00;
    }
    
    repaint();
} 

  
   @Override
    public void paint( Graphics g )
    {   super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setStroke(new BasicStroke(5));
            g.setFont(new Font("TimesRoman", Font.PLAIN, 25)); 
            
        int xBase   = 55;
        float floatxBase = (float) 55.00;
        int top     = 0;
        int yScale  = getHeight()- 20;
        float floatyScale = getHeight()- 20;
        int xAxis   = getWidth();

        int yBase   = top + yScale;
        float floatyBase = top + yScale;
        float offset = top + yBase - yScale * 1/6*amplitude/2;
        float x, y;
        
                // draw the axis
        g.drawLine( xBase, top, xBase, yBase );
        g.drawLine( xBase, yBase, xBase + xAxis, yBase );
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(2));
        g.drawLine( xBase+360, top, xBase+360, yBase);
        g.drawLine( xBase+720, top, xBase+720, yBase);
        
        g.setColor( Color.RED );
        g2.setStroke(new BasicStroke(2)); 
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 1, xBase + xAxis, yBase - yScale * 1/6 * 1);
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 2, xBase + xAxis, yBase - yScale * 1/6 * 2 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 3, xBase + xAxis, yBase - yScale * 1/6 * 3 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 4, xBase + xAxis, yBase - yScale * 1/6 * 4 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 5, xBase + xAxis, yBase - yScale * 1/6 * 5 );
        
        
        g2.setStroke(new BasicStroke(2)); 
        g.drawString("1 V", 10, yBase - yScale * 1/6 * 1);
        g.drawString("2 V", 10, yBase - yScale * 1/6 * 2);
        g.drawString("3 V", 10, yBase - yScale * 1/6 * 3);
        g.drawString("4 V", 10, yBase - yScale * 1/6 * 4);
        g.drawString("5 V", 10, yBase - yScale * 1/6 * 5);
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(4));
        g.setFont(new Font("TimesRoman", Font.PLAIN, 50));
        g.drawString("2\u03C0", xBase+510, top+70);
        
        
        // plot the graph
        g2.setColor( Color.BLUE );
        
        if(freq == 0.00){
            for(int i=0; i < getWidth(); i++ )
        {  
            x = (float) (floatxBase + i);
            y = (float) floatyBase - floatyScale * 1/6 * amplitude;
            
            g2.draw(new Line2D.Float(x, y, x, y));
             
        }
            
        
        } else{
        for(int i=0; i < getWidth()*freq; i++ )
        {       
                x = (float) (floatxBase + i/freq*Math.PI);
                y = (float) ( offset - Math.asin(Math.sin(Math.toRadians(Math.PI*i))) * floatyScale * 1/6 * amplitude/Math.PI);
                              
                    
                g2.draw(new Line2D.Float(x, y, x, y));
               
                
        }
        }
        
       
    }
        
        
    }



final class SquareDraw extends JPanel {
    
   private float amplitude;
   private float freq;
   
public SquareDraw(float volts, float freqs) {
        
     setVoltageandFrequency2((float) 0.00, (float) 0.00);
          
    }
           
public void setVoltageandFrequency2(float newVoltage, float newFrequency) {
    amplitude = newVoltage;
    freq = newFrequency;
    
    if(amplitude >= 5.00){
    amplitude = (float) 5.00;
    }
    
    repaint();
} 

  
   @Override
    public void paint( Graphics g )
    {   super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setStroke(new BasicStroke(5));
            g.setFont(new Font("TimesRoman", Font.PLAIN, 25)); 
            
        int xBase   = 55;
        float floatxBase = (float) 55.00;
        int top     = 0;
        int yScale  = getHeight()- 20;
        float floatyScale = getHeight()- 20;
        int xAxis   = getWidth();

        int yBase   = top + yScale;
        float floatyBase = top + yScale;
        float offset = top + yBase - yScale * 1/6*amplitude/2;
        float x, y;
        
                // draw the axis
        g.drawLine( xBase, top, xBase, yBase );
        g.drawLine( xBase, yBase, xBase + xAxis, yBase );
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(2));
        g.drawLine( xBase+360, top, xBase+360, yBase);
        g.drawLine( xBase+720, top, xBase+720, yBase);
        
        g.setColor( Color.RED );
        g2.setStroke(new BasicStroke(2)); 
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 1, xBase + xAxis, yBase - yScale * 1/6 * 1);
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 2, xBase + xAxis, yBase - yScale * 1/6 * 2 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 3, xBase + xAxis, yBase - yScale * 1/6 * 3 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 4, xBase + xAxis, yBase - yScale * 1/6 * 4 );
        
        g.drawLine( xBase, yBase - yScale * 1/6 * 5, xBase + xAxis, yBase - yScale * 1/6 * 5 );
        
        
        g2.setStroke(new BasicStroke(2)); 
        g.drawString("1 V", 10, yBase - yScale * 1/6 * 1);
        g.drawString("2 V", 10, yBase - yScale * 1/6 * 2);
        g.drawString("3 V", 10, yBase - yScale * 1/6 * 3);
        g.drawString("4 V", 10, yBase - yScale * 1/6 * 4);
        g.drawString("5 V", 10, yBase - yScale * 1/6 * 5);
        
        g.setColor( Color.WHITE );
        g2.setStroke(new BasicStroke(4));
        g.setFont(new Font("TimesRoman", Font.PLAIN, 50));
        g.drawString("2\u03C0", xBase+510, top+70);
        
        
        // plot the graph
        g2.setColor( Color.BLUE );
        
        if(freq == 0.00){
            for(int i=0; i < getWidth(); i++ )
        {  
            x = (float) (floatxBase + i);
            y = (float) floatyBase - floatyScale * 1/6 * amplitude;
           
            g2.draw(new Line2D.Float(x, y, x, y));
            
        }
            
        
        } else{
        for(int i=0; i < getWidth()*freq; i++ )
        {       
                x = (float) (floatxBase + i/freq*2*Math.PI);
                y = (float) ( offset - Math.signum(Math.sin(Math.toRadians(2*Math.PI*i))) * floatyScale * 1/6 * amplitude/2);               
                

                g2.draw(new Line2D.Float(x, y, x, y));
                
        }
        }
        
       
    }
        
        
    }


