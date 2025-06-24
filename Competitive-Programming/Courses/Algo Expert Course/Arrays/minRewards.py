# scores are given. Distribute Rewards. Rules-
# 1. Every one has to get a reward
# 2. if score is high than person next to him than he must get reward + 1 more reward
# 3. if score is less than person next to him than he must get few rewards
# 4. Return minimum number of awards that you can give out

# O(n) Time | O(n) Space

def minRewards(scores):
    rewards = [1 for _ in scores]
    for i in range(1, len(scores)):
        if scores[i] > scores[i-1]:
            rewards[i] = rewards[i-1] + 1
    for i in reversed(range(len(scores)-1)):
        if scores[i] > scores[i+1]:
            rewards[i] = max(rewards[i], rewards[i+1]+1)
    return sum(rewards)
