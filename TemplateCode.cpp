//====================================================================================
//======================================Part 1========================================
//Rehab Ahmed     : 20251509 |||| filter: Frame, Resize
//Mostafa Mohamed : 20250641 |||| filter: Lighten and Darken, Invert
//Mostafa Ali     : 20250640 |||| filter: Rotate, Black and White
//Aisha Hany      : 20250342 |||| filter: GrayScale, Flip
//section: s31-32
//===================================================================================
//===================================================================================

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Image_Class.h"
#include<algorithm>
#include <cmath>

using namespace std;

bool isValidExtension(const string& filename) 
{
    string ext = "";
    size_t dotPos = filename.find_last_of(".");
    if (dotPos != string::npos) {
        ext = filename.substr(dotPos);
        for (auto &c : ext) c = tolower(c);
    }
    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp");
}

// Filters
void filterGrayscale(Image& img)
{
    for(int i=0; i<img.width; i++)
    {
        for(int j=0; j<img.height; j++)
        {
            int ave = 0;

            for(int k=0; k<3; k++)
            {
                ave += img(i, j, k);
            }

            ave /= 3;

            for (int k=0; k<3; k++)
            {
                img(i, j, k) = ave;
            }
        }
    }
}

void filterFlip(Image& img, int x)
{
    Image adjustedimg(img.height, img.width);
    switch (x)
    {
        case 1:
        for(int i=0; i<img.width; i++)
        {
            for(int j = img.height -1; j>=0; j--)
            {
                for(int k=0; k<3; k++)
                {
                    adjustedimg(i, j, k) = img(i, img.height- j -1, k);
                }
            }
        }
        
        break;

        case 2:
        for(int i= img.width-1; i>=0; i--)
        {
            for(int j=0; j<img.height; j++)
            {
                for(int k=0; k<3; k++)
                {
                    adjustedimg(i, j, k) = img(img.width- i -1 ,j ,k);
                }
            }
        }
        
        break;
    }

    img = adjustedimg;
}

void filterBlackAndWhite(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
            }

            avg /= 3;

            if (avg < 128) {
                img(i, j, 0) = 0;
                img(i, j, 1) = 0;
                img(i, j, 2) = 0;
            }
            else {
                img(i, j, 0) = 255;
                img(i, j, 1) = 255;
                img(i, j, 2) = 255;
            }
        }
    }
}

void filterFrame(Image& img, int f) {
    int s = 30;
    int corner = 50;
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            if (x < s || x >= img.width - s || y < s || y >= img.height - s) {
                switch (f) {
                case 1:
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 0;
                    img(x, y, 2) = 0;
                    break;
                case 2:
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 255;
                    img(x, y, 2) = 255;
                    break;
                case 3:
                    img(x, y, 0) = 0;
                    img(x, y, 1) = 0;
                    img(x, y, 2) = 0;
                    break;
                }
            }
            if (f == 4) {
                if (x < s || x >= img.width - s || y < s || y >= img.height - s) {
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 215;
                    img(x, y, 2) = 0;
                }
                else if (x <= corner && y <= corner) {
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 215;
                    img(x, y, 2) = 0;
                }
                else if (x >= img.width - corner && y <= corner) {
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 215;
                    img(x, y, 2) = 0;
                }
                else if (x <= corner && y >= img.height - corner) {
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 215;
                    img(x, y, 2) = 0;
                }
                else if (x >= img.width - corner && y >= img.height - corner) {
                    img(x, y, 0) = 255;
                    img(x, y, 1) = 215;
                    img(x, y, 2) = 0;
                }
            }
        }
    }
}

void filterRotate(Image& img, int rotation) {

    switch (rotation) {

        case 90: {
            Image rotated(img.height, img.width);

            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {

                    rotated(img.height - 1 - j, i, 0) = img(i, j, 0);
                    rotated(img.height - 1 - j, i, 1) = img(i, j, 1);
                    rotated(img.height - 1 - j, i, 2) = img(i, j, 2);
                }
            }

            img = rotated;
            break;
        }

        case 180: {
            Image rotated(img.width, img.height);

            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {

                    rotated(img.width - 1 - i, img.height - 1 - j, 0) = img(i, j, 0);
                    rotated(img.width - 1 - i, img.height - 1 - j, 1) = img(i, j, 1);
                    rotated(img.width - 1 - i, img.height - 1 - j, 2) = img(i, j, 2);
                }
            }

            img = rotated;
            break;
        }

        case 270: {
           Image rotated(img.height, img.width);

            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {

                    rotated(img.height - 1 - j, i, 0) = img(i, j, 0);
                    rotated(img.height - 1 - j, i, 1) = img(i, j, 1);
                    rotated(img.height - 1 - j, i, 2) = img(i, j, 2);
                }
            }

            filterFlip(rotated , 2);

            img = rotated;
            break;
        }

        default:
            cout << "Invalid rotation angle.\n";
    }
}

