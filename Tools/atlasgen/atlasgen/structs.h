/*
 * Copyright (C) 2021 Parallel Realities
*/

typedef struct Node Node;
typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct AtlasImage AtlasImage;

struct Node {
	int x;
	int y;
	int w;
	int h;
	int used;

	struct Node *child;
};

typedef struct {
	char *filename;
	SDL_Surface *surface;
} Image;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct AtlasImage {
	char filename[MAX_FILENAME_LENGTH];
	SDL_Rect rect;
	int rotated;
	SDL_Texture *texture;
	AtlasImage *next;
};

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
} App;

