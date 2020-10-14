#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILE_NAME "Lab 9 input.txt"
#define BITS_IN_BYTE

typedef struct
{
    unsigned char is_valid : 1;
    unsigned char referenced : 1;
    uint8_t counter;
    size_t page_index;
} page_frame_t;

size_t page_frame_count;
page_frame_t *page_frames;

void print_table()
{
    printf("Page\tCounter\tR\n");

    for (size_t i = 0; i < page_frame_count; i++)
    {
        page_frame_t *frame_ptr = page_frames + i;

        if (frame_ptr->is_valid)
        {
            printf("%lu\t%hu\t%hu\n", frame_ptr->page_index, frame_ptr->counter, frame_ptr->referenced);
        }
    }
}

void reset_page_frame(size_t index)
{
    page_frame_t *frame_ptr = page_frames + index;
    frame_ptr->is_valid = 0;
}

void initialize_page_table()
{
    page_frames = (page_frame_t *)calloc(sizeof(page_frame_t), page_frame_count);

    for (size_t i = 0; i < page_frame_count; i++)
    {
        reset_page_frame(i);
    }
}

void free_page_table()
{
    free(page_frames);
}

int is_in_page_table(size_t page_index, size_t *frame_index)
{
    for (size_t i = 0; i < page_frame_count; i++)
    {
        page_frame_t *frame_ptr = page_frames + i;

        if (frame_ptr->is_valid && frame_ptr->page_index == page_index)
        {
            *frame_index = i;
            return 1;
        }
    }

    return 0;
}

int exists_empty_frame(size_t *empty_frame_index)
{
    for (size_t i = 0; i < page_frame_count; i++)
    {
        if (!page_frames[i].is_valid)
        {
            *empty_frame_index = i;
            return 1;
        }
    }

    return 0;
}

void load_page_to_frame(size_t page_index, size_t frame_index)
{
    page_frame_t *frame_ptr = page_frames + frame_index;

    frame_ptr->is_valid = 1;
    frame_ptr->page_index = page_index;
    frame_ptr->referenced = 0;
    frame_ptr->counter = 0;
}

size_t unload_not_frequently_used_frame()
{
    uint8_t min_counter = page_frames[0].counter;
    size_t min_counter_index = 0;

    for (size_t i = 1; i < page_frame_count; i++)
    {
        page_frame_t *frame_ptr = page_frames + i;

        if (frame_ptr->is_valid && frame_ptr->counter < min_counter)
        {
            min_counter = frame_ptr->counter;
            min_counter_index = i;
        }
    }

    reset_page_frame(min_counter_index);

    return min_counter_index;
}

void reference_page_frame(size_t frame_index)
{
    page_frames[frame_index].referenced = 1;
}

void access_page(size_t page_index, size_t *hits_ptr, size_t *misses_ptr)
{
    size_t frame_index;

    if (is_in_page_table(page_index, &frame_index))
    {
        (*hits_ptr)++;
    }
    else
    {
        (*misses_ptr)++;

        if (!exists_empty_frame(&frame_index))
        {
            frame_index = unload_not_frequently_used_frame();
        }

        load_page_to_frame(page_index, frame_index);
    }

    reference_page_frame(frame_index);
}

void age()
{
    for (size_t i = 0; i < page_frame_count; i++)
    {
        page_frame_t *frame_ptr = page_frames + i;

        if (frame_ptr->is_valid)
        {
            frame_ptr->counter >>= 1;
            size_t shift_amount = sizeof(frame_ptr->counter) * (BITS_IN_BYTE - 1);
            frame_ptr->counter += frame_ptr->referenced * shift_amount;
            frame_ptr->referenced = 0;
        }
    }
}

int main(int argc, char **argv)
{
    sscanf(argv[1], "%lu", &page_frame_count);
    initialize_page_table();

    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL)
    {
        printf("File '%s' does not exist.\n", FILE_NAME);
        free_page_table();
        return -1;
    }

    size_t page_index, hits = 0, misses = 0;

    while (fscanf(file, "%lu", &page_index) != EOF)
    {
        access_page(page_index, &hits, &misses);
        age();
    }

    printf("%lu hits/%lu misses. Hit ratio is %f.\n", hits, misses, (float)hits / (hits + misses));
    // 12 hits/991 misses for a table of size 10
    // 53 hits/950 misses for a table of size 50
    // 95 hits/908 misses for a table of size 100

    free_page_table();
    fclose(file);

    return 0;
}