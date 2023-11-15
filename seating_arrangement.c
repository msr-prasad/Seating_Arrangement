#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Student {
    int roll_number;
    char name[50];
    int room_number;
    int seat_number;
    struct Student* next;
} Student;

typedef struct Room {
    int room_number;
    int seats_per_room;
    struct Student* seating_list;
} Room;

Student* students = NULL;
int num_students = 0;
Room* rooms = NULL;
int num_rooms = 0;

int compareStudentsByName(const void* a, const void* b) {
    return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

int compareStudentsByRoll(const void* a, const void* b) {
    return ((Student*)a)->roll_number - ((Student*)b)->roll_number;
}

void initializeStudentsFromFile(const char* student_dataset) {
    FILE* file = fopen(student_dataset, "r");
    if (file == NULL) {
        printf("Failed to open the student data file.\n");
        exit(1);
    }

    int student_count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        student_count++;
    }

    students = (Student*)malloc(student_count * sizeof(Student));
    num_students = student_count;

    rewind(file);

    Student* current_student = NULL;
    for (int i = 0; i < num_students; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading student data from the file.\n");
            exit(1);
        }
        sscanf(line, "%d %49[^\n]", &students[i].roll_number, students[i].name);
        students[i].room_number = 0;
        students[i].seat_number = 0;
        students[i].next = NULL;

        if (current_student != NULL) {
            current_student->next = &students[i];
        }
        current_student = &students[i];
    }

    fclose(file);
}

void initializeRooms(int n_rooms, int seats_per_room) {
    num_rooms = n_rooms;

    rooms = (Room*)malloc(num_rooms * sizeof(Room));

    for (int i = 0; i < num_rooms; i++) {
        rooms[i].room_number = i + 1;
        rooms[i].seats_per_room = seats_per_room;
        rooms[i].seating_list = NULL;
    }
}

int isSeatOccupied(Room room, int seat_number) {
    Student* current_student = room.seating_list;
    while (current_student != NULL) {
        if (current_student->seat_number == seat_number) {
            return 1; // Seat is occupied
        }
        current_student = current_student->next;
    }
    return 0; // Seat is unoccupied
}

void assignSeatsRandomly() {
    printf("Assigning seats to students randomly...\n");

    // Shuffle the students randomly
    for (int i = num_students - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap students[i] and students[j]
        Student temp = students[i];
        students[i] = students[j];
        students[j] = temp;
    }

    // Assign seats based on the shuffled order
    int student_index = 0;
    for (int room = 0; room < num_rooms; room++) {
        rooms[room].seating_list = NULL; // Reset the seating list for the room
        Student* last_student = NULL;
        for (int seat = 1; seat <= rooms[room].seats_per_room; seat++) {
            if (student_index < num_students) {
                students[student_index].room_number = room + 1;
                students[student_index].seat_number = seat;
                students[student_index].next = NULL;

                if (last_student != NULL) {
                    last_student->next = &students[student_index];
                } else {
                    rooms[room].seating_list = &students[student_index];
                }

                last_student = &students[student_index];
                student_index++;
            } else {
                break;
            }
        }
        if (student_index >= num_students) {
            break;
        }
    }
}


void assignSeatsAlphabetically() {
    printf("Assigning seats to students alphabetically...\n");

    qsort(students, num_students, sizeof(Student), compareStudentsByName);

    // Assign seats based on the sorted order
    int student_index = 0;
    for (int room = 0; room < num_rooms; room++) {
        rooms[room].seating_list = NULL; // Reset the seating list for the room
        Student* last_student = NULL;
        for (int seat = 1; seat <= rooms[room].seats_per_room; seat++) {
            if (student_index < num_students) {
                students[student_index].room_number = room + 1;
                students[student_index].seat_number = seat;
                students[student_index].next = NULL;

                if (last_student != NULL) {
                    last_student->next = &students[student_index];
                } else {
                    rooms[room].seating_list = &students[student_index];
                }

                last_student = &students[student_index];
                student_index++;
            } else {
                break;
            }
        }
        if (student_index >= num_students) {
            break;
        }
    }
}

