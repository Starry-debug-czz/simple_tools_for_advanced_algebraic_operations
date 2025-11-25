#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// 打印矩阵，自动对齐
void printMatrix(const vector<vector<double>> &mat) {
  int rows = mat.size(), cols = mat[0].size();
  for (int i = 0; i < rows; i++) {
    cout << "[ ";
    for (int j = 0; j < cols; j++) {
      if (fabs(mat[i][j]) < 1e-10)
        cout << setw(8) << "0";
      else
        cout << setw(8) << fixed << setprecision(3) << mat[i][j];
    }
    cout << " ]" << endl;
  }
}

// 输入矩阵
vector<vector<double>> inputMatrix(int rows, int cols) {
  vector<vector<double>> mat(rows, vector<double>(cols));
  cout << "请输入 " << rows << "×" << cols << " 矩阵:" << endl;
  for (int i = 0; i < rows; i++) {
    cout << "第 " << i + 1 << " 行: ";
    for (int j = 0; j < cols; j++) {
      cin >> mat[i][j];
    }
  }
  return mat;
}

// 矩阵乘法
vector<vector<double>> matrixMultiply(const vector<vector<double>> &A,
                                      const vector<vector<double>> &B) {
  int m = A.size(), n = A[0].size(), p = B[0].size();
  vector<vector<double>> result(m, vector<double>(p, 0));
  for (int i = 0; i < m; i++)
    for (int j = 0; j < p; j++)
      for (int k = 0; k < n; k++)
        result[i][j] += A[i][k] * B[k][j];
  return result;
}

// 矩阵转置
vector<vector<double>> transpose(const vector<vector<double>> &mat) {
  int rows = mat.size(), cols = mat[0].size();
  vector<vector<double>> result(cols, vector<double>(rows));
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      result[j][i] = mat[i][j];
  return result;
}

// 矩阵加法
void matrixAddition() {
  cout << "\n=== 矩阵加法 ===" << endl;
  int rows, cols;
  cout << "输入矩阵行数: ";
  cin >> rows;
  cout << "输入矩阵列数: ";
  cin >> cols;

  cout << "\n矩阵 A:" << endl;
  auto A = inputMatrix(rows, cols);
  cout << "\n矩阵 B:" << endl;
  auto B = inputMatrix(rows, cols);

  vector<vector<double>> result(rows, vector<double>(cols));
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      result[i][j] = A[i][j] + B[i][j];

  cout << "\nA + B =" << endl;
  printMatrix(result);
}

// 矩阵乘法
void matrixMultiplication() {
  cout << "\n=== 矩阵乘法 ===" << endl;
  int m, n, p;
  cout << "A矩阵行数: ";
  cin >> m;
  cout << "A矩阵列数: ";
  cin >> n;
  cout << "B矩阵列数: ";
  cin >> p;

  cout << "\n矩阵 A:" << endl;
  auto A = inputMatrix(m, n);
  cout << "\n矩阵 B:" << endl;
  auto B = inputMatrix(n, p);

  auto result = matrixMultiply(A, B);

  cout << "\nA × B =" << endl;
  printMatrix(result);
}

// 求行列式（递归法）
double determinant(vector<vector<double>> mat) {
  int n = mat.size();
  if (n == 1)
    return mat[0][0];
  if (n == 2)
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

  double det = 0;
  for (int j = 0; j < n; j++) {
    vector<vector<double>> submat(n - 1, vector<double>(n - 1));
    for (int i = 1; i < n; i++) {
      int col = 0;
      for (int k = 0; k < n; k++) {
        if (k == j)
          continue;
        submat[i - 1][col++] = mat[i][k];
      }
    }
    det += (j % 2 == 0 ? 1 : -1) * mat[0][j] * determinant(submat);
  }
  return det;
}

void calcDeterminant() {
  cout << "\n=== 求行列式 ===" << endl;
  int n;
  cout << "输入方阵阶数: ";
  cin >> n;
  auto mat = inputMatrix(n, n);
  cout << "\n行列式 = " << determinant(mat) << endl;
}

