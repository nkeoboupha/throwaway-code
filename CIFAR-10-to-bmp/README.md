# CIFAR-10 to BMP

I developed this program that can be used to convert the CIFAR-10 dataset into sorted BMP files.
Instructions follow.

1. At the following link, download the data at the link titled **CIFAR-10 binary version (suitable for C programs)**

  [https://www.cs.toronto.edu/~kriz/cifar.html](https://www.cs.toronto.edu/~kriz/cifar.html)

2. Extract the ZIP file's contents to a directory

3. Change your current working directory to the one that contains the downloaded file's contents and run the following to create the appropriate subdirectories:

   `mkdir airplane automobile bird cat deer dog frog horse ship truck`

4. Compile the provided C file and run it. An example follows.

  `gcc -o cifar_10_batch_to_sorted_bmp_files cifar_10_batch_to_sorted_bmp_files.c`
  
  `./cifar_10_batch_to_sorted_bmp_files`

After this, the 10 directories created in step 3 should contain BMP files with content appropriate for the directory's name.
