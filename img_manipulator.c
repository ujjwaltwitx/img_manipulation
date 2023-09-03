#include <MagickWand/MagickWand.h>
#include <string.h>

// void input_selector();
void readImage(char* nextFileName);
void crop(size_t height, size_t width, ssize_t x_offset, ssize_t y_offset);
void rotate(double degrees);
void writeImage(char* name);
void executeOperation(char* functionName);
char* generateRandomName(char* originalName);

// declaration of global variables
MagickWand* mw;
char* extName;
// char* generatedName;

int main(int argc, char* argv[]){
    MagickWandGenesis();
    mw = NewMagickWand();
    if(argc == 1){
        printf("No arguments passed");
        return 0;
    }
    else if(argc == 2){
        printf("No operation specified");
    }
    else{
        readImage(argv[1]);
        for(int i = 2; i<argc; i++){
            executeOperation(argv[i]);
        }
        char* generatedName = generateRandomName(argv[1]);
        // printf("%s", generatedName);
        MagickWriteImage(mw, generatedName);
    }
    
    MagickWandTerminus();
    return 0;
}


void executeOperation(char functionName[]){
    if(strcmp(functionName, "-c") == 0 || strcmp(functionName, "-convert") == 0){
        extName = (char*)malloc(4*sizeof(char));
        printf("Enter the extension you want to convert your image to : ");
        scanf("%255s", extName);
    }
    else if(strcmp(functionName, "-r") == 0 || strcmp(functionName, "-rotate") == 0){
        double degrees;
        printf("Enter the no. of degrees you want to rotate the image : ");
        scanf("%lf", &degrees);
        rotate(degrees);
    }
    else if(strcmp(functionName, "-cr") == 0 || strcmp(functionName, "-crop") == 0){
        size_t height, width;
        ssize_t x_offset, y_offset;
        printf("Enter height width x_offset y_offset in order : ");
        scanf("%zd %zd %zd %zd", &height, &width, &x_offset, &y_offset);
        crop(height, width, x_offset, y_offset);
    }else{
        printf("Unable to parse the specified operation");
    }

    return;
}

char* generateRandomName(char* originalName){
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* generatedName = (char*)malloc(6*sizeof(char));
    srand(time(NULL));
    for(int i = 0; i<5; i++){
        generatedName[i] = charset[rand() % (strlen(charset) - 1)];
    }
    if(extName == NULL){
        char* position = strchr(originalName, '.');
        if(position == NULL){
            printf("Enter a valid file name");
        }
        strcat(generatedName, position);
    }
    else{
        strcat(generatedName, ".");
        strcat(generatedName, extName);
    }
    return generatedName;
}


void readImage(char* nextFileName){
    MagickReadImage(mw, nextFileName);
    return;
}


void crop(size_t height, size_t width, ssize_t x_offset, ssize_t y_offset){
    MagickCropImage(mw, width, height, x_offset, y_offset);
    return;
    
}

void rotate(double degrees){
    PixelWand *pWand = NewPixelWand();
    PixelSetColor(pWand, "white"); 
    MagickRotateImage(mw, pWand, degrees);
}

void writeImage(char* name){
    MagickWriteImage(mw, name);
}