// 高斯消元法求逆矩阵
void gaussJordanInverse() {
  cout << "\n=== 高斯-约当消元法求逆矩阵 ===" << endl;
  int n;
  cout << "输入方阵阶数: ";
  cin >> n;
  auto A = inputMatrix(n, n);

  // 创建增广矩阵 [A|I]
  vector<vector<double>> aug(n, vector<double>(2 * n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      aug[i][j] = A[i][j];
    aug[i][n + i] = 1.0; // 单位矩阵
  }

  cout << "\n初始增广矩阵 [A|I]:" << endl;
  printMatrix(aug);

  // 高斯-约当消元
  for (int i = 0; i < n; i++) {
    // 寻找主元
    int pivot = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(aug[j][i]) > fabs(aug[pivot][i])) {
        pivot = j;
      }
    }

    // 检查矩阵是否奇异
    if (fabs(aug[pivot][i]) < 1e-10) {
      cout << "错误：矩阵是奇异的，不可逆！" << endl;
      return;
    }

    // 交换行（如果需要）
    if (pivot != i) {
      swap(aug[i], aug[pivot]);
      cout << "交换行 " << i + 1 << " 和行 " << pivot + 1 << endl;
      printMatrix(aug);
    }

    // 主元归一化
    double pivotValue = aug[i][i];
    for (int j = i; j < 2 * n; j++) {
      aug[i][j] /= pivotValue;
    }

    cout << "主元归一化后:" << endl;
    printMatrix(aug);

    // 消去其他行
    for (int j = 0; j < n; j++) {
      if (j != i) {
        double factor = aug[j][i];
        for (int k = i; k < 2 * n; k++) {
          aug[j][k] -= factor * aug[i][k];
        }
      }
    }

    cout << "第 " << i + 1 << " 次消元后:" << endl;
    printMatrix(aug);
  }

  // 提取逆矩阵
  vector<vector<double>> inv(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      inv[i][j] = aug[i][n + j];
    }
  }

  cout << "\n最终逆矩阵:" << endl;
  printMatrix(inv);

  // 验证 A * A⁻¹ = I
  cout << "=== 验证 A * A⁻¹ ===" << endl;
  vector<vector<double>> result(n, vector<double>(n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        result[i][j] += A[i][k] * inv[k][j];
      }
    }
  }

  cout << "A * A⁻¹ 结果:" << endl;
  printMatrix(result);

  // 检查是否接近单位矩阵
  bool isIdentity = true;
  double tolerance = 1e-6;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double expected = (i == j) ? 1.0 : 0.0;
      if (fabs(result[i][j] - expected) > tolerance) {
        isIdentity = false;
        break;
      }
    }
    if (!isIdentity)
      break;
  }

  if (isIdentity) {
    cout << "✓ 验证成功：A * A⁻¹ 非常接近单位矩阵" << endl;
  } else {
    cout << "✗ 验证失败：A * A⁻¹ 与单位矩阵有较大差异" << endl;
  }

  // 验证 A⁻¹ * A = I
  cout << "\n=== 验证 A⁻¹ * A ===" << endl;
  vector<vector<double>> result2(n, vector<double>(n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        result2[i][j] += inv[i][k] * A[k][j];
      }
    }
  }

  cout << "A⁻¹ * A 结果:" << endl;
  printMatrix(result2);

  // 检查是否接近单位矩阵
  bool isIdentity2 = true;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double expected = (i == j) ? 1.0 : 0.0;
      if (fabs(result2[i][j] - expected) > tolerance) {
        isIdentity2 = false;
        break;
      }
    }
    if (!isIdentity2)
      break;
  }

  if (isIdentity2) {
    cout << "✓ 验证成功：A⁻¹ * A 非常接近单位矩阵" << endl;
  } else {
    cout << "✗ 验证失败：A⁻¹ * A 与单位矩阵有较大差异" << endl;
  }

  // 计算误差范数
  double error1 = 0.0, error2 = 0.0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double diff1 = result[i][j] - ((i == j) ? 1.0 : 0.0);
      double diff2 = result2[i][j] - ((i == j) ? 1.0 : 0.0);
      error1 += diff1 * diff1;
      error2 += diff2 * diff2;
    }
  }

  cout << "\n误差分析:" << endl;
  cout << "A * A⁻¹ 与单位矩阵的均方误差: " << sqrt(error1) << endl;
  cout << "A⁻¹ * A 与单位矩阵的均方误差: " << sqrt(error2) << endl;
}

// 求代数余子式
double cofactor(const vector<vector<double>> &mat, int row, int col) {
  int n = mat.size();
  vector<vector<double>> submat(n - 1, vector<double>(n - 1));

  int r = 0;
  for (int i = 0; i < n; i++) {
    if (i == row)
      continue;
    int c = 0;
    for (int j = 0; j < n; j++) {
      if (j == col)
        continue;
      submat[r][c++] = mat[i][j];
    }
    r++;
  }

  return ((row + col) % 2 == 0 ? 1 : -1) * determinant(submat);
}

