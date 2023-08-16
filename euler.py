
# Calculation of Euler Number e
import math

def euler(n):
    t_sum = 0
    for i in range(n):
        term = 1/math.factorial(i)
        t_sum = t_sum + term
    
    return t_sum

# Reading number of terms to be considered in series
terms = int(input("Enter number of terms: "))

# Function call
e = euler(terms)

# Displaying result
print("e = ", e)

phi = (1 + 5 ** 0.5) / 2
print(f"Golden ratio: {phi}")

"""
What is the golden rectangle?

The golden rectangle is a rectangle whose sides are in the golden ratio, that is (a + b)/a = a/b = φ, where a is the width, a + b is the length of the rectangle, and φ is the golden ratio: φ = (1+√5)/2.

"""