void filterInvert(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

void filterResize(Image& img, int newW, int newH) {
    double scaleX = (double)newW / img.width;
    double scaleY = (double)newH / img.height;
    Image resized (newW, newH);
    for (int x = 0; x < newW; ++x) {
        for (int y = 0; y < newH; ++y) {
            int oldX = x / scaleX;
            int oldY = y / scaleY;
            for (int c = 0; c < 3; ++c) {
                resized(x, y, c) = img(oldX, oldY, c);
            }
        }
    }
    img = resized;
}

void filterLighten(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int newValue = img(i, j, k) + (img(i, j, k) * 0.5);
                img(i, j, k) = min(255, newValue);
            }
        }
    }
}

void filterDarken(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int newValue = img(i, j, k) - (img(i, j, k) * 0.5);
                img(i, j, k) = max(0, newValue);
            }
        }
    }
}


void filterInfrared(Image& img)
{
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            int r = img(x, y, 0);
            int g = img(x, y, 1);
            int b = img(x, y, 2);

            img(x, y, 0) = min(255, r + g);
            img(x, y, 1) = r;
            img(x, y, 2) = b / 3;
        }
    }
}

void filterSkew(Image& img, int k)
{
    double s = 0.3;
    double newWidth = img.width;
    double newHeight = img.height;
    if (k == 1) {
        double newWidth = img.width + (s * (img.height - 1));
    }
    else if (k == 2) {
        double newHeight = img.height + (s * (img.width - 1));
    }
    Image skewed(ceil(newWidth), ceil(newHeight));

    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            for (int c = 0; c < 3; c++) {
                if (k == 1) {
                    int newX = x + s * y;
                    if (newX >= 0 && newX < newWidth) {
                        skewed(newX, y, c) = img(x, y, c);
                    }
                }
                else if (k == 2) {
                    int newY = y + s * x;
                    if (newY >= 0 && newY < newHeight) {
                        skewed(x, newY, c) = img(x, y, c);
                    }
                }
            }
        }
    }
    img = skewed;
}

void filterBlur(Image img, Image blured) {
    long long prefixR[1000 + 1][1000 + 1] = {};
    long long prefixG[1000 + 1][1000 + 1] = {};
    long long prefixB[1000 + 1][1000 + 1] = {};
    for (x = 0; x < img.width; x++) {
        for (y = 0; y < img.height; y++) {

            prefixR[y + 1][x + 1] =
                img(x, y, 0) + prefixR[y][x + 1] + prefixR[y + 1][x] - prefixR[y][x];

            prefixG[y + 1][x + 1] =
                img(x, y, 1) + prefixG[y][x + 1] + prefixG[y + 1][x] - prefixG[y][x];

            prefixB[y + 1][x + 1] =
                img(x, y, 2) + prefixB[y][x + 1] + prefixB[y + 1][x] - prefixB[y][x];

        }
    }

    for (x = 0; x < img.width; x++) {
        for (y = 0; y < img.height; y++) {
            int top = max(0, y - 1);
            int bottom = min(img.height - 1, y + 1);
            int left = max(0, x - 1);
            int right = min(img.width - 1, x + 1);

            int T = top;
            int B = bottom + 1;
            int L = left;
            int R = right + 1;
            long long sumR = prefixR[B][R] - prefixR[T][R] - prefixR[B][L] + prefixR[T][L];
            long long sumG = prefixG[B][R] - prefixG[T][R] - prefixG[B][L] + prefixG[T][L];
            long long sumB = prefixB[B][R] - prefixB[T][R] - prefixB[B][L] + prefixB[T][L];

            int count = (bottom - top + 1) * (right - left + 1);

            blured[y][x].r = sumR / count;
            blured[y][x].g = sumG / count;
            blured[y][x].b = sumB / count;

        }
    }
}
//...

