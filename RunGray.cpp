#include <iostream>
#include <cmath>
#include "BMP/bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE];

//_____________________________________________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name:";
    cin >> imageFileName;
    cout << "___________________________________________________\n";

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_____________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_____________________________________________


//_____________________________________________
void Gray_to_Black_and_White_Image(){
    for(int i{0}; i < SIZE; i++) {
        for (int j{0}; j < SIZE; j++) {
            if(image[i][j] > 128) image[i][j] = 255;
            else image[i][j] = 0;
        }
    }
}

//_____________________________________________
void Invert() {
    for (int i{0}; i < SIZE; i++){
        for (int j{0}; j < SIZE; j++){
            image[i][j] = 255 - image[i][j];
        }
    }
}

//_____________________________________________
void Merge(){

    unsigned char img_to_merge[SIZE][SIZE];
    unsigned char merged_pixel;
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter name of image file to merge with:";
    cin >> imageFileName;
    cout << "___________________________________________________\n";


    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    // reading the image
    readGSBMP(imageFileName, img_to_merge);


    for (int i{0}; i < SIZE; ++i){
        for (int j{0}; j < SIZE; ++j){
            merged_pixel = (image[i][j] + img_to_merge[i][j]) / 2;
            image[i][j] = merged_pixel;
        }
    }
}

//_____________________________________________
void Gray_Image_Flip(){

    // this variable is used to store a value of pixel to not lost it
    unsigned char pixel;
    char choice{};

    cout << "Flip (h)orizontally or (v)ertically\n";
    cin >> choice;


    // horizontal flip algorithm
    if(choice == 'h' || choice == 'H'){
        for (int i{0}; i < SIZE; i++)
            for (int j{0}; j < SIZE / 2; j++)
                pixel = image[i][j], image[i][j] = image[i][255 - j], image[i][255 - j] = pixel;
    }


    // vertical flip algorithm
    else if(choice == 'v' || choice == 'V'){
        for(int i{0}; i < SIZE; i++){
            for (int j{0}; j < SIZE / 2; j++){
                pixel = image[j][i], image[j][i] = image[255 - j][i], image[255 - j][i] = pixel;
            }
        }
    }
}

//_____________________________________________
void Rotate(){

    unsigned char image2[SIZE][SIZE]{};
    int degree{};

    // getting the rotate degree
    cout << "Rotate (90), (180) or (270) degrees\n";
    cin >> degree;

    // 90-degree rotation algorithm
    if (degree == 90){
        for (int i{0}; i < SIZE; i++){
            for (int j{0}; j < SIZE; j++) {
                image2[j][i] = image[255 - i][j];
            }
        }
    }

    // 180-degree rotation algorithm
    else if (degree == 180){
        for (int i{0}; i < SIZE; i++) {
            for (int j{0}; j < SIZE; j++){
                image2[i][j] = image[(SIZE - 1) - i][(SIZE - 1) - j];
            }
        }
    }

        // 270-degree rotation algorithm
    else if (degree == 270) {
        for (int i{0}; i < SIZE; i++){
            for (int j{0}; j < SIZE; j++) {
                image2[i][j] = image[i][(SIZE - 1) - j];
            }
        }
    }

    // applying the changes on the original image
    for (int i{0}; i < SIZE; i++){
        for (int j{0}; j < SIZE; j++){
            image[i][j] = image2[i][j];
        }
    }

}

//_____________________________________________
void Darken_and_Lighten(){
    cout << "(L)ighten or (D)arken\n";
    char choice; cin >> choice;

    // lighten algorithm
    if(choice == 'L' || choice == 'l'){
        for(int i{0}; i < SIZE; ++i){
            for (int j{0}; j < SIZE; ++j){
                image[i][j] = (image[i][j] + 255) / 2;
            }
        }
    }

    // darken algorithm
    else if (choice == 'D' || choice == 'd'){
        for(int i{0}; i < SIZE; ++i){
            for (int j{0}; j < SIZE; ++j){
                image[i][j] = (image[i][j]) / 2;
            }
        }

    }
}

