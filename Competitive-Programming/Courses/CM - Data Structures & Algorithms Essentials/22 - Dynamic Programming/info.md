# Dynamic Programming

- Optimization Technique
- Remembering what we have solved in past
- Memoisation

## Fibonacci Series

- f(n) = f(n-1) + f(n-2)

```cpp

// O(2^n) - Time Complexity
int fib(int n){
    if(n==0 or n==1){
        return n;
    }
    return fib(n-1) + fib(n-2);

}
```

- DP:

```cpp

// O(n) - Time Complexity
int fib(int n, int dp[]){
    if(n==0 or n==1){
        return n;
    }

    // Below step is most common in top down dp approach
    if(dp[n]!=0){
        return dp[n];
    }
    return dp[n] = fib(n-1,dp) + fib(n-2,dp);

}

```
-  We can compute fibonnaci in less than O(n) using **matrix exponentiation** (Adv Topic)

## Top Down DP

- In this we start building the big solution right way explaining how you build it from smaller solutions

## Bottom Up DP

- We start with small solutions and then use small solutions to build larger solutions

```cpp

// O(N)
for(i = 2; i<=n; i++){
    dp[i] = dp[i-1] + dp[i-2];
}

```


