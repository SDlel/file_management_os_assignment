# File Management System - Operating Systems Assignment

**Shaurya Dixit (USN: 1DS25CG046)**  
Subject: Operating Systems  
Submitted to: Prof. Nayana Shinde

## Overview

This repository contains a menu-driven File Management System implemented in C using Linux system calls. The program simulates basic file management operations performed by an operating system: creating files, writing to files, reading file contents, appending data, copying files, renaming files, deleting files, and changing file permissions.

Each operation uses low-level Linux system calls such as `open()`, `read()`, `write()`, `close()`, `unlink()`, `rename()`, `stat()`, and `chmod()`, giving a hands-on demonstration of how an operating system interacts with the file system at the kernel level.

## How to Build and Run

```bash
gcc file_mgmt.c -o file_mgmt
./file_mgmt        # Linux / macOS
file_mgmt.exe      # Windows (MinGW)
```

## Menu Options

| Choice | Operation | System Calls Used |
|--------|-----------|-------------------|
| 1 | Create File | `open()` with `O_CREAT \| O_EXCL \| O_WRONLY` |
| 2 | Write to File | `open()`, `write()`, `stat()` |
| 3 | Read File | `open()`, `read()` |
| 4 | Append to File | `open()` with `O_APPEND`, `write()`, `stat()` |
| 5 | Copy File | `open()`, `read()`, `write()` |
| 6 | Rename File | `rename()` |
| 7 | Delete File | `unlink()` |
| 8 | Change Permissions | `chmod()` |
| 9 | Exit | — |

## Files

- `file_mgmt.c` — complete C source code (comment-free)
- `report.pdf` — full assignment report (theory, design, code snippets, screenshots, viva Q&A)
- `screenshots/` — terminal screenshots of all 8 operations

## Report Contents

1. Introduction to File Management in Operating Systems
2. Linux System Calls Used (`open`, `read`, `write`, `close`, `unlink`, `rename`, `stat`, `chmod`)
3. Program Design and Implementation (with code snippets)
4. How the OS Manages File Creation, Reading, Writing, and Deletion
5. File Attributes Maintained by the OS
6. File Allocation Methods (Contiguous, Linked, Indexed)
7. Free Disk Space Management (Bitmap, Linked List)
8. File Permissions and Security
9. Program Outputs and Screenshots (all operations)
10. Part C: Application and Analysis (file size, chmod, error handling, limitations)
11. Likely Viva Questions and Answers
12. Conclusion

## Sample Output

```
====== File Management System ======
1. Create File
2. Write to File
3. Read File
4. Append to File
5. Copy File
6. Rename File
7. Delete File
8. Change Permissions (chmod)
9. Exit
Enter your choice: 2

--- Write to File ---
Enter file name: notes.txt
Enter text content (single line): Welcome to the File Management System demo.
Written 43 bytes to 'notes.txt'.
File size after write: 43 bytes
```