//_____________________________________________
void Detect_Gray_image_edge(){

    unsigned char image2[SIZE][SIZE]{};
    Gray_to_Black_and_White_Image();

    // we are looping on the whole pixels if there is pixel around it pixel with different
    // colour that's means that this pixel is edge
    for(int i{0}; i < 256; i++)
        for(int j{0}; j < 256; j++){
            if ((j + 1) < 256 && image[i][j + 1] != image[i][j])
                image2[i][j] = 0;

            else if (0 <= (j - 1) && image[i][j - 1] != image[i][j])
                image2[i][j] = 0;

            else if ((i + 1) < 256 && image[i + 1][j] != image[i][j])
                image2[i][j] = 0;

            else if (0 <= (i - 1) && image[i - 1][j] != image[i][j])
                image2[i][j] = 0;

            else if (0 <= (j - 1) && 0 <= (i - 1) && image[i - 1][j - 1] != image[i][j])
                image2[i][j] = 0;

            else if ((j + 1) < 256 && 0 <= (i - 1) && image[i - 1][j + 1] != image[i][j])
                image2[i][j] = 0;

            else if (0 <= (j - 1) && (i + 1) < 256 && image[i + 1][j - 1] != image[i][j])
                image2[i][j] = 0;

            else if ((j + 1) < 256 && (i + 1) < 256 && image[i + 1][j + 1] != image[i][j])
                image2[i][j] = 0;

            else image2[i][j] = 255;
        }
    for(int i{0}; i < 256; i++)
        for(int j{0}; j < 256; j++)
            if(image2[i][j] == 255)image[i][j] = 255;

}

//_____________________________________________
void Enlarge_Gray_Image() {

    unsigned char image2[SIZE][SIZE]{};
    int quarter{};
    cout << "Enter the Quarter NO. you want to enlarge:\n";
    cin >> quarter;


    //top-left quarter
    if(quarter == 1) {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image2[i][j] = image[i / 2][j / 2];
    }


    //top-right quarter
    else if(quarter == 2) {
        for(int i{0}; i < SIZE; i++)
            for(int j{0}; j < SIZE; j++)
                image2[i][j] = image[i/2][SIZE/2 + j/2];


    }


    //lower-left quarter
    else if(quarter == 3){
        for (int i{0}; i < SIZE; i++)
            for (int j{0}; j < SIZE; j++)
                image2[i][j] = image[SIZE/2 + i/2][j/2];
    }


    //lower-right quarter
    else if (quarter == 4) {
        for (int i{0}; i < SIZE; i++)
            for (int j{0}; j < SIZE; j++)
                image2[i][j] = image[SIZE/2+i/2][SIZE/2+j/2];
    }


    // applying the changes on the original image
    for (int i{0}; i < SIZE; i++){
        for (int j{0}; j < SIZE; j++){
            image[i][j] = image2[i][j];
        }
    }


}

