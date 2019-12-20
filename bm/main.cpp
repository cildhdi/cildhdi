#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>

template <typename T>
T read_input(const std::string& tip, std::function<bool(T&)> validator) {
  auto wrap_validator = [&](T& value) -> bool {
    bool success = validator(value);
    if (!success) {
      std::cout << "输入数据不符合要求，请重新输入" << std::endl;
    }
    return success;
  };

  T value;
  do {
    std::cout << "请输入" << tip << std::endl;
    while (!(std::cin >> value)) {
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;
      std::cout << "输入数据错误，请重新输入" << std::endl;
    }
  } while (!wrap_validator(value));
  return value;
}

inline void success(const std::string& msg = "") {
  std::cout << "操作成功！" << msg << std::endl;
}
inline void fail(const std::string& msg = "") {
  std::cout << "操作失败！" << msg << std::endl;
}

template <typename T>
struct has_ptr {
  using ptr = std::shared_ptr<T>;
};

struct book : has_ptr<book> {
  enum { MaxNoLength = 20, MaxNameLength = 20, MaxAuthorLength = 20 };

  std::string no;
  std::string name;
  std::string author;
  int inventory;
  int total_inventory;

 private:
  book(const std::string& _no, const std::string& _name,
       const std::string& _author, int _total_inventory)
      : no(_no),
        name(_name),
        author(_author),
        inventory(_total_inventory),
        total_inventory(_total_inventory) {}

 public:
  std::string summary(bool header = false) const {
    std::ostringstream oss;
    oss << std::setw(MaxNoLength + 1) << (header ? "书号" : no)
        << std::setw(MaxNameLength + 1) << (header ? "书名" : name)
        << std::setw(MaxAuthorLength + 1) << (header ? "作者" : author)
        << std::setw(10) << (header ? "现存量" : std::to_string(inventory))
        << std::setw(10)
        << (header ? "总库存" : std::to_string(total_inventory));
    return oss.str();
  }

  bool operator==(const book& other) const { return no == other.no; }
  bool operator!=(const book& other) const { return no != other.no; }

  // parament order for make(read_input<>(), ... )
  static ptr make(int total_inventory, const std::string& author,
                  const std::string& name, const std::string& no) {
    if (no.empty() || name.empty() || author.empty() ||
        no.length() > MaxNoLength || name.length() > MaxNameLength ||
        author.length() > MaxAuthorLength) {
      throw std::invalid_argument("书号，书名或作者长度错误");
    }
    return ptr(new book(no, name, author, total_inventory));
  }
};

struct record : has_ptr<record> {
  enum { MaxIdLength = 20 };

  std::string no;
  std::string id;
  int day;

 private:
  record(const std::string& _no, const std::string& _id, int _day)
      : no(_no), id(_id), day(_day) {}

 public:
  std::string summary(bool header = false) const {
    std::ostringstream oss;
    oss << std::setw(MaxIdLength + 1) << (header ? "图书证号" : id)
        << std::setw(book::MaxNoLength + 1) << (header ? "书号" : no)
        << std::setw(10) << (header ? "借阅天数" : std::to_string(day));
    return oss.str();
  }

  bool operator==(const record& other) const {
    return no == other.no && id == other.id;
  }
  bool operator!=(const record& other) const {
    return no != other.no || id != other.id;
  }

  static ptr make(int day, const std::string& id, const std::string& no) {
    if (id.empty() || no.empty() || id.length() > MaxIdLength ||
        no.length() > book::MaxNoLength || day < 0) {
      throw std::invalid_argument("书号/借书证长度或借阅天数错误");
    }
    return ptr(new record(no, id, day));
  }
};

class library {
 public:
  using books = std::vector<book::ptr>;
  using records = std::vector<record::ptr>;

 private:
  books _books;
  records _records;

 public:
  void all_books() const {
    std::cout << "库存 " << _books.size() << " 本：" << std::endl;
    if (!_books.empty()) {
      std::cout << _books.front()->summary(true) << std::endl;
      for (auto pb : _books) {
        std::cout << pb->summary() << std::endl;
      }
    }
  }

  void add_book() {
    try {
      book::ptr new_book = book::make(
          read_input<int>("入库数量", [](int i) { return i >= 0; }),
          read_input<std::string>(
              "作者", [](const std::string& s) { return !s.empty(); }),
          read_input<std::string>(
              "书名", [](const std::string& s) { return !s.empty(); }),
          read_input<std::string>(
              "书号", [](const std::string& s) { return !s.empty(); }));

      auto [found, it] = find_book_by_no(new_book->no);
      if (found) {
        std::cout << "库存中已存在以下书号相同的书籍：" << std::endl;
        for (auto header : {true, false}) {
          std::cout << (*it)->summary(header) << std::endl;
        }
        std::cout << "是否添加总库存量？";
        if (read_input<char>("选项(Y/N)", [](char option) {
              return std::toupper(option) == 'Y' || std::toupper(option) == 'N';
            }) == 'Y') {
          (*it)->total_inventory += new_book->total_inventory;
          (*it)->inventory += new_book->total_inventory;
          success();
        } else {
          fail("已取消添加");
        }
      } else {
        _books.push_back(new_book);
        success();
      }
    } catch (const std::exception& e) {
      fail(e.what());
    }
  }

