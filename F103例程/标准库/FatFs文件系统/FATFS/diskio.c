/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2009   
   低端的磁盘I/O模块骨架Petit FatFs（C），2009   */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "stm32f10x.h"
#include "spi.h"

#include "sdio_sdcard.h"


u8 dest_tbuf[512];

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive      
   初始化磁盘驱动器    
   返回0 为成功  返回1 为失败                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	DSTATUS stat;

	// Put your code here	   把你的代码写在这里
	 stat=TFsdio_Init();	  //初始化SD卡 并将返回值给stat


	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector
   读扇区                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* dest,			/* Pointer to the destination object 存放数据的地址*/
	DWORD sector,		/* Sector number (LBA)  要读的扇区数*/
	WORD sofs,			/* Offset in the sector 扇区偏移值*/
	WORD count			/* Byte count (bit15:destination) 读出的数据个数*/
)
{
	DRESULT res;

    // Put your code here	 把你的代码写在这里

	u16 i;
	u8 r1;
    res=RES_ERROR;

	
	r1=SD_ReadDisk(dest_tbuf,sector,1);//直接读取一个扇区所有数据

	if(r1==0)//指令发送成功
	 {
//			 if(sofs)  //如果有偏移量
//			 {		  
//			 for(i=0;i<sofs;i++)Moni_SPI_ReadWriteByte(0xff);  //将偏移值循环掉
			 			      
			 for(i=0;i<count;i++) *(dest++)=dest_tbuf[sofs++];  //接收要读出来的数据		   
//			 }
//			 else   //没有偏移值 即偏移值为0
//			 {
//			   //要读的数据个数复制给tmp
//			   for(i=0;i<count;i++) *(dest++)=Moni_SPI_ReadWriteByte(0xff);  //接收要读出来的数据
//			 }
//			 tmp=512-sofs-count;  //剩余为读数据   扇区数-偏移值-读取数据
//			 for(i=0;i<tmp;i++)Moni_SPI_ReadWriteByte(0xff);// 将剩余数据循环掉 以免对其他函数有干扰
//	

	 }
	else  return res;	 //读指令失败

	res=RES_OK;	   //数据读取成功
	return res;


//	u16 tmp,i;
//	u8 r1;
//    res=RES_ERROR;
//
//	r1=SD_SendCmd(CMD17,sector<<9,0X01);//读命令
//	
//	if(r1==0)//指令发送成功
//		{
//		    while(Moni_SPI_ReadWriteByte(0xff)!=0xfe);  //等待接收数据
//			 if(sofs)  //如果有偏移量
//			 {		  
//			 for(i=0;i<sofs;i++)Moni_SPI_ReadWriteByte(0xff);  //将偏移值循环掉
//			 			      
//			 for(i=0;i<count;i++) *(dest++)=Moni_SPI_ReadWriteByte(0xff);  //接收要读出来的数据		   
//			 }
//			 else   //没有偏移值 即偏移值为0
//			 {
//			   //要读的数据个数复制给tmp
//			   for(i=0;i<count;i++) *(dest++)=Moni_SPI_ReadWriteByte(0xff);  //接收要读出来的数据
//			 }
//			 tmp=512-sofs-count;  //剩余为读数据   扇区数-偏移值-读取数据
//			 for(i=0;i<tmp;i++)Moni_SPI_ReadWriteByte(0xff);// 将剩余数据循环掉 以免对其他函数有干扰
//
//
//			//下面是2个伪CRC（dummy CRC）
//			  Moni_SPI_ReadWriteByte(0xff); 
//              Moni_SPI_ReadWriteByte(0xff); 		   
//		}
//	  else  return res;	 //读指令失败
//
//	SD_DisSelect();//取消片选
//	res=RES_OK;	   //数据读取成功
//	return res;

//	u8 res1=0; 
//    if (!count)return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
////	switch(pdrv)
////	{
////		case SD_CARD://SD卡
//			res1=SD_ReadDisk(dest,sector,count);	 
//			while(res1)//读出错
//			{
//				SD_Init();	//重新初始化SD卡
//				res1=SD_ReadDisk(dest,sector,count);	
//				//printf("sd rd error:%d\r\n",res);
//			}
////			break;
////		case EX_FLASH://外部flash
////			for(;count>0;count--)
////			{
////				W25QXX_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
////				sector++;
////				buff+=FLASH_SECTOR_SIZE;
////			}
////			res=0;
////			break;
////		default:
////			res=1; 
////	}
//   //处理返回值，将SPI_SD_driver.c的返回值转成ff.c的返回值
//    if(res1==0x00)return RES_OK;	 
//    else return RES_ERROR;	 


}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector 
   写扇区                                                 
   
   disk_writep：写部分扇区，里面只有两个参数，
   写入的数据地址* buff与第几个扇区sc两个数据。

   但在编写这个程序的时候要注意，由于FatFs内部调用函数的需要，必须按照以下的顺序来，
   当 buff 指向一个空指针，当sc 不为0 时，则表示对这个扇区的写操作进行初始化；
   当sc 为0 时，则表示对这个扇区的写操作进行结束操作；
   当 buff 指向一个内存缓冲区，则是进行正常的读写。*/
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation 指针的数据被写入，空：启动/完成写操作*/
	DWORD sc		/* Sector number (LBA) or Number of bytes to send 扇区数（LBA）或要发送的字节数*/
)
{
//	DRESULT res;

//	 u8 r1;
//	 u16 t;
//	 u32 m;
//	res = RES_ERROR;
//
//	if (!buff) {						  //如果指向空指针
//		if (sc) {						  //sc不为0 进行写操作初始化
//
//			// Initiate write process		  开始写过程
//				  r1=SD_SendCmd(CMD24,sc<<9,0X01);
//				  if(r1!=0) return res;	 //应答不正确
//			      do
//		          {
//			        if(Moni_SPI_ReadWriteByte(0XFF)==0XFF)break;//OK	  放空数据等待SD卡准备好
//			          m++;		  	
//		           }while(m<0XFFFFFF);//等待 
//	
//		          Moni_SPI_ReadWriteByte(0XFE);		  //发开启符
//				  res=RES_OK;
//
//		} else {							 //sc为0  表示写操作结束
//
//			// Finalize write process		  最后写过程
//
//		           	//下面是2个伪CRC（dummy CRC）
//				 	Moni_SPI_ReadWriteByte(0xFF);
//					Moni_SPI_ReadWriteByte(0xFF);
//					r1 = Moni_SPI_ReadWriteByte(0xFF);
//		
//					if( (r1&0x1f) != 0x05)//等待SD卡应答
//					{
//						SD_DisSelect();
//						return res;
//					}
//					//等待操作完
//					while(!Moni_SPI_ReadWriteByte(0xFF));
//		
//					SD_DisSelect();	
//					res = RES_OK;
//
//
//
//
//		}
//	} else {
//
//		// Send data to the disk			  发送数据到磁盘
//			for(t=0;t<512;t++)Moni_SPI_ReadWriteByte(*buff++);//提高速度,减少函数传参时间
//		    res = RES_OK;
//
//
//	}
//
//	return res;


	u8 res1=0;  
    if (!buff)return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
//	switch(pdrv)
//	{
//		case SD_CARD://SD卡
			res1=SD_WriteDisk((u8*)buff,sc,1);
			while(res1)//写出错
			{
				TFsdio_Init();	//重新初始化SD卡
				res1=SD_WriteDisk((u8*)buff,sc,1);	
				//printf("sd wr error:%d\r\n",res);
			}
//			break;
//		case EX_FLASH://外部flash
//			for(;count>0;count--)
//			{										    
//				W25QXX_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
//				sector++;
//				buff+=FLASH_SECTOR_SIZE;
//			}
//			res=0;
//			break;
//		default:
//			res=1; 
//	}
    //处理返回值，将SPI_SD_driver.c的返回值转成ff.c的返回值
    if(res1 == 0x00)return RES_OK;	 
    else return RES_ERROR;	








}
