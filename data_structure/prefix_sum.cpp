// base: 基数, dim: 次元数
template <class T, int base, int dim>
struct prefix_sum {
  using Coord = array<int, dim>;

  vector<T> data;
  array<size_t, dim + 1> pow_base{};

  prefix_sum() {
    pow_base[0] = 1;
    for (int i = 0; i < dim; i++) {
      pow_base[i + 1] = pow_base[i] * base;
    }
    data.assign(pow_base[dim], T{});
  }

  static Coord id_to_coord(int id) {
    Coord coord{};
    for (int i = dim - 1; i >= 0; i--) {
      coord[i] = id % 10;
      id /= 10;
    }
    return coord;
  };

  // coord[0] を最上位桁として一次元化する
  static size_t coord_to_idx(const Coord& coord) {
    size_t idx = 0;

    for (int k = 0; k < dim; k++) {
      assert(0 <= coord[k] && coord[k] < base);
      idx = idx * base + coord[k];
    }

    return idx;
  }

  // 座標に値を加算する
  // build() より前に呼ぶ
  void add(const Coord& coord, const T& value) {
    data[coord_to_idx(coord)] += value;
  }

  // dim 次元累積和を構築する
  void build() {
    const size_t size = data.size();

    for (int k = 0; k < dim; k++) {
      // coord[k] を1増減させたときの一次元添字の差
      const size_t step = pow_base[dim - 1 - k];
      const size_t block_size = step * base;

      for (size_t block = 0; block < size; block += block_size) {
        for (size_t offset = 0; offset < step; offset++) {
          for (int digit = 1; digit < base; digit++) {
            const size_t idx =
                block + static_cast<size_t>(digit) * step + offset;

            data[idx] += data[idx - step];
          }
        }
      }
    }
  }

  // 0 <= x[k] <= coord[k] を満たす領域の総和
  //
  // 包含排除で coord[k] = -1 が渡された場合は0を返す
  T prefix(const Coord& coord) const {
    for (int k = 0; k < dim; k++) {
      if (coord[k] < 0) {
        return T{};
      }

      assert(coord[k] < base);
    }

    return data[coord_to_idx(coord)];
  }

  // lower[k] <= x[k] <= upper[k] の直方体領域の総和
  T range_sum(const Coord& lower, const Coord& upper) const {
    for (int k = 0; k < dim; k++) {
      assert(0 <= lower[k] && lower[k] < base);
      assert(0 <= upper[k] && upper[k] < base);

      if (lower[k] > upper[k]) {
        return T{};
      }
    }

    T answer{};

    const uint64_t subset_count = uint64_t{1} << dim;

    for (uint64_t mask = 0; mask < subset_count; mask++) {
      Coord corner{};

      for (int k = 0; k < dim; k++) {
        if ((mask >> k) & 1) {
          corner[k] = lower[k] - 1;
        } else {
          corner[k] = upper[k];
        }
      }

      const T value = prefix(corner);

      if (popcount(mask) % 2 == 0) {
        answer += value;
      } else {
        answer -= value;
      }
    }

    return answer;
  }
};
