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

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/numdlg.h>
#include <wx/statbmp.h>

#include "Image_Class.h"

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
    Image adjustedimg(img.width, img.height);
    switch (x)
    {
        case 1:
        for(int i=0; i<img.width; i++)
        {
            for(int j =0; j<img.height; j++)
            {
                for(int k=0; k<3; k++)
                {
                    adjustedimg(i, img.height -j -1, k) = img(i, j, k);
                }
            }
        }
        
        break;

        case 2:
        for(int i= 0; i<img.width; i++)
        {
            for(int j=0; j<img.height; j++)
            {
                for(int k=0; k<3; k++)
                {
                    adjustedimg(img.width-1 -i, j, k) = img(i,j ,k);
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

        case 1: {
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

        case 2: {
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

        case 3: {
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

void filterCrop(Image& img, int x, int y, int W, int H) {
    if (x < 0 || y < 0 || x + W > img.width || y + H > img.height) {
        cout << "Invalid crop dimensions! Out of image boundaries.\n";
        return;
    }

    Image croppedImg(W, H);

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                croppedImg(i, j, k) = img(x + i, y + j, k);
            }
        }
    }

    img = croppedImg;
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

void filterDetectEdges(Image& img) {

    Image edges(img.width, img.height);

    for (int i = 1; i < img.width - 1; ++i) {
        for (int j = 1; j < img.height - 1; ++j) {

            for (int k = 0; k < 3; ++k) {

                int left = img(i - 1, j, k);
                int right = img(i + 1, j, k);
                int top = img(i, j - 1, k);
                int bottom = img(i, j + 1, k);

                int x = right - left;
                int y = bottom - top;

                int edge = abs(x) + abs(y);

                if (edge > 255)
                    edge = 255;

                edges(i, j, k) = edge;
            }
        }
    }

    img = edges;
}

void filterPurple(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int r = img(i, j, 0);
            int g = img(i, j, 1);
            int b = img(i, j, 2);

            int new_r = min(255, (int)(r * 1.25));
            int new_g = (int)(g * 0.60);
            int new_b = min(255, (int)(b * 1.35));

            img(i, j, 0) = new_r;
            img(i, j, 1) = new_g;
            img(i, j, 2) = new_b;
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

void filterTV(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            if (j % 2 == 0) {
                img(i, j, 0) = img(i, j, 0) * 0.4; // Red channel
                img(i, j, 1) = img(i, j, 1) * 0.4; // Green channel
                img(i, j, 2) = img(i, j, 2) * 0.4; // Blue channel
            }
        }
    }
}

void filterMerge(Image& img1, Image& img2)
{
    int newwidth = min(img1.width, img2.width);
    int newheight = min(img1.height, img2.height);

    Image newimage(newwidth, newheight);

    for(int i =0; i< newwidth; i++)
    {
        for(int j=0; j<newheight; j++)
        {
            for(int k=0; k<3; k++)
            {
                newimage(i,j,k) = (img1(i,j,k) +img2(i,j,k))/2;
            }
        }
    }

    img1 = newimage;
}

void filterSunlight(Image& img)
{
    for(int i=0; i<img.width; i++)
    {
        for(int j=0; j<img.height; j++)
        {
            img(i,j,0) = min(255, (int) (img(i,j,0)*1.10));
            img(i,j,1) = min(255, (int) (img(i,j,1)*1.10));
            img(i,j,2) = max(0, (int) (img(i,j,2)*0.85));
        }
    }
}

void filterBlur(Image& img) {
    Image blured(img.width, img.height);
    int w = img.width;
    int h = img.height;
    int radius = 5;
    vector<vector<long long>> prefixR(h + 1, vector<long long>(w + 1, 0));
    vector<vector<long long>> prefixG(h + 1, vector<long long>(w + 1, 0));
    vector<vector<long long>> prefixB(h + 1, vector<long long>(w + 1, 0)); 
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {

            prefixR[y + 1][x + 1] =
                img(x, y, 0) + prefixR[y][x + 1] + prefixR[y + 1][x] - prefixR[y][x];

            prefixG[y + 1][x + 1] =
                img(x, y, 1) + prefixG[y][x + 1] + prefixG[y + 1][x] - prefixG[y][x];

            prefixB[y + 1][x + 1] =
                img(x, y, 2) + prefixB[y][x + 1] + prefixB[y + 1][x] - prefixB[y][x];

        }
    }

    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            int top = max(0, y - radius);
            int bottom = min(img.height - 1, y + radius);
            int left = max(0, x - radius);
            int right = min(img.width - 1, x + radius);

            int T = top;
            int B = bottom + 1;
            int L = left;
            int R = right + 1;
            long long sumR = prefixR[B][R] - prefixR[T][R] - prefixR[B][L] + prefixR[T][L];
            long long sumG = prefixG[B][R] - prefixG[T][R] - prefixG[B][L] + prefixG[T][L];
            long long sumB = prefixB[B][R] - prefixB[T][R] - prefixB[B][L] + prefixB[T][L];

            int count = (bottom - top + 1) * (right - left + 1);

            blured(x,y,0) = sumR / count;
            blured(x,y,1) = sumG / count;
            blured(x,y,2) = sumB / count;

        }
    }

    img = blured;
}

void filterOilPainting(Image& img, int radius = 4, int levels = 20)
{
    Image result(img.width, img.height);

    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            vector<int> count(levels, 0);
            vector<int> sumR(levels, 0);
            vector<int> sumG(levels, 0);
            vector<int> sumB(levels, 0);

            for (int dx = -radius; dx <= radius; dx++)
            {
                for (int dy = -radius; dy <= radius; dy++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= img.width ||
                        ny < 0 || ny >= img.height)
                    {
                        continue;
                    }

                    int r = img(nx, ny, 0);
                    int g = img(nx, ny, 1);
                    int b = img(nx, ny, 2);

                    int intensity = (r + g + b) / 3;

                    int bucket = intensity * levels / 256;

                    if (bucket >= levels)
                        bucket = levels - 1;

                    count[bucket]++;
                    sumR[bucket] += r;
                    sumG[bucket] += g;
                    sumB[bucket] += b;
                }
            }

            int bestBucket = 0;

            for (int i = 1; i < levels; i++)
            {
                if (count[i] > count[bestBucket])
                {
                    bestBucket = i;
                }
            }

            result(x, y, 0) =
                sumR[bestBucket] / count[bestBucket];

            result(x, y, 1) =
                sumG[bestBucket] / count[bestBucket];

            result(x, y, 2) =
                sumB[bestBucket] / count[bestBucket];
        }
    }

    img = result;
}

