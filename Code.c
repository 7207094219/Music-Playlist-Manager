#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a song node
struct Song {
    char title[100];
    struct Song* prev;
    struct Song* next;
};

struct Song* head = NULL;
struct Song* tail = NULL;
struct Song* current = NULL;

// Create new song node
struct Song* createSong(char title[]) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->title, title);
    newSong->prev = NULL;
    newSong->next = NULL;
    return newSong;
}

// Add song to playlist
void addSong(char title[]) {
    struct Song* newSong = createSong(title);

    if (head == NULL) {
        head = tail = current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    printf("Song added: %s\n", title);
}

// Display playlist forward
void displayForward() {
    struct Song* temp = head;
    printf("\nPlaylist (Forward):\n");

    while (temp != NULL) {
        printf("%s\n", temp->title);
        temp = temp->next;
    }
}

// Display playlist reverse
void displayReverse() {
    struct Song* temp = tail;
    printf("\nPlaylist (Reverse):\n");

    while (temp != NULL) {
        printf("%s\n", temp->title);
        temp = temp->prev;
    }
}

// Delete a song
void deleteSong(char title[]) {
    struct Song* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {

            // If head node
            if (temp == head) {
                head = temp->next;
                if (head != NULL)
                    head->prev = NULL;
            }

            // If tail node
            else if (temp == tail) {
                tail = temp->prev;
                tail->next = NULL;
            }

            // Middle node
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            printf("Deleted: %s\n", title);
            free(temp);
            return;
        }
        temp = temp->next;
    }

    printf("Song not found!\n");
}

// Search song
void searchSong(char title[]) {
    struct Song* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("Song found: %s\n", title);
            return;
        }
        temp = temp->next;
    }

    printf("Song not found!\n");
}

// Play next song
void playNext() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        printf("Now playing: %s\n", current->title);
    } else {
        printf("No next song!\n");
    }
}

// Play previous song
void playPrevious() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        printf("Now playing: %s\n", current->title);
    } else {
        printf("No previous song!\n");
    }
}

// Main menu
int main() {
    int choice;
    char title[100];

    while (1) {
        printf("\n--- Music Playlist Manager ---\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Display Playlist Forward\n");
        printf("4. Display Playlist Reverse\n");
        printf("5. Search Song\n");
        printf("6. Play Next\n");
        printf("7. Play Previous\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                addSong(title);
                break;

            case 2:
                printf("Enter song title to delete: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                deleteSong(title);
                break;

            case 3:
                displayForward();
                break;

            case 4:
                displayReverse();
                break;

            case 5:
                printf("Enter song title to search: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                searchSong(title);
                break;

            case 6:
                playNext();
                break;

            case 7:
                playPrevious();
                break;

            case 8:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
