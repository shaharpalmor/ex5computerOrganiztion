

#define  min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define  max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define multBy9(X)    (((X) << 3) + (X))
#define multByMinus1(X)    ((X)*(-1))
#define calcValue(x, y, z)    (((x)*(z))+(y))

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;


void doConvolution1(Image *image, int kernelScale) {
    int mnPixel = m * n * sizeof(pixel);
    //creating a pointer to the image data in oreder to save one allocation and one free at the end of the function.
    pixel *pixelImage = (pixel *) image->data;
    pixel *backupOrg = malloc(mnPixel);
    memcpy(backupOrg, pixelImage, mnPixel);

    int row, col, i, j, ii, jj, currRow, currCol;
    pixel current_pixel;
    pixel current_pixel1;

    int dimMinus1 = m - 1;


    for (i = 1; i < dimMinus1; ++i) {
        int maximumi = i - 1;
        int calc1 = maximumi *n;
        for (j = 1; j < dimMinus1-1; j++) {
            int maximumj = j - 1;
            int sumRed, sumGreen, sumBlue;
            sumRed, sumGreen, sumBlue = 0;
            // compute row index in kernel
            pixel *pixel1 = &backupOrg[calc1];
            pixel *pixel2 = pixel1 + 1;
            pixel *pixel3 = pixel1 + 2;
            pixel *pixel4 = pixel1 + m;
            pixel *pixel5 = pixel4 + 1;
            pixel *pixel6 = pixel4 + 2;
            pixel *pixel7 = pixel4 + m;
            pixel *pixel8 = pixel7 + 1;
            pixel *pixel9 = pixel7 + 2;

            calc1++;
          /*  pixel *nextPixel1 = pixel1+3;
            pixel *nextPixel2 = pixel1+4;
            pixel *nextPixel3 = pixel1+5;
            pixel *nextPixel4 = nextPixel1+n;
            pixel *nextPixel5 = nextPixel4+1;
            pixel *nextPixel6 = nextPixel4+2;
            pixel *nextPixel7 = nextPixel4+n;
            pixel *nextPixel8 = nextPixel7+1;
            pixel *nextPixel9 = nextPixel7+2;

            calc1+=2;*/

            sumRed = ((int) pixel1->red + (int) pixel2->red + (int) pixel3->red + (int) pixel4->red +
                      (int) pixel5->red + (int) pixel6->red +
                      (int) pixel7->red + (int) pixel8->red + (int) pixel9->red);
            sumGreen = ((int) pixel1->green + (int) pixel2->green + (int) pixel3->green + (int) pixel4->green +
                        (int) pixel5->green +
                        (int) pixel6->green +
                        (int) pixel7->green + (int) pixel8->green + (int) pixel9->green);
            sumBlue = ((int) pixel1->blue + (int) pixel2->blue + (int) pixel3->blue + (int) pixel4->blue +
                       (int) pixel5->blue +
                       (int) pixel6->blue +
                       (int) pixel7->blue + (int) pixel8->blue + (int) pixel9->blue);

            // divide by kernel's weight
            sumRed /= 9;
            sumGreen /= 9;
            sumBlue /= 9;

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) min(max(sumRed, 0), 255);
            current_pixel.green = (unsigned char) min(max(sumGreen, 0), 255);
            current_pixel.blue = (unsigned char) min(max(sumBlue, 0), 255);
            pixelImage[calcValue(i, j, n)] = current_pixel;


            /*sumRed, sumGreen, sumBlue = 0;


            sumRed = ((int) nextPixel1->red + (int) nextPixel2->red + (int) nextPixel3->red + (int) nextPixel4->red +
                      (int) nextPixel5->red + (int) nextPixel6->red +
                      (int) nextPixel7->red + (int) nextPixel8->red + (int) nextPixel9->red);
            sumGreen = ((int) nextPixel1->green + (int) nextPixel2->green + (int) nextPixel3->green + (int) nextPixel4->green +
                        (int) nextPixel5->green +
                        (int) nextPixel6->green +
                        (int) nextPixel7->green + (int) nextPixel8->green + (int) nextPixel9->green);
            sumBlue = ((int) nextPixel1->blue + (int) nextPixel2->blue + (int) nextPixel3->blue + (int) nextPixel4->blue +
                       (int) nextPixel5->blue +
                       (int) nextPixel6->blue +
                       (int) nextPixel7->blue + (int) nextPixel8->blue + (int) nextPixel9->blue);

            // divide by kernel's weight
            sumRed /= 9;
            sumGreen /= 9;
            sumBlue /= 9;

            // truncate each pixel's color values to match the range [0,255]
            current_pixel1.red = (unsigned char) min(max(sumRed, 0), 255);
            current_pixel1.green = (unsigned char) min(max(sumGreen, 0), 255);
            current_pixel1.blue = (unsigned char) min(max(sumBlue, 0), 255);
            pixelImage[calcValue(i, j+1, n)] = current_pixel1;*/


        }
    }
    free(backupOrg);
}