void assignSeatsByRollNumber() {
    printf("Assigning seats to students based on roll number...\n");

    // Sort students based on roll number
    qsort(students, num_students, sizeof(Student), compareStudentsByRoll);

    // Assign seats based on the sorted order
    int student_index = 0;
    for (int room = 0; room < num_rooms; room++) {
        rooms[room].seating_list = NULL; // Reset the seating list for the room
        Student* last_student = NULL;
        for (int seat = 1; seat <= rooms[room].seats_per_room; seat++) {
            if (student_index < num_students) {
                students[student_index].room_number = room + 1;
                students[student_index].seat_number = seat;
                students[student_index].next = NULL;

                if (last_student != NULL) {
                    last_student->next = &students[student_index];
                } else {
                    rooms[room].seating_list = &students[student_index];
                }

                last_student = &students[student_index];
                student_index++;
            } else {
                break;
            }
        }
        if (student_index >= num_students) {
            break;
        }
    }
}


void displayStudentByRollAndName(int roll_number, const char* name) {
    Student* current_student = students;
    while (current_student != NULL) {
        if (current_student->roll_number == roll_number && strcmp(current_student->name, name) == 0) {
            printf("Student found: Roll Number: %d, Name: %s, Room: %d, Seat: %d\n",
                   current_student->roll_number, current_student->name,
                   current_student->room_number, current_student->seat_number);
            return;
        }
        current_student = current_student->next;
    }
    printf("Student not found with Roll Number: %d and Name: %s\n", roll_number, name);
}

void generateTotalReport() {
    printf("Total Seating Arrangement Report:\n");
    for (int room = 0; room < num_rooms; room++) {
        printf("Room %d:\n", rooms[room].room_number);
        Student* current_student = rooms[room].seating_list;
        for (int seat = 1; seat <= rooms[room].seats_per_room; seat++) {
            if (current_student != NULL && current_student->seat_number == seat) {
                printf("Seat Number %d: Occupied by Student with Roll Number %d, Name: %s\n",
                       seat, current_student->roll_number, current_student->name);
                current_student = current_student->next;
            } else {
                printf("Seat Number %d: Unoccupied\n", seat);
            }
        }
    }

    FILE* report_file = fopen("seating_report.csv", "w");
    if (report_file == NULL) {
        printf("Failed to open the report file for writing.\n");
    } else {
        fprintf(report_file, "Total Seating Arrangement Report:\n");
        for (int room = 0; room < num_rooms; room++) {
            fprintf(report_file, "Room %d:\n", rooms[room].room_number);
            Student* current_student = rooms[room].seating_list;
            for (int seat = 1; seat <= rooms[room].seats_per_room; seat++) {
                if (current_student != NULL && current_student->seat_number == seat) {
                    fprintf(report_file, "Seat Number %d: Occupied by Student with Roll Number %d, Name: %s\n",
                           seat, current_student->roll_number, current_student->name);
                    current_student = current_student->next;
                } else {
                    fprintf(report_file, "Seat Number %d: Unoccupied\n", seat);
                }
            }
        }
        fclose(report_file);
        printf("The report has been saved to 'seating_report.csv'.\n");
    }
}

int main() {
    srand(time(NULL));

    initializeStudentsFromFile("student_dataset.txt");

    int n_rooms, seats_per_room;
    printf("Enter the number of rooms: ");
    scanf("%d", &n_rooms);
    printf("Enter the number of seats per room: ");
    scanf("%d", &seats_per_room);

    initializeRooms(n_rooms, seats_per_room);

    int choice;
    int roll_number;
    char name[50];

    do {
        printf("\n***WELCOME TO PESU SEATING ARRANGEMENT***\n");
        printf("-------------------------------------------\n");
        printf("1. Assign Seats Randomly\n");
        printf("2. Assign Seats Alphabetically\n");
        printf("3. Assign seats to the students based on Roll number\n");
        printf("4. Search for a student by Roll Number and Name\n");
        printf("5. Generate Total Report and Save to File\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                assignSeatsRandomly();
                break;

            case 2:
                assignSeatsAlphabetically();
                break;
            
            case 3:
                assignSeatsByRollNumber();
                break;

            case 4:
                printf("Enter the student's roll number: ");
                scanf("%d", &roll_number);
                printf("Enter the student's name: ");
                scanf(" %49[^\n]", name);
                displayStudentByRollAndName(roll_number, name);
                break;

            case 5:
                generateTotalReport();
                break;

            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 5);

    free(students);

    for (int i = 0; i < num_rooms; i++) {
        Student* current_student = rooms[i].seating_list;
        while (current_student != NULL) {
            Student* next_student = current_student->next;
            free(current_student);
            current_student = next_student;
        }
    }
    free(rooms);

    return 0;
}
