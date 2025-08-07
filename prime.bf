# Brainfuck Prime Number Generator
# yoinked from https://www.reddit.com/r/brainfuck/comments/847vl0/prime_number_generator_in_brainfuck/
# This program generates and prints all prime numbers up to a given upper bound
# Algorithm: Sieve of Eratosthenes-like approach using nested loops

# Set upper bound (100)
>++++++++++[<++++++++++>-]<

# Main loop: iterate through all numbers from 2 to upper bound
# Current number is stored in the first cell
# Decrement the main counter once to compensate for <1 test
-
[
	# increment the main counter once
	+
  # Copy current number to two adjacent cells
  [>+>+<<-]>>[<<+>>-]<
  # Decrement by 2 (start checking from 2)
  --
  
  # Loop to test if current number is prime
  [
    # Set flag to 1 (assume prime initially)
    +>>[-]<<
    # Copy current number to working area
    <[>>+>+<<<-]>>>[<<<+>>>-]<
    # Increment divisor (start with 2)
    >+
    
    # Inner loop: test divisibility
    [
      <
      # Copy divisor to far position
      [>>>>>+>+<<<<<<-]>>>>>>[<<<<<<+>>>>>>-]<<<<<<
      # Loop to test if divisor divides current number evenly
      [
        # Clear temporary flag
        >[-]<<
        # Copy current number
        [>>+>+<<<-]>>>[<<<+>>>-]
        # Copy divisor
        <<[>>+>+<<<-]>>>[<<<+>>>-]<
        # Subtract divisor from current number
        [<->-]<
        # Increment counter
        >>>+<<<
        # If result is 0, we found a divisor
        [>>>-<<<+++++++++++++++[-]]<
        # Decrement test flag
        -
      ]
      # Move result back
      >>>>>[<<<<<+>>>>>-]
      # If divisor found, mark as not prime
      <[[-]<<<<<[>->+<<-]>>[<<+>>-]+>]<
    ]
    # Move to next divisor
    <<<>>>>>>>+<<<<<<<[>>>>>>>-<<<<<<<[-]]
    # Decrement divisor counter
    <--
  ]
  
  # Check if number is still marked as prime
  >>>>>>>>>+<[>-<[-]]>
  [
    # If prime, print the number
    # Copy number for printing
    -<<<<<<<<<<[>>>>>>>>>>+>+<<<<<<<<<<<-]>>>>>>>>>>>[<<<<<<<<<<<+>>>>>>>>>>>-]<
    
    # Convert number to decimal and print
    [>>+>+<<<-]>>>[<<<+>>>-]<<+>[<->[>++++++++++<[->-[>+>>]>[+[-<+>]>+>>]<<<<<]>[-]
    ++++++++[<++++++>-]>[<<+>>-]>[<<+>>-]<<]>]<[->>++++++++[<++++++>-]]<[.[-]<]<
    [-]>[-]<

    # Print space
    >++++[<+++++++++++>-]<.
    # Print newline
    ------------.
    
    # Clear the printed number
    [-]
  ]
  # Move back to main counter and decrement twice to skip 1
  <<<<<<<<<<--
]