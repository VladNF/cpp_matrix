#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

class Slice {
public:
    Slice() = default;

    explicit Slice(size_t args...) : indices_(args) {}

    Slice(const Slice &other) : indices_(other.indices_) {}

    Slice operator[](size_t next) {
        Slice ix(*this);
        ix.indices_.push_back(next);
        return ix;
    }

    std::string to_string() const {
        std::stringstream s;
        s << "[";
        for (auto &ix : indices_) s << ix << ", ";
        if (!indices_.empty()) s << "\b\b";
        s << "]";
        return s.str();
    }

    bool operator==(Slice const &s) const {
        return indices_ == s.indices_;
    }

    explicit operator bool() { return !indices_.empty(); }

private:
    std::vector<size_t> indices_;
};

namespace std {
    template<>
    struct hash<Slice> {
        size_t operator()(Slice const &s) const noexcept {
            return std::hash<std::string>{}(s.to_string());
        }
    };
}

template<typename T, T default_v, size_t N = 2>
class Matrix {
    using Storage_t = std::unordered_map<Slice, T>;
    using Storage_Ptr_t = std::shared_ptr<Storage_t>;
    using Row_t = Matrix<T, default_v, N - 1>;
    using Iterator_t = typename Storage_t::iterator;

public:
    Matrix() : data_(new Storage_t) {};

    virtual ~Matrix() = default;

    Row_t operator[](size_t index) {
        return Row_t(data_, slice_[index]);
    }

    size_t size() { return data_->size(); }

    Iterator_t begin() { return data_->begin(); }

    Iterator_t end() { return data_->end(); }

private:
    template<typename U, U, size_t> friend
    class Matrix;

    Matrix(Storage_Ptr_t &data, const Slice &slice) : data_(data), slice_(slice) {}

    Storage_Ptr_t data_;
    Slice slice_;
};


template<typename T, T default_v>
class Matrix<T, default_v, 0> {
    using Storage_t = std::unordered_map<Slice, T>;
    using Storage_Ptr_t = std::shared_ptr<Storage_t>;

public:
    virtual ~Matrix() = default;

    Matrix &operator=(const T &value) {
        if (value != default_v) {
            data_->operator[](slice_) = value;
        } else {
            auto found = data_->find(slice_);
            if (found != data_->end()) data_->erase(found);
        }
        return *this;
    }

    operator T() {
        auto found = data_->find(slice_);
        if (found != data_->end()) return found->second;
        return default_v;
    }

    operator const T() const {
        auto found = data_->find(slice_);
        if (found != data_->end()) return found->second;
        return default_v;
    }

    friend bool operator==(const Matrix &m, const T &v) {
        return static_cast<T>(m) == v;
    }

private:
    template<typename U, U, size_t> friend
    class Matrix;

    Matrix(Storage_Ptr_t &data, const Slice &slice) : data_(data), slice_(slice) {}

    Storage_Ptr_t data_;
    Slice slice_;
};