def rod_cutting(n, prices):
    dp = [0] * (n + 1)

    lengths = [1,2,3,4,5,6,7,8,9,10]

    if n == 0:
        return 0

    for i in range(1, n+1):
        dp[i] = max(dp[i], prices[i-1] + rod_cutting(n - i, prices))

n = 20  
prices = [1, 2, 8, 9, 10, 17, 17, 20, 24, 30]

print(rod_cutting(n, prices))