void doConvolution2(Image *image, int kernelScale) {
    int mnPixel = m * n * sizeof(pixel);
    //creating a pointer to the image data in oreder to save one allocation and one free at the end of the function.
    pixel *pixelImage = (pixel *) image->data;
    pixel *backupOrg = malloc(mnPixel);
    memcpy(backupOrg, pixelImage, mnPixel);

    int row, col;
    // there was a function that translate pixels to chaer and than from chars to pixels loop that is  not needed
    int i, j;

    int mMinus1 = m - 1;
    for (i = 1; i < mMinus1; ++i) {
        for (j = 1; j < mMinus1; ++j) {
            //apply kernel
            pixel current_pixel;
            pixel current_pixel1;

            //using macro
            int maximumi = i - 1;
            int maximumj = j - 1;
            int minimumIDim = min(i + 1, mMinus1);
            int minimumJDim = min(j + 1, mMinus1);
            int sumRed, sumGreen, sumBlue;
            sumRed, sumGreen, sumBlue = 0;

            int calc1 = calcValue(maximumi, maximumj, n);

            pixel *pixel1 = &backupOrg[calc1];
            pixel *pixel2 = pixel1 + 1;
            pixel *pixel3 = pixel1 + 2;
            pixel *pixel4 = pixel1 + m;
            pixel *pixel5 = pixel4 + 1;
            pixel *pixel6 = pixel4 + 2;
            pixel *pixel7 = pixel4 + m;
            pixel *pixel8 = pixel7 + 1;
            pixel *pixel9 = pixel7 + 2;






            sumRed = multBy9((int) pixel5->red) + multByMinus1((int) pixel1->red + (int) pixel2->red + (int) pixel3->red
                                                               + (int) pixel4->red +
                                                               (int) pixel6->red + (int) pixel7->red +
                                                               (int) pixel8->red +
                                                               (int) pixel9->red);
            sumGreen = multBy9((int) pixel5->green) + multByMinus1(
                    (int) pixel1->green + (int) pixel2->green + (int) pixel3->green + (int) pixel4->green +
                    (int) pixel6->green + (int) pixel7->green + (int) pixel8->green +
                    (int) pixel9->green);
            sumBlue = multBy9((int) pixel5->blue) +
                      multByMinus1((int) pixel1->blue + (int) pixel2->blue + (int) pixel3->blue + (int) pixel4->blue +
                                   (int) pixel6->blue + (int) pixel7->blue + (int) pixel8->blue +
                                   (int) pixel9->blue);

            // truncate each pixel's color values to match the range [0,255]

            current_pixel.red = (unsigned char) min(max(sumRed, 0), 255);
            current_pixel.green = (unsigned char) min(max(sumGreen, 0), 255);
            current_pixel.blue = (unsigned char) min(max(sumBlue, 0), 255);
            pixelImage[calcValue(i,j,n)] = current_pixel;


           /* sumRed = multBy9((int) nextPixel5->red) + multByMinus1((int) nextPixel1->red + (int) nextPixel2->red + (int) nextPixel3->red
                                                               + (int) nextPixel4->red +
                                                               (int) nextPixel6->red + (int) nextPixel7->red +
                                                               (int) nextPixel8->red +
                                                               (int) nextPixel9->red);
            sumGreen = multBy9((int) nextPixel5->green) + multByMinus1((int) nextPixel1->green + (int) nextPixel2->green + (int) nextPixel3->green
                                                                   + (int) nextPixel4->green +
                                                                   (int) nextPixel6->green + (int) nextPixel7->green +
                                                                   (int) nextPixel8->green +
                                                                   (int) nextPixel9->green);
            sumBlue = multBy9((int) nextPixel5->blue) + multByMinus1((int) nextPixel1->blue + (int) nextPixel2->blue + (int) nextPixel3->blue
                                                                      + (int) nextPixel4->blue +
                                                                      (int) nextPixel6->blue + (int) nextPixel7->blue +
                                                                      (int) nextPixel8->blue +
                                                                      (int) nextPixel9->blue);

            // truncate each pixel's color values to match the range [0,255]

            current_pixel1.red = (unsigned char) min(max(sumRed, 0), 255);
            current_pixel1.green = (unsigned char) min(max(sumGreen, 0), 255);
            current_pixel1.blue = (unsigned char) min(max(sumBlue, 0), 255);
            pixelImage[calcValue(i,j+1,n)] = current_pixel1;
*/



        }
    }
    free(backupOrg);
}

void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName) {
    

    // blur image
    doConvolution1(image, 9);

    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);

    //smooth(m, backupOrg, pixelsImg, kernelSize, sharpKernel, 1);

    // sharpen the resulting image
    doConvolution2(image, 1);

    // write result image to file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}

