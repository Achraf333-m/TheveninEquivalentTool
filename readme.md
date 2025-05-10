# Thevenin Equivalent Circuit Tool

This is a starter project I created after completing my "Basic Circuit Analysis" course.

One of the most fascinating theorems I encountered was the Thevenin Equivalence. I found the ability to reduce complex circuits into simple, digestible "grade 1" equivalents genuinely mesmerizing.

It took me some time to fully grasp the theory, so I built this project both as a way to help other engineering newcomers visualize and interact with the concept — and as a "capstone" for what I've learned this past semester.

This project reflects key topics from both circuit theory and programming, including:

- C++ programming methodology
- Inheritance and operator overloading
- File and exception handling

#using the tool

This tool can be used as a CLI app by downloading the executable file (TheveninEquivalent.exe) and running it directly. It can also be used inside the repository, by using git clone in your personal development environment.
note: this tool does not use Windows API, so downloading the executable and running it can lead to error if your Desktop path is not directly under "Users\\[username]" for windows and "Home/" for linux.
---

### Validating the Tool

Here's an example used to verify the correctness of this tool:

#### LTSpice Circuit
![Thevenin Circuits on LTSpice](images/ltspiceSS.png)

#### Hand-solved Problem
![Thevenin Circuits on Paper](images/paperProblem.png)
