/*
 * @Date         : 2022-01-19 16:29:37
 * @LastEditors  : liu wei
 * @LastEditTime : 2022-01-24 22:29:29
 * @FilePath     : \LED\Core\Inc\mpu6050.h
 * @Github       : https://github.com/Blackerrr
 * @Coding       : utf-8
 */

#ifndef __MPU6050_H
#define __MPU6050_H
#include "main.h"
#include "math.h"
#include "stdlib.h"

/********************************* MPUIIC ***************************************/

#define MPU_SDA_IN()              \
    {                             \
        GPIOC->CRL &= 0XFFFFFF0F; \
        GPIOC->CRL |= 8 << 4;     \
    }
#define MPU_SDA_OUT()             \
    {                             \
        GPIOC->CRL &= 0XFFFFFF0F; \
        GPIOC->CRL |= 3 << 4;     \
    }

#define MPU_IIC_SCL PCout(0) //SCL
#define MPU_IIC_SDA PCout(1) //SDA
#define MPU_READ_SDA PCin(1) // input SDA

//IIC All function operations
void MPU_IIC_Delay(void);                // MPU IIC delay function
void MPU_IIC_Init(void);                 // Initialize the IO port of the IIC
void MPU_IIC_Start(void);                // Send IIC start signal
void MPU_IIC_Stop(void);                 // send IIC stop signal
void MPU_IIC_Send_Byte(u8 txd);          // IIC sends a byte
u8 MPU_IIC_Read_Byte(unsigned char ack); // IIC reads a byte
u8 MPU_IIC_Wait_Ack(void);               // IIC waits for ACK signal
void MPU_IIC_Ack(void);                  // IIC sends ACK signal
void MPU_IIC_NAck(void);                 // IIC does not send ACK signal

void IMPU_IC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr, u8 addr);

/********************************* MPU6050 ***************************************/

// MPU6050 AD0 control pin
// #define MPU_AD0_CTRL PAout(15) // Control the AD0 level, thereby controlling the MPU address

//#define MPU_ACCEL_OFFS_REG		0X06	// The accel_offs register, which can read the version number, is not mentioned in the register manual
//#define MPU_PROD_ID_REG			0X0C	// prod id register, not mentioned in the register manual
#define MPU_SELF_TESTX_REG 0X0D   // Self-Test Register X
#define MPU_SELF_TESTY_REG 0X0E   // Self-Test Register Y
#define MPU_SELF_TESTZ_REG 0X0F   // Self-Test Register Z
#define MPU_SELF_TESTA_REG 0X10   // Self-Test Register A
#define MPU_SAMPLE_RATE_REG 0X19  // Sampling frequency divider
#define MPU_CFG_REG 0X1A          // configuration register
#define MPU_GYRO_CFG_REG 0X1B     // Gyroscope Configuration Register
#define MPU_ACCEL_CFG_REG 0X1C    // Accelerometer Configuration Register
#define MPU_MOTION_DET_REG 0X1F   // Motion Detection Threshold Setting Register
#define MPU_FIFO_EN_REG 0X23      // FIFO enable register
#define MPU_I2CMST_CTRL_REG 0X24  // IIC master control register
#define MPU_I2CSLV0_ADDR_REG 0X25 // IIC Slave 0 Device Address Register
#define MPU_I2CSLV0_REG 0X26      // IIC Slave 0 Data Address Register
#define MPU_I2CSLV0_CTRL_REG 0X27 // IIC slave 0 control register
#define MPU_I2CSLV1_ADDR_REG 0X28 // IIC Slave 1 Device Address Register
#define MPU_I2CSLV1_REG 0X29      // IIC Slave 1 Data Address Register
#define MPU_I2CSLV1_CTRL_REG 0X2A // IIC slave 1 control register
#define MPU_I2CSLV2_ADDR_REG 0X2B // IIC Slave 2 Device Address Register
#define MPU_I2CSLV2_REG 0X2C      // IIC Slave 2 Data Address Register
#define MPU_I2CSLV2_CTRL_REG 0X2D // IIC slave 2 control register
#define MPU_I2CSLV3_ADDR_REG 0X2E // IIC Slave 3 Device Address Register
#define MPU_I2CSLV3_REG 0X2F      // IIC Slave 3 Data Address Register
#define MPU_I2CSLV3_CTRL_REG 0X30 // IIC slave 3 control register
#define MPU_I2CSLV4_ADDR_REG 0X31 // IIC Slave 4 Device Address Register
#define MPU_I2CSLV4_REG 0X32      // IIC Slave 4 Data Address Register
#define MPU_I2CSLV4_DO_REG 0X33   // IIC slave 4 write data register
#define MPU_I2CSLV4_CTRL_REG 0X34 // IIC slave 4 control register
#define MPU_I2CSLV4_DI_REG 0X35   // IIC slave 4 read data register

#define MPU_I2CMST_STA_REG 0X36 // IIC Master Status register
#define MPU_INTBP_CFG_REG 0X37  // Interrupt/Bypass Setting Register
#define MPU_INT_EN_REG 0X38     // Interrupt Enable Register
#define MPU_INT_STA_REG 0X3A    // Interrupt Status Register

