# Tape K-Way Sorting

A C++ program that sorts the numbers on input tape, given RAM memory constraints

## 🛠 Build & Run

### Prerequisites

- Ubuntu (any Linux distro should be fine: project was built on Pop!OS)
- C++17 compiler `g++`
- `make`

### Build

```
make
```

### Run

```
./extrenal_sort input.txt output.txt
```
`input.txt` should exist
You can modify variables in `config.txt` to tweak the program behaviour

## 📥 Input Format

Input should be provided via file in the following format:

```
<number1>
<number2>
<number3>
...
```

### Example:

```
-959721
484454
-18748
843322
268376
-985632
127100
555484
767457
-323525
871813
-96875
-541613
-910562
-822466
-83243
-705822
347028
-784968
236272
-17602
-447570
812853
-619766
790339
-45801
-903324
959998
121712
147688
```

## 📤 Output

The output is printed to output file and consists of numbers from input file in sorted order.

---
