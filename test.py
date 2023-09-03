from random import random
from time import time
from fast_dropout import fast_dropout
import numpy as np


# data = [50 for i in range(10000000)]    # 生成随机数据

start_time = time()              # 计算并统计时间
tt = [fast_dropout(50,0.625,3) for _ in range(10000000)]
# tt = np.random.rand(50,10000000)<0.625
end_time = time()
print(end_time-start_time)     # 输出运行时间
print('hello world')
