import matplotlib.pyplot as plt

# 讀取數據
k_values = []
t_inputs = []
with open('input_times.txt', 'r') as f:
    for line in f:
        k, t_input = map(float, line.split())
        k_values.append(int(k))
        t_inputs.append(t_input)

# 繪製折線圖
plt.figure(figsize=(10, 6))
plt.plot(k_values, t_inputs, marker='o', color='#2196F3', label='Input Time (s)')
plt.xlabel('k (Number of Ways)')
plt.ylabel('Input Time (s)')
plt.title('Input Time vs. k in External Sorting')
plt.grid(True)
plt.legend()
plt.savefig('input_time_plot.png', dpi=300) # 保存圖表
plt.show()