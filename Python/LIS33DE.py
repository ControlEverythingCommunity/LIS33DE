# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LIS33DE
# This code is designed to work with the LIS33DE_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Accelorometer?sku=LIS33DE_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# LIS33DE address, 0x1C(28)
# Select control register1, 0x20(32)
#		0x47(71)	X, Y, Z-Axis enabled, Active mode
bus.write_byte_data(0x1C, 0x20, 0x47)

time.sleep(0.5)

# LIS33DE address, 0x1C(28)
# Read data back from 0x29(41), 1 byte
# X-Axis Accl
data = bus.read_byte_data(0x1C, 0x29)

# Convert the data
xAccl = data
if xAccl > 127 :
	xAccl -= 256

# LIS33DE address, 0x1C(28)
# Read data back from 0x2B(43), 1 byte
# Y-Axis Accl
data = bus.read_byte_data(0x1C, 0x2B)

# Convert the data
yAccl = data
if yAccl > 127 :
	yAccl -= 256

# LIS33DE address, 0x1C(28)
# Read data back from 0x2D(45), 1 byte
# Z-Axis Accl
data = bus.read_byte_data(0x1C, 0x2D)

# Convert the data
zAccl = data
if zAccl > 127 :
	zAccl -= 256

# Output data to screen
print "Acceleration in X-Axis : %d" %xAccl
print "Acceleration in Y-Axis : %d" %yAccl
print "Acceleration in Z-Axis : %d" %zAccl
