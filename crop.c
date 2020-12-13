#include <stdio.h>

int main()
{
FILE *fIn = fopen("/home/anwesha/Desktop/project.bmp","r"); //Input File name
FILE *fOut = fopen("crop_image.bmp","w+");     //Output File name

int i,j,t,b,l,r;
unsigned char byte[54],colorTable[1024];

if(fIn==NULL) // check if the input file has not been opened succesfully.
{
printf("File does not exist.\n");
}

for(i=0;i<54;i++) //read the 54 byte header from fIn
{
byte[i] = getc(fIn);
}

fwrite(byte,sizeof(unsigned char),54,fOut); //write the header back

// extract image height, width and bitDepth from imageHeader
int height = *(int*)&byte[18];
int width = *(int*)&byte[22];
int bitDepth = *(int*)&byte[28];

printf("width: %d\n",width);
printf("height: %d\n",height );

int size = height*width; //calculate image size

if(bitDepth <= 8) //if ColorTable present, extract it.
{
fread(colorTable,sizeof(unsigned char),1024,fIn);
fwrite(colorTable,sizeof(unsigned char),1024,fOut);
}

unsigned char buffer[width][height];

fread(buffer,sizeof(unsigned char),size,fIn); //read the image data
printf("enter top , bottom ,left and right width");
scanf("%d",&t);
scanf("%d",&b);
scanf("%d",&l);
scanf("%d",&r);

for(i=0;i<width;i++)
{
   for(j=0;j<t;j++)
   {
            buffer[i][j]=0;        
   }
}
for(i=0;i<width;i++)
{
   for(j=height-1;j>height-1-b;j--)
   {
            buffer[i][j]=0;        
   }
}
for(i=width-1;i>width-1-r;i--)
{
   for(j=0;j<height;j++)
   {
            buffer[i][j]=0;        
   }
}
for(i=0;i<l;i++)
{
   for(j=0;j<height;j++)
   {
            buffer[i][j]=0;        
   }
}




fwrite(buffer,sizeof(unsigned char),size,fOut); //write back to the output image

fclose(fIn);
fclose(fOut);

return 0;
}
