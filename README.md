# Knapsack Problem Solver

## Problem Overview

The **Knapsack Problem** is a classic optimization problem where we have a set of items, each with a weight and a value. The goal is to determine the most valuable subset of items that can be packed into a knapsack, ensuring the total weight does not exceed the knapsack's weight limit.

### Problem Definition

Given:
- A set of **N** items, each with a weight \( w_i \) and value \( v_i \).
- A knapsack with a weight limit \( L \).

The objective is to maximize the total value:

**maximize** `sum(v_i)`  
**subject to** `sum(w_i) <= L`

### Example

For a knapsack with a weight limit of **6**, we have the following items:

| Item   | Weight | Value |
|--------|--------|-------|
| Heavy  | 4      | 39    |
| Light1 | 1      | 10    |
| Light2 | 1      | 10    |
| Light3 | 1      | 10    |
| Light4 | 1      | 10    |
| Light5 | 1      | 10    |

The optimal solution is to select:
- **Light1**, **Light2**, **Light3**, **Light4**, **Light5** for a total value of **50** (with a weight of **5**).

### Approaches

#### Naive Approach
A brute-force method tests every combination of items to find the optimal solution. However, this approach is computationally expensive, with a time complexity of \( O(2^N) \), making it impractical for larger datasets.

#### Greedy Approach
A greedy strategy might select items based on a value-to-weight ratio. While this can work for some cases, it does not always yield an optimal solution, as demonstrated by the example above.

#### Dynamic Programming (Optimal Solution)
Dynamic programming (DP) is an efficient approach to solving the knapsack problem. We solve subproblems and build up the solution incrementally.

### Dynamic Programming Solution

We define \( V_{n,l} \) as the maximum value obtainable with the first **n** items and a weight limit of **l**.

The solution involves filling a table of size \( N \times L \), where each entry represents the maximum value achievable with a subset of items and a given weight limit.

1. If we include item \( n \), the maximum value is \( v_n + V_{n-1, l - w_n} \).
2. If we exclude item \( n \), the value is \( V_{n-1, l} \).

The final solution is stored in \( V_{N-1, L} \), which represents the maximum value achievable with all items and the full weight limit.

#### Complexity
The time complexity is \( O(N * L) \), where **N** is the number of items and **L** is the weight limit, making this approach efficient for large inputs.

## Program Overview

The `knapsack` program selects a subset of items from a manifest file to maximize total value without exceeding the weight limit.

### Program Features

- **Input:**
  - Weight limit (positive integer)
  - Manifest file (containing item names, weights, and values)

- **Output:**
  - Names of selected items (printed in the order they appear in the manifest)
  - Total value and total weight of the selected items

### Usage

1. **Sample Manifest:**

```txt
6
Heavy 4 39
Light1 1 10
Light2 1 10
Light3 1 10
Light4 1 10
Light5 1 10
```

2. **Run the Program:**

```bash
$ ./knapsack 5 manifest.01.txt
Light1
Light2
Light3
Light4
Light5
50 / 5

$ ./knapsack 6 manifest.01.txt
Heavy
Light1
Light2
59 / 6
```

### Manifest File Format

The manifest file must follow this format:

1. The first line contains the number of items.
2. Subsequent lines contain item details: **name** (up to 31 characters), **weight**, and **value** (both positive integers).
   - Example: `Light1 1 10`

### Constraints

- The manifest must have uniquely named items.
- Weights and values are positive integers.
- The number of items should fit within standard integer limits.

### Output Format

- The program prints the names of selected items, one per line.
- After the list, it prints the total value and total weight of the selected items in the format `value / weight`.

## How It Works

1. **Input Parsing:** Reads the weight limit and manifest file.
2. **Dynamic Programming Table Construction:** Builds a DP table to compute the maximum value for each subset of items.
3. **Item Selection:** Traces back through the DP table to find which items were selected.
4. **Output:** Prints the selected items, total value, and total weight.

### Example Execution

**Manifest File:**
```txt
6
Heavy 4 39
Light1 1 10
Light2 1 10
Light3 1 10
Light4 1 10
Light5 1 10
```

**Command:**

```bash
$ ./knapsack 5 manifest.01.txt
```

**Output:**
```bash
Light1
Light2
Light3
Light4
Light5
50 / 5
```
