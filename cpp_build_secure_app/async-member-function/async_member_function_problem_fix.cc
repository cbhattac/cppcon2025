#include <functional>
#include <iostream>
#include <map>
#include <memory>

using FuncType = std::function<void(const std::string&)>;

void ReadFile(const std::string& name, FuncType callback);
void CompleteReadFile(const std::string& name, const std::string& content);

struct MyClass : public std::enable_shared_from_this<MyClass> {
  MyClass() { std::cout << "MyClass()\n"; }
  ~MyClass() { std::cout << "~MyClass()\n"; }

  void StartReadingFile(const std::string& name) {
    ReadFile(name, [wp = std::weak_ptr<MyClass>{shared_from_this()}](
                       const std::string& content) {
      if (auto p = wp.lock()) {
        p->Callback(content);
      }
    });
  }

 private:
  void Callback(const std::string& content) {
    std::cout << "MyClass::Callback: content: " << content << '\n';
  }
};

class FileReadManager {
 public:
  void AddReader(const std::string& name, FuncType func);
  void CompleteRead(const std::string& name, const std::string& content);

  static FileReadManager& GetInstance() {
    static FileReadManager* manager = new FileReadManager();
    return *manager;
  }

  FileReadManager& operator=(FileReadManager&&) noexcept = delete;

 private:
  FileReadManager() = default;
  std::map<std::string, FuncType, std::less<>> listeners_;
};

int main() {
  {
    auto obj = std::make_shared<MyClass>();
    obj->StartReadingFile("somefile.txt");
  }
  CompleteReadFile("somefile.txt", "Hello world!!");
}

void ReadFile(const std::string& name, FuncType callback) {
  FileReadManager::GetInstance().AddReader(name, std::move(callback));
}

void CompleteReadFile(const std::string& name, const std::string& content) {
  FileReadManager::GetInstance().CompleteRead(name, content);
}

void FileReadManager::AddReader(const std::string& name, FuncType func) {
  listeners_.emplace(name, func);
}

void FileReadManager::CompleteRead(const std::string& name,
                                   const std::string& content) {
  auto it = listeners_.find(name);
  if (it == listeners_.end()) {
    return;
  }
  auto fn = it->second;
  listeners_.erase(it);
  fn(content);
}

/*
MyClass()
~MyClass()
*/