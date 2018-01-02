#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
#include "gmock/gmock.h"
#include "IClientSocket.h"
using ::testing::_;
using ::testing::Invoke;

template <typename T>
class queue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<T>           d_queue;
public:
    void push(T const& value) {
        {
            std::unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{ return !this->d_queue.empty(); });
        T rc(std::move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }
};

class FakeFoo {
public:
    virtual void fake_write_action(void* ptr, size_t nbytes) {
        auto* buf = new char[BUFSIZ];
        memcpy(buf, ptr, nbytes);
        blocking_queue.push(buf);
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "fake_write_action from: " << this_id <<  std::endl;
    }

    virtual ssize_t fake_read_action(void* ptr, size_t nbytes) {
        char * buf  = blocking_queue.pop();
        memcpy(ptr,buf,nbytes);
        delete [] buf;
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "fake_read_action from:" << this_id << std::endl;
    }

private:
    queue<char*> blocking_queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    char buf[BUFSIZ];
};

class Mockclient_sock: public IClientSocket
{
public:
    MOCK_METHOD2(connectSocket, void(sockaddr* sockaddr, socklen_t socklen));
    MOCK_METHOD2(writeToSocket, void(void* ptr, size_t nbytes));
    MOCK_METHOD2(setAddr, void(const std::string host, void* buf));
    MOCK_METHOD2(readFromSocket, ssize_t(void* ptr, size_t nbytes));


    void DelegateToFake() {
        ON_CALL(*this, writeToSocket(_,_))
                .WillByDefault(Invoke(&fake_, &FakeFoo::fake_write_action));
        ON_CALL(*this, readFromSocket(_,_))
                .WillByDefault(Invoke(&fake_, &FakeFoo::fake_read_action));
    }

private:
    FakeFoo fake_;

};


