# Chapter 17 Specialized Library Facilities

**Exercise 17.1:** Define a tuple that holds three int values and initialize the membersto 10, 20, and 30.

**Exercise 17.2:** Define a tuple that holds a string, a `vector<string>`, and a`pair<string, int>`.

**Exercise 17.3:** Rewrite the TextQuery programs from § 12.3 (p. 484) to use a tupleinstead of the QueryResult class. Explain which design you think is better and why.

**Exercise 17.4:** Write and test your own version of the findBook function.

**Exercise 17.5:** Rewrite findBook to return a pair that holds an index and a pair of

**Exercise 17.6:** Rewrite findBook so that it does not use tuple or pair.

**Exercise 17.7:** Explain which version of findBook you prefer and why.

**Exercise 17.8:** What would happen if we passed Sales_data() as the third param-eter to accumulate in the last code example in this section?

**Exercise 17.9:** Explain the bit pattern each of the following bitset objects contains:

```c++
(a) bitset<64> bitvec(32);
(b) bitset<32> bv(1010101);
(c) string bstr; cin >> bstr; bitset<8>bv(bstr);
```

**Exercise 17.10:** Using the sequence 1, 2, 3, 5, 8, 13, 21, initialize a bitset that has a1 bit in each position corresponding to a number in this sequence. Default initializeanother bitset and write a small program to turn on each of the appropriate bits.

**Exercise 17.11:** Define a data structure that contains an integral object to track re-sponses to a true/false quiz containing 10 questions. What changes, if any, wouldyou need to make in your data structure if the quiz had 100 questions?

**Exercise 17.12:** Using the data structure from the previous question, write a functionthat takes a question number and a value to indicate a true/false answer and updatesthe quiz results accordingly.

**Exercise 17.13:** Write an integral object that contains the correct answers for thetrue/false quiz. Use it to generate grades on the quiz for the data structure from theprevious two exercises.

**Exercise 17.14:** Write several regular expressions designed to trigger various errors.Run your program to see what output your compiler generates for each error.

**Exercise 17.15:** Write a program using the pattern that finds words that violate the “ibefore e except after c” rule. Have your program prompt the user to supply a wordand indicate whether the word is okay or not. Test your program with words that doand do not violate the rule.

**Exercise 17.16:** What would happen if your regex object in the previous programwere initialized with "[^c]ei"? Test your program using that pattern to see whetheryour expectations were correct.

**Exercise 17.17:** Update your program so that it finds all the words in an input se-quence that violiate the “ei” grammar rule.

**Exercise 17.18:** Revise your program to ignore words that contain “ei” but are notmisspellings, such as “albeit” and “neighbor.”****

**Exercise 17.19:** Why is it okay to call m[4].str() without first checking whetherm[4] was matched?

**Exercise 17.20:** Write your own version of the program to validate phone numbers.

**Exercise 17.21:** Rewrite your phone number program from § 8.3.2 (p. 323) to use the valid function defined in this section.

**Exercise 17.22:** Rewrite your phone program so that it allows any number of whitespace characters to separate the three parts of a phone number.

**Exercise 17.23:** Write a regular expression to find zip codes. A zip code can have fiveor nine digits. The first five digits can be separated from the remaining four by a dash.

**Exercise 17.24:** Write your own version of the program to reformat phone numbers.

**Exercise 17.25:** Rewrite your phone program so that it writes only the first phone number for each person.

**Exercise 17.26:** Rewrite your phone program so that it writes only the second andsubsequent phone numbers for people with more than one phone number.

**Exercise 17.27:** Write a program that reformats a nine-digit zip code as ddddd-dddd.

**Exercise 17.28:** Write a function that generates and returns a uniformly distributedrandom unsigned int each time it is called.

**Exercise 17.29:** Allow the user to supply a seed as an optional argument to the func-tion you wrote in the previous exercise.

**Exercise 17.30:** Revise your function again this time to take a minimum and maxi-mum value for the numbers that the function should return.

**Exercise 17.31:** What would happen if we defined b and e inside the do loop of thegame-playing program from this section?

**Exercise 17.32:** What would happen if we defined resp inside the loop?

**Exercise 17.33:** Write a version of the word transformation program from § 11.3.6(p. 440) that allows multiple transformations for a given word and randomly selectswhich transformation to apply.

**Exercise 17.34:** Write a program that illustrates the use of each manipulator in Ta-bles 17.17 (p. 757) and 17.18.

**Exercise 17.35:** Write a version of the program from page 758, that printed the squareroot of 2 but this time print hexadecimal digits in uppercase.

**Exercise 17.36:** Modify the program from the previous exercise to print the variousfloating-point values so that they line up in a column.

**Exercise 17.37:** Use the unformatted version of getline to read a file a line at a time.Test your program by giving it a file that contains empty lines as well as lines that arelonger than the character array that you pass to getline.

**Exercise 17.38:** Extend your program from the previous exercise to print each wordyou read onto its own line.

**Exercise 17.39:** Write your own version of the seek program presented in this section.

### Notes

