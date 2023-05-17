# Array Manipulation and Simulations

This repository contains a C program developed as an assignment for the "Programmieren 1" course in the Technical Computer Science program at the Augsburg University of Applied Sciences. The program is composed of various tasks, such as performing operations on arrays (finding minimum, maximum, and mean values, printing array elements, summing array elements), simulating dice rolls, and a coin machine simulation.

## Project Structure

The project is structured as follows:

- `main.c`: This file includes all other necessary files and starts the menu for task selection.
- `aufgaben.h`: This header file contains the definitions for the tasks performed by the program.
- `utilities.h` and `utilities.c`: These files contain utility functions for the project, including functions for reading from the console with additional control over input. The utilities also include a menu for task selection, implemented using the `ncurses` library.

## Code Improvements and User Interface Enhancement

This project began as a straightforward assignment with simple solutions. However, with the passage of time and increased experience in C programming, I decided to revisit and refine the code. These enhancements, though not part of the original assignment, were introduced as a personal initiative to improve code quality, learn new concepts, and make the program more user-friendly.

A significant upgrade has been the integration of the `ncurses` library, which has transformed the program's user interface. The terminal menu is now more interactive and user-friendly, providing a more engaging experience when selecting tasks.

## Compilation and Execution

To compile and run the program, follow these steps:

1. Make sure you have a C compiler installed (e.g., gcc).
2. Ensure the `ncurses` library is installed on your system.
3. Open a terminal and navigate to the directory containing the source files.
4. Compile the program using the following command:

   ```bash
   gcc -o Array-Manipulation-and-Simulations main.c utilities.c -lncurses
   ```

5. Run the compiled program with:

   ```bash
   ./Array-Manipulation-and-Simulations
   ```

## Contributing

Contributions to this project are welcome. If you have any suggestions for improvements or additional features, please feel free to open an issue or submit a pull request on the project's GitHub repository.

## License

This project is licensed under the Apache 2.0 License. See the LICENSE file for more information.

## Acknowledgments

We would like to thank the instructors and teaching assistants of the "Programmieren 1" course for their guidance and support throughout the development of this project.

Additionally, we appreciate the contributions of fellow students and open source community members who have provided feedback and suggestions for improvement.

## Disclaimer

This project is meant for educational purposes only. While the program can be used to perform various operations like array manipulations, dice simulations, and coin machine simulation, it is not intended to replace any official tools or be used for any illegal activities. The creators of this project are not responsible for any misuse or consequences resulting from the use of the program.