//_____________________________________________
void Shrink(){

    unsigned char image2[SIZE][SIZE]{};
    unsigned char doubled_pixel;
    string choice;

    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    cin >> choice;


    for(int i{0}; i < SIZE; ++i){
        for (int j{0}; j < SIZE; ++j){
            image2[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }


    if (choice == "1/2"){
        for(int i{0}, f{0}; i < SIZE / 2; ++i, f += 2){
            for(int j{0}, k{0}; j < SIZE / 2; ++j, k += 2){
                doubled_pixel = (image2[f][k] + image2[f + 1][k + 1]) / 2;
                image[i][j] = doubled_pixel;
            }
        }
    }


    if (choice == "1/3"){
        for (int i{0}, f{0}; i < SIZE / 3; ++i, f += 3){
            for (int j{0}, k{0}; j < SIZE / 3; ++j, k += 3){
                doubled_pixel = (image2[f][k] + image2[f + 1][k + 1]) / 2;
                image[i][j] = doubled_pixel;
            }
        }
    }


    if (choice == "1/4"){
        for (int i{0}, f{0}; i < SIZE / 4; ++i, f += 4){
            for (int j = 0, k = 0; j < SIZE / 4; ++j, k += 4){
                doubled_pixel = (image2[f][k] + image2[f + 1][k + 1]) / 2;
                image[i][j] = doubled_pixel;
            }
        }
    }
}

//_____________________________________________
void Gray_Mirror(){

    char choice;

    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side\n";
    cin >> choice;

    // left mirror algorithm
    if(choice == 'l' || choice == 'L'){
        // filling the right part of the image with the left part
        for(int i{0}; i < SIZE; i++)
            for(int j{0}; j < SIZE / 2; j++)
                image[i][(SIZE - 1) - j] = image[i][j];
    }

    // right mirror algorithm
    if(choice == 'r' || choice == 'R'){
        // filling the left part of the image with the right part
        for(int i{0}; i < SIZE; i++)
            for(int j{0}; j < SIZE / 2; j++)
                image[i][j] = image[i][(SIZE - 1) - j];
    }

    // upper mirror algorithm
    if(choice == 'u' || choice == 'U'){
        // filling the lower part of the image with the upper part
        for(int i{0}; i < SIZE / 2; i++)
            for(int j{0}; j < SIZE; j++)
                image[(SIZE - 1) - i][j] = image[i][j];
    }

    // lower mirror algorithm
    if(choice == 'd' || choice == 'D'){
        // filling the upper part of the image with the lower part
        for(int i{0}; i < SIZE / 2; i++)
            for(int j{0}; j < SIZE; j++)
                image[i][j] = image[(SIZE - 1) - i][j];
    }

}

//_____________________________________________
void Shuffle() {

    unsigned char image2[SIZE][SIZE]; // we store here the new result
    int seq[4]{}; // array tho save the sequence of new image


    // those variables used to detect the initial index of the quarter which will be copied of the old image
    int old_row_idx{}, old_column_idx{};

    // those variables used to detect the initial index of the quarter which will be filled on the new image
    int new_row_idx{}, new_column_idx{};

    cout << "Enter the New order of Quarters \n";
    for(int i{0}; i < 4; i++)
        cin >> seq[i];

    // applying the filter
    for(int i{0}; i < 4; i++){
        new_row_idx = 0, new_column_idx = 0;
        old_row_idx = 0, old_column_idx = 0;

        // detect the initial index of the quarter which will be copied
        if(seq[i] == 2 || seq[i] == 4) old_column_idx = SIZE / 2;
        if(seq[i] == 3 || seq[i] == 4) old_row_idx = SIZE / 2;

        // detect the initial index of the quarter which will be filled
        if(i == 1 || i == 3) new_column_idx = SIZE / 2;
        if(i == 2 || i == 3) new_row_idx = SIZE / 2;

        // filling the quarters
        for(int j{0}; j < SIZE / 2; j++){
            for(int k{0}; k < SIZE / 2; k++){
                image2[new_row_idx + j][new_column_idx + k] = image[old_row_idx + j][old_column_idx + k];
            }
        }
    }

    // applying the changes on the original image
    for (int i{0}; i < SIZE; i++){
        for (int j{0}; j < SIZE; j++){
            image[i][j] = image2[i][j];
        }
    }

}

//_____________________________________________
void Blur(){
    unsigned char doubled_pixel{};

    // applying the blur algorithm two times
    for(int c{0}; c < 2; c++){
        for (int i{0}; i < SIZE; ++i) {
            for (int j{0}; j < SIZE; ++j) {
                doubled_pixel = (image[i][j] + image[i + 1][j + 1] + image[i + 1][j] + image[i][j + 1]
                                 + image[i - 1][j] + image[i][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1] +
                                 image[i - 1][j - 1]) / 9;
                image[i][j] = doubled_pixel;
            }
        }
    }

}

//_____________________________________________
void Gray_Crop(){
    int x, y, l, w;

    cout << "Please enter x y l w\n";
    cin >> x >> y >> l >> w;

    // logical check for rectangle size and image size
    if(y + l - 2 > SIZE || x + w - 2 > SIZE) return;

    // looping on the whole image if the pixel belong to the rectangle take it
    // else make it white
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(!(i >= y - 1 && i <= l + y - 2) || !(j >= x - 1 && j <= x + w - 2))
                image[i][j] = 255;
}

//_____________________________________________
void Skew() {
    unsigned char image2[SIZE][SIZE];
    int degree{};
    char choice{};

    cout << "Skew (H)orizontally or (V)ertically\n";
    cin >> choice;

    cout << "Enter the degree to skew\n";
    cin >> degree;


    // taking a copy from the image and making the original image white
    for(int i{0}; i < SIZE; ++i){
        for (int j{0}; j < SIZE; ++j){
            image2[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }


    double rad = degree * (M_PI/180.0);      //convert from degree to radian
    double scale = 1 / (1 + tan(rad));  //shrink factor to fit the given image into output image
    double dist = 255 - scale * 255;    //distance that will be white


    // horizontal skewing algorithm
    if (choice == 'h' || choice == 'H'){
        for (int i{0}; i < SIZE; i++){
            for (int j{0}; j < SIZE; j++){
                double x = j;
                x *= scale;
                x += dist;

                image[i][int(x)] = image2[i][j];
            }

            dist -= ((256 - scale * 255) / 255);
        }
    }


    // vertical skewing algorithm
    else if (choice == 'v' || choice == 'V'){

        for(int i{0}; i < SIZE; i++){
            for(int j{0}; j < SIZE; j++){
                double x = j;
                x *= scale;
                x += dist;

                image[int(x)][i] = image2[j][i];
            }
            dist -= ((256 - scale * 255) / 255);
        }
    }
}
//_____________________________________________

void menu(){

    int FilterNo{};

    while(true){
        cout << "1) Black & White Filter\n"
             << "2) Invert Filter\n"
             << "3) Merge Images\n"
             << "4) Flip Image\n"
             << "5) Rotate Images\n"
             << "6) Darken and Lighten Image\n"
             << "7) Detect Image Edges\n"
             << "8) Enlarge Image\n"
             << "9) Shrink Image\n"
             << "10) Mirror Image\n"
             << "11) Shuffle Image\n"
             << "12) Blur Image\n"
             << "13) Crop Image\n"
             << "14) Skew Image\n"
             << "15) Save Image\n"
             << "16) Exit\n"
             << "___________________________________________________\n";
        cin >> FilterNo;
        cout << "___________________________________________________\n";

        if(FilterNo == 1)
            Gray_to_Black_and_White_Image();

        else if(FilterNo == 2)
            Invert();

        else if(FilterNo == 3)
            Merge();

        else if(FilterNo == 4)
            Gray_Image_Flip();

        else if(FilterNo == 5)
            Rotate();

        else if(FilterNo == 6)
            Darken_and_Lighten();

        else if(FilterNo == 7)
            Detect_Gray_image_edge();

        else if(FilterNo == 8)
            Enlarge_Gray_Image();

        else if(FilterNo == 9)
            Shrink();

        else if(FilterNo == 10)
            Gray_Mirror();

        else if(FilterNo == 11)
            Shuffle();

        else if(FilterNo == 12)
            Blur();

        else if(FilterNo == 13)
            Gray_Crop();

        else if(FilterNo == 14)
            Skew();


        else if(FilterNo == 15){
            saveImage();
            cout << "Image saved\n"
                 << "___________________________________________________\n";
            continue;
        }

        else if(FilterNo == 16){
            cout << "terminated\n"
                 << "___________________________________________________\n";
            break;
        }

        else{
            cout << "Not Defined Filter\n"
                 << "___________________________________________________\n";
            continue;
        }

        cout << "filter applied\n"
             << "___________________________________________________\n";
    }

}

//_____________________________________________


int main() {
    loadImage();
    menu();
    return 0;
}


