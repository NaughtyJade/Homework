import matplotlib.pyplot as plt

# 讀取數據
n_values = []
ratios = []
with open('bst_ratios.txt', 'r') as f:
    for line in f:
        n, ratio = map(float, line.split())
        n_values.append(int(n))
        ratios.append(ratio)

# 繪製折線圖
plt.figure(figsize=(10, 6))
plt.plot(n_values, ratios, marker='o', color='#4CAF50', label='Height / log₂n')
plt.axhline(y=2, color='r', linestyle='--', label='Expected Ratio (2)')
plt.xlabel('n (Number of Nodes)')
plt.ylabel('Height / log₂n')
plt.title('BST Height Ratio vs. n')
plt.grid(True)
plt.legend()
plt.savefig('bst_ratio_plot.png', dpi=300) # 保存圖表
plt.show()