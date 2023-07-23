#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>

typedef struct data {
  std::string str;
  data(std::string d) : str(std::move(d)) {}
} data;

namespace {
const std::string log_file_ = "/tmp/log.dat";
}

// no constructor required for interface class
// destructor is virtual but not overridden
class iSink {
 public:
  virtual ~iSink(){};
  virtual void log(const std::string& message) = 0;
};

class ConsoleSink : public iSink {
 public:
  explicit ConsoleSink() {}

  ~ConsoleSink() {}

  void log(const std::string& message) override {
    std::cout << message << std::endl;
  }
};

class FileSink : public iSink {
  std::string file_name_;
  std::ofstream file_;

 public:
  explicit FileSink(const std::string& log_file = log_file_)
      : file_name_(log_file) {
    file_.open(file_name_, std::ios::out | std::ios::app);
    if (!file_.is_open()) {
      std::cerr << "file can't be opened" << std::endl;
    }
  }

  ~FileSink() {
    if (file_.is_open()) {
      file_.close();
    }
  }

  void log(const std::string& message) override {
    if (file_.is_open()) {
      file_ << message << std::endl;
    }
  }
};

// logger with a simple file sink
template <typename sink>
class Logger {
 private:
  std::list<data> log_;
  std::unique_ptr<sink> sink_;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

 public:
  Logger() { sink_ = std::make_unique<sink>(); }

  void log(const std::string& message) {
    data d(message);
    log_.push_back(std::move(d));
  }

  int flush() {
    for (const auto& msg : log_) {
      sink_->log(msg.str);
    }
    log_.clear();
    return 0;
  }

  ~Logger() {}
};

int main() {
  Logger<FileSink> file_logger;
  file_logger.log("hello world");
  file_logger.log("the world is what you make out of it");
  file_logger.log("keep logging");
  file_logger.flush();

  Logger<ConsoleSink> console_logger;
  console_logger.log("logging to console");
  console_logger.log("a very crude logger");
  console_logger.flush();
  return 0;
}
