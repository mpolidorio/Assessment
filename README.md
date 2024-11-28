# Introduction

This README contains the answers to the Electrolux Knowledge Assessment.
The code for the Questions 2, 3 and 4 was implemented in C language and compiled used GCC Compiler, implemented in a Linux desktop environment.

## Question 1:

### 1st scenario:

- Resistive Load;
- Controlling the load with a microcontroller;
- Power cannot be changed from 0% to 100%.

In this scenario, i would use a MOSFET for driving the load, with a PWM modulation to ensure that the power is delivered to the load
in a controlled way. Depending on the load requirements, a driver would be necessary. Another point to be consider is the use of an optocoupler to isolate the microcontroller
from the power circuit.

### 2nd scenario:

- Load is now inductive.

In this scenario, i would use a freewheel diode to protect the MOSFET against voltages spikes.

---

## **Question 2**

The code for this question is in the file `ex2.c`.

### **How to Compile and Run**

1. Ensure you are on a **Linux system** with **GCC** installed.
2. Navigate to the directory containing `ex2.c`.
3. Use the following command to compile the code in the terminal:
   ```bash
   cc ex2.c -o ex2
   ```

---

## Question 3:

The code for this question is in the file `ex3.c`.

### **How to Compile and Run**

1. Ensure you are on a **Linux system** with **GCC** installed.
2. Navigate to the directory containing `ex3.c`.
3. Use the following command to compile the code in the terminal:
   ```bash
   cc ex3.c -o ex3
   ```

---

## Question 4:

### Theoretical part:

Considering multiple UART ports, i would suggest using a custom protocol, to ensure that the data is encapsulated and sent to the correct port correctly.
The protocol would need a header, the address to identify the destination board, the length, data and checksum if needed. An example can be observed in the image below.

[Protocol Example](./payload.svg)

The image was generated with protoviz tool: [https://protoviz.stu.art.br/]

### Practical part:

The code for this question is in the file `ex4.c`.

### **How to Compile and Run**

1. Ensure you are on a **Linux system** with **GCC** installed.
2. Navigate to the directory containing `ex4.c`.
3. Use the following command to compile the code in the terminal:
   ```bash
   cc ex4.c -o ex4
   ```
