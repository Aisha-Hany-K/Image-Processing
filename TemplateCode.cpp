#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Image_Class.h"

using namespace std;

bool isValidExtension(const string& filename) {
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
            for(int j=0; j<img.height; i++)
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

                    rotated(j, img.width - 1 - i, 0) = img(i, j, 0);
                    rotated(j, img.width - 1 - i, 1) = img(i, j, 1);
                    rotated(j, img.width - 1 - i, 2) = img(i, j, 2);
                }
            }

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
            cout << "Enter image filename to load: ";
            cin >> filename;
            try {
                currentImage.loadNewImage(filename);
                imageLoaded = true;
                cout << "Image loaded successfully!\n";
            } catch (...) {
                cout << "Failed to load image. Please check the file path.\n";
            }
        } 
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

            //...
            
            int filterChoice;
            cin >> filterChoice;

            switch (filterChoice) {
                case 1: filterGrayscale(currentImage); break;
                case 2: filterBlackAndWhite(currentImage); break;
                case 3: filterInvert(currentImage); break;
                case 4: cout << "Choose:\n";
                        cout << "1. flip Horizontally\n";
                        cout << "2. flip Vertically\n";
                        cout << "Enter choice: "; int x; cin>> x;
                        if (x == 1 || x == 2)
                        {
                            filterFlip(currentImage, x);
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
                                break;

                            case 2:
                                filterRotate(currentImage, 180);
                                break;

                            case 3:
                                filterRotate(currentImage, 270);
                                break;

                            default:
                                cout << "Invalid rotation choice.\n";
                            break;
                        }
                              
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