// ================ GUI ===============//
// ================ GUI ===============//
// ================ GUI ===============//

class MainFrame : public wxFrame
{
    private:
    Image currentimage;
    bool imageloaded = false;
    wxStaticBitmap* preview;
    wxStaticText* statustext;

    void Onloadimge(wxCommandEvent& event);
    void Onapplyfilter(wxCommandEvent& event);
    void Onsaveimage(wxCommandEvent& event);
    void Onexit(wxCommandEvent& event);
    void updatePreview();
    bool requireimage();

    public:
    MainFrame();
};

MainFrame::MainFrame(): wxFrame(nullptr, wxID_ANY, "Image Processing", wxDefaultPosition, wxSize(800,500))
{
    SetIcon(wxIcon("magicapp.ICO", wxBITMAP_TYPE_ICO));
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rightsizer = new wxBoxSizer(wxVERTICAL);


    wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Image Processing");
    wxButton* loadbutton = new wxButton(panel, wxID_ANY, "Load Image", wxDefaultPosition, wxSize(180,40));
    wxButton* applyfilterbutton = new wxButton(panel, wxID_ANY, "Apply Filter", wxDefaultPosition, wxSize(180,40));
    wxButton* saveimagebutton = new wxButton(panel, wxID_ANY, "Save Image", wxDefaultPosition, wxSize(180,40));
    wxButton* exitbutton = new wxButton(panel, wxID_ANY, "Exit", wxDefaultPosition, wxSize(180,40));
    statustext = new wxStaticText(panel, wxID_ANY, "No Image Loaded yet :(");
    wxImage placeholderImage(400, 300);
    placeholderImage.SetRGB(wxRect(0, 0, 400, 300), 220, 220, 220);
    preview = new wxStaticBitmap(panel,wxID_ANY, wxBitmap(placeholderImage));

    sizer->Add(title, 0, wxALIGN_CENTER | wxALL, 15);
    sizer->Add(loadbutton, 0, wxALIGN_CENTER | wxALL, 8);
    sizer->Add(applyfilterbutton, 0, wxALIGN_CENTER | wxALL, 8);
    sizer->Add(saveimagebutton, 0, wxALIGN_CENTER | wxALL, 8);
    sizer->Add(exitbutton, 0, wxALIGN_CENTER | wxALL, 8);

    rightsizer->Add(preview,1, wxEXPAND | wxALL, 8);
    rightsizer->Add(statustext, 0, wxALIGN_CENTRE | wxALL, 8);

    mainsizer->Add(sizer,0,wxEXPAND | wxALL, 10);
    mainsizer->Add(rightsizer,1,wxEXPAND | wxALL, 10);
    panel->SetSizer(mainsizer);

    loadbutton->Bind(wxEVT_BUTTON, &MainFrame::Onloadimge, this);
    applyfilterbutton->Bind(wxEVT_BUTTON, &MainFrame::Onapplyfilter, this);
    saveimagebutton->Bind(wxEVT_BUTTON, &MainFrame::Onsaveimage, this);
    exitbutton->Bind(wxEVT_BUTTON, &MainFrame::Onexit, this);

}

