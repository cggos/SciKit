# Eigen

-----

## 预定义宏

```cpp
EIGEN_STACK_ALLOCATION_LIMIT

EIGEN_MAX_ALIGN_BYTES
EIGEN_MAX_STATIC_ALIGN_BYTES

EIGEN_VECTORIZE_SSE2
EIGEN_VECTORIZE_NEON
```

## 内存分配

### 静态分配内存

```cpp
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor, 16, 1000> A400; // 静态分配内存
```

### 动态内存分配


## 字节对齐


## Vectorization

### 字节对齐

* Eigen::aligned_allocator
  ```cpp
  std::map<int, Eigen::Vector4f> 
  // -->
  std::map<int, Eigen::Vector4f, std::less<int>, Eigen::aligned_allocator<std::pair<const int, Eigen::Vector4f>>>
  ```

### SIMD

* SSE
* NEON 


## Expression Lazy Evaluation

```cpp
eval()

evalTo()

noalias()

XXXinPlace()
```

## 矩阵乘积

* 加速：分治法（矩阵分块乘积）