// 伴随矩阵法求逆
void adjugateInverse() {
  cout << "\n=== 伴随矩阵法求逆 ===" << endl;
  int n;
  cout << "输入方阵阶数: ";
  cin >> n;
  auto A = inputMatrix(n, n);

  double det = determinant(A);
  cout << "\n1. 行列式 det(A) = " << det << endl;

  if (fabs(det) < 1e-10) {
    cout << "矩阵不可逆!" << endl;
    return;
  }

  cout << "\n2. 伴随矩阵:" << endl;
  vector<vector<double>> adj(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      adj[j][i] = cofactor(A, i, j);
    }
  }
  printMatrix(adj);

  cout << "\n3. 逆矩阵 A⁻¹ = (1/" << det << ") * adj(A):" << endl;
  vector<vector<double>> inv(n, vector<double>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      inv[i][j] = adj[i][j] / det;

  printMatrix(inv);
}

// 求矩阵秩
int matrixRank(vector<vector<double>> mat) {
  int rows = mat.size(), cols = mat[0].size();
  int rank = 0;

  for (int col = 0; col < cols && rank < rows; col++) {
    int pivot = rank;
    for (int i = rank + 1; i < rows; i++) {
      if (fabs(mat[i][col]) > fabs(mat[pivot][col]))
        pivot = i;
    }

    if (fabs(mat[pivot][col]) < 1e-10)
      continue;

    if (pivot != rank)
      swap(mat[rank], mat[pivot]);

    for (int i = rank + 1; i < rows; i++) {
      double factor = mat[i][col] / mat[rank][col];
      for (int j = col; j < cols; j++) {
        mat[i][j] -= factor * mat[rank][j];
      }
    }
    rank++;
  }
  return rank;
}

void calcMatrixRank() {
  cout << "\n=== 求矩阵秩 ===" << endl;
  int rows, cols;
  cout << "输入矩阵行数: ";
  cin >> rows;
  cout << "输入矩阵列数: ";
  cin >> cols;
  auto mat = inputMatrix(rows, cols);
  cout << "\n矩阵的秩 = " << matrixRank(mat) << endl;
}

