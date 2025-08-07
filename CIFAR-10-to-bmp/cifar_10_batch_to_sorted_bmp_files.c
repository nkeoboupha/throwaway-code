#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>

char * getSampleClassFromByte(uint8_t categoryNumber){
	switch(categoryNumber){
		case 0: return "airplane";
		case 1: return "automobile";
		case 2: return "bird";
		case 3: return "cat";
		case 4: return "deer";
		case 5: return "dog";
		case 6: return "frog";
		case 7: return "horse";
		case 8: return "ship";
		case 9: return "truck";
	}
}

int main(){

	//List of CIFAR-10 batches to process
	char *pathsToCifarBatches[] =
		{
			"data_batch_1.bin",
			"data_batch_2.bin",
			"data_batch_3.bin",
			"data_batch_4.bin",
			"data_batch_5.bin",
			"test_batch.bin"
		};

	//Read prepared BMP header into memory
	uint8_t bmpFileHeader[54];
	FILE *readPtr;
	readPtr = fopen("bmp_header.bin", "rb");
	fread(bmpFileHeader, sizeof(bmpFileHeader), 1, readPtr);
	fclose(readPtr);

	uint16_t numSamplesPerBatch = 10000;
	uint16_t totalSampleNum = 0;

	//For each batch, write each binary string
	//as a BMP file in the correct directory
	for(
		uint8_t batchNum = 0;
		batchNum < sizeof(pathsToCifarBatches) / sizeof(char *);
		batchNum++
	   ){
		readPtr = fopen(pathsToCifarBatches[batchNum], "rb");
		uint8_t bmpPixelMap[3072];
		for(
			uint16_t sampleNum = 0;
			sampleNum < numSamplesPerBatch;
			sampleNum++
		   ){

			//Find Sample Class
			uint8_t classByte;
			char *sampleClass;
			fread(&classByte, sizeof(classByte), 1, readPtr);
			sampleClass = getSampleClassFromByte(classByte);
			
			//Read image data by color
			uint8_t redValues[1024];
			uint8_t greenValues[1024];
			uint8_t blueValues[1024];
			fread(
				redValues,
				sizeof(redValues),
				1,
				readPtr
			     );
			fread(
				greenValues,
				sizeof(greenValues),
				1,
				readPtr
			     );
			fread(
				blueValues,
				sizeof(blueValues),
				1,
				readPtr
			     );

			for(uint16_t pixNum = 0; pixNum < 1024; pixNum++){
				bmpPixelMap[pixNum * 3] = 
					redValues[pixNum];
				bmpPixelMap[(pixNum * 3) + 1] = 
					greenValues[pixNum];
				bmpPixelMap[(pixNum * 3) + 2] = 
					blueValues[pixNum];
			}

			char *pathToBMP = malloc(21);
			
			sprintf(
				pathToBMP,
				"%s/%d.bmp",
				sampleClass,
				totalSampleNum
			       );

			//Write BMP file
			FILE *writePtr = fopen(pathToBMP, "wb");

			fwrite(
				bmpFileHeader, 
				sizeof(bmpFileHeader), 
				1, 
				writePtr);

			fwrite(bmpPixelMap, sizeof(bmpPixelMap), 1, writePtr);
			fclose(writePtr);

			totalSampleNum++;
		}
		fclose(readPtr);
	}
	return 0;
}
