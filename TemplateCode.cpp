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
void filterInvert(Image& img);
void filterFrame(Image& img, int f) {
    int s = 30;
    int corner = 50;
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            if (x < s || x >= currentImage.width - s || y < s || y >= currentImage.height - s) {
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
                if (x < s || x >= currentImage.width - s || y < s || y >= currentImage.height - s) {
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
            cout << "4. Add Frame/n";
            cout << "5. Resizing/n";
            //...
            
            int filterChoice;
            cin >> filterChoice;

            switch (filterChoice) {
                case 1: filterGrayscale(currentImage); break;
                case 2: filterBlackAndWhite(currentImage); break;
                case 3: filterInvert(currentImage); break;
                case 4: cout << "Choose a frame style: \n";
                    cout << "1. Red \n";
                    cout << "2. White \n";
                    cout << "3. Blach \n";
                    cout << "4. Decorated \n";
                    int f;
                    cin >> f;
                    if (f >= 1 && f <= 4) {
                        filterFrame(currentImage, f);
                    }
                    else {
                        cout << "Invalid input!";
                    } break;
                //...
                default: cout << "Invalid filter choice.\n"; break;
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