#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

// دالة للتحقق من صحة امتداد الصورة عند الحفظ
bool isValidExtension(const string& filename) {
    string ext = "";
    size_t dotPos = filename.find_last_of(".");
    if (dotPos != string::npos) {
        ext = filename.substr(dotPos);
        for (auto &c : ext) c = tolower(c);
    }
    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp");
}

// نماذج لدوال الفلاتر (8 فلاتر للجزء الأول)
void filterGrayscale(Image& img);
void filterBlackAndWhite(Image& img);
void filterInvert(Image& img);
// ... باقي الفلاتر الـ 8

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
            cout << "\n--- Select Filter ---\n";
            cout << "1. Grayscale\n";
            cout << "2. Black and White\n";
            cout << "3. Invert Colors\n";
            //...
            
            int filterChoice;
            cin >> filterChoice;

            switch (filterChoice) {
                case 1: filterGrayscale(currentImage); break;
                case 2: filterBlackAndWhite(currentImage); break;
                case 3: filterInvert(currentImage); break;
                //...
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