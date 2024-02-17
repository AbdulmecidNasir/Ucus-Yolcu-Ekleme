#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kişi veri yapısı
struct Person {
    char name[50];
    int seatNumber;
    char flightFrom[50];
    char flightTo[50];
    struct Person* next;
};

// Bağlantı listesi yapısı
struct LinkedList {
    struct Person* head;
};

// Bağlantı listesi fonksiyonları
struct LinkedList* createLinkedList();
void insertAtHead(struct LinkedList* list, struct Person* person);
void deleteFromHead(struct LinkedList* list);
void printLinkedList(struct LinkedList* list);
void seePassengerCountOnFlight(struct LinkedList* list);

// Diğer işlevler
void addPersonToFlight(struct LinkedList* list);
void deletePersonFromFlight(struct LinkedList* list);
void deletePersonFromHeadOfFlight(struct LinkedList* list);
void listAllPassengersOnFlight(struct LinkedList* list);
void seeAllFlights(struct LinkedList* list);
void quit(struct LinkedList* list);

int main() {
    struct LinkedList* passengerList = createLinkedList();

    char choice;

    do {
        printf("              MENU                 ");
        printf("\nEnter 'A' to add a person to a flight\n");
        printf("Enter 'D' to delete a person from a flight\n");
        printf("Enter 'H' to delete a person from the head of a flight\n");
        printf("Enter 'L' to list all passengers on a flight\n");
        printf("Enter 'I' to see how many passengers are on a flight\n");
        printf("Enter 'S' to see all flights\n");
        printf("Enter 'Q' to quit\n");

        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a':
                addPersonToFlight(passengerList);
                break;
            case 'D':
            case 'd':
                deletePersonFromFlight(passengerList);
                break;
            case 'H':
            case 'h':
                deletePersonFromHeadOfFlight(passengerList);
                break;
            case 'L':
            case 'l':
                listAllPassengersOnFlight(passengerList);
                break;
            case 'I':
            case 'i':
                seePassengerCountOnFlight(passengerList);
                break;
            case 'S':
            case 's':
                seeAllFlights(passengerList);
                break;
            case 'Q':
            case 'q':
                quit(passengerList);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 'Q' && choice != 'q');

    return 0;
}

// Bağlantı listesi fonksiyonları
struct LinkedList* createLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

void insertAtHead(struct LinkedList* list, struct Person* person) {
    person->next = list->head;
    list->head = person;
}

void deleteFromHead(struct LinkedList* list) {
    if (list->head != NULL) {
        struct Person* temp = list->head;
        list->head = temp->next;
        free(temp);
    }
}

void printLinkedList(struct LinkedList* list) {
    struct Person* current = list->head;

    if (current == NULL) {
        printf("The flight is empty.\n");
        return;
    }

    printf("Passengers on the flight:\n");

    while (current != NULL) {
        printf("%s - Seat %d - Flight from %s to %s\n", current->name, current->seatNumber, current->flightFrom, current->flightTo);
        current = current->next;
    }
}

void seePassengerCountOnFlight(struct LinkedList* list) {
    int count = 0;
    struct Person* current = list->head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    printf("Number of passengers on the flight: %d\n", count);
}

// Diğer işlevler
void addPersonToFlight(struct LinkedList* list) {
    struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));

    printf("Enter the name of the pessanger: ");
    scanf("%s", newPerson->name);
    printf("Enter the seat number: ");
    scanf("%d", &(newPerson->seatNumber));
    printf("Enter the flight from: ");
    scanf("%s", newPerson->flightFrom);
    printf("Enter the flight to: ");
    scanf("%s", newPerson->flightTo);

    insertAtHead(list, newPerson);

    printf("Person added to the flight.\n");
}

void deletePersonFromFlight(struct LinkedList* list) {
    if (list->head != NULL) {
        printf("Enter the name of the person to delete: ");
        char nameToDelete[50];
        scanf("%s", nameToDelete);

        struct Person* current = list->head;
        struct Person* prev = NULL;

        while (current != NULL && strcmp(current->name, nameToDelete) != 0) {
            prev = current;
            current = current->next;
        }

        if (current != NULL) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                // If the person to delete is at the head
                list->head = current->next;
            }

            free(current);
            printf("Person '%s' removed from the flight.\n", nameToDelete);
        } else {
            printf("Person '%s' not found on the flight.\n", nameToDelete);
        }
    } else {
        printf("The flight is empty.\n");
    }
}

void deletePersonFromHeadOfFlight(struct LinkedList* list) {
    if (list->head != NULL) {
        struct Person* removedPerson = list->head;
        list->head = removedPerson->next;
        free(removedPerson);
        printf("Person at the head of the flight removed.\n");
    } else {
        printf("The flight is empty.\n");
    }
}

void listAllPassengersOnFlight(struct LinkedList* list) {
    printLinkedList(list);
}

void seeAllFlights(struct LinkedList* list) {
    struct Person* current = list->head;

    if (current == NULL) {
        printf("No flights available.\n");
        return;
    }

    printf("All flights:\n");

    while (current != NULL) {
        printf("Flight from %s to %s\n", current->flightFrom, current->flightTo);
        current = current->next;
    }
}

void quit(struct LinkedList* list) {
    // Implement quit
}
