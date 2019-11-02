

# Fibanacci using two techniques of Dynamic programming

def MemoizationFibonacci(n:int):
    """Fibonacci using Memoization (top-down cache filling)
    """
    # if current sub problem does not solve.
    if (n not in MemoizationFibonacci.mem):
        # calculate current sub problem
        if n < 2:
            result = n
        else:
            result = MemoizationFibonacci(n-2) + MemoizationFibonacci(n-1)
        MemoizationFibonacci.mem[n] = result
    return MemoizationFibonacci.mem[n]


MemoizationFibonacci.mem = {}

print("MemoizationFibonacci({})=".format(5), MemoizationFibonacci(5))
print("MemoizationFibonacci({})=".format(6), MemoizationFibonacci(6))
print("MemoizationFibonacci({})=".format(7), MemoizationFibonacci(7))

def TabulationFibonacci(n:int):
    """Fibonacci using Tabulation (bottom-up cache filling)
    """
    mem = [None] * (n + 1)
    mem[0] = 0
    mem[1] = 1
    for i in range(2, len(mem)):
        mem[i] = mem[i-1] + mem[i-2]
    return mem[n]        

print("TabulationFibonacci({})=".format(5), TabulationFibonacci(5))
print("TabulationFibonacci({})=".format(6), TabulationFibonacci(6))
print("TabulationFibonacci({})=".format(7), TabulationFibonacci(7))    