// 二次型化为标准型（合同变换法）
void quadraticFormCompletion() {
  cout << "\n=== 二次型化为标准型（合同变换法）===" << endl;
  int n;
  cout << "输入变量个数: ";
  cin >> n;
  auto A = inputMatrix(n, n);

  cout << "\n对称矩阵 A:" << endl;
  printMatrix(A);

  // 存储所有变换矩阵
  vector<vector<vector<double>>> transformMatrices;
  vector<string> transformSteps;

  auto currentA = A;
  vector<vector<double>> B(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    B[i][i] = 1; // B初始为单位矩阵

  int step = 0;

  // 合同变换过程
  for (int k = 0; k < n; k++) {
    // 情况1: a_kk ≠ 0
    if (fabs(currentA[k][k]) > 1e-10) {
      // 构造消元矩阵 C_k
      vector<vector<double>> C(n, vector<double>(n, 0));
      for (int i = 0; i < n; i++)
        C[i][i] = 1; // 初始为单位矩阵

      // 设置第一行（除了对角线元素）
      for (int j = k + 1; j < n; j++) {
        C[k][j] = -currentA[k][j] / currentA[k][k];
      }

      transformMatrices.push_back(C);
      transformSteps.push_back("C" + to_string(++step) + " - 消去第" +
                               to_string(k + 1) + "行交叉项");

      cout << "\n" << transformSteps.back() << ":" << endl;
      printMatrix(C);

      // 应用合同变换: A -> C^T * A * C
      auto CT = transpose(C);
      currentA = matrixMultiply(matrixMultiply(CT, currentA), C);

      cout << "变换后的矩阵:" << endl;
      printMatrix(currentA);

      // 更新总变换矩阵: B = B * C
      B = matrixMultiply(B, C);
    }
    // 情况2: a_kk = 0 但存在 a_ii ≠ 0 (i > k)
    else {
      bool found = false;
      for (int i = k + 1; i < n; i++) {
        if (fabs(currentA[i][i]) > 1e-10) {
          // 构造置换矩阵 P，交换第k行和第i行
          vector<vector<double>> P(n, vector<double>(n, 0));
          for (int j = 0; j < n; j++)
            P[j][j] = 1;
          // 交换第k行和第i行
          swap(P[k], P[i]);

          transformMatrices.push_back(P);
          transformSteps.push_back("P" + to_string(++step) + " - 交换第" +
                                   to_string(k + 1) + "行和第" +
                                   to_string(i + 1) + "行");

          cout << "\n" << transformSteps.back() << ":" << endl;
          printMatrix( P);

          // 应用合同变换: A -> P^T * A * P
          currentA = matrixMultiply(matrixMultiply(transpose(P), currentA), P);

          cout << "变换后的矩阵:" << endl;
          printMatrix(currentA);

          // 更新总变换矩阵: B = B * P
          B = matrixMultiply(B, P);

          found = true;
          k--; // 重新处理这一位置
          break;
        }
      }

      // 情况3: 所有对角元为0但存在非对角元 ≠ 0
      if (!found) {
        bool foundOffDiagonal = false;
        for (int i = k + 1; i < n && !foundOffDiagonal; i++) {
          for (int j = i + 1; j < n && !foundOffDiagonal; j++) {
            if (fabs(currentA[i][j]) > 1e-10) {
              // 添加边界检查
              if (k >= n - 1) {
                foundOffDiagonal = true;
                break; // 无法创建平方项，跳过
              }
              // 先交换到合适位置
              vector<vector<double>> P1(n, vector<double>(n, 0));
              for (int idx = 0; idx < n; idx++)
                P1[idx][idx] = 1;
              // 交换第k+1行和第i行
              if (k + 1 != i) {
                swap(P1[k + 1], P1[i]);

                transformMatrices.push_back(P1);
                transformSteps.push_back(
                    "P" + to_string(++step) + " - 准备创造平方项: 交换第" +
                    to_string(k + 2) + "行和第" + to_string(i + 1) + "行");

                cout << "\n" << transformSteps.back() << ":" << endl;
                printMatrix(P1);

                currentA =
                    matrixMultiply(matrixMultiply(transpose(P1), currentA), P1);
                B = matrixMultiply(B, P1);
              }

              // 构造创造平方项的变换矩阵
              vector<vector<double>> C(n, vector<double>(n, 0));
              for (int idx = 0; idx < n; idx++)
                C[idx][idx] = 1;
              C[k][k] = 1;
              C[k][k + 1] = 1;
              C[k + 1][k] = 1;
              C[k + 1][k + 1] = -1;

              transformMatrices.push_back(C);
              transformSteps.push_back("C" + to_string(++step) +
                                       " - 创造平方项");

              cout << "\n" << transformSteps.back() << ":" << endl;
              printMatrix(C);

              // 应用合同变换
              currentA =
                  matrixMultiply(matrixMultiply(transpose(C), currentA), C);

              cout << "变换后的矩阵:" << endl;
              printMatrix(currentA);

              // 更新总变换矩阵
              B = matrixMultiply(B, C);

              foundOffDiagonal = true;
              k--; // 重新处理这一位置
              break;
            }
          }
        }

        if (!foundOffDiagonal) {
          // 所有相关元素都为0，跳过
          cout << "\n位置(" << k + 1 << "," << k + 1
               << ")及其相关元素全为0，跳过" << endl;
        }
      }
    }
  }

  cout << "\n=== 最终结果 ===" << endl;

  // 提取对角线元素作为标准型系数
  vector<double> coeffs(n);
  for (int i = 0; i < n; i++) {
    coeffs[i] = currentA[i][i];
  }

  cout << "1. 标准型: f = ";
  bool first = true;
  for (int i = 0; i < n; i++) {
    if (fabs(coeffs[i]) > 1e-10 || !first) {
      if (!first)
        cout << " + ";
      cout << coeffs[i] << " * y" << i + 1 << "²";
      first = false;
    }
  }
  cout << endl;

  cout << "\n2. 非退化线性变换矩阵 C (使得 X = CY):" << endl;
  printMatrix(B);

  cout << "\n3. 变换矩阵序列:" << endl;
  vector<vector<double>> product(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    product[i][i] = 1;

  for (size_t i = 0; i < transformMatrices.size(); i++) {
    cout << transformSteps[i] << ":" << endl;
    printMatrix(transformMatrices[i]);
    product = matrixMultiply(product, transformMatrices[i]);
    cout << "当前累积矩阵:" << endl;
    printMatrix(product);
  }

  cout << "\n4. 验算过程:" << endl;
  cout << "验证: Cᵀ * A * C = 对角矩阵" << endl;

  auto BT = transpose(B);
  cout << "Cᵀ =" << endl;
  printMatrix(BT);
  cout << "A =" << endl;
  printMatrix(A);
  cout << "C =" << endl;
  printMatrix(B);

  auto temp1 = matrixMultiply(BT, A);
  auto result = matrixMultiply(temp1, B);
  cout << "Cᵀ * A * C =" << endl;
  printMatrix(result);

  // 构建标准型矩阵进行对比
  vector<vector<double>> diagMatrix(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    diagMatrix[i][i] = coeffs[i];

  cout << "理论标准型矩阵:" << endl;
  printMatrix(diagMatrix);

  // 验证误差
  double maxError = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double error = fabs(result[i][j] - diagMatrix[i][j]);
      if (error > maxError)
        maxError = error;
    }
  }
  cout << "最大验证误差: " << maxError
       << (maxError < 1e-8 ? " (验证成功)" : " (可能有误差)") << endl;
}

// 二次型化为规范形
void quadraticFormCanonical() {
  cout << "\n=== 二次型化为规范形 ===" << endl;
  int n;
  cout << "输入变量个数: ";
  cin >> n;
  auto A = inputMatrix(n, n);

  cout << "\n对称矩阵 A:" << endl;
  printMatrix(A);

  // 存储所有变换矩阵
  vector<vector<vector<double>>> transformMatrices;
  vector<string> transformSteps;

  auto currentA = A;
  vector<vector<double>> C(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    C[i][i] = 1; // C初始为单位矩阵

  int step = 0;
  int positive_count = 0, negative_count = 0;

  // 先化为标准型
  for (int k = 0; k < n; k++) {
    // 情况1: a_kk ≠ 0
    if (fabs(currentA[k][k]) > 1e-10) {
      // 构造消元矩阵 C_k
      vector<vector<double>> P(n, vector<double>(n, 0));
      for (int i = 0; i < n; i++)
        P[i][i] = 1;

      for (int j = k + 1; j < n; j++) {
        P[k][j] = -currentA[k][j] / currentA[k][k];
      }

      transformMatrices.push_back(P);
      transformSteps.push_back("P" + to_string(++step) + " - 消去第" +
                               to_string(k + 1) + "行交叉项");

      cout << "\n" << transformSteps.back() << ":" << endl;
      printMatrix(P);

      // 应用合同变换
      auto PT = transpose(P);
      currentA = matrixMultiply(matrixMultiply(PT, currentA), P);
      C = matrixMultiply(C, P);

      cout << "变换后的矩阵:" << endl;
      printMatrix(currentA);
    }
    // 情况2: a_kk = 0 但存在 a_ii ≠ 0 (i > k)
    else {
      bool found = false;
      for (int i = k + 1; i < n; i++) {
        if (fabs(currentA[i][i]) > 1e-10) {
          // 构造置换矩阵
          vector<vector<double>> P(n, vector<double>(n, 0));
          for (int j = 0; j < n; j++)
            P[j][j] = 1;
          swap(P[k], P[i]);

          transformMatrices.push_back(P);
          transformSteps.push_back("P" + to_string(++step) + " - 交换第" +
                                   to_string(k + 1) + "行和第" +
                                   to_string(i + 1) + "行");

          cout << "\n" << transformSteps.back() << ":" << endl;
          printMatrix(P);

          // 应用合同变换
          currentA = matrixMultiply(matrixMultiply(transpose(P), currentA), P);
          C = matrixMultiply(C, P);

          cout << "变换后的矩阵:" << endl;
          printMatrix(currentA);

          found = true;
          k--; // 重新处理这一位置
          break;
        }
      }

      // 情况3: 所有对角元为0但存在非对角元 ≠ 0
      if (!found) {
        bool foundOffDiagonal = false;
        for (int i = k + 1; i < n && !foundOffDiagonal; i++) {
          for (int j = i + 1; j < n && !foundOffDiagonal; j++) {
            if (fabs(currentA[i][j]) > 1e-10) {
              // 先交换到合适位置
              vector<vector<double>> P1(n, vector<double>(n, 0));
              for (int idx = 0; idx < n; idx++)
                P1[idx][idx] = 1;
              if (k + 1 != i) {
                swap(P1[k + 1], P1[i]);

                transformMatrices.push_back(P1);
                transformSteps.push_back(
                    "P" + to_string(++step) + " - 准备创造平方项: 交换第" +
                    to_string(k + 2) + "行和第" + to_string(i + 1) + "行");

                cout << "\n" << transformSteps.back() << ":" << endl;
                printMatrix(P1);

                currentA =
                    matrixMultiply(matrixMultiply(transpose(P1), currentA), P1);
                C = matrixMultiply(C, P1);
              }

              // 构造创造平方项的变换矩阵
              vector<vector<double>> P2(n, vector<double>(n, 0));
              for (int idx = 0; idx < n; idx++)
                P2[idx][idx] = 1;
              P2[k][k] = 1;
              P2[k][k + 1] = 1;
              P2[k + 1][k] = 1;
              P2[k + 1][k + 1] = -1;

              transformMatrices.push_back(P2);
              transformSteps.push_back("P" + to_string(++step) +
                                       " - 创造平方项");

              cout << "\n" << transformSteps.back() << ":" << endl;
              printMatrix(P2);

              // 应用合同变换
              currentA =
                  matrixMultiply(matrixMultiply(transpose(P2), currentA), P2);
              C = matrixMultiply(C, P2);

              cout << "变换后的矩阵:" << endl;
              printMatrix(currentA);

              foundOffDiagonal = true;
              k--; // 重新处理这一位置
              break;
            }
          }
        }

        if (!foundOffDiagonal) {
          cout << "\n位置(" << k + 1 << "," << k + 1
               << ")及其相关元素全为0，跳过" << endl;
        }
      }
    }
  }

  cout << "\n=== 标准型结果 ===" << endl;
  cout << "标准型矩阵:" << endl;
  printMatrix(currentA);

  // 统计正负惯性指数
  for (int i = 0; i < n; i++) {
    if (currentA[i][i] > 1e-10) {
      positive_count++;
    } else if (currentA[i][i] < -1e-10) {
      negative_count++;
    }
  }

  cout << "正惯性指数: " << positive_count << endl;
  cout << "负惯性指数: " << negative_count << endl;
  cout << "秩: " << (positive_count + negative_count) << endl;

  // 化为规范形：对每个非零对角元进行规范化
  cout << "\n=== 化为规范形 ===" << endl;

  int p_index = 0;              // 正项索引
  int n_index = positive_count; // 负项索引

  for (int i = 0; i < n; i++) {
    if (fabs(currentA[i][i]) > 1e-10) {
      // 构造规范化变换矩阵
      vector<vector<double>> N(n, vector<double>(n, 0));
      for (int j = 0; j < n; j++)
        N[j][j] = 1;

      if (currentA[i][i] > 0) {
        // 正项：除以平方根得到系数1
        N[i][i] = 1.0 / sqrt(currentA[i][i]);
        transformMatrices.push_back(N);
        transformSteps.push_back("N" + to_string(++step) + " - 规范化正项 y" +
                                 to_string(i + 1));

        cout << "\n" << transformSteps.back() << ":" << endl;
        printMatrix(N);
      } else {
        // 负项：除以绝对值的平方根，然后调整符号
        N[i][i] = 1.0 / sqrt(-currentA[i][i]);
        transformMatrices.push_back(N);
        transformSteps.push_back("N" + to_string(++step) + " - 规范化负项 y" +
                                 to_string(i + 1));

        cout << "\n" << transformSteps.back() << ":" << endl;
        printMatrix(N);
      }

      // 应用规范化变换
      auto NT = transpose(N);
      currentA = matrixMultiply(matrixMultiply(NT, currentA), N);
      C = matrixMultiply(C, N);

      cout << "规范化后的矩阵:" << endl;
      printMatrix(currentA);
    }
  }

  // 重新排列，使正项在前，负项在后（如果需要）
  if (positive_count > 0 && negative_count > 0) {
    // 找到第一个负项的位置
    int first_negative = -1;
    for (int i = 0; i < n; i++) {
      if (currentA[i][i] < -0.5) { // 规范化后负项约为-1
        first_negative = i;
        break;
      }
    }

    // 找到最后一个正项的位置
    int last_positive = -1;
    for (int i = n - 1; i >= 0; i--) {
      if (currentA[i][i] > 0.5) { // 规范化后正项约为1
        last_positive = i;
        break;
      }
    }

    // 如果需要重新排列
    if (first_negative >= 0 && last_positive >= 0 &&
        first_negative < last_positive) {
      vector<vector<double>> R(n, vector<double>(n, 0));
      for (int i = 0; i < n; i++)
        R[i][i] = 1;

      // 交换正负项位置
      swap(R[first_negative], R[last_positive]);

      transformMatrices.push_back(R);
      transformSteps.push_back("R" + to_string(++step) +
                               " - 重新排列使正项在前");

      cout << "\n" << transformSteps.back() << ":" << endl;
      printMatrix(R);

      // 应用重新排列
      currentA = matrixMultiply(matrixMultiply(transpose(R), currentA), R);
      C = matrixMultiply(C, R);

      cout << "重新排列后的规范形矩阵:" << endl;
      printMatrix(currentA);
    }
  }

  cout << "\n=== 最终结果 ===" << endl;

  cout << "1. 规范形: f = ";
  bool first_term = true;
  for (int i = 0; i < positive_count; i++) {
    if (!first_term)
      cout << " + ";
    cout << "z" << i + 1 << "²";
    first_term = false;
  }
  for (int i = 0; i < negative_count; i++) {
    if (!first_term)
      cout << " - ";
    cout << "z" << positive_count + i + 1 << "²";
    first_term = false;
  }
  if (positive_count + negative_count < n) {
    for (int i = positive_count + negative_count; i < n; i++) {
      if (!first_term)
        cout << " + ";
      cout << "0·z" << i + 1 << "²";
      first_term = false;
    }
  }
  cout << endl;

  cout << "\n2. 非退化线性变换矩阵 C (使得 X = CZ):" << endl;
  printMatrix(C);

  cout << "\n3. 变换矩阵序列:" << endl;
  vector<vector<double>> product(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    product[i][i] = 1;

  for (size_t i = 0; i < transformMatrices.size(); i++) {
    cout << transformSteps[i] << ":" << endl;
    printMatrix(transformMatrices[i]);
    product = matrixMultiply(product, transformMatrices[i]);
  }

  cout << "\n4. 验算过程:" << endl;
  cout << "验证: Cᵀ * A * C = 规范形矩阵" << endl;

  auto CT = transpose(C);
  cout << "Cᵀ =" << endl;
  printMatrix(CT);
  cout << "A =" << endl;
  printMatrix(A);
  cout << "C =" << endl;
  printMatrix(C);

  auto temp1 = matrixMultiply(CT, A);
  auto result = matrixMultiply(temp1, C);
  cout << "Cᵀ * A * C =" << endl;
  printMatrix(result);

  // 构建理论规范形矩阵
  vector<vector<double>> canonicalMatrix(n, vector<double>(n, 0));
  for (int i = 0; i < positive_count; i++) {
    canonicalMatrix[i][i] = 1.0;
  }
  for (int i = positive_count; i < positive_count + negative_count; i++) {
    canonicalMatrix[i][i] = -1.0;
  }

  cout << "理论规范形矩阵:" << endl;
  printMatrix(canonicalMatrix);

  // 验证误差
  double maxError = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double error = fabs(result[i][j] - canonicalMatrix[i][j]);
      if (error > maxError)
        maxError = error;
    }
  }
  cout << "最大验证误差: " << maxError
       << (maxError < 1e-8 ? " (验证成功)" : " (可能有误差)") << endl;

  cout << "\n5. 惯性指数总结:" << endl;
  cout << "正惯性指数: " << positive_count << endl;
  cout << "负惯性指数: " << negative_count << endl;
  cout << "符号差: " << (positive_count - negative_count) << endl;
  cout << "秩: " << (positive_count + negative_count) << endl;
}

// 增广矩阵法求二次型标准型（修正版）
void quadraticFormByAugmentedMatrix() {
  cout << "\n=== 增广矩阵法求二次型标准型 ===" << endl;
  int n;
  cout << "输入变量个数: ";
  cin >> n;
  auto A = inputMatrix(n, n);

  cout << "\n对称矩阵 A:" << endl;
  printMatrix(A);

  // 构建增广矩阵 [A | I]
  vector<vector<double>> aug(n, vector<double>(2 * n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      aug[i][j] = A[i][j];
    aug[i][n + i] = 1;
  }

  cout << "\n初始增广矩阵 [A|I]:" << endl;
  printMatrix(aug);

  // 合同变换过程
  for (int i = 0; i < n; i++) {
    // 寻找主元
    int pivot = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(aug[j][j]) > fabs(aug[pivot][pivot])) {
        pivot = j;
      }
    }

    if (fabs(aug[pivot][pivot]) < 1e-10) {
      // 处理零对角元情况
      bool found = false;
      for (int j = i + 1; j < n && !found; j++) {
        if (fabs(aug[i][j]) > 1e-10) {
          // 构造创造平方项的变换矩阵
          vector<vector<double>> T(n, vector<double>(n, 0));
          for (int k = 0; k < n; k++)
            T[k][k] = 1;
          T[i][i] = 1;
          T[i][j] = 1;
          T[j][i] = 1;
          T[j][j] = -1;

          // 应用合同变换到整个增广矩阵
          auto TT = transpose(T);
          vector<vector<double>> tempA(n, vector<double>(n, 0));
          vector<vector<double>> tempI(n, vector<double>(n, 0));

          for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
              tempA[r][c] = aug[r][c];
              tempI[r][c] = aug[r][n + c];
            }
          }

          tempA = matrixMultiply(matrixMultiply(TT, tempA), T);
          tempI = matrixMultiply(tempI, T);

          for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
              aug[r][c] = tempA[r][c];
              aug[r][n + c] = tempI[r][c];
            }
          }

          cout << "\n处理零对角元，应用变换后:" << endl;
          printMatrix(aug);
          found = true;
          i--; // 重新处理这一行
          break;
        }
      }
      if (!found) {
        cout << "无法处理零对角元，继续下一行" << endl;
        continue;
      }
    } else {
      if (pivot != i) {
        // 行交换和列交换
        swap(aug[i], aug[pivot]);
        for (int j = 0; j < n; j++) {
          swap(aug[j][i], aug[j][pivot]);
          swap(aug[j][n + i], aug[j][n + pivot]);
        }
        cout << "\n交换行 " << i + 1 << " ↔ 行 " << pivot + 1 << " 和列 "
             << i + 1 << " ↔ 列 " << pivot + 1 << endl;
        printMatrix(aug);
      }

      // 消去其他行的对应元素（同时进行行变换和列变换）
      for (int j = 0; j < n; j++) {
        if (j != i && fabs(aug[j][i]) > 1e-10) {
          double factor = aug[j][i] / aug[i][i];

          // 行消去
          for (int k = i; k < 2 * n; k++) {
            aug[j][k] -= factor * aug[i][k];
          }

          // 列消去（保持对称性）
          for (int k = 0; k < n; k++) {
            aug[k][j] -= factor * aug[k][i];
          }
        }
      }

      cout << "\n第 " << i + 1 << " 步消元后:" << endl;
      printMatrix(aug);
    }
  }

  // 提取结果
  vector<double> coeffs(n);
  vector<vector<double>> B(n, vector<double>(n));

  for (int i = 0; i < n; i++) {
    coeffs[i] = aug[i][i];
    for (int j = 0; j < n; j++) {
      B[i][j] = aug[i][n + j];
    }
  }

  cout << "\n=== 最终结果 ===" << endl;
  cout << "最终增广矩阵 [对角矩阵|变换矩阵]:" << endl;
  printMatrix(aug);

  cout << "\n1. 标准型: f = ";
  bool first = true;
  for (int i = 0; i < n; i++) {
    if (fabs(coeffs[i]) > 1e-10) {
      if (!first)
        cout << " + ";
      cout << coeffs[i] << " * y" << i + 1 << "²";
      first = false;
    }
  }
  for (int i = 0; i < n; i++) {
    if (fabs(coeffs[i]) < 1e-10) {
      if (!first)
        cout << " + ";
      cout << "0 * y" << i + 1 << "²";
      first = false;
    }
  }
  cout << endl;

  cout << "\n2. 非退化线性变换矩阵 B (使得 X = BY):" << endl;
  printMatrix(B);

  cout << "\n3. 验算过程:" << endl;
  cout << "验证: B * A * Bᵀ = 对角矩阵" << endl;

  auto BT = transpose(B);
  auto temp = matrixMultiply(B, A);
  auto result = matrixMultiply(temp, BT);

  cout << "B * A * Bᵀ =" << endl;
  printMatrix(result);

  // 构建标准型矩阵进行对比
  vector<vector<double>> diagMatrix(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++)
    diagMatrix[i][i] = coeffs[i];

  cout << "理论标准型矩阵:" << endl;
  printMatrix(diagMatrix);

  // 验证误差
  double maxError = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double error = fabs(result[i][j] - diagMatrix[i][j]);
      if (error > maxError)
        maxError = error;
    }
  }
  cout << "最大验证误差: " << maxError
       << (maxError < 1e-8 ? " (验证成功)" : " (可能有误差)") << endl;

  // 检查变换矩阵是否可逆
  double detB = determinant(B);
  cout << "变换矩阵 B 的行列式: " << detB
       << (fabs(detB) > 1e-10 ? " (可逆)" : " (不可逆!)") << endl;
}

