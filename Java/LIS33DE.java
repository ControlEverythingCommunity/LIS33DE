// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LIS33DE
// This code is designed to work with the LIS33DE_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LIS33DE_I2CS#tabs-0-product_tabset-2


import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LIS33DE
{
	
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus=I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LIS33DE I2C address is 0x1C(28)
		I2CDevice device = Bus.getDevice(0x1C);

		// Select control register1
		// X ,Y and Z-Axis enabled, active mode
		device.write(0x20, (byte)0x47);
		Thread.sleep(500);

		// Read 3 bytes of data
		// xAccl, yAccl, zAccl
		byte[] data = new byte[3];
		data[0] = (byte)device.read(0x29);
		data[1] = (byte)device.read(0x2B);
		data[2] = (byte)device.read(0x2D);
		
		// Convert the data
		int xAccl = data[0] & 0xFF;
		if(xAccl > 127)
		{
			xAccl -= 256;
		}

		int yAccl = data[1] & 0xFF;
		if(yAccl > 127)
		{
			yAccl -= 256;
		}

		int zAccl = data[2] & 0xFF;
		if(zAccl > 127)
		{
			zAccl -= 256;
		}

		// Output data to screen
		System.out.printf("Acceleration in X-Axis : %d %n", xAccl);
		System.out.printf("Acceleration in Y-Axis : %d %n", yAccl);
		System.out.printf("Acceleration in Z-Axis : %d %n", zAccl);
	} 
}
