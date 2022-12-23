# Knapsack

## Background: the knapsack problem

We have a set of items, each of which has a weight and a value. We want to pack these items into a knapsack, but there is a maximum amount of weight that the knapsack can carry. Our goal is to find the most valuable subset of the items whose total weight does not exceed the knapsack’s weight limit.

We assume that the weights and values for each item are positive integers. We also assume that the knapsack can carry any combination of items, as long as the weight limit is not exceeded.

For example, we might have five light items with weight 1 and value 10, and one heavy item with weight 4 and value 39. If our knapsack’s weight limit is 6, what is the maximum total value of the items we can place in the knapsack?

### Formal definition

An instance of the knapsack problem involves a weight limit L and N items, numbered from 0 to N − 1. Each item i has a weight w_i and value v_i.

A solution to the knapsack problem is a set if items S that maximizes the total value sum(v_i) such that sum(w_i) < L.

### Non-optimal approaches

A naïve strategy is to test every combination of items and keep the combination with the highest total value of all combinations that do not exceed the weight limit. This strategy requires checking 2N subsets o items, leaving it impractical for all but the smallest problems.

A greedy approach might sort the items by some metric, such as value or ratio of value to weight, and repeatedly choose the best item that does not exceed the remaining weight limit. Unfortunately, this approach is not guaranteed to find an optimal subset.

Going back to our example, if our weight limit is 5 and we choose the most valuable items first, we will select the heavy item and one light item, for a total value of 49. The optimal subset with total weight 5 is to take five light items, for a total value of 50.

If we choose items to maximize value per weight, we will find the optimal set for weight limit 5. If the weight limit is 6, we will chose five light items again, for a total value of 50. Here, the optimal solution is to choose two light items and the heavy item, for a total value of 59.

### Method: Dynamic programming

Dynamic programming finds a solution to a problem by first finding solutions to smaller sub-problems.

For our knapsack problem, we will write V_(n,l) to indicate the maximum total value obtainable with items 0 through n subject to weight limit l. Thus, V_(N−1,L) is the maximum value obtainable using all N items with weight limit L.

We will construct a table containing V_(n,l) for all subproblems from V_(0,1) to V_(N−1,L). To simplify the definition, we define V_(n,l) = 0 if n < 0 or l < 1.

To compute Vn_(n,l), we must decide whether or not to include item n in the set. We do this by comparing the maximum value obtainable in the cases where we do and do not include item n.

1. If we include item n, then our choices from items 0, . . . , n − 1 must weigh at most l − w_n in order to keep the total weight less than l. As V_(n−1,l−w_n) represents the maximum value obtainable from those items with the reduced limit, we can conclude that v_n + V_(n−1,l−w_n) is the maximum value obtainable from items 0, . . . , n when item n is included.

2. If we do not include item n, then the maximum value we can include is simply V_(n−1,l).

Because our goal is to find the maximum value, we choose whichever scenario results in more value. (If both possibilities give the same value, then it does not matter which one we choose. For this program, we arbitrarily choose not to include item n when v_n + V_(n−1,l−w_n) = V_(n−1,l).)

#### Computation

A naïve approach to computing V_(n,l), such as writing a recursive function, will require exponential time in the worst case (because adding another item would double the number of recursive calls). Instead, we create a table containing all values of V_(n,l) where 0 ≤ n ≤ N and 0 < l ≤ L. Note that
we can fill this table by columns, from left to right, or by rows, from top to bottom. To compute V_(n,l), we only need to know the values of its neighbor to the left and one other value higher in the same column.

The amount of work required, then, is proportional to the product of N and L. Adding another item or increasing the weight limit increases the time (and space) requirements by a fixed amount.

#### Determining the optimum set

The table V_(n,l) gives the maximum value obtainable with items 0 through n and weight limit l, but does not directly indicate which items were selected. This information could be kept in a separate table indicating whether the optimum solution for a particular subproblem includes that item, based on which choice was made when computing V_(n,l).

Alternatively, the set of items can be found by examining the table. In general, if V_(n,l) = V_(n-1,l), we can assume that item n was not included in the solution. We consider the items in reverse order, from N − 1 to 0, with an initial weight limit of L. For each item n, we compare V_(n,l) and V_(n-1,l). If they are the same, then item n is not included and we continue. If they are not the same, we reduce the remaining weight by w_n and continue.

## Program

the program knapsack chooses items from a manifest. knapsack takes two arguments: the weight limit and a manifest file. It chooses a selection of items from the manifest that maximizes the total value without exceeding the weight limit. Once the selection is made, knapsack will print the selected items, one per line, in the same order they appear in the manifest file. After the list, knapsack will print the total value and total weight of the selected items.

The weight limit is a positive integer written in decimal.

The manifest file is specified using a relative or absolute path.

#### Usage

$ cat manifest.01.txt

6

Heavy 4 39

Light1 1 10

Light2 1 10

Light3 1 10

Light4 1 10

Light5 1 10

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

### Manifest file format

The manifest file begins with an integer indicating the number of items in the manifest. This is followed by the item definitions. Each item is specified by giving a name, a weight, and a value. The name is a string of at most 31 non-whitespace characters. The weight and value are positive integers.

All integers will be given in decimal notation.

The format specifies only that names and numbers are separated by whitespace. Items can be given more than one per line.

The program should only be given manifests with uniquely named items. It confirm that all specified weights and values are positive.

There is no specified maximum number of items, but it is assumed that the number of items will fit in a regular int, signed or unsigned.

### Output format

knapsack prints the names of the selected items, one per line, in the same order they are given in the manifest file. Item names must be given exactly as in the file.

Immediately after the list of items, knapsack prints the total value and total weight of the selected items, separated by a slash (/). The numbers are printed in decimal, without leading zeros.
