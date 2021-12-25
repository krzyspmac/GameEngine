//
//  main.c
//  SheetExtractor
//
//  Created by krzysp on 25/12/2021.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "cJSON.h"

static char *sheetTexture;
static char *sheetJson;
static char *outFolder;

static void handleCommandLine(int argc, char *argv[])
{
    int i;

    for (i = 0 ; i < argc ; i++)
    {
        if (strcmp(argv[i], "-inTexture") == 0)
        {
            sheetTexture = argv[i + 1];
        }
        else if (strcmp(argv[i], "-inJson") == 0)
        {
            sheetJson = argv[i + 1];
        }
        else if (strcmp(argv[i], "-outFolder") == 0)
        {
            outFolder = argv[i + 1];
        }
    }
}

char *readFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        void *memory = malloc(size + 1);
        fread(memory, size, 1, fp);

        fclose(fp);
        return memory;
    }
    else
    {
        return NULL;
    }
}

int main(int argc, const char * argv[]) {
    handleCommandLine(argc, argv);

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    cJSON *rootJSON, *frames, *node;
    char *jsonText = readFile(sheetJson);

    rootJSON = cJSON_Parse(jsonText);
    frames = cJSON_GetObjectItem(rootJSON, "frames");

    char *separator = "/";
    char *pngExtension = ".png";

    SDL_Surface *texture = IMG_Load(sheetTexture);

    for (node = frames->child ; node != NULL ; node = node->next)
    {
        char *nodeName = node->string;
        cJSON *frame = cJSON_GetObjectItem(node, "frame");
        int x = cJSON_GetObjectItem(frame, "x")->valueint;
        int y = cJSON_GetObjectItem(frame, "y")->valueint;
        int w = cJSON_GetObjectItem(frame, "w")->valueint;
        int h = cJSON_GetObjectItem(frame, "h")->valueint;

        SDL_Surface *imageSurface = SDL_CreateRGBSurface(0, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        SDL_Rect srcRect;
        SDL_Rect dstRect;

        srcRect.x = x;
        srcRect.y = y;
        srcRect.w = w;
        srcRect.h = h;

        dstRect.x = 0;
        dstRect.y = 0;
        dstRect.w = w;
        dstRect.h = h;

        SDL_BlitSurface(texture, &srcRect, imageSurface, &dstRect);

        char *targetFile = (char*)malloc(strlen(outFolder) + strlen(nodeName) + strlen(separator) + strlen(pngExtension));
        strcpy(targetFile, outFolder);
        strcat(targetFile, separator);
        strcat(targetFile, nodeName);
        strcat(targetFile, pngExtension);

        IMG_SavePNG(imageSurface, targetFile);

        SDL_FreeSurface(imageSurface);

        free(targetFile);
    }

    SDL_Quit();

    cJSON_Delete(rootJSON);
    free(jsonText);
    SDL_FreeSurface(texture);

    return 0;
}
