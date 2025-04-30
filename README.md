# Student Management System (File-Based) – C++ Assignment

## Description

This is a C++ assignment that implements a simple **Student Management System** using file handling. The program allows you to:

- Add new student records, including courses and grades.
- Calculate CGPA and GPA per semester.
- View complete or year-specific grade reports.
- Store all student data in a text file (`student.txt`) using file streams.

The main logic is implemented in `assignment.cpp`. The data is stored and retrieved from `student.txt`.

## Features

- **Add New Student Record**: Inputs student details and course info, calculates grades, and saves data to file.
- **Full Grade Report**: Displays all recorded data for a student.
- **Semester Report**: Shows grades for a specific academic year.
- **File Storage**: Uses `fstream` to write/read structured data from `student.txt`.

## Notes

- Assumes 7 courses per semester for up to 4 years (max 56 courses).
- GPA/CGPA are computed based on grade values.
- File entries are separated by `*` for clarity.

## How to Use

Run the program and follow the on-screen menu to:
1. Add a new student.
2. View full report.
3. View semester report.