  void delete_book() {
    auto no = read_input<std::string>(
        "书号", [](const std::string& s) { return !s.empty(); });
    auto [found, it] = find_book_by_no(no);

    if (!found) {
      fail("未找到该书籍");
    } else {
      std::cout << "找到书籍：" << std::endl;
      for (auto header : {true, false}) {
        std::cout << (*it)->summary(header) << std::endl;
      }
      if ((*it)->total_inventory != (*it)->inventory) {
        fail("该书有未归还记录");
        return;
      }
      std::cout << "是否删除？" << std::endl;
      if (std::toupper(read_input<char>("选项(Y/N)", [](char option) {
            return std::toupper(option) == 'Y' || std::toupper(option) == 'N';
          })) == 'Y') {
        _books.erase(it);
        success();
      }
    }
  }

  void all_records() const {
    std::cout << "记录 " << _records.size() << " 条：" << std::endl;
    if (!_records.empty()) {
      std::cout << _records.front()->summary(true) << std::endl;
      for (auto pr : _records) {
        std::cout << pr->summary() << std::endl;
      }
    }
  }

  record::ptr input_record() {
    return record::make(
        read_input<int>("借阅天数", [](int day) { return day > 0; }),
        read_input<std::string>(
            "图书证号", [](const std::string& id) { return !id.empty(); }),
        read_input<std::string>(
            "书号", [](const std::string& s) { return !s.empty(); }));
  }

  void borrow() {
    try {
      record::ptr new_record = input_record();
      auto [found, it] = find_record_by_id_no(new_record->id, new_record->no);
      if (found) {
        fail("该用户已借过该书");
      } else {
        auto [book_found, book_it] = find_book_by_no(new_record->no);
        if (book_found && (*book_it)->inventory > 0) {
          (*book_it)->inventory--;
          _records.push_back(new_record);
          success();
        } else {
          fail("图书不存在或库存不足");
        }
      }
    } catch (const std::exception& e) {
      fail(e.what());
    }
  }

  void give_back() {
    try {
      record::ptr new_record = input_record();

      auto [found, it] = find_record_by_id_no(new_record->id, new_record->no);
      if (found) {
        auto [book_found, book_it] = find_book_by_no(new_record->no);
        if (book_found) {
          (*book_it)->inventory++;
          _records.erase(it);
          success();
        } else {
          fail("书籍未找到");
        }
      } else {
        fail("未找到该借书记录");
      }
    } catch (const std::exception& e) {
      fail(e.what());
    }
  }

  std::tuple<bool, books::iterator> find_book_by_no(const std::string& no) {
    auto it = std::find_if(_books.begin(), _books.end(),
                           [&no](book::ptr pb) { return pb->no == no; });
    return std::make_tuple(it != _books.end(), it);
  }

  std::tuple<bool, records::iterator> find_record_by_id_no(
      const std::string& id, const std::string& no) {
    auto it = std::find_if(
        _records.begin(), _records.end(),
        [&id, &no](record::ptr pr) { return pr->no == no && pr->id == id; });
    return std::make_tuple(it != _records.end(), it);
  }

  int run() {
    while (true) {
      std::vector<std::pair<std::string, std::function<void(void)>>> options = {
          {"显示所有库存", [this]() { all_books(); }},
          {"显示所有借阅记录", [this]() { all_records(); }},
          {"采编入库", [this]() { add_book(); }},
          {"清除库存", [this]() { delete_book(); }},
          {"图书借阅", [this]() { borrow(); }},
          {"图书归还", [this]() { give_back(); }},
      };

      std::cout << "系统选项：" << std::endl;
      constexpr char index = 'a';
      for (int i = 0; i < options.size(); i++) {
        std::cout << static_cast<char>(index + i) << ". " << options[i].first
                  << std::endl;
      }

      char option = read_input<char>("选项前字母", [&options](char c) {
        return c >= 'a' && c < 'a' + options.size();
      });
      options[option - 'a'].second();

      int blank_line = 5;
      while (blank_line--) {
        std::cout << std::endl;
      }
    }
  }
};

int main() { return library{}.run(); }