// Menu
int main() {
    Image currentImage;
    string filename;
    bool imageLoaded = false;
    int choice = 0;

    while (true) {
        cout << "\n=== Image Processing Menu ===\n";
        cout << "1. Load Image\n";
        cout << "2. Apply Filter\n";
        cout << "3. Save Image\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter image filename to load:\n ";
            cin >> filename;
            try {
                currentImage.loadNewImage(filename);
                imageLoaded = true;
                cout << "Image loaded successfully!\n";
            } catch (...) {
                cout << "Failed to load image. Please check the file path.\n";
            }
        } 
        //Applying Filters
        else if (choice == 2) {
            if (!imageLoaded) {
                cout << "Please load an image first!\n";
                continue;
            }
            // Write your filter in the choices
            cout << "\n--- Select Filter ---\n";
            cout << "1. Grayscale\n";
            cout << "2. Black and White\n";
            cout << "3. Invert Colors\n";
            cout << "4. Flip Image\n";
            cout << "5. Rotate Image\n";
            cout << "6. Add frame\n";
            cout << "7. Resizing\n";
            cout << "8. Lighten Or Darken Image\n";
            //...
            
            int filterChoice;
            cin >> filterChoice;

            switch (filterChoice) {
            case 1: filterGrayscale(currentImage);
                cout << "Implemented Grayscale filter successfully!\n";
                break;

            case 2: filterBlackAndWhite(currentImage);
                cout << "Implemented Black and White filter successfully!\n";
                break;

            case 3: filterInvert(currentImage);
                cout << "Implemented Invert filter successfully!\n";
                break;

            case 4: cout << "Choose:\n";
                cout << "Enter choice: ";
                cout << "1. flip Horizontally\n";
                cout << "2. flip Vertically\n";
                int x; cin >> x;
                if (x == 1 || x == 2)
                {
                    filterFlip(currentImage, x);
                    if (x == 1)
                    {
                        cout << "Implemented Vertical Flip filter successfully!\n";
                    }
                    else
                    {
                        cout << "Implemented Horizontal Flip filter successfully!\n";
                    }
                }
                else
                {
                    cout << "Invalid Input\n";
                }
                break;

            case 5:
                int rotationChoice;

                cout << "Choose rotation:\n";
                cout << "1. 90 degrees\n";
                cout << "2. 180 degrees\n";
                cout << "3. 270 degrees\n";
                cout << "Enter choice: ";
                cin >> rotationChoice;

                switch (rotationChoice) {

                case 1:
                    filterRotate(currentImage, 90);
                    cout << "Implemented 90 Degree Rotation filter successfully!\n";
                    break;

                case 2:
                    filterRotate(currentImage, 180);
                    cout << "Implemented 180 Degree Rotation filter successfully!\n";
                    break;

                case 3:
                    filterRotate(currentImage, 270);
                    cout << "Implemented 270 Degree Rotation filter successfully!\n";
                    break;

                default:
                    cout << "Invalid rotation choice.\n";
                    break;
                }
                break;

            case 6: cout << "Choose a frame style: \n";
                cout << "1. Red\n";
                cout << "2. White\n";
                cout << "3. Black\n";
                cout << "4. Decorated\n";
                int f;
                cin >> f;
                if (f >= 1 && f <= 4) {
                    filterFrame(currentImage, f);
                    switch (f)
                    {
                    case 1: cout << "Implemented Red Frame successfully!\n"; break;
                    case 2: cout << "Implemented White Frame successfully!\n"; break;
                    case 3: cout << "Implemented Black Frame successfully!\n"; break;
                    case 4: cout << "Implemented Decorated Frame successfully!\n"; break;
                    }
                }
                else {
                    cout << "Invalid choice!\n";
                }
                break;

            case 7: cout << "Enter new width and height: \n";
                int newW; char xs; int newH; cin >> newW >> xs >> newH;
                if (newW > 0 && newH > 0) {
                    filterResize(currentImage, newW, newH); break;
                }
                else if (newW <= 0) {
                    cout << "Invalid width!\n";
                }
                else if (newH <= 0) {
                    cout << "Invalid height!\n";
                }
                else {
                    cout << "Invalid height and width!\n";
                }
                break;
                case 8: cout << "Choose: \n";
                cout << "1. Lighten the Image\n";
                cout << "2. Darken the Image\n";
                int ch; cin >> ch;
                if(ch == 1)
                {
                    filterLighten(currentImage);
                    cout << "Implemented Lighten filter successfully!\n";
                }
                else if(ch == 2)
                {
                    filterDarken(currentImage);
                    cout << "Implemented Darken filter successfully!\n";
                }
                else
                {
                    cout << "Invalid Input!\n";
                }
                break;

            case 9:
            filterInfrared(currentImage);
            cout << "Implemented Infared filter successfully!\n";
            break;

            case 10:
                cout << "1. Horizontal \n";
                cout << "2. Vertical \n";
                int k;
                cin >> k;
                if (k == 1 || k == 2) {
                    filterSkew(currentImage, k);
                }
                else {
                    cout << "Invalid input! \n";
                } break;

            case 11:
                filterBlur(currentImage);
                break;

            //....
                     
                default: cout << "Invalid filter choice.\n";    
            }
        }
        else if (choice == 3) {
            if (!imageLoaded) {
                cout << "No image to save!\n";
                continue;
            }
            string saveName;
            cout << "Enter new filename (with .jpg, .png, .bmp): ";
            cin >> saveName;
            while (!isValidExtension(saveName)) {
                cout << "Invalid extension! Must be .jpg, .jpeg, .png, or .bmp. Try again: ";
                cin >> saveName;
            }
            currentImage.saveImage(saveName);
            cout << "Image saved successfully as " << saveName << "\n";
        } 
        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        } 
        else {
            cout << "Invalid menu choice.\n";
        }
    }
    return 0;
}