#define MPU_ACCEL_XOUTH_REG 0X3B // Acceleration value, X-axis high 8-bit register
#define MPU_ACCEL_XOUTL_REG 0X3C // Acceleration value, X-axis low 8-bit register
#define MPU_ACCEL_YOUTH_REG 0X3D // Acceleration value, Y-axis high 8-bit register
#define MPU_ACCEL_YOUTL_REG 0X3E // Acceleration value, Y-axis low 8-bit register
#define MPU_ACCEL_ZOUTH_REG 0X3F // Acceleration value, Z-axis high 8-bit register
#define MPU_ACCEL_ZOUTL_REG 0X40 // Acceleration value, Z-axis low 8-bit register

#define MPU_TEMP_OUTH_REG 0X41 // temperature value, high 8-big register
#define MPU_TEMP_OUTL_REG 0X42 // temperature value, low 8-bit register

#define MPU_GYRO_XOUTH_REG 0X43 // Gyro value, X-axis high 8-bit register
#define MPU_GYRO_XOUTL_REG 0X44 // Gyro value, X-axis low 8-bit register
#define MPU_GYRO_YOUTH_REG 0X45 // Gyro value, Y-axis high 8-bit register
#define MPU_GYRO_YOUTL_REG 0X46 // Gyro value, Y-axis low 8-bit register
#define MPU_GYRO_ZOUTH_REG 0X47 // Gyro value, Z-axis high 8-bit register
#define MPU_GYRO_ZOUTL_REG 0X48 // Gyro value, Z-axis low 8-bit register

#define MPU_I2CSLV0_DO_REG 0X63 // IIC slave 0 data register
#define MPU_I2CSLV1_DO_REG 0X64 // IIC slave 1 data register
#define MPU_I2CSLV2_DO_REG 0X65 // IIC slave 2 data register
#define MPU_I2CSLV3_DO_REG 0X66 // IIC slave 3 data register

#define MPU_I2CMST_DELAY_REG 0X67 // IIC Master Delay Management Register
#define MPU_SIGPATH_RST_REG 0X68  // Signal Channel Reset Register
#define MPU_MDETECT_CTRL_REG 0X69 // Motion Detection Control Register
#define MPU_USER_CTRL_REG 0X6A    // User Control Register 
#define MPU_PWR_MGMT1_REG 0X6B    // Power Management Register 1
#define MPU_PWR_MGMT2_REG 0X6C    // Power Management Register 2
#define MPU_FIFO_CNTH_REG 0X72    // FIFO count register upper eight bits
#define MPU_FIFO_CNTL_REG 0X73    // FIFO count register lower eight bits
#define MPU_FIFO_RW_REG 0X74      // FIFO read and write registers
#define MPU_DEVICE_ID_REG 0X75    // Device ID Register

// If the AD0 pin (9 pin) is grounded, the IIC address is 0X68 (does not include the lowest(least) bit).
// If connected to V3.3, the IIC address is 0X69 (not including the lowest bit).
#define MPU_ADDR 0X68

// Because the module AD0 is connected to GND by default, it is 0XD1 and 0XD0 
// if it is connected to VCC, it is 0XD3 and 0XD2) after switching to the read-write address.
// #define MPU_READ    0XD1
// #define MPU_WRITE   0XD0



// #define G 9.7947  // Hefei gravity acceleration
#define G 9.7914    // Chongqing gravity acceleration
#define halfT 0.01f // Half of the sampling time, in seconds

typedef struct
{
    double Roll;
    double Pitch;
    double Yaw;
    double Gx;
    double Gy;
    double Gz;
    double Ax;
    double Ay;
    double Az;
} MPU6050_InitDefine;

typedef struct
{
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx_e;
    int16_t gy_e;
    int16_t gz_e;
    int16_t ax_e;
    int16_t ay_e;
    int16_t az_e;
} MPU6050_Original;

extern MPU6050_InitDefine mpu6050;
extern MPU6050_Original mpu6050_original;
extern float q0, q1, q2, q3;      //��Ԫ��
extern float exInt, eyInt, ezInt; //������������ۼƻ���
extern unsigned int a_LSB;        //aԭʼֵϵ��
extern float g_LSB;               //gԭʼֵϵ��

u8 MPU_Init(void);                                  // Initialize MPU6050
u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf); // IIC continuous write
u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf);  // IIC continuous read
u8 MPU_Write_Byte(u8 reg, u8 data);                 // IIC writes a byte
u8 MPU_Read_Byte(u8 reg);                           // IIC reads a byte

u8 MPU_Set_Gyro_Fsr(u8 fsr);
u8 MPU_Set_Accel_Fsr(u8 fsr);
u8 MPU_Set_LPF(u16 lpf);
u8 MPU_Set_Rate(u16 rate);
u8 MPU_Set_Fifo(u8 sens);

short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(void);
u8 MPU_Get_Accelerometer(void);


void MPU_Update(void);
float Kalman_Filter_Roll(void);
float Kalman_Filter_Pitch(void);
float Kalman_Filter_Yaw(void);

#endif
