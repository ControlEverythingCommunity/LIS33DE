// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LIS33DE
// This code is designed to work with the LIS33DE_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LIS33DE_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LIS33DE I2C address is 0x1C(28)
	ioctl(file, I2C_SLAVE, 0x1C);

	// Select control register1(0x20)
	// X ,Y and Z-Axis enabled, active mode(0x47)
	char config[2] = {0};
	config[0] = 0x20;
	config[1] = 0x47;
	write(file, config, 2);
	sleep(1);

	// Read 3 bytes of data
	// Read xAccl data from register(0x29)
	char reg[1] = {0x29};
	write(file, reg, 1);
	char data[1] = {0};
	if(read(file, data, 1) != 1)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		int xAccl = data[0];
		if(xAccl > 127)
		{
			xAccl -= 256;
		}

		// Read yAccl data from register(0x2B)
		reg[0] = 0x2B;
		write(file, reg, 1);
		read(file, data, 1);
		int yAccl = data[0];
		if(yAccl > 127)
		{
			yAccl -= 256;
		}

		// Read zAccl data from register(0x2D)
		reg[0] = 0x2D;
		write(file, reg, 1);
		read(file, data, 1);
		int zAccl = data[0];
		if(zAccl > 127)
		{
			zAccl -= 256;
		}

		// Output data to screen
		printf("Acceleration in X-Axis : %d \n", xAccl);
		printf("Acceleration in Y-Axis : %d \n", yAccl);
		printf("Acceleration in Z-Axis : %d \n", zAccl);
	}
}
