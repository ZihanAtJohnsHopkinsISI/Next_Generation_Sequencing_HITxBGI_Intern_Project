## Description

**This program is to find the starting position of matching DNA sequence and the ending position of matching DNA sequence in the reference DNA sequence.**

### Steps need to implement:

- Implement an first and secondary hash table to store the starting
          position of each 20bp Kmer in the reference list, the data is read
          from the input file. 

- Read the character from the NGS file and find the match key in the 
          table, store the starting position of reference and starting position
          of NGS to the query. 

- Use the priority queue to store the queries and implement the graph 
          which crafts the starting and ending position of the relative position 
          that mapping from the NGS to the reference. 
 

## How to compile
- Run main. There is no valid Makefile in the project. 
    The target and rules are already set up in the main function. 

## How to run

**As same as above**

## Normal Output

### Usually, the normal output should gives the query groups seperately and sequencially. It should be printed out the relatively starting position and relatively ending position on the referencial list. 

### Abnormal Output

- The both position on above is out of the legal range of the referential list
    

### Testing

- Threshold in the checkSameGroup in the Query class can be changed into any
    legal value. The testing result might seems different as long as the threshold
    changing. 
    
- The find match process is strictly follows the search all policy. The result 
    might seems different to the referential result. Loops time can be furtherly
    optimized in the referentialPositionGraph class.
    
- Testing process used small groups of reference data and matching data. The 
    program seems to work in such testing. 

- Input.txt is a test file instead of a real existing file. 

## Attention

### In the FileIO object, there exists a parameter named target with type integer, which might be removed later. Several details list below:
    
- If the target is set to 1, then it create the two chain hashtable from
          a file, which created from a input file. The input file removes all 
          invalid character ('N' and the '\n'). But this way is time consuming. 
          The optimized method might be released later. 
          
        




