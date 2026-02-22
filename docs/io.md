# I/O - Input and Output
This project can take in a sudoku puzzle from a file, and can output solved puzzles to a file.

## Syntax
The syntax for representing the puzzles is very simple. The parser will ignore newlines and whitespace, and it will also ignore any unspecified characters.

The only real rule is that there must be at least 81 specified characters (one character for each cell of a sudoku puzzle). If there are less than 81 specified characters in the file, an error will be thrown. it is important to note that **only the first 81 specified characters are parsed**. Once the first 81 characters have been discovered, the parser will stop reading the file. So you can place whatever you like below your 81 specified characters.

### Specified characters
There are 11 specified characters, each of which represents a cell and its state. Any characters in an input file which are not specified will be ignored and treated like whitespace.

Below is a description of every specified character:

| Character | Description                                |
|:---------:|:-------------------------------------------|
| **.**     | Represents an unsolved, empty cell         |
| **0**     | Same as above. Represents an unsolved cell |
| **1**     | Represents a solved cell whose value is 1  |
| **2**     | Represents a solved cell whose value is 2  |
| **3**     | Represents a solved cell whose value is 3  |
| **4**     | Represents a solved cell whose value is 4  |
| **5**     | Represents a solved cell whose value is 5  |
| **6**     | Represents a solved cell whose value is 6  |
| **7**     | Represents a solved cell whose value is 7  |
| **8**     | Represents a solved cell whose value is 8  |
| **9**     | Represents a solved cell whose value is 9  |

### Examples of valid input files
Whitespace, newlines, and unspecified characters are ignored and can be freely used in an input file so all of the following are valid examples of input files that represent the exact same puzzle:

#### Example 1 - An input file that uses newlines as well as spaces
```
004 050 000
900 734 600
003 021 049

035 090 480
090 000 030
076 010 920

310 970 200
009 182 003
000 060 100
```

#### Example 2 - An input file that uses no spaces and less newlines
```
004050000
900734600
003021049
035090480
090000030
076010920
310970200
009182003
000060100
```

#### Example 3 - An input file that does not use newlines or spaces
```
004050000900734600003021049035090480090000030076010920310970200009182003000060100
```

#### Example 4 - An input file that is erratic and freely uses newlines and spaces everywhere
```
0040
  50
   0 00
   9 0 073
460000
   30    2 104903
      5090      48 0 0900
      
00030              07601092 0 310

970 2 000
0 91
8 2 0030            00


0            6 


01


00
```

#### Example 5 - An input file that uses newlines and whitespaces and a variety of random unspecified characters
```
004 050 hello 000
900 73abcd4 600
00'''''''''3 021 049

03abcd5 090 480 Random stuff
090 000 03@@@@0
076 010 920

310 970 200 Characters could be used as comments
009 182 !!!!003
000 060 100
```

#### Example 6 - An input file that uses additional specified characters for notes *after* the first 81 characters in the file.
```
004 050 000
900 734 600
003 021 049

035 090 480
090 000 030
076 010 920

310 970 200
009 182 003
000 060 100

This is a note. Any specified characters (such as 0, 4, 8, or .) from here on out will be ignored as there are 81 valid specified characters above this.
You can place whatever you want down here.
```

### Examples of invalid input files
#### Example 1 - An input file that contains less than 81 specified characters
```
004 050 000
900 734 600
003 021 049

035 090 480
090 000 030
076 010 920

310 970 200
009 182 003
```

#### Example 2 - An input file that accidentally uses the period character '.' (this would be parsed, but incorrectly as the period would be understood as a blank cell) 
```
This is a note.
004 050 000
900 734 600
003 021 049

035 090 480 This is a note.
090 000 030
076 010 920

310 970 200
009 182 003
000 060 100
```

#### Example 3 - An input file that only contains unspecified characters (less than 81 specified characters)
```
zero zero four zero five zero zero zero zero
nine zero zero seven three four six zero zero
zero zero three zero...
```