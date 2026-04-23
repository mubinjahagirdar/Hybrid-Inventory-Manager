#include "inventory.h"
#include <stdio.h>
#include <string.h>

const char* FILE_NAME = "inventory.dat";

// Helper to open file, creates it if not exists
static FILE* open_file(const char* mode) {
    FILE* fp = fopen(FILE_NAME, mode);
    if (!fp && (strcmp(mode, "rb+") == 0 || strcmp(mode, "ab+") == 0)) {
        fp = fopen(FILE_NAME, "wb+");
    }
    return fp;
}

int add_item(const Item item) {
    FILE* fp = open_file("rb+");
    if (!fp) return 0;
    
    // Check for duplicate ID
    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp) == 1) {
        if (temp.id == item.id && temp.is_deleted == 0) {
            fclose(fp);
            return 0; // Duplicate ID
        }
    }
    
    // Append at the end
    fseek(fp, 0, SEEK_END);
    int written = fwrite(&item, sizeof(Item), 1, fp);
    fclose(fp);
    return written == 1 ? 1 : 0;
}

int get_item(int id, Item* out) {
    if (!out) return 0;
    FILE* fp = open_file("rb");
    if (!fp) return 0;
    
    Item temp;
    while (fread(&temp, sizeof(Item), 1, fp) == 1) {
        if (temp.id == id && temp.is_deleted == 0) {
            *out = temp;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int update_item(int id, const Item updated) {
    FILE* fp = open_file("rb+");
    if (!fp) return 0;
    
    Item temp;
    long pos = 0;
    while (fread(&temp, sizeof(Item), 1, fp) == 1) {
        if (temp.id == id && temp.is_deleted == 0) {
            fseek(fp, pos, SEEK_SET);
            int written = fwrite(&updated, sizeof(Item), 1, fp);
            fclose(fp);
            return written == 1 ? 1 : 0;
        }
        pos = ftell(fp);
    }
    fclose(fp);
    return 0;
}

int delete_item(int id) {
    FILE* fp = open_file("rb+");
    if (!fp) return 0;
    
    Item temp;
    long pos = 0;
    while (fread(&temp, sizeof(Item), 1, fp) == 1) {
        if (temp.id == id && temp.is_deleted == 0) {
            temp.is_deleted = 1; // Mark as deleted
            fseek(fp, pos, SEEK_SET);
            int written = fwrite(&temp, sizeof(Item), 1, fp);
            fclose(fp);
            return written == 1 ? 1 : 0;
        }
        pos = ftell(fp);
    }
    fclose(fp);
    return 0;
}

int list_items(Item* buffer, int max_items) {
    if (!buffer) return 0;
    FILE* fp = open_file("rb");
    if (!fp) return 0;
    
    Item temp;
    int count = 0;
    while (fread(&temp, sizeof(Item), 1, fp) == 1 && count < max_items) {
        if (temp.is_deleted == 0) {
            buffer[count++] = temp;
        }
    }
    fclose(fp);
    return count;
}
