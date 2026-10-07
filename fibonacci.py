def fibonacci(n):
    fib_sequence = []
    a, b = 0, 1

    for _ in range(n):
        fib_sequence.append(a)
        a, b = b, a + b

    return fib_sequence


# Example usage
if __name__ == "__main__":
    count = 10
    print(f"First {count} Fibonacci numbers:")
    print(fibonacci(count))