void MainFrame::Onexit(wxCommandEvent& event)
{
    Close(true);
}

bool MainFrame::requireimage()
{
    if(!imageloaded)
    {
        wxMessageBox("Please load an Image first", "No Image loaded!", wxOK | wxICON_INFORMATION, this);
        return false;
    }
    else
    {
        return true;
    }
}

void MainFrame::updatePreview()
{
    //convert currentimage t0 wximage
    //convert wximage to wxbitmap
    //call preview to set setbitmap()
    int width = currentimage.width;
    int height = currentimage.height;

    wxImage wximage(width, height);
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            int r = currentimage(i,j,0);
            int g = currentimage(i,j,1);
            int b = currentimage(i,j,2);
            wximage.SetRGB(i , j, r, g ,b);
        }
    }

    wxBitmap bitmap(wximage);
    preview->SetBitmap(bitmap);
    preview->Refresh();
}

void MainFrame::Onloadimge(wxCommandEvent& event)
{
    //open file dialog
    //load selected file into current image
    //set image laoded to true
    // call update preview
    string filename;

    wxFileDialog dialog(this, "Choose an Image :3", "", "", "Image files (*.png;*.jpg;*.jpeg;*.bmp;*.tga)|*.png;*.jpg;*.jpeg;*.bmp;*.tga", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    else
    {
        filename = dialog.GetPath().ToStdString();
    }

    try
    {
        currentimage.loadNewImage(filename);
        imageloaded = true;
        statustext->SetLabel("Image Loaded yay :)\n" "Image Loaded:" +to_string(currentimage.width) + " x " + to_string(currentimage.height) );
        updatePreview();
    }
    catch(const std::exception& e)
    {
        imageloaded = false;
        statustext->SetLabel("No Image Loaded yet");
        wxMessageBox(e.what(), "Image Loading Error", wxOK | wxICON_ERROR, this);
    }
    
}

void MainFrame::Onsaveimage(wxCommandEvent& event)
{
    //call requireimage()
    //open save dialog
    //save currentimage to the selected path
    string filename;
    if(!requireimage())
    {
        return;
    }

    wxFileDialog dialog(this, "Save an Image", "", "", "Image files (*.png;*.jpg;*.jpeg;*.bmp;*.tga)|*.png;*.jpg;*.jpeg;*.bmp;*.tga", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal()== wxID_CANCEL)
    {
        return;
    }
    filename = dialog.GetPath().ToStdString();
    try
    {
        currentimage.saveImage(filename);
        wxMessageBox("Image saved successfully :)", "Save Image", wxOK | wxICON_INFORMATION, this);
    }
    catch(const std::exception& e)
    {
        wxMessageBox(e.what(), "Save Error", wxOK|wxICON_ERROR, this);
    } 

}

void MainFrame::Onapplyfilter(wxCommandEvent& event)
{
    //call requireimage()
    //show filter selection dialog
    //call the selected filter
    //call updatepreview
    if(!requireimage())
    {
        return;
    }

    wxArrayString filters;
    filters.Add("GrayScale");
    filters.Add("Flip");
    filters.Add("Black and White");
    filters.Add("Frame");
    filters.Add("Rotate");
    filters.Add("Invert");
    filters.Add("Resize");
    filters.Add("Lighten");
    filters.Add("Darken");
    filters.Add("Crop");
    filters.Add("Infrared");
    filters.Add("Detect Edges");
    filters.Add("Purple");
    filters.Add("Skew");
    filters.Add("TV");
    filters.Add("Merge");
    filters.Add("Natural Sunlight");
    filters.Add("Oil Painting");
    filters.Add("Blur");

    wxSingleChoiceDialog dialog (this,"Choose a filter to apply :3", "Apply Filter", filters);

    if(dialog.ShowModal()== wxID_CANCEL)
    {
        return;
    }

    int choise = dialog.GetSelection();

    switch(choise)
    {
        case 0:
        filterGrayscale(currentimage);
        break;

        case 1:
        {
            wxArrayString userinput;
            userinput.Add("Vertical");
            userinput.Add("Horizontal");

            wxSingleChoiceDialog flipdialog (this, "Choose the flip direction: ", "Flip Image", userinput);
            if(flipdialog.ShowModal()==wxID_CANCEL)
            {
                return;
            }

            int direction = flipdialog.GetSelection()+1;
            filterFlip(currentimage, direction);
            break;
        }

        case 2:
        filterBlackAndWhite(currentimage);
        break;

        case 3:
        {
            wxArrayString frameinput;
            frameinput.Add("Red Frame");
            frameinput.Add("White Frame");
            frameinput.Add("Black Frame");
            frameinput.Add("Decorated Frame");

            wxSingleChoiceDialog frameinputdialog(this, "Choose a frame: ", "Image Frame", frameinput);
            if(frameinputdialog.ShowModal()==wxID_CANCEL)
            {
                return;
            }
            int fi = frameinputdialog.GetSelection()+1;
            filterFrame(currentimage, fi);
            break;
        }

        case 4:
        {
            wxArrayString rotationinput;
            rotationinput.Add("90 Degrees");
            rotationinput.Add("180 Degrees");
            rotationinput.Add("270 Degrees");

            wxSingleChoiceDialog rotationdialog(this, "Choose a Rotation", "Image Rotation", rotationinput);
            if(rotationdialog.ShowModal()==wxID_CANCEL)
            {
                return;
            }
            int ri = rotationdialog.GetSelection()+1;
            filterRotate(currentimage, ri);
            break;
        }

        case 5:
        filterInvert(currentimage);
        break;

        case 6:
        {
            wxNumberEntryDialog widthDialog(this, "Enter the new width:","Width:","Resize Image",currentimage.width, 1, 10000);
            if (widthDialog.ShowModal() == wxID_CANCEL)
            {
                return;
            }
            int newWidth = widthDialog.GetValue();

            wxNumberEntryDialog heightDialog(this,"Enter the new height:", "Height:","Resize Image", currentimage.height,1,10000);
            if (heightDialog.ShowModal() == wxID_CANCEL)
            {
                return;
            }
            int newHeight = heightDialog.GetValue();

            filterResize(currentimage, newWidth, newHeight);
            statustext->SetLabel("Image Loaded: " +to_string(currentimage.width) + " x " + to_string(currentimage.height));
            break;
        }

        case 7:
        filterLighten(currentimage);
        break;

        case 8:
        filterDarken(currentimage);
        break;

        case 9:
        {
            int w = currentimage.width;
            int h = currentimage.height;

            int xval;
            while (true)
            {
                wxTextEntryDialog xdialog(this,"Enter Distance from the left edge (1 to " + to_string(w - 1) + ")","Starting point (X,Y) of the top-left corner","1");
                if (xdialog.ShowModal() == wxID_CANCEL)
                    return;

                long value;
                if (xdialog.GetValue().ToLong(&value) && value >= 1 && value < w)
                {
                    xval = value;
                    break;
                }
                wxMessageBox("Invalid X! Enter an integer between 1 and " +to_string(w - 1) + ". Stupid :|","Invalid Input",wxOK | wxICON_ERROR);
            }

            int yval;
            while (true)
            {   
                wxTextEntryDialog ydialog(this,"Enter Distance from the Top edge (1 to " + to_string(h - 1) + ")","Starting point (X,Y) of the top-left corner","1");
                if (ydialog.ShowModal() == wxID_CANCEL)
                {
                    return;
                }    

                long value;
                if (ydialog.GetValue().ToLong(&value) &&value >= 1 && value < h)
                {
                    yval = value;
                    break;
                }
                wxMessageBox("Invalid Y! Enter an integer between 1 and " +to_string(h - 1) + ". Stupid :|","Invalid Input", wxOK | wxICON_ERROR);
            }

            int wval;
            while (true)
            {
                wxTextEntryDialog wdialog(this,"Enter Width of the cropped area (1 to " + to_string(w - xval) + ")","Width","1");
                if (wdialog.ShowModal() == wxID_CANCEL)
                {   return;}

                long value;
                if (wdialog.GetValue().ToLong(&value) &&value >= 1 && value <= w - xval)
                {
                    wval = value;
                    break;
                }

                wxMessageBox("Invalid Width! Enter an integer between 1 and " +to_string(w - xval) + ". Stupid :|","Invalid Input",wxOK | wxICON_ERROR);
            }

            int hval;
            while (true)
            {
                wxTextEntryDialog hdialog(this,"Enter Height of the cropped area (1 to " + to_string(h - yval) + ")","Height", "1");
                if (hdialog.ShowModal() == wxID_CANCEL)
                {
                    return;
                }
                long value;
                if (hdialog.GetValue().ToLong(&value) &&value >= 1 && value <= h - yval)
                {
                    hval = value;
                    break;
                }
                wxMessageBox("Invalid Height! Enter an integer between 1 and " +to_string(h - yval) + ". Stupid :|","Invalid Input",wxOK | wxICON_ERROR);
            }

            filterCrop(currentimage, xval, yval, wval, hval);
            statustext->SetLabel("Image Loaded: " + to_string(currentimage.width) +" x " + to_string(currentimage.height));
            break;
        }

        case 10:
        filterInfrared(currentimage);
        break;

        case 11:
        filterDetectEdges(currentimage);
        break;

        case 12:
        filterPurple(currentimage);
        break;

        case 13:
        {
            wxArrayString skewdialog;
            skewdialog.Add("Horizontal Skew");
            skewdialog.Add("Vertical Skew");

            wxSingleChoiceDialog skewdialogchoice(this, "Choose skew direction", "Image skew", skewdialog);
            if(skewdialogchoice.ShowModal()==wxID_CANCEL)
            {
                return;
            }
            int skewd = skewdialogchoice.GetSelection()+1;
            filterSkew(currentimage, skewd);
        }

        case 14:
        filterTV(currentimage);
        break;

        case 15:
        {
            Image secondimage;
            string filename;

            wxFileDialog dialog(this, "Choose a Second Image :)", "", "", "Image files (*.png;*.jpg;*.jpeg;*.bmp;*.tga)|*.png;*.jpg;*.jpeg;*.bmp;*.tga", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if(dialog.ShowModal() == wxID_CANCEL)
            {
                return;
            }
            else
            {
                filename = dialog.GetPath().ToStdString();
            }

            try
            {
                secondimage.loadNewImage(filename);
            }
            catch(const std::exception& e)
            {
                wxMessageBox(e.what(), "Image Loading Error", wxOK | wxICON_ERROR, this);
            }

            filterMerge(currentimage, secondimage);
            break;
        }
        case 16:
        filterSunlight(currentimage);
        break;

        case 17:
        filterOilPainting(currentimage);
        break;

        case 18:
        filterBlur(currentimage);
        break;
    }
    updatePreview();
}

class App : public wxApp
{
    public:
    bool OnInit() override
    {
        MainFrame* frame = new MainFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);


// int main() {
//     Image currentImage;
//     string filename;
//     bool imageLoaded = false;
//     int choice = 0;

//     while (true) {
//         cout << "\n=== Image Processing Menu ===\n";
//         cout << "1. Load Image\n";
//         cout << "2. Apply Filter\n";
//         cout << "3. Save Image\n";
//         cout << "4. Exit\n";
//         cout << "Enter choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             cout << "Enter image filename to load:\n ";
//             cin >> filename;
//             try {
//                 currentImage.loadNewImage(filename);
//                 imageLoaded = true;
//                 cout << "Image loaded successfully!\n";
//             } catch (...) {
//                 cout << "Failed to load image. Please check the file path.\n";
//             }
//         } 
//         //Applying Filters
//         else if (choice == 2) {
//             if (!imageLoaded) {
//                 cout << "Please load an image first!\n";
//                 continue;
//             }
//             // Write your filter in the choices
//             cout << "\n--- Select Filter ---\n";
//             cout << "1. Grayscale\n";
//             cout << "2. Black and White\n";
//             cout << "3. Invert Colors\n";
//             cout << "4. Flip Image\n";
//             cout << "5. Rotate Image\n";
//             cout << "6. Add frame\n";
//             cout << "7. Resizing\n";
//             cout << "8. Lighten Or Darken Image\n";
//             //...
            
//             int filterChoice;
//             cin >> filterChoice;

//             switch (filterChoice) {
//             case 1: filterGrayscale(currentImage); 
//             cout << "Implemented Grayscale filter successfully!\n";
//             break;

//             case 2: filterBlackAndWhite(currentImage); 
//             cout << "Implemented Black and White filter successfully!\n";
//             break;

//             case 3: filterInvert(currentImage);
//             cout << "Implemented Invert filter successfully!\n";
//             break;

//             case 4: cout << "Choose:\n";
//                 cout << "Enter choice: "; 
//                 cout << "1. flip Horizontally\n";
//                 cout << "2. flip Vertically\n";
//                 int x; cin >> x;
//                 if (x == 1 || x == 2)
//                 {
//                     filterFlip(currentImage, x);
//                     if(x==1)
//                     {
//                         cout << "Implemented Vertical Flip filter successfully!\n";
//                     }
//                     else
//                     {
//                         cout << "Implemented Horizontal Flip filter successfully!\n";
//                     }
//                 }
//                 else
//                 {
//                     cout << "Invalid Input\n";
//                 }
//                 break;

//             case 5:
//                 int rotationChoice;

//                 cout << "Choose rotation:\n";
//                 cout << "1. 90 degrees\n";
//                 cout << "2. 180 degrees\n";
//                 cout << "3. 270 degrees\n";
//                 cout << "Enter choice: ";
//                 cin >> rotationChoice;

//                 switch (rotationChoice) {

//                 case 1:
//                     filterRotate(currentImage, 90);
//                     cout << "Implemented 90 Degree Rotation filter successfully!\n";
//                     break;

//                 case 2:
//                     filterRotate(currentImage, 180);
//                     cout << "Implemented 180 Degree Rotation filter successfully!\n";
//                     break;

//                 case 3:
//                     filterRotate(currentImage, 270);
//                     cout << "Implemented 270 Degree Rotation filter successfully!\n";
//                     break;

//                 default:
//                     cout << "Invalid rotation choice.\n";
//                     break;
//                 } 
//                 break;

//             case 6: cout << "Choose a frame style: \n";
//                 cout << "1. Red\n";
//                 cout << "2. White\n";
//                 cout << "3. Blach\n";
//                 cout << "4. Decorated\n";
//                 int f;
//                 cin >> f;
//                 if (f >= 1 && f <= 4) {
//                     filterFrame(currentImage, f);
//                     switch(f)
//                     {
//                         case 1: cout << "Implemented Red Frame successfully!\n"; break;
//                         case 2: cout << "Implemented White Frame successfully!\n"; break;
//                         case 3: cout << "Implemented Black Frame successfully!\n"; break;
//                         case 4: cout << "Implemented Decorated Frame successfully!\n"; break;
//                     }
//                 }
//                 else {
//                     cout << "Invalid choice!\n";
//                 } 
//                 break;

//             case 7: cout << "Enter new width and height: \n";
//             int newW; char xs; int newH; cin >> newW >> xs >> newH;
//                 if (newW > 0 && newH > 0) {
//                     filterResize(currentImage, newW, newH); break;
//                 }
//                 else if (newW <= 0) {
//                     cout << "Invalid width!\n";
//                 }
//                 else if (newH <= 0) {
//                     cout << "Invalid height!\n";
//                 }
//                 else {
//                     cout << "Invalid height and width!\n";
//                 }
//                 break;
//                 case 8: cout << "Choose: \n";
//                 cout << "1. Lighten the Image\n";
//                 cout << "2. Darken the Image\n";
//                 int ch; cin >> ch;
//                 if(ch == 1)
//                 {
//                     filterLighten(currentImage);
//                     cout << "Implemented Lighten filter successfully!\n";
//                 }
//                 else if(ch == 2)
//                 {
//                     filterDarken(currentImage);
//                     cout << "Implemented Darken filter successfully!\n";
//                 }
//                 else
//                 {
//                     cout << "Invalid Input!\n";
//                 }
//                 break;
//             //....
                     
//                 default: cout << "Invalid filter choice.\n";    
//             }
//         }
//         else if (choice == 3) {
//             if (!imageLoaded) {
//                 cout << "No image to save!\n";
//                 continue;
//             }
//             string saveName;
//             cout << "Enter new filename (with .jpg, .png, .bmp): ";
//             cin >> saveName;
//             while (!isValidExtension(saveName)) {
//                 cout << "Invalid extension! Must be .jpg, .jpeg, .png, or .bmp. Try again: ";
//                 cin >> saveName;
//             }
//             currentImage.saveImage(saveName);
//             cout << "Image saved successfully as " << saveName << "\n";
//         } 
//         else if (choice == 4) {
//             cout << "Exiting program...\n";
//             break;
//         } 
//         else {
//             cout << "Invalid menu choice.\n";
//         }
//     }
//     return 0;
// }