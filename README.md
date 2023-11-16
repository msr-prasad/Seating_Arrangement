PROJECT:Seating Arraangement for Examinations

Problem Statement:
PES University is organizing a large-scale event and needs to efficiently arrange seating for the registered students. The event will take place in multiple rooms, and each room has a specified number of seats. The goal is to implement a program that manages the seating arrangement for students based on different criteria.

Synopsis:
This C program manages the seating arrangement for students at PES University.
The program uses a data structure to represent students and rooms.
It reads student data from a file, initializes room information, and provides options to assign seats randomly, alphabetically by name, or based on roll numbers. 
Users can also search for a student by roll number and name, generate a total seating arrangement report, and save it to a CSV file. 
The main loop allows users to interact with these functionalities until choosing to exit the program.
The code includes functions for initializing data, assigning seats, searching for students, and generating reports.


Features:
          1.Initialize Student Data:
          Read student data from a file ("student_dataset.txt") containing information about each student, including roll number and name.
          Create a linked list of students.
          
          2.Initialize Rooms:
          Accept the number of rooms and the number of seats per room as input.
          Create an array of rooms, each with a unique room number and specified seats per room.
          
          3.Assign Seats Randomly:
          Shuffle the list of students randomly.
          Assign seats to students in each room based on the shuffled order.
          Ensure no seat is assigned to more than one student.
          
          4.Assign Seats Alphabetically:
          Sort the list of students alphabetically by name.
          Assign seats to students in each room based on the sorted order.
          Ensure no seat is assigned to more than one student.
          
          5.Assign Seats by Roll Number:
          Sort the list of students based on their roll numbers.
          Assign seats to students in each room based on the sorted order of roll numbers.
          Ensure no seat is assigned to more than one student.
          
          6.Search for a Student:
          Allow the user to search for a student by providing the roll number and name.
          Display the student's assigned room and seat number.
          
          7.Generate Total Seating Arrangement Report:
          Display the seating arrangement for each room, indicating whether each seat is occupied or unoccupied.
          Save the seating arrangement report to a CSV file named "seating_report.csv."
          
          8.Exit Program:
          Allow the user to exit the program.

          
Data Structures used are:

1.Structrues
2.Arrays
3.Linked list





