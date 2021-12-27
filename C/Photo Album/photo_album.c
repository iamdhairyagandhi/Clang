#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include "photo_album.h"
#include "my_memory_checker_216.h"

Photo* create_photo(int id, const char* description);
void print_photo(Photo* photo);
void destroy_photo(Photo* photo);
void initialize_album(Album* album);
void print_album(const Album* album);
void destroy_album(Album* album);
void add_photo_to_album(Album* album, int id, const char* description);


Photo* create_photo(int id, const char* description) {
    Photo* photo = malloc(sizeof(Photo));
    if (photo == NULL) {
        return NULL;
    }
    photo->id = id;
    if (description != NULL) {
        photo->description = malloc(strlen(description) * sizeof(char) + 1);
        if (photo->description == NULL) {
            return NULL;
        }
        strcpy(photo->description, description);


    }
    else {
        photo->description = NULL;
    }
    return photo;
}
void print_photo(Photo* photo) {
    if (photo != NULL) {
        if (photo->description != NULL) {
            printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);
        }
        else {
            printf("Photo Id: %d, Description: None\n", photo->id);
        }
    }
    else {
        return;
    }
}
void destroy_photo(Photo* photo) {
    if (photo != NULL) {
        free(photo->description);
        free(photo);
    }
}
void initialize_album(Album* album) {
    if (album != NULL) {
        album->size = 0;
    }
    else {
        return;
    }
}
void print_album(const Album* album) {
    int i = 0;
    if (album == NULL) {
        return;
    }
    if (album->size == 0) {
        printf("Album has no photos.\n");
        return;
    }
    else {
        for (i = 0;i < album->size; i++) {
            print_photo(album->all_photos[i]);
        }
    }
}
void add_photo_to_album(Album* album, int id, const char* description) {

    if (album == NULL || album->size >= MAX_ALBUM_SIZE) {
        return;
    }
    if (album != NULL) {
        if (album->size < MAX_ALBUM_SIZE) {
            album->all_photos[album->size] = create_photo(id, description);;
            album->size++;
        }
    }
}

void destroy_album(Album* album) {
    int i = 0;
    if (album == NULL || album->size == 0) {
        return;
    }
    else {
        for (i = 0;i < album->size; i++) {
            destroy_photo(album->all_photos[i]);
        }
        album->size = 0;
    }
}