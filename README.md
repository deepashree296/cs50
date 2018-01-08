# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust

## According to its man page, what does `getrusage` do?

returns resource usage by a process or thread or children process

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?


to save space

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Forloop of `main` reads one character at a time from the file using fgetc. when it reaches end of file, fgetc returns EOF,
and hence Forloop terminates there.

for each character read from the file, actions taken based on following cases:

1.  when the character is alphabetical or apostrophe
        put the character in the word array till it reaches the max word length. if the word length becomes more than
        the defined, ignore that alphabetical string completely and reset index to zero and start reading next character
2.  when the character is a digit
         ignore the alphanumeric string and reset index to 0
3.  when the character is \0
         it means a word is ending here and so , it is checked for misspelling and also time for checking is calculated.
         Again index is reset to zero. and for loop reads next character in the file

Note: In all cases when character read is neither end of string, nor alphabets nor a digit, we ignore everything else and
      for loop repeats to read next character.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

1. we dont know what max length of a word can be in the text file. so, storing the word will be a challenge using `fscanf`


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Since these parameters are passed as reference, these methods have direct access to the memory where current word in case
of `check` and dictionary in case of `load` is loaded . but these methods should not be able to modify these
parameters. so declaring these parameters as constant ensures that no changes are made to that parameter in the
scope of the function.