int main() {
  while (true) {
    cout << "\n" << string(50, '=') << endl;
    cout << "              线性代数运算工具" << endl;
    cout << string(50, '=') << endl;
    cout << "1. 矩阵加法            5. 伴随矩阵法求逆" << endl;
    cout << "2. 矩阵乘法            6. 求矩阵的秩" << endl;
    cout << "3. 求行列式            7. 二次型化标准型" << endl;
    cout << "4. 高斯消元法求逆      8. 二次型化规范形" << endl;
    cout << "9. 增广矩阵法求标准型  0. 退出" << endl;
    cout << string(50, '-') << endl;
    cout << "You want to ? ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      matrixAddition();
      break;
    case 2:
      matrixMultiplication();
      break;
    case 3:
      calcDeterminant();
      break;
    case 4:
      gaussJordanInverse();
      break;
    case 5:
      adjugateInverse();
      break;
    case 6:
      calcMatrixRank();
      break;
    case 7:
      quadraticFormCompletion();
      break;
    case 8:
      quadraticFormCanonical();
      break;
    case 9:
      quadraticFormByAugmentedMatrix();
      break;
    case 0:
      cout << "Good luck!" << endl;
      return 0;
    default:
      cout << "Invailid operation!" << endl;
    }

    cout << "\n" << string(50, '=') << endl;
  }
}