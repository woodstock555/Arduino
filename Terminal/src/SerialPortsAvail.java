import com.fazecast.jSerialComm.*;

import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class SerialPortsAvail {
    SerialPort aPort;

    /** Buffered input stream from the port */
    private InputStream input;

    /** The output stream to the port */
    private OutputStream output;

    /** Milliseconds to block while waiting for port open */
    private static final int TIME_OUT = 2000;

    /** Default bits per second for COM port. */
    private static final int BAUD_RATE = 9600;
    private static final int DATA_BITS = 8;
    private static final int STOP_BITS = SerialPort.ONE_STOP_BIT;
    private static final int PARITY   = SerialPort.NO_PARITY;


    public static void main (String[] Args) throws InterruptedException {
        SerialPortsAvail mainClass = new SerialPortsAvail();
        mainClass.initialize();
        mainClass.start();
    }

    public SerialPort getArduinoPort()
    {
        SerialPort arduinoPort=null;
        SerialPort [] AvailablePorts = SerialPort.getCommPorts();
        for(SerialPort S : AvailablePorts) {
            if (S.getDescriptivePortName().indexOf("CH340")>=0) {
                // нашли порт с ардуиной
                arduinoPort = S;
                break;
            }
        }
        return arduinoPort;
    }

    public void initialize() throws InterruptedException {
        aPort = getArduinoPort();
        if (aPort == null) {
            System.out.println("Arduino Port is not find");
            System.exit(0);
        }
        System.out.println("Arduino find on port: " + aPort.getSystemPortName());

        aPort.setComPortParameters(BAUD_RATE,DATA_BITS,STOP_BITS,PARITY); //Sets all serial port parameters at one time
        //aPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 1000, 0); //Set Read Time outs
        //.setComPortTimeouts(TIMEOUT_Mode, READ_TIMEOUT_milliSec, WRITE_TIMEOUT_milliSec);

        //Display the Serial Port parameters
        System.out.println("\n Selected Port               = " + aPort.getSystemPortName());
        System.out.println(" Selected Baud rate          = " + aPort.getBaudRate());
        System.out.println(" Selected Number of DataBits = " + aPort.getNumDataBits());
        System.out.println(" Selected Number of StopBits = " + aPort.getNumStopBits());
        System.out.println(" Selected Parity             = " + aPort.getParity());

        aPort.openPort();    //open the port
        System.out.println(" Watch Arduino for Reset ...");
        Thread.sleep(5000);//Delay added to so you can see the Arduino getting Resetted


        //Arduino May get reset
        if (!aPort.isOpen()) {
            System.out.println(" Port "+aPort.getSystemPortName()+" not open ");
            System.exit(0);
        }
        System.out.println("\n" + aPort.getSystemPortName() + "  is Open ");

        aPort.addDataListener(new SerialPortDataListener() {

            @Override
            public void serialEvent(SerialPortEvent event) {
                int size = event.getSerialPort().bytesAvailable();
                byte[] buffer = new byte[size];
                event.getSerialPort().readBytes(buffer, size);
                for(byte b:buffer)
                    System.out.print((char)b);
            }

            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
            }
        });

    }


        public void start() {
            byte[] readBuffer = new byte[100];
            //byte[] writeBuffer = new byte[100];
            String s;
            Scanner reader = new Scanner(System.in);
            aPort.flushIOBuffers();
            try
            {
                while (true)
                {
                    s = reader.nextLine(); // Считали строку с клавиатуры
                    if (s.startsWith("exit")) {
                        break;
                    }

                    if (s.length()>0) {
                        byte[] writeBuffer = s.getBytes(StandardCharsets.UTF_8); // преобразовали строку в массив
                        int bytesTxed  = 0;
                        bytesTxed  = aPort.writeBytes(writeBuffer,writeBuffer.length); // отправили в порт
                        System.out.println("Write " + bytesTxed + " bytes");
                    }
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
            finally {
                reader.close();
            }

        }

    public synchronized void close() {
        if (aPort != null) {
            aPort.removeDataListener();
            aPort.closePort();
        }
    }


    //int numRead = aPort.readBytes(readBuffer, readBuffer.length);
//                    System.out.print("Read " + numRead + " bytes -");
    //System.out.println(readBuffer);
//    readBuffer[35]=0;
//    String S = new String(readBuffer, "UTF-8"); //convert bytes to String
 //                   System.out.println("Received -> "+ S);

 /*       try
        {
            byte[] WriteByte = new byte[1];
            WriteByte[0] = 65; //send A
            int bytesTxed  = 0;
            bytesTxed  = aPort.writeBytes(WriteByte,1);
            System.out.print(" Bytes Transmitted -> " + bytesTxed );
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }*/
    }//end of main()


