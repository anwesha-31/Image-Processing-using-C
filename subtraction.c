#include <stdio.h>

int main(){

FILE *fIn1 = fopen("/home/anwesha/Desktop/addition.bmp","rb"); //Input File name
FILE *fIn2 = fopen("/home/anwesha/Desktop/jerry.bmp","rb");
FILE *fOut = fopen("subtraction.bmp","wb");            //Output File name

int i,j;
unsigned char byte1[54]; //to get the image header
unsigned char colorTable1[1024]; //to get the colortable

unsigned char byte2[54]; //to get the image header
unsigned char colorTable2[1024];

if(fIn1==NULL) // check if the input file has not been opened succesfully.
{
printf("File does not exist.\n");
}

for(i=0;i<54;i++) //read the 54 byte header from fIn
{
byte1[i]=getc(fIn1);
}
for(i=0;i<54;i++) //read the 54 byte header from fIn
{
byte2[i]=getc(fIn2);
}

fwrite(byte1,sizeof(unsigned char),54,fOut); //write the header back

// extract image height, width and bitDepth from imageHeader
int height = *(int*)&byte1[18];
int width = *(int*)&byte1[22];
int bitDepth = *(int*)&byte1[28];

printf("width: %d\n",width);
printf("height: %d\n",height );

int size=height*width; //calculate image size

if(bitDepth<=8) //if ColorTable present, extract it.
{
fread(colorTable1,sizeof(unsigned char),1024,fIn1);
fread(colorTable2,sizeof(unsigned char),1024,fIn2);
fwrite(colorTable1,sizeof(unsigned char),1024,fOut);
}
  unsigned char pixel1[width][height][3];
  unsigned char pixel2[width][height][3];

	for(i=0;i<width;i++)
	{
        for(j=0;j<height;j++)
            {
            pixel1[i][j][2]=getc(fIn1);									//blue
            pixel1[i][j][1]=getc(fIn1);									//green
            pixel1[i][j][0]=getc(fIn1);                                  //red

            pixel2[i][j][2]=getc(fIn2);									//blue
            pixel2[i][j][1]=getc(fIn2);									//green
            pixel2[i][j][0]=getc(fIn2);                                     //red

            pixel1[i][j][2]=pixel1[i][j][2]-pixel2[i][j][2];
            pixel1[i][j][1]=pixel1[i][j][1]-pixel2[i][j][1];
            pixel1[i][j][0]=pixel1[i][j][0]-pixel2[i][j][0];
            }
	}


   // writing back the pixels
    for(i=0;i<height;i++)
    {
        for(j=0;j<height;j++)
        {

            putc(pixel1[i][j][2],fOut);
            putc(pixel1[i][j][1],fOut);
            putc(pixel1[i][j][0],fOut);
        }

    }
/*unsigned char buffer1[size]; //to store the image data
    unsigned char buffer2[size];
    unsigned char out_buffer[size];


fread(buffer1,sizeof(unsigned char),size,fIn1); //read image data
    fread(buffer2,sizeof(unsigned char),size,fIn2);

for(i=0;i<size;i++) //store 0(black) and 255(white) values to buffer
{
out_buffer[i] = buffer1[i] + buffer2[i] ;
}

fwrite(out_buffer,sizeof(unsigned char),size,fOut); //write back to the output image*/

fclose(fIn1);
fclose(fIn2);
fclose(fOut);

return 0;
}